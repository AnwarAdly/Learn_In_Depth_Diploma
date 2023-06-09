/*
 * app.c
 *
 *  Created on: 6 Jan 2023
 *      Author: DELL
 */


#include "FIFO.h"

FIFO_buf_t UART_buf;
unsigned int buf[5];
void main (void){
	int i ,temp;
	FIFO_init(&UART_buf ,buf ,5);
	for (i=0;i<5;i++){
		if (FIFO_enqueue(&UART_buf,i)==FIFO_NO_ERROR)
			printf("FIFO Enqueue : %d \n",i);
	}
	if (FIFO_dequeue(&UART_buf,&temp)==FIFO_NO_ERROR)
		printf("FIFO dequeue : %d \n",temp);
	if (FIFO_dequeue(&UART_buf,&temp)==FIFO_NO_ERROR)
		printf("FIFO dequeue : %d \n",temp);
	FIFO_Print(&UART_buf);
}
