#include "LCD.h"

void LCD_INIT(){
	_delay_ms(20); // delay time to lcd configs
	DIR_LCD_CTRL |= ((1<<RS) | (1<<RW) | (1<<EN));
	LCD_CTRL &= ~((1<<RS) | (1<<RW) | (1<<EN));
	_delay_ms(15);
	LCD_CLEAR_SCREEN();
	#ifdef EIGHT_BIT_MODE
		LCD_WRITE_COMMAND(LCD_CMD_FUNCTION_8BIT_2LINES);
	#endif
	#ifdef FOUR_BIT_MODE
		LCD_WRITE_COMMAND(0x02);
		LCD_WRITE_COMMAND(LCD_CMD_FUNCTION_4BIT_2LINES);
	#endif
	LCD_WRITE_COMMAND(LCD_CMD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_CMD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_CMD_DISP_ON_CURSOR_BLINK);
}
void LCD_WRITE_COMMAND(unsigned char command){
	LCD_ISBUSY();
	#ifdef EIGHT_BIT_MODE
		LCD_PORT = command ;
		LCD_CTRL &= ~((1<<RS) | (1<<RW));
		LCD_KICK();
	#endif
	#ifdef FOUR_BIT_MODE
		LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0) ;
		LCD_CTRL &= ~((1<<RS) | (1<<RW));
		LCD_KICK();
		LCD_PORT = (LCD_PORT & 0x0F) | (command << 4) ;
		LCD_CTRL &= ~((1<<RS) | (1<<RW));
		LCD_KICK();
	#endif	
}
void LCD_WRITE_CHAR(unsigned char character){
	LCD_ISBUSY();
	#ifdef EIGHT_BIT_MODE
		LCD_CTRL |= (1<<RS);
		LCD_PORT = character ;
		LCD_CTRL |= (1<<RS);
		LCD_CTRL &= ~(1<<RW);
		LCD_KICK();
	#endif
	#ifdef FOUR_BIT_MODE
		LCD_PORT = (LCD_PORT & 0x0F) | (character & 0xF0) ;
		LCD_CTRL |= (1<<RS);
		LCD_CTRL &= ~(1<<RW);
		LCD_KICK();
		LCD_PORT = (LCD_PORT & 0x0F) | (character << 4) ;
		LCD_CTRL |= (1<<RS);
		LCD_CTRL &= ~(1<<RW);
		LCD_KICK();
	#endif	
}
void LCD_WRITE_STRING(char* string){
	int count = 0;
	while(*string >0){
		count++;
		LCD_WRITE_CHAR(*string);
		if(count == 16){
			LCD_GOTOXY(1,0);
		}
		else if (count == 32){
			LCD_CLEAR_SCREEN();
			LCD_GOTOXY(0,0);
			count = 0;
		}
	}
}
void LCD_ISBUSY(void){
	DIR_LCD_PORT &= ~(0xFF << DATA_SHIFT);
	LCD_CTRL |= (1<<RW);
	LCD_CTRL &= ~(1<<RS);
	LCD_KICK();
	DIR_LCD_PORT = 0xFF;
	LCD_CTRL &= ~(1<<RW);
}
void LCD_CLEAR_SCREEN(void){
	LCD_WRITE_COMMAND(LCD_CMD_CLEAR_SCREEN);
}
void LCD_GOTOXY(unsigned char line, unsigned char position){
	if(line == 0){
		if(position < 16 && position >= 0)
			LCD_WRITE_COMMAND(LCD_CMD_BEGIN_AT_FIRST_ROW + position);
	}
	else if(line == 1){
		if(position < 16 && position >= 0)
			LCD_WRITE_COMMAND(LCD_CMD_BEGIN_AT_SECOND_ROW + position);
	}
}
void LCD_KICK(void){
	LCD_CTRL &= ~(1<<EN);
	_delay_ms(50);
	LCD_CTRL |= (1<<EN);
}