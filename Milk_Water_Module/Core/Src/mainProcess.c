#include "main.h"
#include <mainProcessFunction.h>
#include <mainProcessVariables.h>
#include <Digital_Sensor.h>
#include <mainIT_CallBackFunctions.h>


extern	ADC_HandleTypeDef	hadc;
extern	TIM_HandleTypeDef 	htim1;
extern	TIM_HandleTypeDef 	htim3;
extern	UART_HandleTypeDef 	huart2;


void	StartProcess	(	void	)
{

	switch	(	Process.Variables.InitProcess	)
	{

	// ********************************************************************************************* //
	// ***************************	MilkWater Cycle		******************************************** //
	// ********************************************************************************************* //

	case	Milk_Water	:
	{
		Process.Flags.MilkWater.Count 	=	SET	;

		if(Process.Flags.MilkWater.ProcessEnable)
		{
			LevelSensor_CheckForMilkWater	()	;
			Temperature_CheckForMilkWater	()	;

			if	(	Process.Variables.Milk.LevelSensor	)	Process.Flags.MilkWater.Stirrer	=	SET;

		}

		Process.Variables.InitProcess	=	Idle;

		break;
	}

	// ********************************************************************************************* //
	// *****************************	Water Cycle		******************************************** //
	// ********************************************************************************************* //

	case	Water	:
	{
		Process.Flags.Water.Count 		= 	SET	;

		if	(	Process.Flags.Water.ProcessEnable	)
		{

			LevelSensor_CheckForWater	()		;
			Temperature_CheckForWater	()		;

			if	(	Process.Flags.Water.ProcessEnableMilkWater	)
			{
				LevelSensor_CheckForOnlyMilkWater	()	;
				Temperature_CheckForOnlyMilkWater	()	;
			}

		}

		Process.Variables.InitProcess 	= 	Idle;

		break;
	}


	// ********************************************************************************************* //
	// *************************** 	Cleaning Cycle	******************************************** //
	// ********************************************************************************************* //

	case	Cleaning	:
	{
		Process.Flags.Cleaning.Count = SET	;

		if	(	Process.Flags.Cleaning.ProcessEnable	)
		{
			Process.Flags.Cleaning.ProcessCompleted_Pril	= 	RESET	;
			Process.Flags.Cleaning.ProcessCompleted_Water	= 	RESET	;

//			if(Process.Variables.MilkWater.Temperature.Read < MaxTemperatureValue)	SSRHeater_ON_MilkWater()	;
//			else																	SSRHeater_OFF_MilkWater()	;


			switch	(	Process.Variables.Cleaning.InitProcess	)
			{
			case	PrilCleaning	:
			{
				switch	(	Process.Variables.Cleaning.ProcessExecution	)
				{
				case	CheckForLevel	:
				{
					LevelSensor_CheckForPrilCleaning()	;
					Process.Flags.Cleaning.ProcessOngoing_Pril 	= 	One								;

					if(	Process.Flags.Cleaning.LevelFilled_Pril	)
					{
						Process.Flags.Cleaning.LevelFilled_Pril 	= 	RESET						;
						Process.Variables.Cleaning.ProcessExecution =	FillMoreThanRequiredLevel	;
					}
					break	;
				}

				case	FillMoreThanRequiredLevel	:
				{

					Motor_Milk_Clkwise	()												;
					Process.Flags.Cleaning.TimerEnable_Pril			= 	SET				;
					Process.Flags.Cleaning.ProcessOngoing_Pril 		= 	Two				;

					if (Process.Variables.Cleaning.TimerCounts_MotorLevelUp >= Process.Variables.Cleaning.RxLevelUp_Pril)
					{

						Process.Variables.Cleaning.TimerCounts_MotorLevelUp	= 	RESET	;
						Process.Flags.Cleaning.TimerEnable_Pril 	= 	RESET			;
						Process.Variables.Cleaning.ProcessExecution = 	StirrerMotor	;


						Motor_Milk_Stop	()												;
					}
					break;
				}

				case	StirrerMotor	:
				{
					//					Motor_Milk_Stop();
					Process.Flags.Cleaning.TimerEnable_StirrerPril = SET								;

					switch	(	Process.Variables.Cleaning.ProcessExeCounts	)
					{
					case	One	:
					{		// This will execute only in First Cycle
						if(Process.Variables.Cleaning.TimerCounts_StirrerPril 	>= 	Process.Variables.Cleaning.RxStirrerOnTimePrilFirstCycle)
						{
							Motor_Stirrer_Stop()														;

							Process.Flags.Cleaning.TimerEnable_StirrerPril 		= 	RESET				;
							Process.Variables.Cleaning.TimerCounts_StirrerPril 	= 	RESET				;
							Process.Variables.Cleaning.ProcessExecution 		= 	SendAcknowledgement	;

						}

						break;
					}

					default:
					{
						if(Process.Variables.Cleaning.TimerCounts_StirrerPril >= Process.Variables.Cleaning.RxStirrerOnTimePrilSecondCycle)
						{
							Motor_Stirrer_Stop	()															;

							Process.Flags.Cleaning.TimerEnable_StirrerPril		= 	RESET					;
							Process.Variables.Cleaning.TimerCounts_StirrerPril 	= 	RESET					;
							Process.Variables.Cleaning.ProcessExecution 		=	CheckForLastPrilSteps	;

						}

						break;
					}

					}

					Process.Flags.Cleaning.ProcessOngoing_Pril 			= 	Three					;

					break	;
				}

				case	CheckForLastPrilSteps	:
				{

					if	(	Process.Flags.Cleaning.LevelEmptied	)
					{
						Motor_Milk_Stop	()																;

						Process.Flags.Cleaning.LevelEmptied						= 	RESET				;
						Process.Variables.Cleaning.ProcessExecution 			= 	SendAcknowledgement	;

					}

					else
					{
						LevelSensor_DrainOutPrilFromMilkPipe	()										;
						Process.Flags.Cleaning.ProcessOngoing_Pril 				= 	Four				;
					}

					break;
				}

				case	SendAcknowledgement	:
				{

					Process.Flags.Cleaning.ProcessEnable 			=	RESET							;
					Process.Flags.Cleaning.ProcessCompleted_Pril	=	SET								;
					Process.Flags.Cleaning.ProcessOngoing_Pril 		=	Five							;
					Process.Flags.Cleaning.ProcessBusy				=	RESET							;

					break	;
				}

				default	:
					break	;

				}

				break		;
			}



			case	WaterCleaning	:
			{

				switch	(	Process.Variables.Cleaning.ProcessExecution	)
				{
				case	CheckForLevel	:
				{
					LevelSensor_CheckForWaterCleaning	()											;
					Process.Flags.Cleaning.ProcessOngoing_Water = 	One								;

					if	(	Process.Flags.Cleaning.LevelFilled_Water	)
					{
						Process.Flags.Cleaning.LevelFilled_Water 	= 	RESET						;
						Process.Variables.Cleaning.ProcessExecution = 	FillMoreThanRequiredLevel	;

					}

					break	;
				}

				case 	FillMoreThanRequiredLevel	:
				{
					Motor_CleaningWater_Clkwise	()													;
					Process.Flags.Cleaning.TimerEnable_Water 				= 	SET					;
					Process.Flags.Cleaning.ProcessOngoing_Water 			= 	Two					;

					if (Process.Variables.Cleaning.TimerCounts_MotorLevelUp >= Process.Variables.Cleaning.RxLevelUp_Water)
					{

						Process.Flags.Cleaning.TimerEnable_Water 			= 	RESET				;
						Process.Variables.Cleaning.TimerCounts_MotorLevelUp = 	RESET				;
						Process.Variables.Cleaning.ProcessExecution 		= 	StirrerMotor		;

						Motor_CleaningWater_Stop	()												;
					}

					break	;
				}

				case 	StirrerMotor	:
				{

					Process.Flags.Cleaning.TimerEnable_StirrerWater			=	SET						;

					if(Process.Variables.Cleaning.TimerCounts_StirrerWater	>= 	Process.Variables.Cleaning.RxStirrerOnTimeWaterCycle)
					{

						Process.Flags.Cleaning.TimerEnable_StirrerWater 	= 	RESET					;
						Process.Variables.Cleaning.TimerCounts_StirrerWater = 	RESET					;

						Motor_Stirrer_Stop	()															;

						switch(Process.Variables.Cleaning.ProcessExeCounts)
						{
						case	2	:
						{		// This will execute only for Second Cycle which will be always Water
							Process.Variables.Cleaning.ProcessExecution 	=	SendAcknowledgement		;
							break;
						}

						default		:
						{		// For 4 and 5 cycle
							Process.Variables.Cleaning.ProcessExecution 	= 	CheckForLastWaterSteps	;
							break;
						}

						}

					}

					Process.Flags.Cleaning.ProcessOngoing_Water 	= 	Three							;

					break;
				}

				case 	CheckForLastWaterSteps	:
				{

					if	(	Process.Flags.Cleaning.LevelEmptied	)
					{
						Motor_Milk_Stop	()																;

						Process.Flags.Cleaning.LevelEmptied 					= 	RESET				;
						Process.Variables.Cleaning.TimerCounts_DrainOut_Water 	= 	RESET				;
						Process.Variables.Cleaning.ProcessExecution 			= 	SendAcknowledgement	;
					}
					else
					{
						LevelSensor_DrainOutWaterFromMilkPipe	()										;
						Process.Flags.Cleaning.ProcessOngoing_Water 			= 	Four				;
					}

					break;
				}

				case	SendAcknowledgement	:
				{

					Process.Flags.Cleaning.ProcessEnable 			= 	RESET	;
					Process.Flags.Cleaning.ProcessCompleted_Water	= 	SET		;
					Process.Flags.Cleaning.ProcessOngoing_Water 	= 	Five	;
					Process.Flags.Cleaning.ProcessBusy				=	RESET	;

					SSRHeater_OFF_MilkWater	()									;

					break	;
				}

				default	:
					break	;
				}
				break		;
			}

			default:
				break;
			}
		}




		if	(	Process.Variables.MilkWater.LevelSensor	)
		{
			Motor_MilkWater_Stop	()							;
		}

		else
		{
			Motor_MilkWater_Clkwise	()						;
		}


		Process.Variables.InitProcess = Idle				;
		break	;
	}

	// ********************************************************************************************* //
	// ***************************  HotWater Cycle  	******************************************** //
	// ********************************************************************************************* //

	case	HotWater:
	{
		Process.Flags.HotWater.Count = SET;

		if(Process.Flags.HotWater.ProcessEnable)
		{
			Motor_HotWater_Clkwise();
			Process.Flags.HotWater.TimerEnable = SET;
			Process.Flags.HotWater.ProcessEnable = RESET;
		}

		Process.Variables.InitProcess = Idle;
		break;
	}

	// ********************************************************************************************* //
	// ***************************	 Idle State		******************************************** //
	// ********************************************************************************************* //
	case	Idle:
	{

		static int counts = 0;

		Process.Variables.Milk.LevelSensor_temp_OpampProtection[counts]	=	not	(HAL_GPIO_ReadPin(Milk_LevelSensor_OpampProtection_GPIO_Port, Milk_LevelSensor_OpampProtection_Pin));
		Process.Variables.Milk.LevelSensor_temp_Float[counts]	=			(HAL_GPIO_ReadPin(Milk_FloatSensor_GPIO_Port, Milk_FloatSensor_Pin));
//		Process.Variables.Milk.LevelSensor_temp[counts] 	 =	not	(HAL_GPIO_ReadPin(Balloff_Read_GPIO_Port, Balloff_Read_Pin));

		Process.Variables.MilkWater.LevelSensor_temp[counts] =	not	(HAL_GPIO_ReadPin(MilkWater_Level_GPIO_Port, MilkWater_Level_Pin));
		Process.Variables.Water.LevelSensor_temp[counts++]	 =  	(HAL_GPIO_ReadPin(Water_LevelSensor_GPIO_Port, Water_LevelSensor_Pin));
		//		Process.Variables.Water.LevelSensor_temp[counts++]	 =  (HAL_GPIO_ReadPin(ADC_Water_Level_GPIO_Port, ADC_Water_Level_Pin));


		// ************ For the Second Machine ************************** //
		//		Process.Variables.MilkWater.LevelSensor_temp[counts] = not	(HAL_GPIO_ReadPin(Level_Toggling_1_GPIO_Port, Level_Toggling_1_Pin));
		//		Process.Variables.Milk.LevelSensor_temp[counts] 	 = not	(HAL_GPIO_ReadPin(Level_Toggling_2_GPIO_Port, Level_Toggling_2_Pin));
		//		Process.Variables.Water.LevelSensor_temp[counts++]	 = 		(HAL_GPIO_ReadPin(ADC_Water_Level_GPIO_Port, ADC_Water_Level_Pin));

		// ******************************************************************************* //

		if(counts == LevelBuffer)
		{
			counts 					= 	RESET;
			uint8_t LevelMilk 		= 	RESET;
			uint8_t LevelMilkWater 	= 	RESET;
			uint8_t LevelWater 		= 	RESET;

			uint8_t LevelMilkLevelProtection 	= 	RESET;


			for(int x = 0; x < LevelBuffer; x++)
			{
//				LevelMilk		+= 	Process.Variables.Milk.LevelSensor_temp[x];
				LevelMilk +=	Process.Variables.Milk.LevelSensor_temp_Float[x];

				LevelMilkWater 	+= 	Process.Variables.MilkWater.LevelSensor_temp[x];
				LevelWater 		+= 	Process.Variables.Water.LevelSensor_temp[x];
				LevelMilkLevelProtection +=	Process.Variables.Milk.LevelSensor_temp_OpampProtection[x];

			}


			if	(LevelMilk 		>= 8)					Process.Variables.Milk.LevelSensor					=	SET;
			else										Process.Variables.Milk.LevelSensor					=	RESET;

			if	(LevelMilkWater >= 8)					Process.Variables.MilkWater.LevelSensor				=	SET;
			else										Process.Variables.MilkWater.LevelSensor 			= 	RESET;

			if	(LevelWater 	>= 8)					Process.Variables.Water.LevelSensor					=	SET;
			else										Process.Variables.Water.LevelSensor 				= 	RESET;

			if	(LevelMilkLevelProtection	>=	8)		Process.Variables.Milk.LevelSensor_OpampProtection	=	SET;		// OverProtection step is taken in timer
			else										Process.Variables.Milk.LevelSensor_OpampProtection 	= 	RESET;

		}



		Temperature_NextValue_Milk 							= 	DigitalSensor_Read_Milk();

		if (	(	(Temperature_NextValue_Milk - Temperature_PreviousValue_Milk)			<=		2	)
				or	(	(Temperature_PreviousValue_Milk - Temperature_NextValue_Milk)		<=		2	)	)
		{

			if (	Temperature_NextValue_Milk <= 100	)
				Process.Variables.Milk.Temperature.Read 	= 	Temperature_NextValue_Milk;
			{
				Temperature_PreviousValue_Milk					=	Temperature_NextValue_Milk;
			}

		}
		else
			Process.Variables.Milk.Temperature.Read 		= 	Temperature_PreviousValue_Milk;



		Temperature_NextValue_MilkWater 					= 	DigitalSensor_Read_MilkWater();

		if (	(	(Temperature_NextValue_MilkWater - Temperature_PreviousValue_MilkWater) 	<=		2	)
				or	(	(Temperature_PreviousValue_MilkWater - Temperature_NextValue_MilkWater) <=		2	)	)
		{

			if	(Temperature_NextValue_MilkWater	<=	100	)
				Process.Variables.MilkWater.Temperature.Read 	= 	Temperature_NextValue_MilkWater;

			Temperature_PreviousValue_MilkWater				=	Temperature_NextValue_MilkWater;

		}
		else
			Process.Variables.MilkWater.Temperature.Read 	= 	Temperature_PreviousValue_MilkWater;



		Temperature_NextValue_Water 						= 	DigitalSensor_Read_Water();

		if (	(	(Temperature_NextValue_Water - Temperature_PreviousValue_Water	)		<=		2	)
				or	(	(Temperature_PreviousValue_Water - Temperature_NextValue_Water	)	<=		2	)	)
		{

			if	(Temperature_NextValue_Water	<= 	100	)
				Process.Variables.Water.Temperature.Read 	= 	Temperature_NextValue_Water;

			Temperature_PreviousValue_Water					=	Temperature_NextValue_Water;

		}
		else
			Process.Variables.Water.Temperature.Read 		= 	Temperature_PreviousValue_Water;



		if(Process.Variables.MilkWater.Temperature.Read > MaxTemperatureValue)	SSRHeater_OFF_MilkWater();
		if(Process.Variables.Water.Temperature.Read > MaxTemperatureValue)		SSRHeater_OFF_Water();


		HAL_GPIO_WritePin(USART_DE_GPIO_Port, USART_DE_Pin, RESET);
		HAL_UART_Receive_IT(&huart2, Process.Variables.ReceivedData, sizeof(Process.Variables.ReceivedData));


		if	(Process.Flags.StopInitiated)
		{
			Process.Flags.StopInitiated				=	RESET;
			Process.Variables.InitProcess			=	Stop;
			break;
		}

		/*
		if (Process.Variables.Milk.LevelSensor_OpampProtection)
		{

			Process.Flags.ErrorGenerated			=	SET;
			Process.Variables.InitProcess			=	Stop;

//			Process.Variables.InitProcess			=	Error;

			break;
		}

		 */


		switch(Process.Flags.MilkWater.Count)
		{

		case	SET	:
		{
			switch(Process.Flags.Water.Count)
			{

			case	SET	:
			{

				if	(	Process.Flags.Cleaning.ProcessEnable	)
				{
					Process.Flags.MilkWater.Count 	= 	SET;
					Process.Flags.HotWater.Count 	= 	SET;
					Process.Flags.Water.Count 		= 	RESET;
					Process.Variables.InitProcess 	= 	Cleaning;
				}

				else if	(	(	Process.Flags.HotWater.Count) and (not(Process.Flags.Cleaning.ProcessEnable)	)	)
				{
					Process.Flags.MilkWater.Count 	= 	RESET;
					Process.Flags.Water.Count 		= 	RESET;
					Process.Flags.HotWater.Count 	= 	RESET;
					break;
				}

				else
				{
					Process.Variables.InitProcess	= 	HotWater;
				}

				break;

			}

			case	RESET	:
			{
				Process.Variables.InitProcess = Water;
				break;
			}


			default	:
				break;

			}
			break;
		}


		case	RESET	:
		{
			Process.Variables.InitProcess = Milk_Water;
			break;
		}


		default:
			break;

		}

		break;
	}


	// ********************************************************************************************* //
	// ***************************	 Error State	******************************************** //
	// ********************************************************************************************* //
	case	Error	:
	{
		//				Process.Flags.ErrorGenerated			=	SET		;


		Process.Variables.InitProcess 			= 	Stop	;
		break;
	}


	// ********************************************************************************************* //
	// ***************************	 Halt All Process	******************************************** //
	// ********************************************************************************************* //
	case	Stop	:
	{

		Process.Flags.Water.ProcessEnable 		= 	RESET	;
		Process.Flags.Cleaning.ProcessEnable 	= 	RESET	;
		Process.Flags.MilkWater.ProcessEnable 	= 	RESET	;
		Process.Flags.MilkWater.Count 			= 	RESET	;
		Process.Flags.Water.Count 				= 	RESET	;
		Process.Flags.HotWater.Count 			= 	RESET	;
		Process.Flags.Cleaning.Count 			= 	RESET	;


		SSRHeater_OFF_MilkWater()				;
		SSRHeater_OFF_Water()					;

		Motor_Stirrer_Stop()					;
		Motor_Water_Stop()						;
		Motor_MilkWater_Stop()					;
		Motor_Milk_Stop()						;
		Motor_HotWater_Stop()					;
		Motor_CleaningWater_Stop()				;

		Process.Variables.InitProcess = Idle	;

		break	;
	}


	// ********************************************************************************************* //
	// ***************************	 	xoxox		******************************************** //
	// ********************************************************************************************* //

	default	:
		break;
	}
}


