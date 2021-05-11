/*
 * sparelogics.c
 *
 *  Created on: Feb 16, 2021
 *      Author: Naveen
 */

void extra(void);


void extra(void)
{


	// **************** Capacitive Sensor Testing for Second Machine************************************* //
#if 0
	// Check backup : 9. Milk_Water_16_Feb_Pins_Needs_to_be_Changed

	if (Cap_Buff_Read)
	{
		// Wait for 1 minute  -> Timer
		if (  (Cap_WaitSeconds >= 60 * TimerMultiplicationFactor) )
		{
			Motor_CleaningWater_Clkwise();
			Cap_WaitFlag 		=	RESET;
			Cap_DrainWaitFlag	=	SET;
			Cap_WaitSeconds		=	RESET;

			Process.Flags.MilkWater.ProcessEnable	= 	RESET;
			SSRHeater_OFF_MilkWater();
		}

		// Drain the Milk for 30 seconds
		if (Cap_MilkDrainWaitSeconds >= 30 * TimerMultiplicationFactor)
		{
			Motor_CleaningWater_Stop();
			Cap_DrainWaitFlag			=	RESET;
			Cap_MilkDrainWaitSeconds	=	RESET;
			Process.Flags.MilkWater.ProcessEnable	=	SET;
		}

	}
#endif

#if 0
	// Check backup : 9. Milk_Water_16_Feb_Pins_Needs_to_be_Changed

		float TempRead = 0;

		TempRead = DigitalSensor_Read_MilkWater();
		if (TempRead < 100)		Process.Variables.MilkWater.Temperature.Read = TempRead;		// To protect from garbage values

		TempRead = DigitalSensor_Read_Milk();
		if (TempRead < 100)		Process.Variables.Milk.Temperature.Read = TempRead;

		TempRead = DigitalSensor_Read_Water();
		if (TempRead < 100)		Process.Variables.Water.Temperature.Read = TempRead;
#endif

}
