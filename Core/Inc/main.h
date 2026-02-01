/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */

/* GPIO Pin Definitions ----------------------------- */

/* Crosswalk RGB LED Pins (White/Red light for pedestrians) */
#define RGB_GPIO_PORT GPIOB
#define RGB_RED_PIN GPIO_PIN_15
#define RGB_GREEN_PIN GPIO_PIN_14
#define RGB_BLUE_PIN GPIO_PIN_13

/* Traffic Light LED Pins (Red/Yellow/Green for cars) */
#define LED_GPIO_PORT GPIOC
#define LED_GREEN_PIN GPIO_PIN_1
#define LED_RED_PIN GPIO_PIN_2
#define LED_YELLOW_PIN GPIO_PIN_3

/* Crosswalk Button */
#define BUTTON_GPIO_PORT GPIOB
#define BUTTON_PIN GPIO_PIN_1
#define BUTTON_EXTI_IRQn EXTI1_IRQn

/* Timing Constants (in ms) ------------------------- */

/* Traffic Light Timimg */
#define TRAFFIC_GREEN_TIME 30000      // 30 seconds for green
#define TRAFFIC_YELLOW_TIME 5000      // 5 seonds for yellow
#define TRAFFIC_RED_TIME 5000         // 5 seconds for red

/* Crosswalk Timing */
#define CROSSWALK_WALK_TIME 15000     // 15 seconds to cross
#define CROSSWALK_WARNING_TIME 10000  // 10 seconds of flashing
#define CROSSWALK_BLINK_RATE 500      // Blink every second (ON for 0.5s, OFF for 0.5s)

/* Button Debouncing */
#define BUTTON_DEBOUNCE_MS 50         // 50ms debounce

/* Error Blink Rate */
#define ERROR_BLINK_RATE 500          // Blink red lights every 500ms on fatal error

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
