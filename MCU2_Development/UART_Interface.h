/*
 * UART_Interface.h
 *
 *  Created on: Mar 8, 2019
 *      Author: Mahmoud Rezk Mahmoud
 *      UART Communication protocole Driver
 *      Rev1
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#include "STD_Types.h"


		/***************************************************************/

#define UART_5_Bits 0
#define UART_6_Bits 1
#define UART_7_Bits 2
#define UART_8_Bits 3
#define UART_9_Bits 4
#define UART_DataLength UART_8_Bits

		/***************************************************************/

#define MCU_ClK 8000000UL
#define UART_u16BaudRate 9600

		/***************************************************************/

#define ASNormalMode 0
#define ASDoubleMode 1
#define SMasterMode  2
#define UART_OperatingMode ASNormalMode

		/***************************************************************/

#define UART_NoParity 0
#define UART_EvenParity 1
#define UART_OddParity 2
#define ParityMode UART_NoParity

		/***************************************************************/

#define UART_OneStopBit 0
#define UART_TwoStopBit 1
#define UART_StopBits UART_OneStopBit

		/***************************************************************/

#define UART_FullDuplex   0
#define UART_TxHalfDuplex 1
#define UART_RxHalfDuplex 2
#define UART_DuplexMode UART_FullDuplex

	/***************************************************************/

#define Disable 0
#define Enable  1
#define UART_RecieveInterruptState Enable
#define UART_TransmitInterruptState Disable
#define UART_UdrInterruptState Disable

		/******************************************************************/

 /*
Description:Initialize UART Module
Inputs:  NA.
OutPut: NA.
*/
extern void UART_vidInitialize(void);
		/******************************************************************/

/*
Description:Send word from  UART Module
Inputs:  u16 has the word which Transmit.
OutPut: NA.
*/
extern void UART_vidSendWord(uint16 Copy_u16DataWord);
		/******************************************************************/

/*
Description:Recieve word from UART Module
Inputs: Address of a variable which save the data which received.
OutPut: NA.
*/
extern void UART_vidReceiveWord(uint8 * Copy_Pu16DataWord);
		/******************************************************************/

/*
Description:Send Buffer from UART Module
Inputs:
OutPut:
*/
extern void UART_vidSendBuffer();

		/******************************************************************/

/*
Description:Recieve Buffer from UART Module
Inputs:
OutPut:
*/
extern void UART_vidRecieveBuffer();


		/******************************************************************/

extern void UART_sendString(const uint8 *Str);

/***
 * ISR Vector for Rx UART Interrupt
 * */
extern void INTPRx_vidSetCallBack(void(*COPY_pvidCallBackFunction)(void));
		/******************************************************************/
/***
 * ISR Vector for UDR UART Interrupt
 * */
extern void INTPUdr_vidSetCallBack(void(*COPY_pvidCallBackFunction)(void));
		/******************************************************************/
/***
 * ISR Vector for Tx UART Interrupt
 * */
extern void INTPTx_vidSetCallBack(void(*COPY_pvidCallBackFunction)(void));
		/******************************************************************/

#endif /* UART_INTERFACE_H_ */
