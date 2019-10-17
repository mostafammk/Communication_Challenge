/*
 * UART_Prog.c
 *
 *  Created on: Mar 8, 2019
 *      Author: Mahmoud Rezk Mahmoud
 *      UART Communication protocole Driver
 *      Rev1
 */

#include "Utilize.h"
#include "AVR_UART_REG.h"
#include "UART_Interface.h"
#include "REG_Lib.h"

void __vector_13 (void) __attribute__ ((signal,used));
void __vector_14 (void) __attribute__ ((signal,used));
void __vector_15 (void) __attribute__ ((signal,used));
static void (*pvidCallBackPtrRx) (void) = NULL;
static void (*pvidCallBackPtrUdr) (void) = NULL;
static void (*pvidCallBackPtrTx) (void) = NULL;

void INTPRx_vidSetCallBack(void(*COPY_pvidCallBackFunction)(void))
{
	pvidCallBackPtrRx=COPY_pvidCallBackFunction ;
}

void INTPUdr_vidSetCallBack(void(*COPY_pvidCallBackFunction)(void))
{
	pvidCallBackPtrUdr=COPY_pvidCallBackFunction ;
}
void INTPTx_vidSetCallBack(void(*COPY_pvidCallBackFunction)(void))
{
	pvidCallBackPtrTx=COPY_pvidCallBackFunction ;
}
/*
Description:Initialize UART Module
Inputs:  NA.
OutPut:  NA.
 */

void UART_vidInitialize(void)
{
	/*Local Variables*/
	/*Boad Rate Calculation */
	uint16 Local_u16UBRRValue;

	/*UCSRC helper*/
	uint8 Local_u8UCSRCValue= 0b10000000;


	/*set Baud Rate*/
	/*the Equation*/
	#if(UART_OperatingMode==ASNormalMode)
		Local_u16UBRRValue = ((MCU_ClK/(UART_u16BaudRate*16UL))-1);
	#elif(UART_OperatingMode==ASDoubleMode)
		SET_BIT(UCSRA,UCSRA_U2X);
		Local_u16UBRRValue = (MCU_ClK/8*UART_u16BaudRate)-1;
	#elif(UART_OperatingMode==SMasterMode)
		CLR_BIT(UCSRA,UCSRA_U2X);
		Local_u16UBRRValue = (MCU_ClK/2*UART_u16BaudRate)-1;
	#endif


	/*Update UBRR*/
	UBRRL =(uint8)Local_u16UBRRValue;
	UBRRH= (uint8)(Local_u16UBRRValue>>8);


	/*Select Date Length(8)*/
	/*update UCSRB, UCSRC*/
	#if(UART_DataLength==UART_5_Bits)
		CLR_BIT(UCSRB,UCSRB_UCSZ2);
		CLR_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
		CLR_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
	#elif(UART_DataLength==UART_6_Bits)
		CLR_BIT(UCSRB,UCSRB_UCSZ2);
		CLR_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
		SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
	#elif(UART_DataLength==UART_7_Bits)
		CLR_BIT(UCSRB,UCSRB_UCSZ2);
		SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
		CLR_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
	#elif(UART_DataLength==UART_8_Bits)
		CLR_BIT(UCSRB,UCSRB_UCSZ2);
		SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
		SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
	#elif(UART_DataLength==UART_9_Bits)
		SET_BIT(UCSRB,UCSRB_UCSZ2);
		SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
		SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
	#endif
	/*Select Parity(No Parity)*/
	#if(ParityMode==UART_NoParity)
		CLR_BIT(Local_u8UCSRCValue,UCSRC_UPM1);
		CLR_BIT(Local_u8UCSRCValue,UCSRC_UPM0);
	#elif(ParityMode==Uart_EvenParity)
		SET_BIT(Local_u8UCSRCValue,UCSRC_UPM1);
		CLR_BIT(Local_u8UCSRCValue,UCSRC_UPM0);
	#elif(ParityMode==Uart_OddParity)
		SET_BIT(Local_u8UCSRCValue,UCSRC_UPM1);
		SET_BIT(Local_u8UCSRCValue,UCSRC_UPM0);
	#endif
	/*Select Stop Bits(1)*/
	#if(UART_StopBits==UART_OneStopBit)
		CLR_BIT(Local_u8UCSRCValue,UCSRC_USBS);
	#elif(UART_StopBits==UART_TwoStopBit)
		SET_BIT(Local_u8UCSRCValue,UCSRC_USBS);
	#endif
	/*Select if to use INTP*/
	#if(UART_RecieveInterruptState==Enable)
		SET_BIT(UCSRB,UCSRB_RXCIE);
	#elif(UART_RecieveInterruptState==Disable)

		CLR_BIT(UCSRB,UCSRB_RXCIE);
	#endif

	#if(UART_TransmitInterruptState==Enable)
		SET_BIT(UCSRB,UCSRB_TXCIE);
	#elif(UART_RecieveInterruptState==Disable)
		CLR_BIT(UCSRB,UCSRB_TXCIE);
	#endif
	#if(UART_UdrInterruptState==Enable)
		SET_BIT(UCSRB,UCSRB_UDRIE);
	#elif(UART_RecieveInterruptState==Disable)
		CLR_BIT(UCSRB,UCSRB_UDRIE);
	#endif


	/*update USRC*/
	UCSRC = Local_u8UCSRCValue;

	/*Enable Peripheral*/
	#if(UART_DuplexMode==UART_FullDuplex)
		SET_BIT(UCSRB,UCSRB_RXEN);
		SET_BIT(UCSRB,UCSRB_TXEN);
	#elif(UART_DuplexMode==UART_TxHalfDuplex)
		CLR_BIT(UCSRB,UCSRB_RXEN);
		SET_BIT(UCSRB,UCSRB_TXEN);
	#elif(UART_DuplexMode==UART_RxHalfDuplex)
		SET_BIT(UCSRB,UCSRB_RXEN);
		CLR_BIT(UCSRB,UCSRB_TXEN);
	#endif
}
/*
Description:Send word from  UART Module
Inputs:  u16 has the word which Transmit.
OutPut: NA.
*/
void UART_vidSendWord(uint16 Copy_u16DataWord)
{
	/*wait on UDR to be Empty*/
	while((GET_BIT(UCSRA,UCSRA_UDRE)==0));
	#if UART_DataLength == UART_9_Bits
		/*Write the 9th bit*/

	#endif
	/*Write  on Data Register*/
	UDR = (uint8)Copy_u16DataWord;

}


/*
Description:Recieve word from UART Module
Inputs: Address of a variable which save the data which received.
OutPut: NA.
*/
void UART_vidReceiveWord(uint8 * Copy_Pu16DataWord)
{
	/*Wait till Data is received*/
	while ((GET_BIT(UCSRA,UCSRA_RXC))==0);
	#if UART_DataLength == UART_9_Bits
		/*Read the 9th bit*/

	#endif
	/*Copy data from UDR*/
	*Copy_Pu16DataWord = UDR;
}


void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		UART_vidSendWord(Str[i]);
		i++;
	}
}


/*
Description:Send Buffer from UART Module
Inputs:
OutPut:
*/
void UART_vidSendBuffer()
{

}
/*
Description:Recieve Buffer from UART Module
Inputs:
OutPut:
*/
void UART_vidRecieveBuffer()
{

}

/***
 * ISR Vector for Rx UART Interrupt
 * */
void __vector_13(void )
{
	if(pvidCallBackPtrRx != NULL)
	{
		pvidCallBackPtrRx();
	}
	else
	{

	}
}
/***
 * ISR Vector for UDR UART Interrupt
 * */
void __vector_14(void )
{
	if(pvidCallBackPtrUdr != NULL)
	{
		pvidCallBackPtrUdr();
	}
	else
	{

	}
}
/***
 * ISR Vector for Tx UART Interrupt
 * */
void __vector_15(void )
{
	if(pvidCallBackPtrTx != NULL)
	{
		pvidCallBackPtrTx();
	}
	else
	{

	}
}
