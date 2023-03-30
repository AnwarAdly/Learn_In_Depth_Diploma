/*
 * fifo.h
 *
 *  Created on: 3 Feb 2023
 *      Author: DELL
 */

#ifndef FIFO_H_
#define FIFO_H_

#include <stdio.h>
#include "sdatabase.h"

#define element_type student_t

typedef struct {
	element_type* base;
	element_type* head;
	element_type* tail;
	unsigned int count;
	unsigned int length;
}fifo_t;

typedef enum{
	FIFO_NO_ERROR,
	FIFO_EMPTY,
	FIFO_FULL,
	FIFO_NULL
}fifo_status;

fifo_status fifo_init (fifo_t* fifo , element_type* buf, unsigned int length);
fifo_status fifo_enqueue(fifo_t* fifo , element_type item);
fifo_status fifo_dequeue(fifo_t* fifo , element_type* item);
void fifo_print(fifo_t* fifo);
unsigned int fifo_search_studentID(fifo_t* fifo , element_type* buf, unsigned int ID);


#endif /* FIFO_H_ */
