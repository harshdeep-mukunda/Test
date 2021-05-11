/*
 * DS.h
 *
 *  Created on: Nov 18, 2020
 *      Author: Naveen
 */

#ifndef INC_DS_H_
#define INC_DS_H_


#include <main.h>
#include <mainProcessVariables.h>



int _write(int file, char *ptr, int len);
void delay (uint16_t time);
void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

void DS_Start (void);
void DS_Read (void);
void DS_Write (uint8_t data);

#endif /* INC_DS_H_ */
