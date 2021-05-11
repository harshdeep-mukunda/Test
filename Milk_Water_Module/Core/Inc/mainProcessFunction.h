/*
 * mainProcessFUnction.h
 *
 *  Created on: Oct 27, 2020
 *      Author: Naveen
 */

#ifndef INC_MAINPROCESSFUNCTION_H_
#define INC_MAINPROCESSFUNCTION_H_

#include <main.h>
#include <mainProcessVariables.h>

extern ADC_HandleTypeDef hadc;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart2;

void SendAckowledgement(uint8_t ProcessID, uint8_t ProcessStep);
void SendStatus(void);

void LevelSensor_DrainOutPrilFromMilkPipe(void);
void LevelSensor_DrainOutWaterFromMilkPipe(void);

void Motor_Milk_Clkwise(void);
void Motor_Milk_AntiClkwise(void);
void Motor_Milk_Stop(void);

void Motor_MilkWater_Clkwise(void);
void Motor_MilkWater_AntiClkwise(void);
void Motor_MilkWater_Stop(void);

void Motor_Water_Clkwise(void);
void Motor_Water_Stop(void);

void Motor_CleaningWater_Clkwise(void);
void Motor_CleaningWater_Stop(void);

void Motor_Stirrer_Clkwise(void);
void Motor_Stirrer_AntiClkwise(void);
void Motor_Stirrer_Stop(void);

void Motor_HotWater_Clkwise(void);
void Motor_HotWater_Stop(void);

void SSRHeater_ON_MilkWater(void);
void SSRHeater_OFF_MilkWater(void);

void SSRHeater_ON_Water(void);
void SSRHeater_OFF_Water(void);



float LevelSensor_Read(uint8_t Channel);

void LevelSensor_CheckForMilkWater(void);

void LevelSensor_CheckForWater(void);

void Temperature_CheckForMilkWater(void);
void Temperature_CheckForWater(void);

void LevelSensor_CheckForWaterCleaning(void);
void LevelSensor_CheckForPrilCleaning(void);

void	LevelSensor_CheckForOnlyMilkWater	(void);
void 	Temperature_CheckForOnlyMilkWater(void);

#endif /* INC_MAINPROCESSFUNCTION_H_ */
