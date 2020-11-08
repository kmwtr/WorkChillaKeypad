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
#define OUT0_Pin GPIO_PIN_0
#define OUT0_GPIO_Port GPIOA
#define OUT1_Pin GPIO_PIN_1
#define OUT1_GPIO_Port GPIOA
#define OUT2_Pin GPIO_PIN_2
#define OUT2_GPIO_Port GPIOA
#define OUT3_Pin GPIO_PIN_3
#define OUT3_GPIO_Port GPIOA
#define OUT4_Pin GPIO_PIN_4
#define OUT4_GPIO_Port GPIOA
#define OUT5_Pin GPIO_PIN_5
#define OUT5_GPIO_Port GPIOA
#define OUT6_Pin GPIO_PIN_6
#define OUT6_GPIO_Port GPIOA
#define OUT7_Pin GPIO_PIN_7
#define OUT7_GPIO_Port GPIOA
#define SWICH_Pin GPIO_PIN_0
#define SWICH_GPIO_Port GPIOB
#define IN0_Pin GPIO_PIN_1
#define IN0_GPIO_Port GPIOB
#define OUT8_Pin GPIO_PIN_8
#define OUT8_GPIO_Port GPIOA
#define OUT9_Pin GPIO_PIN_9
#define OUT9_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_10
#define LED_GPIO_Port GPIOA
#define TCM809_Pin GPIO_PIN_15
#define TCM809_GPIO_Port GPIOA
#define IN1_Pin GPIO_PIN_3
#define IN1_GPIO_Port GPIOB
#define IN2_Pin GPIO_PIN_4
#define IN2_GPIO_Port GPIOB
#define IN3_Pin GPIO_PIN_5
#define IN3_GPIO_Port GPIOB
#define IN4_Pin GPIO_PIN_6
#define IN4_GPIO_Port GPIOB
#define IN5_Pin GPIO_PIN_7
#define IN5_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
