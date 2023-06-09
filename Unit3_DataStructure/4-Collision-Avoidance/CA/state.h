/*
 * state.h
 *
 *  Created on: 9 Jan 2023
 *      Author: DELL
 */

#ifndef STATE_H_
#define STATE_H_

#include "stdio.h"
#include "stdlib.h"

#define STATE_define(_statefunc_) void ST_##_statefunc_()
#define STATE(_statefunc_) ST_##_statefunc_

// prototypes for signal connection , implement it in destination not source
void US_distance(int d); //signal for send distance from US to CA
void DC_Motor(int s);    //signal for send speed    from CA to DC

#endif /* STATE_H_ */
