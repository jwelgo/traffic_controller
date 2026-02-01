/* Crosswalk Signal Implementation
   
   Non-blocking crosswalk controller
*/

#include "crosssignal.h"
#include "main.h"


/* -- Private Variables ----------------------------- */
static CrosswalkState_t current_state = CROSSWALK_IDLE;
static uint32_t state_entry_time = 0;
static uint32_t last_blink_time = 0;
static bool blink_on = false;


/* -- Public Functions ------------------------------ */

/* Initialize crosswalk */
void Crosswalk_Init(void) {
    current_state = CROSSWALK_IDLE;
    state_entry_time = 0;
    last_blink_time = 0;
    blink_on = false;
    
    Crosswalk_SetLight(CROSS_DONT_WALK); 
}


/* Start crosswalk sequence */
void Crosswalk_Start(void) {
    current_state = CROSSWALK_WALKING;
    state_entry_time = HAL_GetTick();
    last_blink_time = 0;
    blink_on = false;
    
    Crosswalk_SetLight(CROSS_WALK);  
}


/* Update crosswalk state machine */
CrosswalkStatus_t Crosswalk_Update(void) {
    uint32_t current_time = HAL_GetTick();
    uint32_t time_in_state = current_time - state_entry_time;
    
    switch (current_state) {
        case CROSSWALK_IDLE:
            return CROSSWALK_OK;
            
        case CROSSWALK_WALKING:
            if (time_in_state >= CROSSWALK_WALK_TIME) {
                current_state = CROSSWALK_WARNING;
                state_entry_time = HAL_GetTick();
                last_blink_time = state_entry_time;
                blink_on = true;
                Crosswalk_SetLight(CROSS_DONT_WALK);  
            }
            return CROSSWALK_OK;
            
        case CROSSWALK_WARNING:
            if (current_time - last_blink_time >= CROSSWALK_BLINK_RATE) {
                last_blink_time = current_time;
                blink_on = !blink_on;
                
                if (blink_on) {
                    Crosswalk_SetLight(CROSS_DONT_WALK);  // RED ON
                } else {
                    Crosswalk_SetLight(CROSS_OFF);        // ALL OFF
                }
            }
            
            if (time_in_state >= CROSSWALK_WARNING_TIME) {
                current_state = CROSSWALK_DONE;
                Crosswalk_SetLight(CROSS_DONT_WALK);  
                return CROSSWALK_COMPLETE;
            }
            return CROSSWALK_OK;
            
        case CROSSWALK_DONE:
            current_state = CROSSWALK_IDLE;
            return CROSSWALK_COMPLETE;
            
        default:
            return CROSSWALK_ERROR;
    }
}


/* Set crosswalk RGB LED color */
void Crosswalk_SetLight(CrosswalkLight_t light) {
    switch (light) {
        case CROSS_OFF: //ALL OFF
            HAL_GPIO_WritePin(RGB_GPIO_PORT, RGB_RED_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(RGB_GPIO_PORT, RGB_GREEN_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(RGB_GPIO_PORT, RGB_BLUE_PIN, GPIO_PIN_RESET);
            break;
            
        case CROSS_WALK: //WHITE LIGHT
            HAL_GPIO_WritePin(RGB_GPIO_PORT, RGB_RED_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(RGB_GPIO_PORT, RGB_GREEN_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(RGB_GPIO_PORT, RGB_BLUE_PIN, GPIO_PIN_SET);
            break;
            
        case CROSS_DONT_WALK: //RED LIGHT
            HAL_GPIO_WritePin(RGB_GPIO_PORT, RGB_RED_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(RGB_GPIO_PORT, RGB_GREEN_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(RGB_GPIO_PORT, RGB_BLUE_PIN, GPIO_PIN_RESET);
            break;
    }
}


/* Get current crosswalk state */
CrosswalkState_t Crosswalk_GetState(void) {
    return current_state;
}
