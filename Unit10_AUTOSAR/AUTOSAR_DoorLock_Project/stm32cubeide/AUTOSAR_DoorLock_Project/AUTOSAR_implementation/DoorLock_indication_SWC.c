/*
 * DoorLock_indication_SWC.c
 *
 *  Created on: July 27, 2023
 *      Author: Anwar
 */


#include"Rte_DoorLock_indication_SWC.h"

#define LEDON 0
#define LEDOFF 1
void DoorLock_indication_runnable(void)
{

	unsigned char DoorState = 0;

	//read door state
	DoorState = Rte_IRead_DoorLock_indication_SWC_DoorLock_indication_RP_SR_DOORState_DoorState();
   if(DoorState)
   {
	   //door is opened
	   //Invoke operation led_switch
	   Rte_Call_DoorLock_indication_SWC_RP_CS_LedSwitch_Led_switch(LEDON);

   }else{

	   //door is closed
	   	   //Invoke operation led_switch
	   	   Rte_Call_DoorLock_indication_SWC_RP_CS_LedSwitch_Led_switch(LEDOFF);

   }

}
