/*
 * TIMER.h
 *
 *  Created on: Sep 20, 2019
 *      Author: Mahmoud Rezk Mahmoud
 */

#ifndef TIMER_H_
#define TIMER_H_


#include "TIMER_cnfg.h"
#include "Interrupts.h"

/*TIMERS IDs */

#define TIMER0 0
#define TIMER1 1
#define TIMER2 2


									/*TIMERS OC MODES */

#define OC_DISABLED 0
#define OC_TOGGLE 1
#define OC_CLEAR 2
#define OC_SET 3

									/*TIMERS PRESCALER */

#define NO_CLK_SRC 0
#define F_CPU_1 1
#define F_CPU_8 2
#define F_CPU_32 6
#define F_CPU_64 3
#define F_CPU_128 7
#define F_CPU_256 4
#define F_CPU_1024 5
#define EXT_CLK_FALLING 6
#define EXT_CLK_RISING 7

									/*INTERRUPTS STATE */
#define INTERRUPT 0
#define POOLING 1

#define INITIALIZED			1
#define NOT_INITIALIZED		0


#define NA 0xff
#define NA_16 0xffff

					/*******************************************************/
#define MAX_NUM_OF_TIMERS		(uint8)3
#define OK 1
#define NOK 0

extern uint8 TIMER_init(void);

extern uint8 TIMER_start(uint8 TIMER_ID);
extern uint8 TIMER_stop(uint8 TIMER_ID);
/*extern uint8 TIME_Calc(uint8 TIMER_Id,uint8 TIME, void (* ptrcallback)(void));*/



extern void TIMER0_OVF_setCallBack(void (*COPY_TIMER0_OVF_callBackPtr)(void));
extern void TIMER0_CMP_setCallBack(void (*COPY_TIMER0_CMP_callBackPtr)(void));
extern void TIMER1_OVF_setCallBack(void (*COPY_TIMER1_OVF_callBackPtr)(void));
extern void TIMER1_CMPA_setCallBack(void (*COPY_TIMER1_CMPA_callBackPtr)(void));
extern void TIMER1_CMPB_setCallBack(void (*COPY_TIMER1_CMPB_callBackPtr)(void));
extern void TIMER2_OVF_setCallBack(void (*COPY_TIMER2_OVF_callBackPtr)(void));
extern void TIMER2_CMP_setCallBack(void (*COPY_TIMER2_CMP_callBackPtr)(void));

#endif /* TIMER_H_ */
