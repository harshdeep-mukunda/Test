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
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

#include <stdarg.h>
#include <signal.h>
#include <inttypes.h>
#include <math.h>
#include <limits.h>
#include <setjmp.h>
#include <stddef.h>
#include <tgmath.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>
#include <iso646.h>
#include <inttypes.h>
#include <assert.h>

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
#define USART_DE_Pin GPIO_PIN_1
#define USART_DE_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define Milk_Motor_NF_Pin GPIO_PIN_4
#define Milk_Motor_NF_GPIO_Port GPIOF
#define Balloff_Read_Pin GPIO_PIN_5
#define Balloff_Read_GPIO_Port GPIOF
#define Capacitive_Input_Pin GPIO_PIN_5
#define Capacitive_Input_GPIO_Port GPIOA
#define Capacitive_Reset_Pin GPIO_PIN_7
#define Capacitive_Reset_GPIO_Port GPIOA
#define Milk_Motor_IN1_Pin GPIO_PIN_4
#define Milk_Motor_IN1_GPIO_Port GPIOC
#define Milk_Motor_IN2_Pin GPIO_PIN_5
#define Milk_Motor_IN2_GPIO_Port GPIOC
#define MilkWater_Motor_NF_Pin GPIO_PIN_0
#define MilkWater_Motor_NF_GPIO_Port GPIOB
#define MilkWater_Motor_IN1_Pin GPIO_PIN_1
#define MilkWater_Motor_IN1_GPIO_Port GPIOB
#define MilkWater_Motor_IN2_Pin GPIO_PIN_2
#define MilkWater_Motor_IN2_GPIO_Port GPIOB
#define Water_Motor_NF_Pin GPIO_PIN_10
#define Water_Motor_NF_GPIO_Port GPIOB
#define Water_Motor_IN1_Pin GPIO_PIN_11
#define Water_Motor_IN1_GPIO_Port GPIOB
#define Water_Motor_IN2_Pin GPIO_PIN_12
#define Water_Motor_IN2_GPIO_Port GPIOB
#define CleaningWater_Motor_NF_Pin GPIO_PIN_13
#define CleaningWater_Motor_NF_GPIO_Port GPIOB
#define CleaningWater_Motor_IN1_Pin GPIO_PIN_14
#define CleaningWater_Motor_IN1_GPIO_Port GPIOB
#define CleaningWater_Motor_IN2_Pin GPIO_PIN_15
#define CleaningWater_Motor_IN2_GPIO_Port GPIOB
#define Stirrer_Motor_NF_Pin GPIO_PIN_6
#define Stirrer_Motor_NF_GPIO_Port GPIOC
#define Stirrer_Motor_IN1_Pin GPIO_PIN_7
#define Stirrer_Motor_IN1_GPIO_Port GPIOC
#define Stirrer_Motor_IN2_Pin GPIO_PIN_8
#define Stirrer_Motor_IN2_GPIO_Port GPIOC
#define HotWater_Motor_NF_Pin GPIO_PIN_9
#define HotWater_Motor_NF_GPIO_Port GPIOC
#define HotWater_Motor_IN2_Pin GPIO_PIN_8
#define HotWater_Motor_IN2_GPIO_Port GPIOA
#define HotWater_Motor_IN1_Pin GPIO_PIN_9
#define HotWater_Motor_IN1_GPIO_Port GPIOA
#define Milk_LevelSensor_OpampProtection_Pin GPIO_PIN_10
#define Milk_LevelSensor_OpampProtection_GPIO_Port GPIOA
#define Water_LevelSensor_Pin GPIO_PIN_11
#define Water_LevelSensor_GPIO_Port GPIOA
#define SSRHeater_MilkWater_Pin GPIO_PIN_12
#define SSRHeater_MilkWater_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define SSRHeater_Water_Pin GPIO_PIN_6
#define SSRHeater_Water_GPIO_Port GPIOF
#define Solenoid_Valve_Pin GPIO_PIN_7
#define Solenoid_Valve_GPIO_Port GPIOF
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define Digital_Temperature_Sensor_Milk_Pin GPIO_PIN_15
#define Digital_Temperature_Sensor_Milk_GPIO_Port GPIOA
#define Digital_Temperature_Sensor_MilkWater_Pin GPIO_PIN_10
#define Digital_Temperature_Sensor_MilkWater_GPIO_Port GPIOC
#define Digital_Temperature_Sensor_Water_Pin GPIO_PIN_11
#define Digital_Temperature_Sensor_Water_GPIO_Port GPIOC
#define MilkWater_Level_Pin GPIO_PIN_12
#define MilkWater_Level_GPIO_Port GPIOC
#define Flow_Sensor_Water_Pin GPIO_PIN_4
#define Flow_Sensor_Water_GPIO_Port GPIOB
#define Flow_Sensor_MilkWater_Pin GPIO_PIN_5
#define Flow_Sensor_MilkWater_GPIO_Port GPIOB
#define CAP_READ_Pin GPIO_PIN_6
#define CAP_READ_GPIO_Port GPIOB
#define Milk_FloatSensor_Pin GPIO_PIN_9
#define Milk_FloatSensor_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
