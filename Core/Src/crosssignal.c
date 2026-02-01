/* Library for cross walk signal
   
   Signal uses RGB, but no PWM,
   Signal only uses red and white light
*/

#include "stm32f3xx_hal.h"
#include "crosssignal.h"
#include "main.h"


void warning_delay() {
    HAL_Delay(CROSS_DELAY);
}

void walking_delay() {
    HAL_Delay(WALK_DELAY);
}

/* Function to set white light */
void set_white() {
    RGB_RED_ON();
    RGB_GREEN_ON();
    RGB_BLUE_ON();
}

/* Function to set red light */
void set_red() {
    RGB_RED_ON();
    RGB_GREEN_OFF();
    RGB_BLUE_OFF();
}

/* Function to reset the crosswalk light */
void reset_light() {
    RGB_RED_OFF();
    RGB_GREEN_OFF();
    RGB_BLUE_OFF();
}

/* Function to warn pedestrian light will turn red */
RGB_status_t warn_pedestrian() {
    set_red();

    for (int i = 0; i < N_WARNS; i++) {
        warning_delay();
        reset_light();
        warning_delay();
        set_red();  
    }  //loop blinks red light to warn pedestrian

    return RGB_OK;
}

/* Logical sequence to service pedestrian walk */
RGB_status_t service_crosswalk() {
    reset_light();
    set_white();

    walking_delay();    //delays infinite loop to let pedestrian walk

    RGB_status_t status = warn_pedestrian(); //delays infinite loop to warn pedestrian
    if (status != RGB_OK) {
        return RGB_FATAL;
    }

    return RGB_OK;
}