/*
 * AVR_SPI_REG.h
 *
 *  Created on: Mar 10, 2019
 *      Author: alx
 */

#ifndef AVR_SPI_REG_H_
#define AVR_SPI_REG_H_
/* SPI Control Register Address */
#define SPCR (*((volatile uint8*)0x2D))
#define SPCR_SPIE 7
#define SPCR_SPE  6
#define SPCR_DORD 5
#define SPCR_MSTR 4
#define SPCR_CPOL 3
#define SPCR_CPHA 2
#define SPCR_SPR1 1
#define SPCR_SPR0 0
/* SPSR Status Register Address */
#define SPSR (*((volatile uint8*)0x2E))
#define SPSR_SPIF  7
#define SPSR_WCOL  6
#define SPSR_SPI2X 0
/* SPDR Data Register Address */
#define SPDR (*((volatile uint8*)0x2F))
#define SPDR_MSB 7
#define SPDR_LSB 0
#endif /* AVR_SPI_REG_H_ */
