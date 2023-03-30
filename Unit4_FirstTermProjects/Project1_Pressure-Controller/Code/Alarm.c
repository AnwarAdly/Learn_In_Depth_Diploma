#include "Alarm.h"
#include "GPIO.h"

extern void (*AL_state)();

void start_timer(){
	AL_state = STATE(Alarm_ON);
}
void stop_timer(){
	AL_state = STATE(Alarm_OFF);
}

void AL_init(){
	AL_state = STATE(Alarm_OFF);
	//printf("Alarm Actuator Init \n");
}
STATE_define(Alarm_OFF){
	AL_state_id = Alarm_OFF;
	Set_Alarm_actuator(1);
}
STATE_define(Alarm_ON){
	AL_state_id = Alarm_ON;
	Set_Alarm_actuator(0);
}