/*
 * Digital_Sensor.h
 *
 *  Created on: Oct 27, 2020
 *      Author: Naveen
 */

#ifndef INC_DIGITAL_SENSOR_H_
#define INC_DIGITAL_SENSOR_H_


#include <main.h>


int _write(int file, char *ptr, int len);
void delay (uint16_t time);
void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);


uint8_t DS_MilkWater_Start (void);
uint8_t DS_Milk_Start (void);
uint8_t DS_Water_Start (void);

void DS_MilkWater_Write (uint8_t data);
void DS_Milk_Write (uint8_t data);
void DS_Water_Write (uint8_t data);

uint8_t DS_MilkWater_Read (void);
uint8_t DS_Milk_Read (void);
uint8_t DS_Water_Read (void);

float DigitalSensor_Read_MilkWater(void);
float DigitalSensor_Read_Water(void);
float DigitalSensor_Read_Milk(void);


#endif /* INC_DIGITAL_SENSOR_H_ */
