/*
 * ProcessVariables.h
 *
 *  Created on: Oct 27, 2020
 *      Author: Naveen
 */

#ifndef INC_MAINPROCESSVARIABLES_H_
#define INC_MAINPROCESSVARIABLES_H_

#include "main.h"

// *******************************************************************//
// ******************* Numbering the InitProcess *****************//
// *******************************************************************//

#define TimerMultiplicationFactor	10U
#define Minutes						60U

#define LevelBuffer					10U
#define ReceivedUsartPulses			64U
#define MaxTemperatureValue			90U


#define	CutoffMinimumValue					0.1
#define	CutoffMaximumValue 					3.15
#define AverageValue						1.65

int Temperature_PreviousValue_Milk;
int Temperature_NextValue_Milk;

int Temperature_PreviousValue_MilkWater;
int Temperature_NextValue_MilkWater;

int Temperature_PreviousValue_Water;
int Temperature_NextValue_Water;

uint8_t LevelFlag;
typedef enum
{
	One = 1,
	Two,
	Three,
	Four,
	Five,

}ProcessNum_def_t;

typedef enum
{
	Milk = 1,
	Milk_Water,
	Water,
	Cleaning,
	HotWater,
	Idle,
	Error,
	Stop
}ProcessInit_def_t;


typedef enum
{
	Channel_Milk = 10,
	Channel_MilkWater = 11,
	Channel_Water = 7
}ADC_Chanel_def_t;



typedef enum
{
	False 	= 	0,
	True 	= 	1
}Flags_def_t;

typedef enum
{

	StartByte			= 	0x13,
	ModuleID 			= 	0x01,
	MainController 		= 	0x01,
	Destination 		= 	0x02,
	StatusID 			= 	0x05,
	CleaningStatusID 	= 	0x06,
	StopCommand 		= 	0x07,
	EndByte 			= 	0x12,

}USARTBytes_def_t;

typedef enum
{
	PrilCleaning = 1,
	WaterCleaning,

	CheckForLevel,
	FillMoreThanRequiredLevel,
	StirrerMotor,
	CheckForLastPrilSteps,
	CheckForLastWaterSteps,
	SendAcknowledgement,


	PrilCleaning_FirstCycle = 1,
	PrilCleaning_OtherCycles,
	WaterCleaning_FirstCycle = 1,
	WaterCleaning_OtherCycles


}CleaningCycle_def_t;

#if 0

typedef enum
{

	CheckForMilkWaterLevel = 1,
	CheckForTemperature

}MilkWater_def_t;

#endif

typedef enum
{
	Lower = 1,
	Middle,
	Higher
}MilkTemp_def_t;



// *********************************************************************** //
//	********** All Process Flags are included here  ***************** //
// *********************************************************************** //


typedef struct
{
	uint_fast8_t Count:1;
	uint_fast8_t ProcessEnable:1;
	uint_fast8_t SSRHeater:1;
	uint_fast8_t InitTemp:1;
	uint_fast8_t Stirrer:1;
	uint_fast8_t TimerMilkLevelUp:1;
	uint_fast8_t LevelFilledandStirrerCounts:2;
	uint_fast8_t LevelFilledandStirrerStart:1;

}Flags_MilkWater_def_t;

typedef struct
{
	uint_fast8_t Count:1;
	uint_fast8_t ProcessEnable:1;
	uint_fast8_t ProcessEnableMilkWater:1;
	uint_fast8_t SSRHeater:1;

}Flags_Water_def_t;

typedef struct
{
	uint_fast8_t Count:1;
	uint_fast8_t ProcessEnable:1;
	uint_fast8_t ProcessBusy:1;

	uint_fast8_t ProcessOngoing_Pril:3;	// whether any process is ongoing or not
	uint_fast8_t ProcessOngoing_Water:3;	// whether any process is ongoing or not
	uint_fast8_t ProcessCompleted_Pril:1;	// whether any process is ongoing or not
	uint_fast8_t ProcessCompleted_Water:1;	// whether any process is ongoing or not

	uint_fast8_t TimerEnable_Pril:1;
//	uint_fast8_t ProcessInitiate_Pril:1;


	uint_fast8_t LevelEmptied:1;
	uint_fast8_t LevelFilled_Pril:1;
	uint_fast8_t LevelFilled_Water:1;

	uint_fast8_t TimerEnable_Water:1;
	uint_fast8_t TimerEnable_DrainOut_Pril:1;
	uint_fast8_t TimerEnable_DrainOut_Water:1;
	uint_fast8_t TimerDisable_Water:1;
	uint_fast8_t TimerDisable_WaterDrainOut:1;
//	uint_fast8_t ProcessInitiate_Water:1;

	uint_fast8_t StirrerDirectionToggle:1;
	uint_fast8_t TimerEnable_StirrerPril:1;
	uint_fast8_t TimerEnable_StirrerWater:1;
	uint_fast8_t TimerDisable_StirrerPril:1;
	uint_fast8_t TimerDisable_StirrerWater:1;
	uint_fast8_t StirrerCompleted:1;
}Flags_Cleaning_def_t;

typedef struct
{
	uint_fast8_t Count:1;
	uint_fast8_t ProcessEnable:1;
	uint_fast8_t ProcessCompleted:1;
	uint_fast8_t TimerEnable:1;

}Flags_HotWater_def_t;

// *********************************************************************** //
//	********** All Process Variables are included here  ***************** //
// *********************************************************************** //

typedef struct
{
	float Read;
	uint_fast8_t RangeValue;
	uint_fast8_t RxValue;
	uint_fast8_t RxInitTemp;
	uint_fast8_t RxHighValue;
	uint_fast8_t RxMiddleValue;
	uint_fast8_t RxLowValue;

}Temperature_Milk_def_t;

typedef struct
{
	float Read;
	uint_fast8_t RxHighValue;
	uint_fast8_t RxMiddleValue;
	uint_fast8_t RxLowValue;
	uint_fast8_t RxInitTemp;
}Temperature_MilkWater_def_t;

typedef struct
{
	float Read;
	uint_fast8_t RxValue;
	uint_fast8_t RxMilkWaterValue;
}Temperature_Water_def_t;



typedef struct
{
	Temperature_MilkWater_def_t	Temperature;
//	uint8_t LevelSensor;
	float LevelSensor;

//	uint_fast8_t LevelSensor_temp[LevelBuffer];
	float LevelSensor_temp[LevelBuffer];

}Variables_MilkWater_def_t;

typedef struct
{
	Temperature_Water_def_t	Temperature;
//	uint8_t LevelSensor;
	float LevelSensor;

//	uint_fast8_t LevelSensor_temp[LevelBuffer];
	float LevelSensor_temp[LevelBuffer];

}Variables_Water_def_t;

typedef struct
{
	Temperature_Milk_def_t Temperature;

	uint_fast8_t 	LevelSensor;
	uint_fast8_t 	LevelSensor_temp[LevelBuffer];

	uint_fast8_t 	LevelSensor_Float;
	uint_fast8_t 	LevelSensor_temp_Float[LevelBuffer];

	uint_fast8_t 	LevelSensor_OpampProtection;
	uint_fast8_t 	LevelSensor_temp_OpampProtection[LevelBuffer];

	uint_fast8_t 	RxStirrerTime;
	uint_fast8_t 	RxStirrerWaitTime;
	uint_fast8_t 	StirrerCounts;

	uint_fast8_t 	LevelUpCounts;
	uint_fast8_t 	RxLevelUp;
	uint_fast8_t	Capacitive_Error;
}Variables_Milk_def_t;



typedef struct
{
	uint_fast8_t InitProcess;	// Processwise Pril or Water Cleaning
	uint_fast8_t ProcessExeCounts;	// Processwise Pril or Water Cleaning

	uint_fast8_t ProcessExecution;	// Stepwise Execution
//	uint8_t LevelSensor;
	float LevelSensor;

	uint_fast8_t TimerCounts_MotorLevelUp;

	uint_fast16_t RxTimerCounts_StirrerToggling_Pril;
	uint_fast16_t RxTimerCounts_StirrerToggling_Water;
	uint_fast16_t TimerCounts_StirrerToggling;
	uint_fast8_t TimerCounts_StirrerPril;
	uint_fast8_t TimerCounts_StirrerWater;

	uint_fast8_t TimerCounts_DrainOut_Pril;
	uint_fast8_t TimerCounts_DrainOut_Water;

	uint_fast8_t RxLevelUp_Pril;
	uint_fast8_t RxLevelUp_Water;

	uint_fast8_t RxRepeatProcessCounts;

	uint_fast8_t RxTimePrilDrainOut;
	uint_fast8_t RxTimeWaterDrainOut;

	uint_fast16_t StirrerOnTime;

	uint_fast16_t RxStirrerOnTimePrilFirstCycle;
	uint_fast16_t RxStirrerOnTimePrilSecondCycle;
	uint_fast16_t RxStirrerOnTimeWaterCycle;

	uint_fast8_t RxTotalCycles:2;
}Variables_Cleaning_def_t;


typedef struct
{
	uint_fast8_t TimerCounts;
	uint_fast8_t RxOnTime;

}Variables_HotWater_def_t;


// *************************************************************************//
// *************** Common Process Flags and Variables *******************//
// *********************************************************************** //
typedef struct
{
	Flags_MilkWater_def_t	MilkWater;
	Flags_Water_def_t 		Water;
	Flags_Cleaning_def_t 	Cleaning;
	Flags_HotWater_def_t	HotWater;
	uint_fast8_t			UART_Enable:1;
	uint_fast8_t			Status_Enable;
	uint_fast8_t			StopInitiated:1;

	uint_fast8_t			ErrorGenerated:1;
}ProcessFlags_def_t;

typedef struct
{
	Variables_Milk_def_t		Milk;
	Variables_MilkWater_def_t	MilkWater;
	Variables_Water_def_t 		Water;
	Variables_Cleaning_def_t 	Cleaning;
	Variables_HotWater_def_t	HotWater;


	uint8_t InitProcess;

	uint8_t RxCounts;
	uint8_t ReceivedData[64];
	uint8_t TimerPrintCounts;
}ProcessVariables_def_t;

// *********************************************************************** //
// ******************** Processes *********************************//
// *********************************************************************** //

typedef struct
{
	ProcessVariables_def_t	Variables;
	ProcessFlags_def_t		Flags;
}Process_def_t;


Process_def_t	Process;


typedef struct
{
	uint8_t Milk;
	uint8_t MilkWater;
	uint8_t Water;
}DigitalResponse_def_t;

typedef struct
{
	uint8_t TempMilk[1];
	uint8_t TempMilkWater[1];
	uint8_t TempWater[1];
}DigitalReadInit_def_t;

typedef struct
{

	float Milk;
	float MilkWater;
	float Water;
}DigitalReadData_def_t;


typedef struct
{
	DigitalResponse_def_t 	Response;
	DigitalReadInit_def_t	ReadInit;
	DigitalReadData_def_t	ReadData;

	uint8_t ReadFlag;
}DigitalSensor_def_t;

DigitalSensor_def_t	DigitalSensor;

#endif /* INC_MAINPROCESSVARIABLES_H_ */
