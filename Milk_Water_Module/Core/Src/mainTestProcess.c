/*
 * mainTestProcess.c
 *
 *  Created on: 18-Nov-2020
 *      Author: Naveen
 */

#include "main.h"
#include <mainProcessFunction.h>
#include <mainProcessVariables.h>

void TestProcess(void)
{
	  // MilkWater DC Motor
//	  Motor_MilkWater_Clkwise();
//	  HAL_Delay(10000);
//	  Motor_MilkWater_Stop();

	  // Milk DC Motor
//	  Motor_Milk_AntiClkwise();
//	  HAL_Delay(5000);
//	  Motor_Milk_Stop();

	Motor_Stirrer_Clkwise();
	HAL_Delay(5000);
	Motor_Stirrer_Stop();
}
