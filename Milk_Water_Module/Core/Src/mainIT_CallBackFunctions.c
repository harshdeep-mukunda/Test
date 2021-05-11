/*
 * mainIT_CallBackFunctions.c
 *
 *  Created on: Nov 5, 2020
 *      Author: Naveen
 */


#include "main.h"
#include "stm32f0xx_it.h"
#include <mainProcessFunction.h>
#include <mainProcessVariables.h>
#include <mainIT_CallBackFunctions.h>

#include <string.h>

extern uint8_t Os_Status[64];
// ********************************************************************************************* //
// ***************************	 UART CallBack	******************************************** //
// ********************************************************************************************* //

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
void HAL_UART_CpltCallback(void)
{

	if (Process.Flags.UART_Enable == SET)
	{

		Process.Flags.UART_Enable = RESET;

		if (Process.Variables.ReceivedData[1] == Two)			// Milk Water Process Enable
		{

			Process.Variables.Milk.Temperature.RxInitTemp			=	(Process.Variables.ReceivedData[4]<<8)  + Process.Variables.ReceivedData[5];
			Process.Variables.MilkWater.Temperature.RxInitTemp		=	(Process.Variables.ReceivedData[6]<<8)  + Process.Variables.ReceivedData[7];

			Process.Variables.Milk.Temperature.RxLowValue			=	(Process.Variables.ReceivedData[8]<<8)  + Process.Variables.ReceivedData[9];
			Process.Variables.Milk.Temperature.RxMiddleValue		=	(Process.Variables.ReceivedData[10]<<8) + Process.Variables.ReceivedData[11];
//			Process.Variables.Milk.Temperature.RxHighValue			=	(Process.Variables.ReceivedData[12]<<8) + Process.Variables.ReceivedData[13];

			Process.Variables.MilkWater.Temperature.RxLowValue		=	(Process.Variables.ReceivedData[14]<<8) + Process.Variables.ReceivedData[15];
			Process.Variables.MilkWater.Temperature.RxMiddleValue	=	(Process.Variables.ReceivedData[16]<<8) + Process.Variables.ReceivedData[17];
			Process.Variables.MilkWater.Temperature.RxHighValue		=	(Process.Variables.ReceivedData[18]<<8) + Process.Variables.ReceivedData[19];

			Process.Flags.MilkWater.ProcessEnable 					=	SET;

#if 0
			Process.Variables.Milk.Temperature.RxInitTemp			=	(Process.Variables.ReceivedData[5]<<8)  + Process.Variables.ReceivedData[6];
			Process.Variables.MilkWater.Temperature.RxInitTemp		=	(Process.Variables.ReceivedData[7]<<8)  + Process.Variables.ReceivedData[8];

			Process.Variables.Milk.Temperature.RxLowValue			=	(Process.Variables.ReceivedData[9]<<8)  + Process.Variables.ReceivedData[10];
			Process.Variables.Milk.Temperature.RxMiddleValue		=	(Process.Variables.ReceivedData[11]<<8)  + Process.Variables.ReceivedData[12];
			Process.Variables.Milk.Temperature.RxHighValue			=	(Process.Variables.ReceivedData[13]<<8) + Process.Variables.ReceivedData[14];

			Process.Variables.MilkWater.Temperature.RxLowValue		=	(Process.Variables.ReceivedData[15]<<8) + Process.Variables.ReceivedData[16];
			Process.Variables.MilkWater.Temperature.RxMiddleValue	=	(Process.Variables.ReceivedData[17]<<8) + Process.Variables.ReceivedData[18];
			Process.Variables.MilkWater.Temperature.RxHighValue		=	(Process.Variables.ReceivedData[19]<<8) + Process.Variables.ReceivedData[20];

			Process.Variables.Milk.RxStirrerWaitTime				=	((Process.Variables.ReceivedData[21]<<8) + Process.Variables.ReceivedData[22]) * TimerMultiplicationFactor; // waiting time for stirrer motor
			Process.Variables.Milk.RxStirrerTime 					=	((Process.Variables.ReceivedData[23]<<8) + Process.Variables.ReceivedData[24]) * TimerMultiplicationFactor; // stirrer time ON

			Process.Variables.Milk.RxLevelUp 						=	((Process.Variables.ReceivedData[25]<<8) + Process.Variables.ReceivedData[26]) * TimerMultiplicationFactor;	// How many seconds milk goes up after the level is sensed

			Process.Flags.MilkWater.ProcessEnable 					=	SET;

#endif

			SendAckowledgement(Two , 0);
		}


		else if (Process.Variables.ReceivedData[1] == One)		// Water Process Enable
		{
			Process.Variables.Water.Temperature.RxValue				=	(Process.Variables.ReceivedData[4]<<8) + Process.Variables.ReceivedData[5];

			if	(	Process.Variables.ReceivedData[10] == One	)
			{
				Process.Variables.Water.Temperature.RxMilkWaterValue	=	(Process.Variables.ReceivedData[11]<<8) + Process.Variables.ReceivedData[12];
				Process.Flags.Water.ProcessEnableMilkWater			=	SET;
			}

			Process.Flags.Water.ProcessEnable						=	SET;

			SendAckowledgement(One, 0);
		}


		else if (Process.Variables.ReceivedData[1] == Three)	// Cleaning Process Enable
		{
			//			Process.Flags.Water.ProcessEnable						=	RESET;

			if (not(Process.Flags.Cleaning.ProcessBusy))
			{
				Process.Flags.Cleaning.ProcessBusy				=	SET;
				Process.Flags.Cleaning.ProcessOngoing_Pril		=	RESET;
				Process.Flags.Cleaning.ProcessOngoing_Water		=	RESET;
				Process.Variables.Cleaning.ProcessExeCounts++;					// counting the cycle executing

				Process.Flags.Cleaning.ProcessCompleted_Pril	= 	RESET;
				Process.Flags.Cleaning.ProcessCompleted_Water	= 	RESET;
			}


			switch (Process.Variables.ReceivedData[4])
			{
			case	PrilCleaning:
			{

				Process.Variables.Cleaning.InitProcess 								=	PrilCleaning;
				Process.Variables.Cleaning.ProcessExecution							=	CheckForLevel;

				switch(Process.Variables.ReceivedData[5])
				{
				case	PrilCleaning_FirstCycle:
				{
					Process.Variables.Cleaning.RxLevelUp_Pril						=	((Process.Variables.ReceivedData[6]<<8)  + Process.Variables.ReceivedData[7])  * TimerMultiplicationFactor;				// How much pril level goes up
					//					Process.Variables.Cleaning.RxLevelUp_Pril						=	0;
					//					Process.Variables.Cleaning.RxTimerCounts_StirrerToggling_Pril 	=	((Process.Variables.ReceivedData[8]<<8)  + Process.Variables.ReceivedData[9])  * TimerMultiplicationFactor * Minutes;		// How much time Pril Stirrer rotate Toggles for 5 seconds (in Mins)
					Process.Variables.Cleaning.RxStirrerOnTimePrilFirstCycle		=	((Process.Variables.ReceivedData[10]<<8) + Process.Variables.ReceivedData[11]) * TimerMultiplicationFactor * Minutes;	// How much time Pril Stirrer rotate in first cycle in (in Mins)

					Process.Variables.Cleaning.RxTotalCycles						= 	((Process.Variables.ReceivedData[12]<<8) + Process.Variables.ReceivedData[13]);	// Total Number of Cycles needs to be processed

					break;
				}

				case	PrilCleaning_OtherCycles:
				{

					Process.Variables.Cleaning.RxLevelUp_Pril						=	((Process.Variables.ReceivedData[6]<<8)  + Process.Variables.ReceivedData[7])  * TimerMultiplicationFactor;;				// How much pril level goes up
					//					Process.Variables.Cleaning.RxLevelUp_Pril						=	0;
					Process.Variables.Cleaning.RxTimePrilDrainOut					=	((Process.Variables.ReceivedData[8]<<8)  + Process.Variables.ReceivedData[9])  * TimerMultiplicationFactor;				// How much pril level goes out in drain out
					//					Process.Variables.Cleaning.RxTimerCounts_StirrerToggling_Pril 	=	((Process.Variables.ReceivedData[10]<<8) + Process.Variables.ReceivedData[11]) * TimerMultiplicationFactor * Minutes;	// How much time Pril Stirrer rotate Toggles for 5 seconds (in Mins)
					Process.Variables.Cleaning.RxStirrerOnTimePrilSecondCycle		=	((Process.Variables.ReceivedData[12]<<8) + Process.Variables.ReceivedData[13]) * TimerMultiplicationFactor * Minutes;	// How much time Pril Stirrer rotate in second cycle (in Mins)

					break;
				}

				default:
					break;
				}
				break;
			}

			case	WaterCleaning:
			{

				Process.Variables.Cleaning.InitProcess 								=	WaterCleaning;
				Process.Variables.Cleaning.ProcessExecution							=	CheckForLevel;

				switch(Process.Variables.ReceivedData[5])
				{
				case	WaterCleaning_FirstCycle:
				{
					Process.Variables.Cleaning.RxLevelUp_Water						=	((Process.Variables.ReceivedData[6]<<8)  + Process.Variables.ReceivedData[7])  * TimerMultiplicationFactor;				// How much water level goes up
					//					Process.Variables.Cleaning.RxLevelUp_Water						=	0;
					Process.Variables.Cleaning.RxStirrerOnTimeWaterCycle			=	((Process.Variables.ReceivedData[8]<<8)	 + Process.Variables.ReceivedData[9])  * TimerMultiplicationFactor * Minutes;	// How much time Water Stirrer rotate (in Mins)

					break;
				}

				case	WaterCleaning_OtherCycles:
				{
					Process.Variables.Cleaning.RxLevelUp_Water						=	((Process.Variables.ReceivedData[6]<<8)  + Process.Variables.ReceivedData[7])  * TimerMultiplicationFactor;				// How much water level goes up
					//					Process.Variables.Cleaning.RxLevelUp_Water						=	0;
					Process.Variables.Cleaning.RxTimeWaterDrainOut					=	((Process.Variables.ReceivedData[8]<<8)  + Process.Variables.ReceivedData[9])  * TimerMultiplicationFactor;				// How much water level goes out in drain out
					Process.Variables.Cleaning.RxStirrerOnTimeWaterCycle			=	((Process.Variables.ReceivedData[10]<<8) + Process.Variables.ReceivedData[11]) * TimerMultiplicationFactor * Minutes;	// How much time Water Stirrer rotate (in Mins)

					break;
				}

				default:
					break;
				}
			}

			default:
				break;

			}

			Process.Flags.Cleaning.ProcessEnable					=	SET;
			Process.Variables.InitProcess							= 	Cleaning;

			Process.Flags.Water.ProcessEnable						=	SET;
			Process.Variables.Water.Temperature.RxValue				=	90;

			SendAckowledgement(Three, Process.Variables.ReceivedData[4]);



		}

		else if (Process.Variables.ReceivedData[1] == Four)		// Hot Water Process Enable
		{
			Process.Variables.HotWater.RxOnTime			=	((Process.Variables.ReceivedData[4]<<8) + Process.Variables.ReceivedData[5]);
			Process.Flags.HotWater.ProcessEnable		=	SET;
			Process.Flags.HotWater.ProcessCompleted		=	RESET;

			SendAckowledgement(Four, 0);
		}

		else if (	(Process.Variables.ReceivedData[1] 	== StatusID)
				or (Process.Variables.ReceivedData[1] 	== CleaningStatusID)	)
		{
			SendStatus();
		}


		else if (Process.Variables.ReceivedData[1] == StopCommand)
		{
			SendStatus();
			Process.Flags.StopInitiated = SET;
		}


		HAL_GPIO_WritePin(USART_DE_GPIO_Port, USART_DE_Pin, RESET);
		HAL_UART_Receive_IT(&huart2, Process.Variables.ReceivedData, sizeof(Process.Variables.ReceivedData));
	}
}

// ********************************************************************************************* //
// ***************************	 Timer CallBack	******************************************** //
// ********************************************************************************************* //

int Val = 0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
//ifdef (CapacitiveSensorEN)
//	DigitalCap_Read = HAL_GPIO_ReadPin(CAP_READ_GPIO_Port, CAP_READ_Pin);



#if 0

	static int i = 0;

	if (Cap_Counts == 0x01)
	{
		HAL_GPIO_TogglePin(Capacitive_Reset_GPIO_Port, Capacitive_Reset_Pin);
	}
	else if (Cap_Counts == 0x02)
	{
		HAL_GPIO_WritePin(Capacitive_Reset_GPIO_Port, Capacitive_Reset_Pin, RESET);
	}

	else if (Cap_Counts == 0x03)
	{
		Cap_Counts = 0;
		HAL_GPIO_WritePin(Capacitive_Reset_GPIO_Port, Capacitive_Reset_Pin, SET);
		Cap_Read = !(HAL_GPIO_ReadPin(Capacitive_Input_GPIO_Port, Capacitive_Input_Pin));
		Cap_buff[i++] = !(HAL_GPIO_ReadPin(Capacitive_Input_GPIO_Port, Capacitive_Input_Pin));
	}
#endif


#if 0
	if (Cap_Buff_Read)				// If the level is high continuously for 10 readings
	{
		Cap_Flag = SET;
	}

	else if (Cap_Flag)
	{
		if(!Cap_Buff_Read)			//	waiting to get level empty -> This is because when level gets empty then reading shows 0, then suddenly it gets 1
		{
			Cap_Flag_Reset = SET;
			Cap_Flag = RESET;
			//			HAL_GPIO_WritePin(Capacitive_Voltage_GPIO_Port, Capacitive_Voltage_Pin, SET);
		}
	}

	else if(Cap_Flag_Reset)			// This is used to wake up from the sleep mode -> when level is empty but value shows 1
	{
		Cap_WaitSeconds++;

		//		HAL_GPIO_WritePin(Capacitive_Reset_GPIO_Port, Capacitive_Reset_Pin, RESET);
		HAL_GPIO_TogglePin(Capacitive_Reset_GPIO_Port, Capacitive_Reset_Pin);

		//		HAL_GPIO_WritePin(Capacitive_Voltage_GPIO_Port, Capacitive_Voltage_Pin, RESET);
		//		HAL_GPIO_WritePin(Capacitive_Voltage_GPIO_Port, Capacitive_Voltage_Pin, SET);

		if (Cap_WaitSeconds >= 50)
		{
			HAL_GPIO_WritePin(Capacitive_Reset_GPIO_Port, Capacitive_Reset_Pin, RESET);
		}

		else if ( (Cap_WaitSeconds >= 50) and (Cap_WaitSeconds <= 100) )
		{
			Cap_Flag_Reset = RESET;
			Cap_WaitSeconds = 0;
			HAL_GPIO_WritePin(Capacitive_Reset_GPIO_Port, Capacitive_Reset_Pin, SET);
		}

	}

#endif

//	Cap_Counts++;
//
//	static int i = 0;

	/*if (Cap_Counts == 0)
	{
		HAL_GPIO_WritePin(Capacitive_Voltage_GPIO_Port, Capacitive_Voltage_Pin, SET);
	}
	else if ((Cap_Counts >= 1) and (Cap_Counts <= 51) )
	{
		if (Cap_Counts == 1)
		{
			HAL_GPIO_WritePin(Capacitive_Reset_GPIO_Port, Capacitive_Reset_Pin, SET);
		}

		Cap_Read = !(HAL_GPIO_ReadPin(Capacitive_Input_GPIO_Port, Capacitive_Input_Pin));
		Cap_buff[i++] = !(HAL_GPIO_ReadPin(Capacitive_Input_GPIO_Port, Capacitive_Input_Pin));

		if (Cap_Counts == 51)
		{
			HAL_GPIO_WritePin(Capacitive_Reset_GPIO_Port, Capacitive_Reset_Pin, RESET);
			HAL_GPIO_WritePin(Capacitive_Voltage_GPIO_Port, Capacitive_Voltage_Pin, RESET);
			Cap_Counts = 0;
		}
	}*/

#if 0
	if ( (Cap_Counts > 0) and (Cap_Counts <= 20))
	{
		if ((Cap_Read == 0))
		{
			HAL_GPIO_WritePin(Capacitive_Reset_GPIO_Port, Capacitive_Reset_Pin, RESET);
			//			HAL_GPIO_TogglePin(Capacitive_Reset_GPIO_Port, Capacitive_Reset_Pin);

		}
		else
		{
			HAL_GPIO_WritePin(Capacitive_Reset_GPIO_Port, Capacitive_Reset_Pin, SET);
		}

	}
	else if (	(Cap_Counts > 20) and (Cap_Counts <= 50)	)
	{
		HAL_GPIO_WritePin(Capacitive_Reset_GPIO_Port, Capacitive_Reset_Pin, SET);
		//		Cap_Read = !(HAL_GPIO_ReadPin(Capacitive_Input_GPIO_Port, Capacitive_Input_Pin));
		//		Cap_buff[i++] = !(HAL_GPIO_ReadPin(Capacitive_Input_GPIO_Port, Capacitive_Input_Pin));
	}

	else
	{
		Cap_Counts = 0;
	}

	Cap_Read = !(HAL_GPIO_ReadPin(Capacitive_Input_GPIO_Port, Capacitive_Input_Pin));
	Cap_buff[i++] = !(HAL_GPIO_ReadPin(Capacitive_Input_GPIO_Port, Capacitive_Input_Pin));


	if (i == 10)
	{
		i = 0;
		//		HAL_GPIO_WritePin(Capacitive_Reset_GPIO_Port, Capacitive_Reset_Pin, RESET);
		uint8_t Cap_buff_Counts = 0;

		for (int z = 0; z < 10; z++)
		{
			Cap_buff_Counts += Cap_buff[z];
		}

		if (Cap_buff_Counts >= 8)
		{
			Cap_Buff_Read 	= 	SET;
		}
		else if ( (Cap_buff_Counts >= 2) and (Cap_buff_Counts < 8) )
		{
			Cap_Buff_Read	= 0;
		}
		else if (Cap_buff_Counts <= 1)
		{
			Cap_Buff_Read = RESET;

		}

		//		HAL_GPIO_WritePin(Capacitive_Reset_GPIO_Port, Capacitive_Reset_Pin, SET);
	}

#endif
	// ********************************* Milk Stirrer every 10 mins ******************************************* //

#if 0
	if	(	Process.Flags.MilkWater.Stirrer	)		Process.Variables.Milk.StirrerCounts++;

	if (	Process.Variables.Milk.StirrerCounts		>=	10	*	Minutes	*	TimerMultiplicationFactor	)
	{
		if	(	Process.Variables.MilkWater.LevelSensor	)
		{
			Motor_Stirrer_Clkwise();
			Process.Variables.Milk.StirrerCounts		=	RESET;
		}
	}
	else if (	Process.Variables.Milk.StirrerCounts	==	10	*	TimerMultiplicationFactor	)
	{
			Motor_Stirrer_Stop();
	}
#endif

	// *************************** Milk Level Goes Up and then Start the Stirrer Motor ***************************************** //

#if 0

	if(Process.Flags.MilkWater.TimerMilkLevelUp)			// Not Required
	{
		Process.Variables.Milk.LevelUpCounts++;

		if (Process.Variables.Milk.LevelUpCounts 		>=	Process.Variables.Milk.RxLevelUp)
		{
			Motor_Milk_Stop();
			Process.Variables.Milk.LevelUpCounts		= 	RESET;
			Process.Flags.MilkWater.TimerMilkLevelUp 	= 	RESET;
		}

	}

	else if(Process.Flags.MilkWater.Stirrer)
	{
		if (Process.Flags.MilkWater.LevelFilledandStirrerCounts == Two)
		{
			Process.Variables.Milk.StirrerCounts++;
		}

		if (Process.Variables.Milk.StirrerCounts 		>= 	Process.Variables.Milk.RxStirrerWaitTime)
		{
			Motor_Stirrer_Clkwise();

			if(Process.Variables.Milk.StirrerCounts 	>= 	(Process.Variables.Milk.RxStirrerWaitTime + Process.Variables.Milk.RxStirrerTime))
			{
				Motor_Stirrer_Stop();
				Process.Flags.MilkWater.Stirrer 		= 	RESET;
				Process.Variables.Milk.StirrerCounts 	= 	RESET;
			}
		}
		else
		{
			Motor_Stirrer_Stop();
		}
	}
#endif


	// ********************************************************************************************* //
	// **********************  Fill More Than the Required Level  ****************************** //
	// ********************************************************************************************* //

	if (Process.Flags.Cleaning.TimerEnable_Pril)
	{
		Process.Variables.Cleaning.TimerCounts_MotorLevelUp++;
	}


	else if (Process.Flags.Cleaning.TimerEnable_Water)
	{
		Process.Variables.Cleaning.TimerCounts_MotorLevelUp++;
	}



	// ********************************************************************************************* //
	// **********************  Stirrer Motor Enable  *************************************** //
	// ********************************************************************************************* //

	else if (Process.Flags.Cleaning.TimerEnable_StirrerPril)
	{

		if	( (Process.Variables.Cleaning.TimerCounts_StirrerPril % (2 * TimerMultiplicationFactor * Minutes))	==  RESET	)		// for every even minutes -> Stirrer Toggles
		{
			Process.Flags.Cleaning.StirrerDirectionToggle	= 	SET;
		}

		else if (	(Process.Variables.Cleaning.TimerCounts_StirrerPril % (1 * TimerMultiplicationFactor * Minutes))	==  RESET)		// in every odd minutes -> Stirrer Same Direction
		{
			Process.Flags.Cleaning.StirrerDirectionToggle	= 	RESET;
		}


		Process.Variables.Cleaning.TimerCounts_StirrerPril++;
		//		Process.Variables.Cleaning.TimerCounts_StirrerToggling = 2 * TimerMultiplicationFactor;

		switch(Process.Flags.Cleaning.StirrerDirectionToggle)
		{
		case	SET:
		{
			static int counts;

			counts++;

			if (	(counts > 0) 		and	(counts <= 20)	)
			{
				Motor_Stirrer_Clkwise();
			}
			else if ((	counts > 20) 	and (counts <= 30)	)
			{
				Motor_Stirrer_Stop();
			}
			else if ((	counts > 30) 	and (counts <= 50)	)
			{
				Motor_Stirrer_AntiClkwise();
			}
			else if ((	counts > 50) 	and (counts <= 60)	)
			{
				Motor_Stirrer_Stop();
			}
			else if ( counts > 60	)
			{
				counts = RESET;
			}

			break;
		}

		case	RESET:
		{
			Motor_Stirrer_AntiClkwise();
			break;
		}

		default:
			break;
		}

	}


	else if (Process.Flags.Cleaning.TimerEnable_StirrerWater)
	{
		if		(	(Process.Variables.Cleaning.TimerCounts_StirrerWater %	(2 * TimerMultiplicationFactor * Minutes))	==  RESET)		// for every even minutes -> Stirrer Toggles
		{
			Process.Flags.Cleaning.StirrerDirectionToggle	= 	SET;
		}

		else if (	(Process.Variables.Cleaning.TimerCounts_StirrerWater %	(1 * TimerMultiplicationFactor * Minutes))	==  RESET)		// in every odd minutes -> Stirrer Same Direction
		{
			Process.Flags.Cleaning.StirrerDirectionToggle	= 	RESET;
		}


		Process.Variables.Cleaning.TimerCounts_StirrerWater++;


		switch(Process.Flags.Cleaning.StirrerDirectionToggle)
		{
		case	SET:
		{
			static int counts;

			counts++;

			if (	(counts > 0) 		and		(counts <= 20)	)
			{
				Motor_Stirrer_Clkwise();
			}

			else if ((	counts > 20) 	and 	(counts <= 30)	)
			{
				Motor_Stirrer_Stop();
			}


			else if ((	counts > 30) 	and 	(counts <= 50)	)
			{
				Motor_Stirrer_AntiClkwise();
			}

			else if ((	counts > 50) 	and 	(counts <= 60)	)
			{
				Motor_Stirrer_Stop();
			}

			else if ( counts > 60	)
			{
				counts = RESET;
			}

			break;
		}

		case	RESET:
		{
			Motor_Stirrer_AntiClkwise();
			break;
		}

		default:
			break;
		}
	}



	// ********************************************************************************************* //
	// *****************  Drain Out Water from Cleaning Pipe  *********************************** //
	// ********************************************************************************************* //

	else if (Process.Flags.Cleaning.TimerEnable_DrainOut_Pril)
	{
		Process.Variables.Cleaning.TimerCounts_DrainOut_Pril++;

		if(Process.Variables.Cleaning.TimerCounts_DrainOut_Pril >= 	Process.Variables.Cleaning.RxTimePrilDrainOut)
		{
			Process.Flags.Cleaning.LevelEmptied					= 	SET;
			Process.Flags.Cleaning.TimerEnable_DrainOut_Pril 	=	RESET;
			Motor_Milk_Stop();
		}
	}


	else if (Process.Flags.Cleaning.TimerEnable_DrainOut_Water)
	{

		Process.Variables.Cleaning.TimerCounts_DrainOut_Water++;

		if (Process.Variables.Cleaning.TimerCounts_DrainOut_Water >= Process.Variables.Cleaning.RxTimeWaterDrainOut)
		{
			Motor_Milk_Stop();
			Process.Flags.Cleaning.LevelEmptied 				=	SET;
			Process.Flags.Cleaning.TimerEnable_DrainOut_Water 	= 	RESET;
		}
	}



	// ********************************************************************************************* //
	// *************************  Hot Water Counts  *********************************** //
	// ********************************************************************************************* //

	if (Process.Flags.HotWater.TimerEnable)
	{
		Process.Variables.HotWater.TimerCounts++;

		if (Process.Variables.HotWater.TimerCounts >= Process.Variables.HotWater.RxOnTime)
		{
			Motor_HotWater_Stop();
//			Process.Variables.HotWater.TimerCounts 	= 	RESET;		// Disable in Send_Status
			Process.Flags.HotWater.TimerEnable		= 	RESET;
			Process.Flags.HotWater.ProcessCompleted	=	SET;
		}
	}

}
