#ifndef STATE_H_
#define STATE_H_

#define STATE_define(_statefunc_)	void ST_##_statefunc_()
#define STATE(_statefunc_)	ST_##_statefunc_

#include <stdio.h>
#include <stdlib.h>

// prototypes for signal connection , implement it in destination not source
void read_pval(int pval); //signal from PSensor to CheckPval
void start_timer(); 	  //signal from CheckPval to Alarm
void stop_timer(); 		  //signal from CheckPval to Alarm

#endif