/* Library for traffic light signal
   
   State machine based traffic light controller with non-blocking delays
   and interrupt-driven crosswalk button support.
*/


#ifndef __CORE_INC_TRAFFICLIGHT_H
#define __CORE_INC_TRAFFICLIGHT_H

/* -- Includes -------------------------------------- */
#include "stm32f3xx_hal.h"
#include <stdbool.h>
#include "main.h"


/* -- Type Defs ------------------------------------- */
typedef enum {
    STATE_GREEN,
    STATE_YELLOW,
    STATE_RED,
    STATE_RED_CROSSWALK,
    STATE_ERROR
} TrafficState_t;

typedef enum {
    TRAFFIC_OK = 0,
    TRAFFIC_ERROR 
} TrafficStatus_t; 


/* -- Function Prototypes --------------------------- */

/**
 * @brief Initialize traffic light controller
 * @note Must be called before using the traffic light system
 */
void Traffic_Init(void);

/**
 * @brief Main state machine update - call this in main loop
 * @note Non-blocking, processes state transitions
 */
void Traffic_Update(void);

/**
 * @brief Request a pedestrian crossing
 * @note Call this from button interrupt or main loop
 * @retval true if request accepted, false if already pending/active
 */
bool Traffic_RequestCrosswalk(void);

/**
 * @brief Get current traffic state
 * @retval Current state
 */
TrafficState_t Traffic_GetState(void);


/* -- Helper Fucntion Prototypes -------------------- */
void Traffic_SetLight(bool green, bool yellow, bool red);
void Traffic_ChangeState(TrafficState_t new_state);


#endif /* __CORE_INC_TRAFFICLIGHT_H */