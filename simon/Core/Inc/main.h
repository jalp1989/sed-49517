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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define potenciometro_Pin GPIO_PIN_0
#define potenciometro_GPIO_Port GPIOC
#define LDR_Pin GPIO_PIN_1
#define LDR_GPIO_Port GPIOC
#define reserva_Pin GPIO_PIN_0
#define reserva_GPIO_Port GPIOA
#define Boton_rojo_Pin GPIO_PIN_0
#define Boton_rojo_GPIO_Port GPIOB
#define Boton_rojo_EXTI_IRQn EXTI0_IRQn
#define Boton_verde_Pin GPIO_PIN_1
#define Boton_verde_GPIO_Port GPIOB
#define Boton_verde_EXTI_IRQn EXTI1_IRQn
#define boton_azul_Pin GPIO_PIN_2
#define boton_azul_GPIO_Port GPIOB
#define boton_azul_EXTI_IRQn EXTI2_IRQn
#define LED_VERDE_Pin GPIO_PIN_12
#define LED_VERDE_GPIO_Port GPIOD
#define LED_NARANJA_Pin GPIO_PIN_13
#define LED_NARANJA_GPIO_Port GPIOD
#define LED_ROJO_Pin GPIO_PIN_14
#define LED_ROJO_GPIO_Port GPIOD
#define LED_AZUL_Pin GPIO_PIN_15
#define LED_AZUL_GPIO_Port GPIOD
#define Boton_naranja_Pin GPIO_PIN_5
#define Boton_naranja_GPIO_Port GPIOB
#define Boton_naranja_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
