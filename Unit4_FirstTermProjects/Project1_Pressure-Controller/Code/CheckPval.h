#ifndef CHECKPVAL_H_
#define CHECKPVAL_H_

#include "state.h"

enum{
	CP_Checking,
	CP_Waiting
}CP_state_id;

STATE_define(CP_Checking);
STATE_define(CP_Waiting);

void (*CP_state)();

#endif