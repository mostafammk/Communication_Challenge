
#ifndef LCD_H_
#define LCD_H_


#define F_CPU 16000000ul
//#include <avr/io.h>
#include "REG_Lib.h"
#include "STD_Types.h"
#include <util/delay.h>
#define DATA_PORT PORTA
#define CMD_PORT PORTA

#define DATA_DDR DDRA
#define CMD_DDR DDRA
#define RS 1
#define EN 3
#define RW 2

void Enable();
void CMD_WRT_8bit(uint8 cmd);
void CMD_WRT_4bit(uint8 cmd);
void DATA_WRT_8bit(uint8 data);
void DATA_WRT_4bit(uint8 data);
void LCD_INIT_4bit();
void LCD_CLR();
void LCD_Cursor_Home();
void LCD_CUSRSOR_POS(uint8 row , uint8 col);
void LCD_CHAR_DISP(uint8 row , uint8 col , uint8 data);
void LCD_String_DISP(uint8 row , uint8 col ,char *s);
void LCD_NUM_DISP(uint8 row , uint8 col ,uint16_t num);


#endif
