/*
 * mainProcess.h
 *
 *  Created on: Oct 27, 2020
 *      Author: Naveen
 */

#ifndef INC_MAINPROCESS_H_
#define INC_MAINPROCESS_H_

#include <main.h>
#include <mainProcessVariables.h>
#include <mainProcessFunction.h>
#include <Digital_Sensor.h>

extern ADC_HandleTypeDef hadc;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart2;


void StartProcess(void);
void TestProcess(void);


#endif /* INC_MAINPROCESS_H_ */
