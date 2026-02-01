/* Crosswalk Signal Controller
   
   Non-blocking crosswalk controller with walk/don't walk states
   RGB LED shows white (walk) or red (don't walk/warning)
*/


#ifndef __CORE_INC_CROSSSIGNAL_H
#define __CORE_INC_CROSSSIGNAL_H

/* -- Includes -------------------------------------- */
#include "stm32f3xx_hal.h"
#include <stdbool.h>
#include "main.h"


/* -- Type Defs ------------------------------------- */
typedef enum {
    CROSS_OFF,          
    CROSS_WALK,        
    CROSS_DONT_WALK     
} CrosswalkLight_t;

typedef enum {
    CROSSWALK_IDLE,        
    CROSSWALK_WALKING,      
    CROSSWALK_WARNING,   
    CROSSWALK_DONE         
} CrosswalkState_t;

typedef enum {
    CROSSWALK_OK = 0,       
    CROSSWALK_COMPLETE,     
    CROSSWALK_ERROR        
} CrosswalkStatus_t;


/* -- Function Prototypes --------------------------- */

/**
 * @brief Initialize crosswalk controller
 */
void Crosswalk_Init(void);

/**
 * @brief Start crosswalk sequence (call when traffic light is red)
 */
void Crosswalk_Start(void);

/**
 * @brief Update crosswalk state machine (call continuously)
 * @retval Status: OK (running), COMPLETE (done), or ERROR
 */
CrosswalkStatus_t Crosswalk_Update(void);

/**
 * @brief Set crosswalk light color
 * @param light Color to display
 */
void Crosswalk_SetLight(CrosswalkLight_t light);

/**
 * @brief Get current crosswalk state
 * @retval Current state
 */
CrosswalkState_t Crosswalk_GetState(void);


#endif /* __CORE_INC_CROSSSIGNAL_H */