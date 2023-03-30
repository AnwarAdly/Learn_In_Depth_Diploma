#include "CheckPval.h"
#include "GPIO.h"

extern void (*CP_state)();

unsigned int cpval=0;
unsigned int threshold=20;

void read_pval(int pval){
	cpval = pval;
	(cpval <= threshold) ? (CP_state = STATE(CP_Checking)) : (CP_state = STATE(CP_Waiting));
	//printf("PS-----Pval=%d----->CP\n",cpval);
}

STATE_define(CP_Checking){
	CP_state_id = CP_Checking;
}
STATE_define(CP_Waiting){
	CP_state_id = CP_Waiting;
	start_timer();
	Delay(6000);
	stop_timer();
}