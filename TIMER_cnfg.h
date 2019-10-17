/*
 * TIMER_cnfg.h
 *
 *  Created on: Sep 20, 2019
 *      Author: Mahmoud Rezk
 */

#ifndef TIMER_CNFG_H_
#define TIMER_CNFG_H_

#include "STD_TYPES.h"
#include "REG_Lib.h"

typedef enum {T1,NUM_OF_TIMERS}Timers_Name;

#define TIMER_MODE CTC_MODE
#define NORMAL_MODE 0
#define CTC_MODE 1




typedef struct
{
	uint8 TIMER_ID;
	uint8 OC_ChA_Mode;
	uint8 OC_ChB_Mode;
	uint16 Normal_PreloadedValue;
	uint8 Prescaler;
	uint16 OCR_ChA;
	uint16 OCR_ChB;
	uint8 Interrupt_ChA;
	uint8 Interrupt_ChB;
}TIMER_SConfg;


extern TIMER_SConfg TIMER_cnfg_arr [NUM_OF_TIMERS];

#endif /* TIMER_CNFG_H_ */
