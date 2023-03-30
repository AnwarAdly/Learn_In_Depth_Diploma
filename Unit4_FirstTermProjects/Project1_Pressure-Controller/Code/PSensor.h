#ifndef PSENSOR_H_
#define PSENSOR_H_

#include "state.h"

enum{
	PS_Reading,
	PS_Sending
}PS_state_id;

void PS_init();
STATE_define(PS_Reading);
STATE_define(PS_Sending);

void (*PS_state)();

#endif