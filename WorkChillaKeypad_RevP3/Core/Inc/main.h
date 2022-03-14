/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32l4xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define OUT_0_Pin GPIO_PIN_0
#define OUT_0_GPIO_Port GPIOA
#define OUT_1_Pin GPIO_PIN_1
#define OUT_1_GPIO_Port GPIOA
#define OUT_2_Pin GPIO_PIN_2
#define OUT_2_GPIO_Port GPIOA
#define OUT_3_Pin GPIO_PIN_3
#define OUT_3_GPIO_Port GPIOA
#define OUT_4_Pin GPIO_PIN_4
#define OUT_4_GPIO_Port GPIOA
#define OUT_5_Pin GPIO_PIN_5
#define OUT_5_GPIO_Port GPIOA
#define OUT_6_Pin GPIO_PIN_6
#define OUT_6_GPIO_Port GPIOA
#define OUT_7_Pin GPIO_PIN_7
#define OUT_7_GPIO_Port GPIOA
#define OUT_9_Pin GPIO_PIN_0
#define OUT_9_GPIO_Port GPIOB
#define IN_0_Pin GPIO_PIN_1
#define IN_0_GPIO_Port GPIOB
#define LED_TX_Pin GPIO_PIN_9
#define LED_TX_GPIO_Port GPIOA
#define LED_RX_Pin GPIO_PIN_10
#define LED_RX_GPIO_Port GPIOA
#define OUT_8_Pin GPIO_PIN_15
#define OUT_8_GPIO_Port GPIOA
#define IN_1_Pin GPIO_PIN_3
#define IN_1_GPIO_Port GPIOB
#define IN_2_Pin GPIO_PIN_4
#define IN_2_GPIO_Port GPIOB
#define IN_3_Pin GPIO_PIN_5
#define IN_3_GPIO_Port GPIOB
#define IN_4_Pin GPIO_PIN_6
#define IN_4_GPIO_Port GPIOB
#define IN_5_Pin GPIO_PIN_7
#define IN_5_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
