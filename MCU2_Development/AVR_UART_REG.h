/*
 * AVR_UART_REG.h
 *
 *  Created on: Mar 8, 2019
 *      Author: Mahmoud Rezk
 *      UART Communication protocol Registers Addresses
 *      Rev1
 */

#ifndef AVR_UART_REG_H_
#define AVR_UART_REG_H_

#include "STD_Types.h"
/*
 * AVR_UART_REG.h
 *
 *  Created on: Mar 8, 2019
 *      Author: alx
 */

/*USART I/O Data Register Address –UDR*/
#define UDR (*((volatile uint8*)0x2C))

/*USART Control and Status Register A Adderss – UCSRA*/
#define UCSRA (*((volatile uint8*)0x2B))
#define UCSRA_RXC 7
#define UCSRA_TXC 6
#define UCSRA_UDRE 5
#define UCSRA_FE 4
#define UCSRA_DOR 3
#define UCSRA_PE 2
#define UCSRA_U2X 1
#define UCSRA_MPCM 0
/*USART Control and Status Register B Address– UCSRB*/
#define UCSRB (*((volatile uint8*)0x2A))
#define UCSRB_RXCIE 7
#define UCSRB_TXCIE 6
#define UCSRB_UDRIE 5
#define UCSRB_RXEN  4
#define UCSRB_TXEN  3
#define UCSRB_UCSZ2 2
#define UCSRB_RXB8  1
#define UCSRB_TXB8  0

/*USART Control and Status Register C Adderss – UCSRC*/
#define UCSRC (*((volatile uint8*)0x40))
#define UCSRC_URSEL  7
#define UCSRC_UMSEL  6
#define UCSRC_UPM1  5
#define UCSRC_UPM0  4
#define UCSRC_USBS  3
#define UCSRC_UCSZ1  2
#define UCSRC_UCSZ0  1
#define UCSRC_UCPOL  0
/*USART Baud Rate Register Address –UBRRL */
#define UBRRL (*((volatile uint8*)0x29))

/*USART Baud Rate Register Address –UBRRH */

#define UBRRH (*((volatile uint8*)0x40))



#endif /* AVR_UART_REG_H_ */
