/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <mainProcess.h>
#include <mainProcessFunction.h>
#include <mainProcessVariables.h>
#include <stdint.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//uint8_t Cap_buff[10];
//uint8_t Cap_Read = 0;
//uint8_t Cap_Flag = 0;
//uint8_t Cap_Flag_Reset = 0;
//uint8_t Cap_Buff_Read = 0;
//uint8_t Cap_Counts = 0;
//extern uint8_t Cap_WaitSeconds;
//uint8_t Cap_WaitFlag = 0;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM3_Init(void);
static void MX_ADC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int read = 0;
int read2 = 0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_ADC_Init();
  /* USER CODE BEGIN 2 */


	//  Process.Variables.InitProcess = Milk_Water;
	//  Process.Variables.Cleaning.InitProcess = PrilCleaning;

//	HAL_GPIO_WritePin(Level_Toggling_1_GPIO_Port, Level_Toggling_1_Pin, SET);
//	HAL_GPIO_WritePin(Level_Toggling_2_GPIO_Port, Level_Toggling_2_Pin, RESET);

	//	int i = 10;
	//	while (i>0)
	//	{
#if 0			// Runnign Code
	HAL_GPIO_WritePin(Capacitive_Reset_GPIO_Port, Capacitive_Reset_Pin, SET);
	HAL_Delay(110);
	Cap_Read = !(HAL_GPIO_ReadPin(Capacitive_Input_GPIO_Port, Capacitive_Input_Pin));
#endif


	//	HAL_GPIO_WritePin(Capacitive_Reset_GPIO_Port, Capacitive_Reset_Pin, SET);
	//	HAL_Delay(4.5);
	//	HAL_GPIO_WritePin(Capacitive_Reset_GPIO_Port, Capacitive_Reset_Pin, RESET);
	//	Cap_Read = !(HAL_GPIO_ReadPin(Capacitive_Input_GPIO_Port, Capacitive_Input_Pin));

	//	HAL_GPIO_WritePin(Capacitive_Reset_GPIO_Port, Capacitive_Reset_Pin, RESET);
	//	HAL_Delay(4.5);
	//
	//	HAL_GPIO_WritePin(Capacitive_Reset_GPIO_Port, Capacitive_Reset_Pin, SET);
	//	HAL_Delay(110);
	//	Cap_Read = !(HAL_GPIO_ReadPin(Capacitive_Input_GPIO_Port, Capacitive_Input_Pin));

	//	HAL_GPIO_WritePin(Capacitive_Reset_GPIO_Port, Capacitive_Reset_Pin, SET);
	//	HAL_Delay(110);
	//	Cap_Read = !(HAL_GPIO_ReadPin(Capacitive_Input_GPIO_Port, Capacitive_Input_Pin));
	//	Cap_buff[0] = !(HAL_GPIO_ReadPin(Capacitive_Input_GPIO_Port, Capacitive_Input_Pin));
	//
	//	HAL_UART_Transmit(&huart2, (uint8_t *) Cap_buff, sizeof(Cap_buff), HAL_MAX_DELAY);
	//	i--;
	//	}
	//
	//	HAL_GPIO_WritePin(Capacitive_Reset_GPIO_Port, Capacitive_Reset_Pin, SET);

	//	HAL_GPIO_WritePin(Capacitive_Voltage_GPIO_Port, Capacitive_Voltage_Pin, SET);
	//  HAL_Delay(100);
	//
	//  Motor_Milk_AntiClkwise();
	//  HAL_GPIO_WritePin(Capacitive_Reset_GPIO_Port, Capacitive_Reset_Pin, RESET);
	//
	//  HAL_Delay(1000);
	//  Motor_Milk_Stop();
	//
	//  HAL_GPIO_WritePin(Capacitive_Reset_GPIO_Port, Capacitive_Reset_Pin, SET);


	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_Base_Start(&htim3);

	//  HAL_GPIO_WritePin(Capacitive_Reset_GPIO_Port, Capacitive_Reset_Pin, SET);
	//  HAL_Delay(100);

	Process.Variables.InitProcess = Idle;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

	//  Process.Variables.Cleaning.RxRepeatProcessCounts = 3;
	//  Process.Variables.Cleaning.ProcessExeCounts = 2;
	//  TestProcess();		// Only for Testing Purpose

	// Change milk pin with milkwater pin on board
//	  Motor_MilkWater_Clkwise();			//
//	  HAL_Delay(5000);
	Motor_MilkWater_Stop();

	//  Motor_Milk_Clkwise();
//	  Motor_Milk_AntiClkwise();
//	  HAL_Delay(5000);
	Motor_Milk_Stop();

//	  Motor_Water_Clkwise();
//	  HAL_Delay(5000);
	Motor_Water_Stop();

//	  Motor_CleaningWater_Clkwise();		// Cleaning
//	  HAL_Delay(5000);
	Motor_CleaningWater_Stop();

//	  Motor_Stirrer_Clkwise();
//	  HAL_Delay(5000);
	Motor_Stirrer_Stop();

//	  Motor_HotWater_Clkwise();
//	  HAL_Delay(5000);
	Motor_HotWater_Stop();

//	  SSRHeater_ON_MilkWater();			// Interchange the pins on board
//	  HAL_Delay(5000);
	SSRHeater_OFF_MilkWater();

//	  SSRHeater_ON_Water();
//	  HAL_Delay(5000);
	SSRHeater_OFF_Water();

	HAL_GPIO_WritePin(Stirrer_Motor_NF_GPIO_Port, Stirrer_Motor_NF_Pin, SET);

//	  Motor_Stirrer_Clkwise();
//	  HAL_Delay(5000);
	  Motor_Stirrer_Stop();



	Temperature_PreviousValue_Milk		= 	DigitalSensor_Read_Milk();
	Temperature_PreviousValue_MilkWater = 	DigitalSensor_Read_MilkWater();
	Temperature_PreviousValue_Water 	= 	DigitalSensor_Read_Water();

	while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		StartProcess();
//		read = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11);
//		read2 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9);
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI14;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC_Init(void)
{

  /* USER CODE BEGIN ADC_Init 0 */

  /* USER CODE END ADC_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
  */
  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  hadc.Init.ContinuousConvMode = DISABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = DISABLE;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC_Init 2 */

  /* USER CODE END ADC_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 999;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 4799;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 47;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 0xFFFF-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OC_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, USART_DE_Pin|Capacitive_Reset_Pin|HotWater_Motor_IN2_Pin|HotWater_Motor_IN1_Pin 
                          |SSRHeater_MilkWater_Pin|Digital_Temperature_Sensor_Milk_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, Milk_Motor_IN1_Pin|Milk_Motor_IN2_Pin|Stirrer_Motor_NF_Pin|Stirrer_Motor_IN1_Pin 
                          |Stirrer_Motor_IN2_Pin|Digital_Temperature_Sensor_MilkWater_Pin|Digital_Temperature_Sensor_Water_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, MilkWater_Motor_IN1_Pin|MilkWater_Motor_IN2_Pin|Water_Motor_IN1_Pin|Water_Motor_IN2_Pin 
                          |CleaningWater_Motor_IN1_Pin|CleaningWater_Motor_IN2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, SSRHeater_Water_Pin|Solenoid_Valve_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : USART_DE_Pin Capacitive_Reset_Pin HotWater_Motor_IN2_Pin HotWater_Motor_IN1_Pin 
                           Digital_Temperature_Sensor_Milk_Pin */
  GPIO_InitStruct.Pin = USART_DE_Pin|Capacitive_Reset_Pin|HotWater_Motor_IN2_Pin|HotWater_Motor_IN1_Pin 
                          |Digital_Temperature_Sensor_Milk_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : Milk_Motor_NF_Pin */
  GPIO_InitStruct.Pin = Milk_Motor_NF_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Milk_Motor_NF_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Balloff_Read_Pin */
  GPIO_InitStruct.Pin = Balloff_Read_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Balloff_Read_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Capacitive_Input_Pin Milk_LevelSensor_OpampProtection_Pin Water_LevelSensor_Pin */
  GPIO_InitStruct.Pin = Capacitive_Input_Pin|Milk_LevelSensor_OpampProtection_Pin|Water_LevelSensor_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : Milk_Motor_IN1_Pin Milk_Motor_IN2_Pin Stirrer_Motor_NF_Pin Stirrer_Motor_IN1_Pin 
                           Stirrer_Motor_IN2_Pin Digital_Temperature_Sensor_MilkWater_Pin Digital_Temperature_Sensor_Water_Pin */
  GPIO_InitStruct.Pin = Milk_Motor_IN1_Pin|Milk_Motor_IN2_Pin|Stirrer_Motor_NF_Pin|Stirrer_Motor_IN1_Pin 
                          |Stirrer_Motor_IN2_Pin|Digital_Temperature_Sensor_MilkWater_Pin|Digital_Temperature_Sensor_Water_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : MilkWater_Motor_NF_Pin Water_Motor_NF_Pin CleaningWater_Motor_NF_Pin Flow_Sensor_Water_Pin 
                           Flow_Sensor_MilkWater_Pin CAP_READ_Pin */
  GPIO_InitStruct.Pin = MilkWater_Motor_NF_Pin|Water_Motor_NF_Pin|CleaningWater_Motor_NF_Pin|Flow_Sensor_Water_Pin 
                          |Flow_Sensor_MilkWater_Pin|CAP_READ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : MilkWater_Motor_IN1_Pin MilkWater_Motor_IN2_Pin Water_Motor_IN1_Pin Water_Motor_IN2_Pin 
                           CleaningWater_Motor_IN1_Pin CleaningWater_Motor_IN2_Pin */
  GPIO_InitStruct.Pin = MilkWater_Motor_IN1_Pin|MilkWater_Motor_IN2_Pin|Water_Motor_IN1_Pin|Water_Motor_IN2_Pin 
                          |CleaningWater_Motor_IN1_Pin|CleaningWater_Motor_IN2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : HotWater_Motor_NF_Pin */
  GPIO_InitStruct.Pin = HotWater_Motor_NF_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(HotWater_Motor_NF_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SSRHeater_MilkWater_Pin */
  GPIO_InitStruct.Pin = SSRHeater_MilkWater_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SSRHeater_MilkWater_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SSRHeater_Water_Pin Solenoid_Valve_Pin */
  GPIO_InitStruct.Pin = SSRHeater_Water_Pin|Solenoid_Valve_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : MilkWater_Level_Pin */
  GPIO_InitStruct.Pin = MilkWater_Level_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(MilkWater_Level_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Milk_FloatSensor_Pin */
  GPIO_InitStruct.Pin = Milk_FloatSensor_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Milk_FloatSensor_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
		/* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
		/* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
