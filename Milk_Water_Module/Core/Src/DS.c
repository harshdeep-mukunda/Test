/*
 * DS.c
 *
 *  Created on: Nov 18, 2020
 *      Author: Naveen
 */


#include <Digital_Sensor.h>
#include <main.h>
#include <stdint.h>
#include <DS.h>
#include <mainProcessVariables.h>

extern TIM_HandleTypeDef htim3;





int _write(int file, char *ptr, int len)
{
	int i = 0;
	for (i=0; i< len; i++ );
	//		ITM_SendChar((*ptr++));
	return len;
}

void delay (uint16_t time)
{
	__HAL_TIM_SET_COUNTER(&htim3, 0);
	while ((__HAL_TIM_GET_COUNTER(&htim3))<time);
}



void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

/*********************************** DS18B20 FUNCTIONS ****************************************/

void DS_Start (void)
{

	DigitalSensor.Response.Milk = 0;
	DigitalSensor.Response.MilkWater = 0;
	DigitalSensor.Response.Water = 0;


	Set_Pin_Output(Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin);
	Set_Pin_Output(Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin);
	Set_Pin_Output(Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin);

	HAL_GPIO_WritePin (Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin, RESET);
	HAL_GPIO_WritePin (Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin, RESET);
	HAL_GPIO_WritePin (Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin, RESET);
	delay (480);

	Set_Pin_Input(Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin);
	Set_Pin_Input(Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin);
	Set_Pin_Input(Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin);
	delay (80);

	if (!(HAL_GPIO_ReadPin (Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin))) DigitalSensor.Response.MilkWater = 1;
	else DigitalSensor.Response.MilkWater = -1;
	if (!(HAL_GPIO_ReadPin (Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin))) DigitalSensor.Response.Milk = 1;
	else DigitalSensor.Response.Milk = -1;
	if (!(HAL_GPIO_ReadPin (Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin))) DigitalSensor.Response.Water = 1;
	else DigitalSensor.Response.Water = -1;

	delay (400);

}


void DS_Read (void)
{
	DigitalSensor.ReadFlag += One;

	if(DigitalSensor.ReadFlag == One)
	{
		DigitalSensor.ReadInit.TempMilk[0] = 0;
		DigitalSensor.ReadInit.TempMilkWater[0] = 0;
		DigitalSensor.ReadInit.TempWater[0] = 0;

		DigitalSensor.ReadInit.TempMilk[1] = 0;
		DigitalSensor.ReadInit.TempMilkWater[1] = 0;
		DigitalSensor.ReadInit.TempWater[1] = 0;
	}

	else if (DigitalSensor.ReadFlag == Two)
	{
		DigitalSensor.ReadInit.TempMilk[1] = 0;
		DigitalSensor.ReadInit.TempMilkWater[1] = 0;
		DigitalSensor.ReadInit.TempWater[1] = 0;
	}


	Set_Pin_Input(Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin);
	Set_Pin_Input(Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin);
	Set_Pin_Input(Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin);


	for (int i=0;i<8;i++)
	{
		Set_Pin_Output(Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin);
		Set_Pin_Output(Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin);
		Set_Pin_Output(Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin);

		HAL_GPIO_WritePin (Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin, RESET);
		HAL_GPIO_WritePin (Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin, RESET);
		HAL_GPIO_WritePin (Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin, RESET);

		delay (1);

		Set_Pin_Input(Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin);
		Set_Pin_Input(Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin);
		Set_Pin_Input(Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin);


		switch(DigitalSensor.ReadFlag)
		{
		case One:
		{
			if (HAL_GPIO_ReadPin (Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin))
			{
				DigitalSensor.ReadInit.TempMilkWater[0] |= 1<<i;
			}
			if (HAL_GPIO_ReadPin (Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin))
			{
				DigitalSensor.ReadInit.TempMilk[0] |= 1<<i;
			}
			if (HAL_GPIO_ReadPin (Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin))
			{
				DigitalSensor.ReadInit.TempWater[0] |= 1<<i;
			}
			break;
		}

		case Two:
		{
			if (HAL_GPIO_ReadPin (Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin))
			{
				DigitalSensor.ReadInit.TempMilkWater[1] |= 1<<i;
			}
			if (HAL_GPIO_ReadPin (Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin))
			{
				DigitalSensor.ReadInit.TempMilk[1] |= 1<<i;
			}
			if (HAL_GPIO_ReadPin (Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin))
			{
				DigitalSensor.ReadInit.TempWater[1] |= 1<<i;
			}

			DigitalSensor.ReadFlag = RESET;

			break;
		}

		default:
			break;
		}

		delay (50);
	}

}


void DS_Write (uint8_t data)
{
	Set_Pin_Output(Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin);
	Set_Pin_Output(Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin);
	Set_Pin_Output(Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin);  // set as output


	for (int i=0; i<8; i++)
	{

		if ((data & (1<<i))!=0)
		{

			Set_Pin_Output(Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin);
			HAL_GPIO_WritePin (Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin, RESET);

			Set_Pin_Output(Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin);
			HAL_GPIO_WritePin (Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin, RESET);

			Set_Pin_Output(Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin);
			HAL_GPIO_WritePin (Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin, RESET);

			delay (1);

			Set_Pin_Input(Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin);
			Set_Pin_Input(Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin);
			Set_Pin_Input(Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin);

			delay (50);
		}

		else
		{


			Set_Pin_Output(Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin);
			HAL_GPIO_WritePin (Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin, RESET);

			Set_Pin_Output(Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin);
			HAL_GPIO_WritePin (Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin, RESET);

			Set_Pin_Output(Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin);
			HAL_GPIO_WritePin (Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin, RESET);

			delay (50);

			Set_Pin_Input(Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin);
			Set_Pin_Input(Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin);
			Set_Pin_Input(Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin);
		}
	}
}






void DigitalSensor_ReadTemperature()
{
	DigitalSensor.ReadData.Milk = 0;
	DigitalSensor.ReadData.MilkWater = 0;
	DigitalSensor.ReadData.Water = 0;

	DS_Start ();
	HAL_Delay (1);
	DS_Write (0xCC);  // skip ROM
	DS_Write (0x44);  // convert t

	HAL_Delay (800);

	DS_Start ();
	HAL_Delay(1);
	DS_Write (0xCC);
	DS_Write (0xBE);

	DS_Read();
	DS_Read();

	DigitalSensor.ReadData.Milk =  ((DigitalSensor.ReadInit.TempMilk[1] << 8) + DigitalSensor.ReadInit.TempMilk[0]) / 16;
	DigitalSensor.ReadData.MilkWater =  ((DigitalSensor.ReadInit.TempMilkWater[1] << 8) + DigitalSensor.ReadInit.TempMilkWater[0]) / 16;
	DigitalSensor.ReadData.Water =  ((DigitalSensor.ReadInit.TempWater[1] << 8) + DigitalSensor.ReadInit.TempWater[0]) / 16;

}

