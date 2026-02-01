/* Traffic Light Controller Implementation
   
   State machine based traffic light with non-blocking operation
*/


#include "crosssignal.h"
#include "trafficlight.h"
#include "main.h"


/* -- Private Variables ----------------------------- */
static TrafficState_t current_state = STATE_GREEN;
static uint32_t state_entry_time = 0;       //tmstp: entered current state
static bool crosswalk_requested = false;    //pedestrian button pressed flag
static bool crosswalk_active = false;       //currently servicing crosswalk


/* -- Public Functions ------------------------------ */

/* Initialize traffic controller */
void Traffic_Init(void) {
    current_state = STATE_GREEN;
    state_entry_time = HAL_GetTick();
    crosswalk_requested = false;
    crosswalk_active = false;
    
    //set initial state -> GREEN
    Traffic_SetLight(true, false, false);
    Crosswalk_SetLight(CROSS_DONT_WALK);
}


/* Main state machine - call continuously from main loop */
void Traffic_Update(void) {
    uint32_t current_time = HAL_GetTick();
    uint32_t time_in_state = current_time - state_entry_time;
    
    switch (current_state) {

        case STATE_GREEN:
            if (time_in_state >= TRAFFIC_GREEN_TIME) {
                Traffic_ChangeState(STATE_YELLOW);
            }
            else if (crosswalk_requested && time_in_state >= 10000) {
                Traffic_ChangeState(STATE_YELLOW);
            }
            break;
            
        case STATE_YELLOW:
            if (time_in_state >= TRAFFIC_YELLOW_TIME) {
                if (crosswalk_requested) {
                    Traffic_ChangeState(STATE_RED_CROSSWALK);
                    crosswalk_requested = false;
                } 
                else {
                    Traffic_ChangeState(STATE_RED);
                }
            }
            break;
            
        case STATE_RED:
            if (time_in_state >= TRAFFIC_RED_TIME) {
                Traffic_ChangeState(STATE_GREEN);
            }
            break;
            
        case STATE_RED_CROSSWALK:
            if (!crosswalk_active) {
                crosswalk_active = true;
                Crosswalk_Start();
            } 
            else {
                CrosswalkStatus_t status = Crosswalk_Update();
                
                if (status == CROSSWALK_COMPLETE) {
                    crosswalk_active = false;
                    Traffic_ChangeState(STATE_GREEN);
                } 
                else if (status == CROSSWALK_ERROR) {
                    Traffic_ChangeState(STATE_ERROR);
                }
            }
            break;
            
        case STATE_ERROR:
            Error_Handler();
            break;
            
        default:
            Traffic_ChangeState(STATE_ERROR);
            break;
    }
}


/* Request pedestrian crossing: true if accepted, false if already active/pending */
bool Traffic_RequestCrosswalk(void) {
    if (crosswalk_requested || crosswalk_active) {
        return false;
    } //don't accept if already requested or currently crossing
    
    if (current_state == STATE_GREEN || current_state == STATE_YELLOW) {
        crosswalk_requested = true;
        return true;
    } //only accept during green or yellow (not during red)
    
    return false;
}


/* Get current traffic state */
TrafficState_t Traffic_GetState(void) {
    return current_state;
}


/* -- Internal Helper Functions --------------------- */

/* Change traffic light state, new_state is state to transition to */
void Traffic_ChangeState(TrafficState_t new_state) {
    current_state = new_state;
    state_entry_time = HAL_GetTick();
    
    //set hardware outputs based on new state
    switch (new_state) {
        case STATE_GREEN:
            Traffic_SetLight(true, false, false);   //GREEN ON
            break;
            
        case STATE_YELLOW:
            Traffic_SetLight(false, true, false);   //YELLOW ON
            break;
            
        case STATE_RED:
        case STATE_RED_CROSSWALK:
            Traffic_SetLight(false, false, true);   //RED ON
            break;
            
        case STATE_ERROR:
            break;
            
        default:
            break;
    }
}


/** Set traffic light hardware outputs
 * green true -> green LED on
 * yellow true -> yellow LED on  
 * red true -> red LED on
 */
void Traffic_SetLight(bool green, bool yellow, bool red) {
    HAL_GPIO_WritePin(LED_GPIO_PORT, LED_GREEN_PIN, green ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_GPIO_PORT, LED_YELLOW_PIN, yellow ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_GPIO_PORT, LED_RED_PIN, red ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
