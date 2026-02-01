/* Library for traffic light signal
   
   Signal uses three led
   Signal uses red yellow and green lights
*/

#include "stm32f3xx_hal.h"
#include "trafficlight.h"
#include "main.h"


void s_delay() {
    HAL_Delay(1000);
}

/* Function to toggle green light */
void toggle_green() {
    GPIO_PinState greenState = HAL_GPIO_ReadPin(LED_GPIO_PORT, LED_GREEN_PIN);

    if (greenState == GPIO_PIN_SET) {
        LED_GREEN_OFF();
    }
    else {
        LED_GREEN_ON();
    }
}

/* Function to toggle yellow light */
void toggle_yellow() {
    GPIO_PinState yellowState = HAL_GPIO_ReadPin(LED_GPIO_PORT, LED_YELLOW_PIN);

    if (yellowState == GPIO_PIN_SET) {
        LED_YELLOW_OFF();
    }
    else {
        LED_YELLOW_ON();
    }
}

/* Function to toggle red light */
void toggle_red() {
    GPIO_PinState redState = HAL_GPIO_ReadPin(LED_GPIO_PORT, LED_RED_PIN);

    if (redState == GPIO_PIN_SET) {
        LED_RED_OFF();
    }
    else {
        LED_RED_ON();
    }
}

/* Function to carry out the green light */
LED_status_t green_light(volatile bool *cross_triggered) {
    toggle_green(); 

    for (int i = 0; i < GREEN_CYCLES; i++) {
        GPIO_PinState button = HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_PIN);
        
        if (button == GPIO_PIN_SET) {
            *cross_triggered = true;
        }

        s_delay();
    } 

    toggle_green();

    return LED_OK;
}

/* Function carry out the yellow light */
LED_status_t yellow_light(volatile bool *cross_triggered) {
    toggle_yellow(); 

    for (int i = 0; i < YELLOW_CYCLES; i++) {
        GPIO_PinState button = HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_PIN);
        
        if (button == GPIO_PIN_SET) {
            *cross_triggered = true;
        }

        s_delay();
    } 

    toggle_yellow();

    return LED_OK;
}

/* Logical sequence to service cars thru junction */
LED_status_t cycle_lights(volatile bool *cross_triggered) {
    LED_RED_OFF();
    LED_YELLOW_OFF();
    LED_RED_OFF();

    LED_status_t green_status = green_light(cross_triggered);
    if (green_status != LED_OK) {
        return LED_FATAL;
    }

    LED_status_t yellow_status = yellow_light(cross_triggered);
    if (yellow_status != LED_OK) {
        return LED_FATAL;
    }

    toggle_red();

    return LED_OK;
}