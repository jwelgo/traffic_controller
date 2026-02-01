/* Library for traffic light signal
   
   Signal uses three led
   Signal uses red yellow and green lights
*/


#ifndef __CORE_INC_TRAFFICLIGHT_H
#define __CORE_INC_TRAFFICLIGHT_H

/* -- Includes -------------------------------------- */
#include "stm32f3xx_hal.h"
#include "stdbool.h"
#include "main.h"


/* -- Defines --------------------------------------- */
#define GREEN_CYCLES 25     //time for cars to pass thru junction minus 5 (25 -> 30 seconds)
#define YELLOW_CYCLES 5     //time for yellow light warning

#define LED_RED_ON() HAL_GPIO_WritePin(LED_GPIO_PORT, LED_RED_PIN, GPIO_PIN_SET)
#define LED_RED_OFF() HAL_GPIO_WritePin(LED_GPIO_PORT, LED_RED_PIN, GPIO_PIN_RESET)

#define LED_YELLOW_ON() HAL_GPIO_WritePin(LED_GPIO_PORT, LED_YELLOW_PIN, GPIO_PIN_SET)
#define LED_YELLOW_OFF() HAL_GPIO_WritePin(LED_GPIO_PORT, LED_YELLOW_PIN, GPIO_PIN_RESET)

#define LED_GREEN_ON() HAL_GPIO_WritePin(LED_GPIO_PORT, LED_GREEN_PIN, GPIO_PIN_SET)
#define LED_GREEN_OFF() HAL_GPIO_WritePin(LED_GPIO_PORT, LED_GREEN_PIN, GPIO_PIN_RESET)


/* -- Type Defs ------------------------------------- */
typedef enum {
    LED_OK = 0,
    LED_FATAL 
} LED_status_t; 


/* -- Function Prototypes --------------------------- */
LED_status_t cycle_lights(volatile bool *cross_triggered);
LED_status_t green_light(volatile bool *cross_triggered);
LED_status_t yellow_light(volatile bool *cross_triggered);


/* -- Helper Fucntion Prototypes -------------------- */
void toggle_red();
void toggle_yellow();
void toggle_green();
void s_delay();


#endif /* __CORE_INC_TRAFFICLIGHT_H */