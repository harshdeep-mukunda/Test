/*
 * mainIT_CallBackFunctions.h
 *
 *  Created on: Nov 5, 2020
 *      Author: Naveen
 */

#ifndef INC_MAINIT_CALLBACKFUNCTIONS_H_
#define INC_MAINIT_CALLBACKFUNCTIONS_H_


extern ADC_HandleTypeDef hadc;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart2;

void HAL_UART_CpltCallback(void);

#endif /* INC_MAINIT_CALLBACKFUNCTIONS_H_ */
