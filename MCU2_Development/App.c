/*


#include "STD_Types.h"
#include "DIO_interface.h"
#include "LCD.h"
#include "AVR_UART_REG.h"
#include "Utilize.h"
#include "UART_Interface.h"
#include <util/delay.h>


int main (void)
{
	DDRB=0xFF;
	uint16 Local_u16ReceivedData;

	LCD_INIT_4bit();
	LCD_String_DISP(0,0,"RECIEVEING:");
	UART_vidInitialize();
	DIO_SetPinDirection(PORT_D,PIN0,INPUT);
	DIO_SetPinDirection(PORT_D,PIN1,OUTPUT);
	while (1)
	{
		UART_vidSendWord(20);
		UART_vidReceiveWord(&Local_u16ReceivedData);
		_delay_ms(250);
		PORTB ^= 0xFF;
		LCD_CHAR_DISP(0,13,Local_u16ReceivedData);

	}

	return 0;
}
 */


/*
 * SPI_App.c
 *
 *  Created on: Mar 10, 2019
 *      Author: alx
 */

#include "DIO_interface.h"
#include "SPI_Interface.h"
#include "util/delay.h"
#include "REG_Lib.h"
#include "LCD.h"

void main (void)
{
	uint8 LOC_u8TxData='z';
	uint8 LOC_u8RxData=0;
	DDRD=0x00;
	LCD_INIT_4bit();
	SPI_vidInitialize();
	while(1)
	{
		LCD_String_DISP(0,0,"Slave");
		SPI_vidTransfer(LOC_u8TxData,&LOC_u8RxData);
		LCD_CHAR_DISP(0,10,LOC_u8RxData);
		_delay_ms(500);
		LOC_u8TxData--;
	}
}

