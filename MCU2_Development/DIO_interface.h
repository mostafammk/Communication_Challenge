/*
 * DIO_interface.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: orcl
 */
#ifndef _DIO_INT_H
#define _DIO_INT_H

#include"STD_Types.h"

#define PIN0   0
#define PIN1   1
#define PIN2   2
#define PIN3   3
#define PIN4   4
#define PIN5   5
#define PIN6   6
#define PIN7   7


/* Port Defines */
#define PORT_A 0
#define PORT_B 1
#define PORT_C 2
#define PORT_D 3


#define INPUT  0
#define OUTPUT 1


#define HIGH   1
#define LOW    0


void DIO_SetPinValue(uint8 u8PortIdCopy , uint8 u8PinIdCopy, uint8 u8PinValCopy);

uint8 DIO_GetPinValue(uint8 u8PortIdCopy, uint8 u8PinIdCopy);

void DIO_SetPinDirection (uint8 u8PortIdCopy, uint8 u8PinIdCopy, uint8 u8PinDirCopy);


void DIO_SetPortDirection (uint8 u8PortId, uint8 u8PortDir);

void DIO_SetPortValue     (uint8 u8PortId, uint8 u8PortVal);

#endif
