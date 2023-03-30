#include "LCD.h"
#include "Keypad.h"

void main (){
	char Key_pressed;
	LCD_INIT();
	KEYPAD_INIT();
	while(1){
		Key_pressed = KEYPAD_GET_KEY();
		switch(Key_pressed){
		case('N') : 								break;
		case("?") : LCD_CLEAR_SCREEN(); 			break;
		default   : LCD_WRITE_CHAR(Key_pressed);	break;
		}
	}
}