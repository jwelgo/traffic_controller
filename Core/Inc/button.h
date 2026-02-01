/* Button Controller
   
   Interrupt-driven button handler with debouncing
*/

#ifndef __CORE_INC_BUTTON_H
#define __CORE_INC_BUTTON_H


/* -- Includes -------------------------------------- */
#include "stm32f3xx_hal.h"
#include <stdbool.h>
#include "main.h"


/* -- Type Defs ------------------------------------- */

/* Button callback function pointer */
typedef void (*ButtonCallback_t)(void);


/* -- Function Prototypes --------------------------- */

/**
 * @brief Initialize button with interrupt
 * @param callback Function to call when button is pressed (can be NULL)
 */
void Button_Init(ButtonCallback_t callback);

/**
 * @brief Check if button is currently pressed
 * @retval true if pressed, false if not
 */
bool Button_IsPressed(void);

/**
 * @brief Get button state (debounced)
 * @retval true if button press detected, false otherwise
 * @note This is edge-triggered and auto-clears after reading
 */
bool Button_GetPress(void);

/**
 * @brief GPIO EXTI Callback (called from interrupt)
 * @note This should be called from HAL_GPIO_EXTI_Callback
 */
void Button_InterruptHandler(uint16_t GPIO_Pin);


#endif /* __CORE_INC_BUTTON_H */