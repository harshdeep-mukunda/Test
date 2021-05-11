
/*
 * Note:
 * Configure Timer 3 or any other with Configuration:
 * ARR = 48 - 1
 * PSC = 0xFFFF - 1 or 65534
 *
 * Output compare no output
 */

#include <Digital_Sensor.h>
#include <main.h>
#include <stdint.h>

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

uint8_t DS_MilkWater_Start (void)     // Start for First Sensor 0
{
	uint8_t Response = 0;
	Set_Pin_Output(Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin);   // set the pin as output
	HAL_GPIO_WritePin (Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin, RESET);  // pull the pin low
	delay (480);   // delay according to datasheet

	Set_Pin_Input(Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin);    // set the pin as input
	delay (80);    // delay according to datasheet

	if (!(HAL_GPIO_ReadPin (Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin))) Response = 1;    // if the pin is low i.e the presence pulse is detected
	else Response = -1;

	delay (400); // 480 us delay totally.

	return Response;
}


uint8_t DS_MilkWater_Read (void)
{
	uint8_t value=0;

	Set_Pin_Input(Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin);


	for (int i=0;i<8;i++)
	{
		Set_Pin_Output(Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin);   // set as output

		HAL_GPIO_WritePin (Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin, RESET);  // pull the data pin LOW
		delay (1);  // wait for > 1us

		Set_Pin_Input(Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin);  // set as input
		if (HAL_GPIO_ReadPin (Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin))  // if the pin is HIGH
		{
			value |= 1<<i;  // read = 1
		}
		delay (50);  // wait for 60 us
	}
	return value;
}


void DS_MilkWater_Write (uint8_t data)
{
	Set_Pin_Output(Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin);  // set as output

	for (int i=0; i<8; i++)
	{

		if ((data & (1<<i))!=0)  // if the bit is high
		{
			// write 1

			Set_Pin_Output(Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin);  // set as output
			HAL_GPIO_WritePin (Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin, RESET);  // pull the pin LOW
			delay (1);  // wait for 1 us

			Set_Pin_Input(Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin);  // set as input
			delay (50);  // wait for 60 us
		}

		else  // if the bit is low
		{
			// write 0

			Set_Pin_Output(Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin);
			HAL_GPIO_WritePin (Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin, RESET);  // pull the pin LOW
			delay (50);  // wait for 60 us

			Set_Pin_Input(Digital_Temperature_Sensor_MilkWater_GPIO_Port, Digital_Temperature_Sensor_MilkWater_Pin);
		}
	}
}



uint8_t DS_Milk_Start (void)     // Start for First Sensor 0
{
	uint8_t Response = 0;
	Set_Pin_Output(Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin);   // set the pin as output
	HAL_GPIO_WritePin (Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin, RESET);  // pull the pin low
	delay (480);   // delay according to datasheet

	Set_Pin_Input(Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin);    // set the pin as input
	delay (80);    // delay according to datasheet

	if (!(HAL_GPIO_ReadPin (Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin))) Response = 1;    // if the pin is low i.e the presence pulse is detected
	else Response = -1;

	delay (400); // 480 us delay totally.

	return Response;
}


uint8_t DS_Milk_Read (void)
{
	uint8_t value=0;

	Set_Pin_Input(Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin);


	for (int i=0;i<8;i++)
	{
		Set_Pin_Output(Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin);   // set as output

		HAL_GPIO_WritePin (Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin, RESET);  // pull the data pin LOW
		delay (1);  // wait for > 1us

		Set_Pin_Input(Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin);  // set as input
		if (HAL_GPIO_ReadPin (Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin))  // if the pin is HIGH
		{
			value |= 1<<i;  // read = 1
		}
		delay (50);  // wait for 60 us
	}
	return value;
}

void DS_Milk_Write (uint8_t data)
{
	Set_Pin_Output(Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin);  // set as output

	for (int i=0; i<8; i++)
	{

		if ((data & (1<<i))!=0)  // if the bit is high
		{
			// write 1

			Set_Pin_Output(Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin);  // set as output
			HAL_GPIO_WritePin (Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin, RESET);  // pull the pin LOW
			delay (1);  // wait for 1 us

			Set_Pin_Input(Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin);  // set as input
			delay (50);  // wait for 60 us
		}

		else  // if the bit is low
		{
			// write 0

			Set_Pin_Output(Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin);
			HAL_GPIO_WritePin (Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin, RESET);  // pull the pin LOW
			delay (50);  // wait for 60 us

			Set_Pin_Input(Digital_Temperature_Sensor_Milk_GPIO_Port, Digital_Temperature_Sensor_Milk_Pin);
		}
	}
}

uint8_t DS_Water_Start (void)     // Start for First Sensor 0
{
	uint8_t Response = 0;
	Set_Pin_Output(Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin);   // set the pin as output
	HAL_GPIO_WritePin (Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin, RESET);  // pull the pin low
	delay (480);   // delay according to datasheet

	Set_Pin_Input(Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin);    // set the pin as input
	delay (80);    // delay according to datasheet

	if (!(HAL_GPIO_ReadPin (Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin))) Response = 1;    // if the pin is low i.e the presence pulse is detected
	else Response = -1;

	delay (400); // 480 us delay totally.

	return Response;
}




void DS_Water_Write (uint8_t data)
{
	Set_Pin_Output(Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin);  // set as output

	for (int i=0; i<8; i++)
	{

		if ((data & (1<<i))!=0)  // if the bit is high
		{
			// write 1

			Set_Pin_Output(Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin);  // set as output
			HAL_GPIO_WritePin (Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin, RESET);  // pull the pin LOW
			delay (1);  // wait for 1 us

			Set_Pin_Input(Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin);  // set as input
			delay (50);  // wait for 60 us
		}

		else  // if the bit is low
		{
			// write 0

			Set_Pin_Output(Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin);
			HAL_GPIO_WritePin (Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin, RESET);  // pull the pin LOW
			delay (50);  // wait for 60 us

			Set_Pin_Input(Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin);
		}
	}
}



uint8_t DS_Water_Read (void)
{
	uint8_t value=0;

	Set_Pin_Input(Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin);


	for (int i=0;i<8;i++)
	{
		Set_Pin_Output(Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin);   // set as output

		HAL_GPIO_WritePin (Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin, RESET);  // pull the data pin LOW
		delay (1);  // wait for > 1us

		Set_Pin_Input(Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin);  // set as input
		if (HAL_GPIO_ReadPin (Digital_Temperature_Sensor_Water_GPIO_Port, Digital_Temperature_Sensor_Water_Pin))  // if the pin is HIGH
		{
			value |= 1<<i;  // read = 1
		}
		delay (50);  // wait for 60 us
	}
	return value;
}



float DigitalSensor_Read_MilkWater()
{
	float T0 = 0;
	uint8_t Sensor_available = 0;
	uint8_t T0_byte1, T0_byte2;
	uint16_t TEMP0;


	Sensor_available = DS_MilkWater_Start ();
	HAL_Delay (1);
	DS_MilkWater_Write (0xCC);  // skip ROM
	DS_MilkWater_Write (0x44);  // convert t
	HAL_Delay (10);

	Sensor_available = DS_MilkWater_Start ();
	HAL_Delay(1);
	DS_MilkWater_Write (0xCC);
	DS_MilkWater_Write (0xBE);

	T0_byte1 = DS_MilkWater_Read();
	T0_byte2 = DS_MilkWater_Read();
	TEMP0 = (T0_byte2<<8)|T0_byte1;
	T0 = (float)TEMP0/16;

	return T0;
}


float DigitalSensor_Read_Water()
{
	float T0 = 0;
	uint8_t Sensor_available = 0;
	uint8_t T0_byte1, T0_byte2;
	uint16_t TEMP0;


	Sensor_available = DS_Water_Start ();
	HAL_Delay (1);
	DS_Water_Write (0xCC);
	DS_Water_Write (0x44);
	HAL_Delay (10);

	Sensor_available = DS_Water_Start ();
	HAL_Delay(1);
	DS_Water_Write (0xCC);
	DS_Water_Write (0xBE);

	T0_byte1 = DS_Water_Read();
	T0_byte2 = DS_Water_Read();
	TEMP0 = (T0_byte2<<8)|T0_byte1;
	T0 = (float)TEMP0/16;

	return T0;
}


float DigitalSensor_Read_Milk()
{
	float T0 = 0;
	uint8_t Sensor_available = 0;
	uint8_t T0_byte1, T0_byte2;
	uint16_t TEMP0;


	Sensor_available = DS_Milk_Start ();
	HAL_Delay (1);
	DS_Milk_Write (0xCC);
	DS_Milk_Write (0x44);
	HAL_Delay (10);

	Sensor_available = DS_Milk_Start ();
	HAL_Delay(1);
	DS_Milk_Write (0xCC);
	DS_Milk_Write (0xBE);

	T0_byte1 = DS_Milk_Read();
	T0_byte2 = DS_Milk_Read();
	TEMP0 = (T0_byte2<<8)|T0_byte1;
	T0 = (float)TEMP0/16;

	return T0;
}

