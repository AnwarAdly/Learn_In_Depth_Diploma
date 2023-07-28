/*
 * DoorSensorAbstractionSWC.c
 *
 *  Created on: July 27, 2023
 *      Author: Anwar
 */

#include "Rte_DoorSensorAbstractionSWC.h"
#include "DIO.h"

#define LEDON 0
#define LEDOFF 1

/*****************************************************
 * Port: 		PP_CS_LEDSwitch
 * Interface:	IF_CS_LED
 * Operation:	Led_switch
 *****************************************************/
Std_ReturnType Led_Switch_runnable(myuint8 LedState)
{

	if(LedState == LEDON)
	{
		DIO_WriteChannel(LED_ID, LedState);
		return RTE_E_IF_CS_LED_E_ok;
	}
	else if(LedState == LEDOFF)
	{
		DIO_WriteChannel(LED_ID, LedState);
		return RTE_E_IF_CS_LED_E_ok;
	}else{

		return RTE_E_IF_CS_LED_E_Not_ok;
	}
}


/*****************************************************
 * Runnable: 	ReadDoorSensor
 * Period:		0.01
 *****************************************************/
void ReadDoorSensor_runnable(void)
{
	uint8 DoorState =0;
	//read GPIO PIN 3
	DoorState =	DIO_ReadChannel( DIO_DOOR);

	//write DoorState to the port
	Rte_IWrite_DoorSensorAbstractionSWC_ReadDoorSensor_PP_SRI_DoorState(DoorState);
}
