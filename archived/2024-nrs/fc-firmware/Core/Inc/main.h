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
#define Barometer_Interrupt_Pin GPIO_PIN_2
#define Barometer_Interrupt_GPIO_Port GPIOE
#define Barometer_Interrupt_EXTI_IRQn EXTI2_IRQn
#define Gyro_Interrupt_1_Pin GPIO_PIN_3
#define Gyro_Interrupt_1_GPIO_Port GPIOE
#define Gyro_Interrupt_1_EXTI_IRQn EXTI3_IRQn
#define Gyro_Interrupt_2_Pin GPIO_PIN_4
#define Gyro_Interrupt_2_GPIO_Port GPIOE
#define Gyro_Interrupt_2_EXTI_IRQn EXTI4_IRQn
#define Accelerometer_Interrupt_1_Pin GPIO_PIN_5
#define Accelerometer_Interrupt_1_GPIO_Port GPIOE
#define Accelerometer_Interrupt_1_EXTI_IRQn EXTI9_5_IRQn
#define Accelerometer_Interrupt_2_Pin GPIO_PIN_6
#define Accelerometer_Interrupt_2_GPIO_Port GPIOE
#define Accelerometer_Interrupt_2_EXTI_IRQn EXTI9_5_IRQn
#define Temperature_Alert_Pin GPIO_PIN_13
#define Temperature_Alert_GPIO_Port GPIOC
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
