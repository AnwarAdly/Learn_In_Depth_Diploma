#include "uart.h"
#define UART0DR *((volatile unsigned int* )((unsigned int *)0x101f1000))
void Uart_Send(unsigned char *P_Tx_String){
	while(*P_Tx_String != '\0'){
		UART0DR = (unsigned int)(*P_Tx_String);
		P_Tx_String++;
	}
}