#include "PSensor.h"
#include "GPIO.h"

extern void (*PS_state)();
unsigned int pval=0;

void PS_init(){
	PS_state = STATE(PS_Reading);
}
STATE_define(PS_Reading){
	PS_state_id = PS_Reading;
	pval = getPressureVal();
	//printf("PS_Reading state reads Pressure value = %d \n",pval);
	read_pval(pval);
}
STATE_define(PS_Sending){
	PS_state_id = PS_Sending;
	//printf("PS_Sending state sends Pressure value = %d \n",pval);
	PS_state = STATE(PS_Reading);
}