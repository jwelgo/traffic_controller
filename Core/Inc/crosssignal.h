/* Library for cross walk signal
   
   Signal uses RGB, but no PWM,
   Signal only uses red and white light
*/


#ifndef __CORE_INC_CROSSSIGNAL_H
#define __CORE_INC_CROSSSIGNAL_H

/* -- Includes -------------------------------------- */
#include "stm32f3xx_hal.h"
#include "main.h"


/* -- Defines --------------------------------------- */
#define WALK_DELAY 15000    //time for pedestrians to walk minus 10 (15000 -> 25 seconds)
#define CROSS_DELAY 500     //rate at which the red light will blink
#define N_WARNS 10          //give 10 secinds of warning for crossing

#define RGB_RED_ON() HAL_GPIO_WritePin(RGB_GPIO_PORT, RGB_RED_PIN, GPIO_PIN_SET)
#define RGB_RED_OFF() HAL_GPIO_WritePin(RGB_GPIO_PORT, RGB_RED_PIN, GPIO_PIN_RESET)

#define RGB_GREEN_ON() HAL_GPIO_WritePin(RGB_GPIO_PORT, RGB_GREEN_PIN, GPIO_PIN_SET)
#define RGB_GREEN_OFF() HAL_GPIO_WritePin(RGB_GPIO_PORT, RGB_GREEN_PIN, GPIO_PIN_RESET)

#define RGB_BLUE_ON() HAL_GPIO_WritePin(RGB_GPIO_PORT, RGB_BLUE_PIN, GPIO_PIN_SET)
#define RGB_BLUE_OFF() HAL_GPIO_WritePin(RGB_GPIO_PORT, RGB_BLUE_PIN, GPIO_PIN_RESET)


/* -- Type Defs ------------------------------------- */
typedef enum {
    RGB_OK = 0,
    RGB_FATAL 
} RGB_status_t; 


/* -- Function Prototypes --------------------------- */
RGB_status_t warn_pedestrian();
RGB_status_t service_crosswalk();


/* -- Helper Fucntion Prototypes -------------------- */
void warning_delay();
void walking_delay();
void set_white();
void set_red();
void reset_light();


#endif /* __CORE_INC_CROSSSIGNAL_H */