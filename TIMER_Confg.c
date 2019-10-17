/*
 * TIMER_Confg.c
 *
 *  Created on: Sep 20, 2019
 *      Author: Mahmoud Rezk Mahmoud
 */
#include "TIMER_cnfg.h"
#include "TIMER.h"




				/******************TIMERS PARAMETERS***********************/
/*	uint8 TIMER_ID;
	uint8 OC_ChA_Mode;
	uint8 OC_ChB_Mode;
	uint16 Normal_PreloadedValue;
	uint8 Prescaler;
	uint16 OCR_ChA;
	uint16 OCR_ChB;
	uint8 Interrupt_ChA;
	uint8 Interrupt_ChB;*/

TIMER_SConfg TIMER_cnfg_arr [NUM_OF_TIMERS] =
{
	{TIMER0,OC_DISABLED,NA,0,F_CPU_8,250,NA,INTERRUPT,NA}
};
