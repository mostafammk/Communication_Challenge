/*
 * Utilize.h
 *
 *  Created on: Mar 8, 2019
 *      Author: Mahmoud Rezk Mahmoud
 *      Rev1
 */
#ifndef _UTILIZE_H
#define _UTILIZE_H

#define SET_BIT(Var,BITNB)    Var|= ( 1 << (BITNB))
#define CLR_BIT(Var,BITNB)  Var&=~( 1 << (BITNB))
#define TOGGLE_BIT(Var,BITNB) Var^= ( 1 << (BITNB))
#define GET_BIT(Var,BITNB) (Var&((1<<BITNB)))>>BITNB
#define SET_LowNibble(Var)         Var|=(15)
#define SET_HighNibble(Var)        Var|=(15<<4)
#define CLR_LowNibble(Var)         Var&=(15<<4)
#define CLR_HighNibble(Var)        Var&=(15)
#define GET_Lownibble(Var)         Var&=(15)
#define GET_Highnibble(Var)        Var&=(15<<4)
#define ASSIGN_LowNibble(Var,Val)  Var=(Var|Val)
#define ASSIGN_HighNibble(Var,Val) Var=(Var|(Val<<4))

#endif
