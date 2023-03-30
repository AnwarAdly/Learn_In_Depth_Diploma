#include "uart.h"
unsigned char string[100]="Learn-in-depth : Anwar Adly";
void main (void){
	Uart_Send(string);
}