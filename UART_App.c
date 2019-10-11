/*
 * UART_App.c
 *  Created on: Mar 8, 2019
 *      Author: Mahmoud Rezk
 *      UART Communication protocol Driver
 *      Rev1
 */

#include "STD_Types.h"
#include "DIO_interface.h"
#include "LCD.h"
#include "AVR_UART_REG.h"
#include "Utilize.h"
#include <util/delay.h>
#include "UART_Interface.h"


int main (void)
{

	uint8 Transmit='A';

	DDRB=0xFF;
	UART_vidInitialize();
	LCD_INIT_4bit();
	LCD_String_DISP(0,0,"TRANSMITTING:");
	LCD_CHAR_DISP(0,13,Transmit);
	DIO_SetPinDirection(PORT_B,PIN2,INPUT);
	uint8 PUSH_button=0;
	while (1)
	{

		UART_vidSendWord(Transmit);
		LCD_CHAR_DISP(0,13,Transmit);
		PORTB |= 0x80;
		PUSH_button=DIO_GetPinValue(PORT_B,PIN2);
		if(PUSH_button==1)
		{
			PORTB |= 0x40;
			_delay_ms(30);
			PUSH_button=DIO_GetPinValue(PORT_B,PIN2);
			if(PUSH_button==1)
			{
				if(Transmit=='Z')
				{
					Transmit='A';
				}
				else
				{
					Transmit++;


				}

				while(PUSH_button==1)
				{
					PUSH_button=DIO_GetPinValue(PORT_B,PIN2);
				}
			}
			else
			{

			}

		}
		else
		{

		}

	}

	return 0;
}
