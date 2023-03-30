/*
 * fifo.c
 *
 *  Created on: 3 Feb 2023
 *      Author: DELL
 */


#include "fifo.h"

fifo_status fifo_init (fifo_t* fifo , element_type* buf, unsigned int length){
	if (buf == NULL)
		return FIFO_NULL;
	fifo->base = buf;
	fifo->head = buf;
	fifo->tail = buf;
	fifo->length = length;
	fifo->count = 0;
	return FIFO_NO_ERROR;
}
fifo_status fifo_enqueue(fifo_t* fifo , element_type item){
	if (!fifo || !fifo->base || !fifo->base)
		return FIFO_NULL;
	if (fifo->length == fifo->count)
		return FIFO_FULL;
	*(fifo->head)=item;
	if (fifo->length == fifo->count)
		fifo->head = fifo->base;
	else
		fifo->head++;
	fifo->count++;
	return FIFO_NO_ERROR;
}
fifo_status fifo_dequeue(fifo_t* fifo , element_type* item){
	if (!fifo || !fifo->base || !fifo->base)
		return FIFO_NULL;
	if (fifo->count==0)
		return FIFO_EMPTY;
	*item = *(fifo->tail);
	if (fifo->tail == (fifo->base+(fifo->length * sizeof(element_type))))
		fifo->tail = fifo->base;
	else
		fifo->tail++;
	fifo->count--;
	return FIFO_NO_ERROR;
}
void fifo_print(fifo_t* fifo){
	unsigned int i , *temp;
	if (fifo->count==0)
		printf("FIFO is Empty \n");
	else{
		temp=fifo->tail;
		printf("=====FIFO PRINT=====\n");
		for(i=0;i<fifo->count;i++){
			printf("%d\n",*temp);
			temp++;
		}
	}
}
unsigned int fifo_search_studentID(fifo_t* fifo , element_type* buf, unsigned int ID){
	unsigned int flag=0 ,i;
	if (!fifo || !fifo->base || !fifo->base)
		flag = 0;
	if (fifo->count==0)
		flag = 0;
	element_type* temp = fifo->tail;
	for(i=0;i<fifo->count;i++){
		if(temp->ID == ID){
			*buf = *temp;
			flag=1;
			break;
		}
		if (fifo->tail == (fifo->base+(fifo->length * sizeof(element_type))))
			temp = fifo->base;
		else
			temp++;
	}
	return flag;
}
