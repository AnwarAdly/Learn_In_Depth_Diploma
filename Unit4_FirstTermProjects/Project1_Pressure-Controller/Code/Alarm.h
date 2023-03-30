#ifndef ALARM_H_
#define ALARM_H_

#include "state.h"

enum{
	Alarm_OFF,
	Alarm_ON
}AL_state_id;

void AL_init();
STATE_define(Alarm_OFF);
STATE_define(Alarm_ON);

void (*AL_state)();

#endif