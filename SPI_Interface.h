/*
 * SPI_Interface.h
 *
 *  Created on: Mar 10, 2019
 *      Author: Mahmoud Rezk Mahmoud
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#include "STD_Types.h"

/*******************Defines Modes for SPI*********************/

#define SPI_Master 1
#define SPI_Slave 0

/********************Choose the SPI mode*********************/

#define SPI_Mode SPI_Slave

/*******************Defines SPI Interrupt or Pooling*********************/

#define INTERRUPT 1
#define POOLING 0
#define SPI_INTERRUPT POOLING

/***************Defines which bit send first******************/

#define LSB_FIRST 1
#define MSB_FIRST 0
#define SELECT_BIT MSB_FIRST

/***************Defines Clock polarity modes******************/

#define LEADING_RISING_EDGE 0
#define LEADING_FALLING_EDGE 1
#define CPOL_LEADING LEADING_RISING_EDGE

/***************Defines Clock phase modes******************/

#define LEADING_SAMPLE 0
#define LEADING_SETUP  1
#define CPHA_LEADING LEADING_RISING_EDGE

/********************Defines Pin  of SPI*********************/

#define MISO 6
#define MOSI 5
#define MASTER_SCLK 7
#define SLAVE_SLECT 4

/********************Choose the SPI clock rate*********************/
#define FOSC_4 0
#define FOSC_16 1
#define FOSC_64 2
#define FOSC_128 3
#define FOSC_D_2 4
#define FOSC_D_8 5
#define FOSC_D_32 6
#define FOSC_D_64 7

#define SPI_CLK_RATE FOSC_4

/********************SPI Prototypes*********************/

uint8 SPI_vidInitialize(void);
uint8 SPI_vidTransfer(uint8 Copy_u8TxData,uint8 * Copy_u8RxData);

/********************SPI ISR Prototypes*********************/
void __vector_12 (void) __attribute__ ((signal,used));


#endif /* SPI_INTERFACE_H_ */
