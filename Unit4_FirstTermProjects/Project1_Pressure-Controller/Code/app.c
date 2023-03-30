#include "PSensor.h"
#include "CheckPval.h"
#include "Alarm.h"
#include "GPIO.h"
#include "state.h"

void setup(){
	PS_init();
	AL_init();
	GPIO_INITIALIZATION();
	//PS_state = STATE(PS_Reading);
	CP_state = STATE(CP_Checking);
	//AL_state = STATE(Alarm_OFF);
}

void main(){
	setup();
	while(1){
		PS_state();
		CP_state();
		AL_state();
	}
}