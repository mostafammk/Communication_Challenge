

#include "STD_Types.h"
#include "DIO_interface.h"
#include "LCD.h"
#include "AVR_UART_REG.h"
#include "Utilize.h"
#include "UART_Interface.h"


int main (void)
{
	uint16 Local_u16ReceivedData;

	UART_vidInitialize();
	LCD_INIT_4bit();
	LCD_String_DISP(0,0,"RECIEVEING:");
	DIO_SetPinDirection(PORT_D,PIN0,INPUT);
	DIO_SetPinDirection(PORT_D,PIN1,OUTPUT);
	PORTB = 0xFF;
	while (1)
	{
		UART_vidReceiveWord(&Local_u16ReceivedData);

		LCD_CHAR_DISP(0,13,Local_u16ReceivedData);

	}

	return 0;
}
