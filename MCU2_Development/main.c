/*
 * App.c
 *
 *  Created on: Oct 17, 2019
 *      Author: Mahmoud Rezk Mahmoud
 */
#include "STD_TYPES.h"
#include "LCD.h"
#include "SPI_Interface.h"
#include "UART_Interface.h"
#include "TIMER.h"


static uint16 g_Time=0;
static uint8 LOC_SpiRx=0;
static uint8 LOC_Distance=0;
static uint8 LOC_UartRx='0';
static uint8 g_char_time[20];
static uint8 g_char_distance[20];


void intToStr(sint32 inputNum, uint8*outStr){
	/* using reminder as your giving number to can modify it without changing the giving original
	 * number   ex: reminder =123 or -123
	 */
	sint32 reminder=inputNum;
	sint32 count_digit=0,i,arr_lenght;
	/* counting the giving number digits*/
	while(reminder !=0){
		count_digit++;
		reminder/=10;
	}
	/* the array length is the same of number digits*/
	arr_lenght=count_digit;
	/*if the number giving is negative number ex:-123*/
	if(inputNum<0){
		/*consider your number is -123 this will mean 3 digits + 1 minis
		 * the total size should be 4 =3+1
		 */
		arr_lenght=count_digit+1;
		for(i=0;i<arr_lenght;i++){
			/*but the first elemnt of the string is the minis*/
			if(arr_lenght-i-1==0)
				outStr[0]='-';
			/*except that put the number in the right place
			 * if ex:-123
			 * arr[3]=3   arr[2]=2  arr[1]=1  arr[0]=-
			 */
			else{
				/*(inputNum*-1) to save the number without any sign as string*/
				outStr[arr_lenght-i-1]=((inputNum*-1)%10)+'0';
				inputNum/=10;
			}
		}
	}
	/*if the number is postive*/
	else{
		/*make the same sequance to put the number in the right place*/
		for(i=0;i<count_digit;i++){
			outStr[count_digit-i-1]=(inputNum%10)+'0';
			inputNum/=10;
		}
	}
	/*put null into the last place */
	outStr[arr_lenght]='\0';


}

void TIME_DIS_Calc(void)
{
	g_Time++;
	intToStr(g_Time,g_char_time);
	LOC_Distance += LOC_SpiRx*1;
	intToStr(LOC_Distance,g_char_distance);

}

void UART_Callback(void)
{
	UART_vidReceiveWord(&LOC_UartRx);
}
void main (void)
{
	static uint8 LOC_SpiTx=0;

	UART_vidInitialize();
	SPI_vidInitialize();
	TIMER_init();
	INTPRx_vidSetCallBack(UART_Callback);
	LCD_INIT_4bit();
	SREG|= 0X80;
	while(1)
	{
		LCD_String_DISP(0,0,"WELCOM");
		LCD_CHAR_DISP(1,0,LOC_UartRx);
		SPI_vidTransfer(LOC_SpiTx,&LOC_SpiRx);
		LCD_NUM_DISP(1,5,LOC_SpiRx);
		if('S' == LOC_UartRx)
		{
			TIMER_start(TIMER1);
			TIMER1_CMPA_setCallBack(TIME_DIS_Calc);
			UART_sendString("TIME: ");
			UART_sendString(g_char_time);
			UART_sendString(" Sec \n\r");

		}
		else if ('F' == LOC_UartRx)
		{
			UART_sendString("TIME: ");
			UART_sendString(g_char_time);
			UART_sendString("- DIS: ");
			UART_sendString(g_char_distance);
			UART_sendString("\n\r");
			LOC_UartRx='0';
			g_Time=0;
			LOC_Distance=0;
		}
		else
		{

		}
	}
}

