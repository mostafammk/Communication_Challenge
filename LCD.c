#include "LCD.h"

void Enable()
{
	CMD_PORT|=(1<<EN);
	_delay_us(700);
	CMD_PORT&=~(1<<EN);
	_delay_us(700);
}

void DATA_WRT_4bit(uint8 data)
{
	CMD_PORT|=(1<<RS);
	DATA_PORT&=(0x0f);
	DATA_PORT|=(data & 0xf0);
	Enable();
	DATA_PORT&=(0x0f);
	DATA_PORT|=((data & 0x0f)<<4);
	Enable();
}

void DATA_WRT_8bit(uint8 data)
{
	CMD_PORT|=(1<<RS);
	DATA_PORT&=~(0xff);
	DATA_PORT|=data;
	Enable();
}

void CMD_WRT_4bit(uint8 cmd)
{
	CMD_PORT &= ~(1<<RS);
	DATA_PORT &= ~(0xf0);
	DATA_PORT|=(cmd & 0xf0);
	Enable();
	DATA_PORT&=~(0xf0);
	DATA_PORT|=((cmd & 0x0f)<<4);
	Enable();
}

void CMD_WRT_8bit(uint8 cmd)
{
	CMD_PORT&=~(1<<RS);
	DATA_PORT&=~(0xff);
	DATA_PORT|=cmd;
	Enable();
}

void LCD_INIT_4bit()
{
	CMD_DDR |= (1<<RS)|(1<<EN)|(1<<RW);
	DATA_DDR |=(0xf0);
	DATA_PORT &= ~(0xf0);
	CMD_PORT &= ~(1<<RS);	// RS <= 0 to send commands
	CMD_PORT &= ~(1<<EN);
	CMD_PORT &= (~1<<RW);
	_delay_ms(20);
	
	DATA_PORT &= ~(0xf0);
	DATA_PORT |= (0x30);
	Enable();
	_delay_us(150);
	DATA_PORT &= ~(0xf0);
	DATA_PORT |= (0x30);
	Enable();
	_delay_us(150);
	DATA_PORT &= ~(0xf0);
	DATA_PORT |= (0x30);
	Enable();
	_delay_us(150);
	
	DATA_PORT &= ~(0xf0);
	DATA_PORT |= (0x20);
	Enable();
	_delay_ms(2);
	
	CMD_WRT_4bit(0x2C);
	_delay_us(45);
	
	CMD_WRT_4bit(0x0E);  // Display --> oN , Cursor --> Off , Cursor blinking --> off
	_delay_us(45);
	
	CMD_WRT_4bit(0x06);  // Entry set mode : Display shift --> Off , Increment by 1	
	_delay_us(45);
	
	CMD_WRT_4bit(0x01);  // Clear LCD
	_delay_us(45);
	
	CMD_WRT_4bit(0x1C);  // Cursor Display shift : shift --> Cursor ,  Shift --> Right
	_delay_us(120);	
	
	
	
}

void LCD_CLR()
{
	CMD_WRT_4bit(0x01);
	_delay_us(45);
}

void LCD_Cursor_Home()
{
	CMD_WRT_4bit(0x02);
	_delay_ms(2);
}

void LCD_CUSRSOR_POS(uint8 row , uint8 col)
{
	CMD_WRT_4bit((0x80)|(col+(0x40*row)));
}

void LCD_CHAR_DISP(uint8 row , uint8 col, uint8 data)
{
	LCD_CUSRSOR_POS(row,col);
	DATA_WRT_4bit(data);
}


void LCD_String_DISP(uint8 row , uint8 col ,char *s)
{
	LCD_CUSRSOR_POS(row ,col);
	while(*s)
	{
	  DATA_WRT_4bit(*s++);
	}
	
}

void LCD_NUM_DISP(uint8 row , uint8 col, uint16_t num)
{
	LCD_CUSRSOR_POS(row ,col);
	if (0<=num)
	{
		
	if (num<=9) DATA_WRT_4bit(num+0x30);
	else if(num<=99) 
		{
			DATA_WRT_4bit((num/10)+0x30);
			DATA_WRT_4bit((num%10)+0x30);
		}
	else if(num<=999)
		{
			DATA_WRT_4bit((num/100)+0x30);
			DATA_WRT_4bit(((num/10)%10)+0x30);
			DATA_WRT_4bit((num%10)+0x30);	
		}
	else if (num<=9999)
	{
		DATA_WRT_4bit((num/1000)+0x30);
		DATA_WRT_4bit(((num/100)%10)+0x30);
		DATA_WRT_4bit(((num/10)%10)+0x30);
		DATA_WRT_4bit((num%10)+0x30);
	}
	else if (num<=99999)
	{
		DATA_WRT_4bit((num/10000)+0x30);
		DATA_WRT_4bit(((num/1000)%10)+0x30);
		DATA_WRT_4bit(((num/100)%10)+0x30);
		DATA_WRT_4bit(((num/10)%10)+0x30);
		DATA_WRT_4bit((num%10)+0x30);
	}
	}

	if (0>num)
	{
		num = -1*num;
		
	if (num<=9)
	{
		DATA_WRT_4bit(0x2d);
	    DATA_WRT_4bit(num+0x30);
	}
	else if(num<=99)
	{
		DATA_WRT_4bit(0x2d);
		DATA_WRT_4bit((num/10)+0x30);
		DATA_WRT_4bit((num%10)+0x30);
	}
	else if(num<=999)
	{
		DATA_WRT_4bit(0x2d);
		DATA_WRT_4bit((num/100)+0x30);
		DATA_WRT_4bit(((num/10)%10)+0x30);
		DATA_WRT_4bit((num%10)+0x30);
	}
	
	}
		
}