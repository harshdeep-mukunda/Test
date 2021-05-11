/*
 * mainProcessFUnction.c
 *
 *  Created on: Oct 27, 2020
 *      Author: Naveen
 */

#include <mainProcessFunction.h>
#include <mainProcessVariables.h>
#include <main.h>


uint8_t		Os_Ack[64]
				   =		{0x13, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 \
						   , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 \
						   , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 \
						   , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 \
						   , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 \
						   , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12};

uint8_t 	Os_Status[64]
					  =			{0x13, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 \
							  , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 \
							  , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 \
							  , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 \
							  , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 \
							  , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12};

void SendAckowledgement(uint8_t ProcessID, uint8_t ProcessStep)
{
	Os_Ack[1] = ProcessID;
	Os_Ack[4] = ProcessStep;

	HAL_GPIO_WritePin	(USART_DE_GPIO_Port,	USART_DE_Pin, SET);
	HAL_UART_Transmit	(&huart2,	Os_Ack, sizeof(Os_Ack), HAL_MAX_DELAY);
	HAL_GPIO_WritePin	(USART_DE_GPIO_Port,	USART_DE_Pin, RESET);
	HAL_UART_Receive_IT(&huart2, Process.Variables.ReceivedData, sizeof(Process.Variables.ReceivedData));
}

void SendStatus(void)
{

	switch (Process.Variables.ReceivedData[1])
	{

	case	StatusID:
	{

		if (	Process.Variables.ReceivedData[5]	)
			Motor_Stirrer_Clkwise();
		else
			Motor_Stirrer_Stop();


		Os_Status[1]	= StatusID;

		Os_Status[5] 	= (int)Process.Variables.Water.LevelSensor;
		Os_Status[7] 	= (int)Process.Variables.Water.Temperature.Read;

		Os_Status[9] 	= (int)Process.Variables.Milk.LevelSensor;
		Os_Status[11] 	= (int)Process.Variables.MilkWater.LevelSensor;

		Os_Status[13] 	= (int)Process.Variables.Milk.Temperature.Read;
		Os_Status[15]	= (int)Process.Variables.MilkWater.Temperature.Read;


		if	(	Process.Variables.HotWater.TimerCounts		>= 		Process.Variables.HotWater.RxOnTime		)
			Process.Variables.HotWater.TimerCounts 	= 	RESET;

		Os_Status[17]	=	Process.Flags.HotWater.TimerEnable;
		Os_Status[18]	=	(Process.Variables.HotWater.TimerCounts / 10 );


		Os_Status[30]	=	Process.Flags.ErrorGenerated;
		Os_Status[31]	=	Process.Variables.Milk.LevelSensor_OpampProtection;			// Failure of Balluff Sensor


		break;
	}

	case	CleaningStatusID:
	{
		Os_Status[1]	= CleaningStatusID;


		Os_Status[5] 	= (int)Process.Variables.Water.LevelSensor;
		Os_Status[7] 	= (int)Process.Variables.Water.Temperature.Read;

		Os_Status[9] 	= (int)Process.Variables.Milk.LevelSensor;
		Os_Status[11] 	= (int)Process.Variables.MilkWater.LevelSensor;

		Os_Status[13] 	= (int)Process.Variables.Milk.Temperature.Read;
		Os_Status[15]	= (int)Process.Variables.MilkWater.Temperature.Read;


		Os_Status[18]	= Process.Variables.Cleaning.ProcessExeCounts;
		Os_Status[19]	= Process.Flags.Cleaning.ProcessOngoing_Pril;
		Os_Status[20]	= Process.Flags.Cleaning.ProcessOngoing_Water;
		Os_Status[21]	= Process.Flags.Cleaning.ProcessCompleted_Pril;
		Os_Status[22]	= Process.Flags.Cleaning.ProcessCompleted_Water;


		Os_Status[23]	=	RESET	;
		if (Process.Flags.Cleaning.TimerEnable_StirrerPril)
			Os_Status[23]	= (int)	(Process.Variables.Cleaning.TimerCounts_StirrerPril / ( Minutes * TimerMultiplicationFactor) );


		else if (Process.Flags.Cleaning.TimerEnable_StirrerWater)
			Os_Status[23]	= (int)	(Process.Variables.Cleaning.TimerCounts_StirrerWater / ( Minutes * TimerMultiplicationFactor) );

//		else
//			Os_Status[23]	= 0;


//		Os_Status[12] 	= 	(int)Process.Variables.Milk.Temperature.Read;
//		Os_Status[14]	= 	(int)Process.Variables.MilkWater.Temperature.Read;
//		Os_Status[16]	= 	(int)Process.Variables.Water.Temperature.Read;


		break;
	}


	case	StopCommand:
	{
		Os_Status[1]	= 	StopCommand;
		Os_Status[5]	= 	SET;

		break;
	}

	default	:
		break;

	}


	HAL_GPIO_WritePin	(USART_DE_GPIO_Port,	USART_DE_Pin, SET);
	HAL_UART_Transmit	(&huart2,	Os_Status, sizeof(Os_Status), HAL_MAX_DELAY);
	HAL_GPIO_WritePin	(USART_DE_GPIO_Port,	USART_DE_Pin, RESET);
	HAL_UART_Receive_IT(&huart2, Process.Variables.ReceivedData, sizeof(Process.Variables.ReceivedData));

}


void Motor_Milk_AntiClkwise(void)
{
	HAL_GPIO_WritePin(Milk_Motor_IN1_GPIO_Port, Milk_Motor_IN1_Pin, RESET);
	HAL_GPIO_WritePin(Milk_Motor_IN2_GPIO_Port, Milk_Motor_IN2_Pin, SET);
}
void Motor_Milk_Clkwise(void)
{
	HAL_GPIO_WritePin(Milk_Motor_IN1_GPIO_Port, Milk_Motor_IN1_Pin, SET);
	HAL_GPIO_WritePin(Milk_Motor_IN2_GPIO_Port, Milk_Motor_IN2_Pin, RESET);
}
void Motor_Milk_Stop(void)
{
	HAL_GPIO_WritePin(Milk_Motor_IN1_GPIO_Port, Milk_Motor_IN1_Pin, RESET);
	HAL_GPIO_WritePin(Milk_Motor_IN2_GPIO_Port, Milk_Motor_IN2_Pin, RESET);
}


void Motor_MilkWater_Clkwise(void)
{
	HAL_GPIO_WritePin(MilkWater_Motor_IN1_GPIO_Port, MilkWater_Motor_IN1_Pin, SET);
	HAL_GPIO_WritePin(MilkWater_Motor_IN2_GPIO_Port, MilkWater_Motor_IN2_Pin, RESET);
}

void Motor_MilkWater_AntiClkwise(void)
{
	HAL_GPIO_WritePin(MilkWater_Motor_IN1_GPIO_Port, MilkWater_Motor_IN1_Pin, RESET);
	HAL_GPIO_WritePin(MilkWater_Motor_IN2_GPIO_Port, MilkWater_Motor_IN2_Pin, SET);
}

void Motor_MilkWater_Stop(void)
{
	HAL_GPIO_WritePin(MilkWater_Motor_IN1_GPIO_Port, MilkWater_Motor_IN1_Pin, RESET);
	HAL_GPIO_WritePin(MilkWater_Motor_IN2_GPIO_Port, MilkWater_Motor_IN2_Pin, RESET);
}


void Motor_Water_Clkwise(void)
{
	HAL_GPIO_WritePin(Water_Motor_IN1_GPIO_Port, Water_Motor_IN1_Pin, SET);
	HAL_GPIO_WritePin(Water_Motor_IN2_GPIO_Port, Water_Motor_IN2_Pin, RESET);
}
void Motor_Water_Stop(void)
{
	HAL_GPIO_WritePin(Water_Motor_IN1_GPIO_Port, Water_Motor_IN1_Pin, RESET);
	HAL_GPIO_WritePin(Water_Motor_IN2_GPIO_Port, Water_Motor_IN2_Pin, RESET);
}


void Motor_CleaningWater_Clkwise(void)
{
	HAL_GPIO_WritePin(CleaningWater_Motor_IN1_GPIO_Port, CleaningWater_Motor_IN1_Pin, SET);
	HAL_GPIO_WritePin(CleaningWater_Motor_IN2_GPIO_Port, CleaningWater_Motor_IN2_Pin, RESET);
}
void Motor_CleaningWater_Stop(void)
{
	HAL_GPIO_WritePin(CleaningWater_Motor_IN1_GPIO_Port, CleaningWater_Motor_IN1_Pin, RESET);
	HAL_GPIO_WritePin(CleaningWater_Motor_IN2_GPIO_Port, CleaningWater_Motor_IN2_Pin, RESET);
}

void Motor_Stirrer_Clkwise(void)
{
	HAL_GPIO_WritePin(Stirrer_Motor_IN1_GPIO_Port, Stirrer_Motor_IN1_Pin, SET);
	HAL_GPIO_WritePin(Stirrer_Motor_IN2_GPIO_Port, Stirrer_Motor_IN2_Pin, RESET);
}
void Motor_Stirrer_AntiClkwise(void)
{
	HAL_GPIO_WritePin(Stirrer_Motor_IN1_GPIO_Port, Stirrer_Motor_IN1_Pin, RESET);
	HAL_GPIO_WritePin(Stirrer_Motor_IN2_GPIO_Port, Stirrer_Motor_IN2_Pin, SET);
}
void Motor_Stirrer_Stop(void)
{
	HAL_GPIO_WritePin(Stirrer_Motor_IN1_GPIO_Port, Stirrer_Motor_IN1_Pin, RESET);
	HAL_GPIO_WritePin(Stirrer_Motor_IN2_GPIO_Port, Stirrer_Motor_IN2_Pin, RESET);
}


void Motor_HotWater_Clkwise(void)
{
	HAL_GPIO_WritePin(HotWater_Motor_IN1_GPIO_Port, HotWater_Motor_IN1_Pin, SET);
	HAL_GPIO_WritePin(HotWater_Motor_IN2_GPIO_Port, HotWater_Motor_IN2_Pin, RESET);
}
void Motor_HotWater_Stop(void)
{
	HAL_GPIO_WritePin(HotWater_Motor_IN1_GPIO_Port, HotWater_Motor_IN1_Pin, RESET);
	HAL_GPIO_WritePin(HotWater_Motor_IN2_GPIO_Port, HotWater_Motor_IN2_Pin, RESET);
}


void SSRHeater_ON_MilkWater(void)
{
	HAL_GPIO_WritePin(SSRHeater_MilkWater_GPIO_Port, SSRHeater_MilkWater_Pin, SET);
}
void SSRHeater_OFF_MilkWater(void)
{
	HAL_GPIO_WritePin(SSRHeater_MilkWater_GPIO_Port, SSRHeater_MilkWater_Pin, RESET);
}


void SSRHeater_ON_Water(void)
{
	HAL_GPIO_WritePin(SSRHeater_Water_GPIO_Port, SSRHeater_Water_Pin, SET);
}
void SSRHeater_OFF_Water(void)
{
	HAL_GPIO_WritePin(SSRHeater_Water_GPIO_Port, SSRHeater_Water_Pin, RESET);
}


#if 0
float LevelSensor_Read(uint8_t Channel)
{

	float Value = 0;

	if(Channel == Milk)
	{
		ADC1->CHSELR = (1 << Channel_Milk);
	}
	else if(Channel == Milk_Water)
	{
		ADC1->CHSELR = (1 << Channel_MilkWater);
	}
	else if(Channel == Water)
	{
		ADC1->CHSELR = (1 << Channel_Water);
	}

	HAL_ADC_Start(&hadc);
	HAL_ADC_PollForConversion(&hadc, 100);
	Value = HAL_ADC_GetValue(&hadc);
	Value = (Value * 3.3)/ 4095;

	HAL_ADC_Stop(&hadc);


	return Value;
}
#endif


void LevelSensor_CheckForPrilCleaning(void)
{
	if(Process.Variables.Milk.LevelSensor)
	{
		Motor_Milk_Stop();
		Process.Flags.Cleaning.LevelFilled_Pril = SET;
	}
	else
	{
		Motor_Milk_Clkwise();
		Process.Flags.Cleaning.LevelFilled_Pril = RESET;
	}
}

void LevelSensor_CheckForWaterCleaning(void)
{
	if(Process.Variables.Milk.LevelSensor)
	{
		Motor_CleaningWater_Stop();
		Process.Flags.Cleaning.LevelFilled_Water = SET;
	}
	else
	{
		Motor_CleaningWater_Clkwise();
		Process.Flags.Cleaning.LevelFilled_Water = RESET;
	}
}

void LevelSensor_CheckForMilkWater(void)
{
	// *************** For Water in the Milk Chamber ************************* //
	if(Process.Variables.MilkWater.LevelSensor)
	{
		Motor_MilkWater_Stop();

		Process.Flags.MilkWater.SSRHeater = True;		// Enable in the Timer
	}

	else
	{
		Motor_MilkWater_Clkwise();
		Process.Flags.MilkWater.SSRHeater = False;
	}

	// *************** For Milk Chamber ************************* //
	if (Process.Variables.Milk.LevelSensor)
	{
		Motor_Milk_Stop();
	}
	else
	{
		Motor_Milk_Clkwise();
	}

#if 0			// Not required
	if(Process.Variables.Milk.LevelSensor)					// This includes Stirrer Motor ROtating part
	{
		if (not(Process.Flags.MilkWater.InitTemp))								// Stirrer will start only after Initialization Complete
		{
			Motor_Milk_Stop();
		}

		else if(Process.Flags.MilkWater.LevelFilledandStirrerCounts == One)			// It will become One in the Timer Callback Function -> @Process.Variables.Milk.LevelSensor
		{
			Process.Flags.MilkWater.LevelFilledandStirrerCounts = Two;			// Only one time Stirrer Motor should run after the level is full	-> GoTo Line 258 and Timer Callback function

			Process.Flags.MilkWater.TimerMilkLevelUp = SET;					// More than Required Level Filled
			Process.Flags.MilkWater.LevelFilledandStirrerStart = SET;		// Check the level is filled and when gets emptied -> Turn ON the stirrer Motor -> Goto Line 256

		}

	}
	else
	{
		Motor_Milk_Clkwise();

		if(Process.Flags.MilkWater.LevelFilledandStirrerStart)					// Check the level is filled and when get emptied -> Turn ON the stirrer Motor
		{
			Process.Flags.MilkWater.LevelFilledandStirrerCounts = RESET;
			Process.Flags.MilkWater.LevelFilledandStirrerStart = RESET;
			Process.Flags.MilkWater.Stirrer = SET;								// First Wait for 6 seconds, then turn ON
		}

	}
#endif

}

void	LevelSensor_CheckForOnlyMilkWater	(void)
{

	if(Process.Variables.MilkWater.LevelSensor)
	{
		Motor_MilkWater_Stop();
		Process.Flags.MilkWater.SSRHeater = True;
	}

	else
	{
		Motor_MilkWater_Clkwise();
		Process.Flags.MilkWater.SSRHeater = False;
	}
}


void LevelSensor_DrainOutPrilFromMilkPipe(void)
{

	if(Process.Variables.Milk.LevelSensor)
	{
		Motor_Milk_AntiClkwise();
		Process.Flags.Cleaning.LevelEmptied = RESET;
	}
	else
	{
		Motor_Milk_AntiClkwise();
		//		Motor_Milk_Stop();
		//		Process.Flags.Cleaning.LevelEmptied = SET;
		Process.Flags.Cleaning.TimerEnable_DrainOut_Pril = SET;					// extra drain out -> Timer Callback @Process.Variables.Cleaning.TimerCounts_DrainOut_Pril
	}
}


void LevelSensor_DrainOutWaterFromMilkPipe(void)
{

	if(Process.Variables.Milk.LevelSensor)
	{
		Motor_Milk_AntiClkwise();
		Process.Flags.Cleaning.LevelEmptied = RESET;
	}

	else
	{
		//		Motor_Milk_Stop();
		//		Process.Flags.Cleaning.LevelEmptied = SET;		// not required

		Motor_Milk_AntiClkwise();
		Process.Flags.Cleaning.TimerEnable_DrainOut_Water = SET;		// extra drain out
	}
}



void Temperature_CheckForMilkWater(void)
{
	if(Process.Flags.MilkWater.SSRHeater)
	{
		Process.Flags.MilkWater.SSRHeater = RESET;

		// This is initialization when Water Temperature is 80 and Milk Temp also reached upto 75

		if(!Process.Flags.MilkWater.InitTemp)
		{
			if(Process.Variables.MilkWater.Temperature.Read < Process.Variables.MilkWater.Temperature.RxInitTemp)
			{
				SSRHeater_ON_MilkWater();
			}
			else if(Process.Variables.MilkWater.Temperature.Read >= Process.Variables.MilkWater.Temperature.RxInitTemp)
			{
				SSRHeater_OFF_MilkWater();


				// Wait until Milk Temperature reaches until 75
				if ( Process.Variables.Milk.Temperature.Read >= Process.Variables.Milk.Temperature.RxInitTemp )
				{
					Process.Flags.MilkWater.InitTemp = SET;
				}


			}
		}

		else
		{
			if(Process.Variables.Milk.Temperature.Read < Process.Variables.Milk.Temperature.RxLowValue)
			{
				if(Process.Variables.MilkWater.Temperature.Read < Process.Variables.MilkWater.Temperature.RxHighValue)
				{
					SSRHeater_ON_MilkWater();
				}
				else
				{
					SSRHeater_OFF_MilkWater();
				}
			}

			else if((Process.Variables.Milk.Temperature.Read >= Process.Variables.Milk.Temperature.RxLowValue)
					and (Process.Variables.Milk.Temperature.Read <= Process.Variables.Milk.Temperature.RxMiddleValue))
			{
				if(Process.Variables.MilkWater.Temperature.Read < Process.Variables.MilkWater.Temperature.RxMiddleValue)
				{
					SSRHeater_ON_MilkWater();
				}
				else
				{
					SSRHeater_OFF_MilkWater();
				}
			}

			else if(Process.Variables.Milk.Temperature.Read >= Process.Variables.Milk.Temperature.RxMiddleValue){

				if(Process.Variables.MilkWater.Temperature.Read < Process.Variables.MilkWater.Temperature.RxLowValue)
				{
					SSRHeater_ON_MilkWater();
				}
				else
				{
					SSRHeater_OFF_MilkWater();
				}
			}
		}
	}
	else
	{
		SSRHeater_OFF_MilkWater();
	}
}

void 	Temperature_CheckForOnlyMilkWater(void)
{
	if(Process.Flags.MilkWater.SSRHeater)
	{
		Process.Flags.MilkWater.SSRHeater = RESET;

		if(Process.Variables.MilkWater.Temperature.Read < Process.Variables.Water.Temperature.RxMilkWaterValue)
		{
			SSRHeater_ON_MilkWater();
		}
		else
		{
			SSRHeater_OFF_MilkWater();
		}
	}
}


void LevelSensor_CheckForWater(void)
{
	if(Process.Variables.Water.LevelSensor)
	{
		Motor_Water_Stop();
		Process.Flags.Water.SSRHeater = SET;
	}

	else
	{
		Motor_Water_Clkwise();
		Process.Flags.Water.SSRHeater = RESET;
	}
}



void Temperature_CheckForWater(void)
{
	if(Process.Flags.Water.SSRHeater)
	{

		Process.Flags.Water.SSRHeater = RESET;

		if(Process.Variables.Water.Temperature.Read < Process.Variables.Water.Temperature.RxValue)
		{
			SSRHeater_ON_Water();
		}

		else
		{
			SSRHeater_OFF_Water();
		}
	}
}

