/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BarometerInterrupt_Pin GPIO_PIN_2
#define BarometerInterrupt_GPIO_Port GPIOE
#define GyroInterrupt1_Pin GPIO_PIN_3
#define GyroInterrupt1_GPIO_Port GPIOE
#define GyroInterrupt2_Pin GPIO_PIN_4
#define GyroInterrupt2_GPIO_Port GPIOE
#define AccelerometerInterrupt1_Pin GPIO_PIN_5
#define AccelerometerInterrupt1_GPIO_Port GPIOE
#define AccelerometerInterrupt2_Pin GPIO_PIN_6
#define AccelerometerInterrupt2_GPIO_Port GPIOE
#define TemperatureAlert_Pin GPIO_PIN_13
#define TemperatureAlert_GPIO_Port GPIOC
#define Boot1_Pin GPIO_PIN_2
#define Boot1_GPIO_Port GPIOB
#define Servo2_Pin GPIO_PIN_9
#define Servo2_GPIO_Port GPIOE
#define Servo1_Pin GPIO_PIN_11
#define Servo1_GPIO_Port GPIOE
#define PWM1_Pin GPIO_PIN_13
#define PWM1_GPIO_Port GPIOE
#define PWM2_Pin GPIO_PIN_14
#define PWM2_GPIO_Port GPIOE
#define ETH_NRST_Pin GPIO_PIN_2
#define ETH_NRST_GPIO_Port GPIOD
#define SDCardDetect_Pin GPIO_PIN_1
#define SDCardDetect_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
