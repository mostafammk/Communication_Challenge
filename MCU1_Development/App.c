/*
 * LCD.c
 *
 *  Created on: Oct 16, 2019
 *      Author: Mostafa Khalil
 */

#include "DIO_interface.h"
#include "LCD.h"
#include "UART_Interface.h"
#include "SPI_Interface.h"
#include <string.h>


uint8 g_speed = 0;
uint8 loc_u8ReceiveData[20]={'0'};

sint32 strToInt(uint8 *inputString){
	uint32 count = 0;
	sint32 result=0;
	uint32 weight=1;
	while(inputString[count] != '\0'){
		count++;
	}

	if(inputString[0] == '-'){
		for(count-=1 ; count>0 ; count--){
			result += (inputString[count]-'0')*weight;
			weight*=10;
		}
		result*=-1;
	}
	else{
		for(count-=1 ; count>0 ; count--){
			result += (inputString[count]-'0')*weight;
			weight*=10;
		}
		result += (inputString[count]-'0')*weight;
	}
	return result;
}

void RX_interrupt (void)
{

	static uint8 loc_receiveString[20];
	static uint8 indx=0;

	UART_vidReceiveWord(&loc_u8ReceiveData);

	if((loc_u8ReceiveData[0]>='0') && (loc_u8ReceiveData[0]<='9'))
	{
		strcat(loc_receiveString,loc_u8ReceiveData);
		indx++;
	}
	else if(loc_u8ReceiveData[0] == '#')
	{
		loc_receiveString[indx] = '\0';
		g_speed = strToInt(loc_receiveString);
		loc_receiveString[0]= '\0';
		indx = 0;
	}
	else if(loc_u8ReceiveData[0] == '+')
	{
		g_speed++;
	}
	else if(loc_u8ReceiveData[0] == '-')
	{
		g_speed--;
	}

}


int main (void)
{
	uint8 LOC_SPI_u8RxData;

	LCD_INIT_4bit();
	UART_vidInitialize();
	SPI_vidInitialize();

	INTPRx_vidSetCallBack(RX_interrupt);
	SREG |= (1<<7);

	UART_vidSendWord('M');

	UART_sendString("\n\rEnter the speed in (m/s) endedd with #\n\r");
	UART_sendString("Or Enter +/- to increment/decrement the speed with 1m/s\n\r");

	while (1)
	{
		LCD_String_DISP(0,0,"Speed:");
		LCD_CHAR_DISP(1,0,loc_u8ReceiveData[0]);
		LCD_NUM_DISP(0,8,g_speed);
		SPI_vidTransfer(g_speed,&LOC_SPI_u8RxData);
	}

	return 0;
}



/*
 * SPI_App.c
 *
 *  Created on: Mar 10, 2019
 *      Author: alx
 */

/*

#include "DIO_interface.h"
#include "SPI_Interface.h"
#include "util/delay.h"
#include "REG_Lib.h"
#include "LCD.h"

void main (void)
{
	uint8 LOC_u8TxData='A';
	uint8 LOC_u8RxData= '0';
	DDRD=0xFF;
	LCD_INIT_4bit();
	SPI_vidInitialize();
	while(1)
	{
		LCD_String_DISP(0,0,"Master");
		SPI_vidTransfer(LOC_u8TxData,&LOC_u8RxData);
		LCD_CHAR_DISP(0,10,LOC_u8RxData);
		_delay_ms(500);
		LOC_u8TxData++;
	}
}

*/
