/*
 * DC.c
 *
 *  Created on: 9 Jan 2023
 *      Author: DELL
 */

#include "DC.h"

extern void (*DC_state)();

unsigned int speed=0;

void DC_Motor(int s){
	speed=s;
	DC_state = STATE(DC_busy);
	printf("CA----speed=%d---->DC \n",speed);
}
void DC_init(){
	printf("DC Motor init \n");
}

STATE_define(DC_idle){
	DC_state_id = DC_idle;
	printf("DC_idle state : speed=%d \n",speed);
}
STATE_define(DC_busy){
	DC_state_id = DC_busy;
	DC_state = STATE(DC_idle);
	printf("DC_busy state : speed=%d \n",speed);
}

