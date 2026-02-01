/* Button Controller Implementation
   
   Interrupt-driven button with software debouncing
*/

#include "button.h"
#include "main.h"


/* -- Private Variables ----------------------------- */
static ButtonCallback_t button_callback = NULL;
static uint32_t last_press_time = 0;
static volatile bool button_pressed_flag = false;


/* -- Public Functions ------------------------------ */

/**
 * Initialize button
 * 
 * @note GPIO initialization is done in MX_GPIO_Init()
 * This function just sets up the software debouncing 
 */ 
void Button_Init(ButtonCallback_t callback){
    button_callback = callback;
    last_press_time = 0;
    button_pressed_flag = false;
}


/* Check if button is currently pressed (raw state) */
bool Button_IsPressed(void) {
    GPIO_PinState state = HAL_GPIO_ReadPin(BUTTON_GPIO_PORT, BUTTON_PIN);
    return (state == GPIO_PIN_SET);
}


/* Get debounced button press (edge-triggered, auto-clears) */
bool Button_GetPress(void) {
    if (button_pressed_flag) {
        button_pressed_flag = false;  
        return true;
    }

    return false;
}


/* Button interrupt handler (call from HAL_GPIO_EXTI_Callback) */
void Button_InterruptHandler(uint16_t GPIO_Pin) {
    if (GPIO_Pin != BUTTON_PIN) {
        return;
    }

    HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_RED_PIN); //DEBUG Line

    uint32_t current_time = HAL_GetTick();
    
    if (current_time - last_press_time < BUTTON_DEBOUNCE_MS) {
        return;
    }
    
    last_press_time = current_time;  //update last press time
    button_pressed_flag = true; //set flag for edge detection
    
    if (button_callback != NULL) {
        button_callback();
    }  //callback if registered
}
