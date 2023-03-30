/*
 * Lab2.c
 *
 * Created: 06/03/2023 01:31:04
 * Author : DELL
 */ 

#define DDRD  (*(volatile unsigned char*)0x31)
#define PORTD (*(volatile unsigned char*)0x32)
#define SET_BIT(REG,BIT)	(REG = REG |  (1<<BIT))
#define CLEAR_BIT(REG,BIT)	(REG = REG &~ (1<<BIT))
#define TOGGLE_BIT(REG,BIT)	((REG>>BIT)&1)
#define GET_BIT(REG,BIT)	(REG &=  (1<<BIT))
#define F_CPU	8000000UL
#define LED1	5
#define LED2	6
#define LED3	7
#define Buzzer	4
#include <util/delay.h>

int main(void)
{
	// Set Pins 4,5,6,7 in portD as output
    DDRD = 0xF0;
	int i;
    while (1) 
    {
		for(i=5;i<8;i++){
			SET_BIT(PORTD,i);
			_delay_ms(300);
		}
		SET_BIT(PORTD,Buzzer);
		_delay_ms(300);
		for(i=5;i<8;i++){
			CLEAR_BIT(PORTD,i);
			_delay_ms(300);
		}
		CLEAR_BIT(PORTD,Buzzer);
    }
}

