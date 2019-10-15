/*
 * SPI_Prog.c
 *
 *  Created on: Mar 10, 2019
 *      Author: alx
 */

#include "Utilize.h"
#include "AVR_SPI_REG.h"
#include "REG_Lib.h"
#include "SPI_Interface.h"
#include "STD_Types.h"


static void (*pvidCallBackPtrSpi) (void);

void INTPSPI_vidSetCallBack(void(*COPY_pvidCallBackFunction)(void))
{
	pvidCallBackPtrSpi = COPY_pvidCallBackFunction ;
}
uint8 SPI_vidInitialize(void)
{
	/*in case configured as master*/
	STD_Fun_t LOC_SpiStatus = OK;
/*************Configure SPI as a interrupt or pooling****************/
#if(SPI_INTERRUPT==POOLING)
	CLR_BIT(SPCR,SPCR_SPIE);
	//SET_BIT(SREG,SREG_I);
#elif(SPI_INTERRUPT==INTERRUPT)

	SET_BIT(SPCR,SPCR_SPIE);
#else
	LOC_SpiStatus=NOK;
#endif

/*****************Configure SPI Pins as a master or slave********************/

#if SPI_Mode == SPI_Master
	SET_BIT(SPCR,SPCR_MSTR);

	/*****************Configure SPI Pins as a master********************/
	SET_BIT(DDRB,SLAVE_SLECT);
	SET_BIT(DDRB,MOSI);
	SET_BIT(DDRB,MASTER_SCLK);
	CLR_BIT(DDRB,MISO);

	/*in case of slave*/
#elif SPI_Mode == SPI_Slave
	/*****************Configure SPI Pins as a Slave********************/
	CLR_BIT(SPCR,SPCR_MSTR);
	CLR_BIT(DDRB,SLAVE_SLECT);
	CLR_BIT(DDRB,MOSI);
	CLR_BIT(DDRB,MASTER_SCLK);
	SET_BIT(DDRB,MISO);
#else
	LOC_SpiStatus=NOK;
#endif

	/*******Selecting which bit will send first MSB or LSB*******/

#if (SELECT_BIT==MSB_FIRST)
	CLR_BIT(SPCR,SPCR_DORD);
#elif (SELECT_BIT==LSB_FIRST)
	SET__BIT(SPCR,SPCR_DORD);
#else
	LOC_SpiStatus=NOK;
#endif

	/*******Selecting the clock polarity rising or falling*******/

#if (CPOL_LEADING==LEADING_RISING_EDGE)
	CLR_BIT(SPCR,SPCR_CPOL);
#elif (CPOL_LEADING==LEADING_FALLING_EDGE)
	SET_BIT(SPCR,SPCR_CPOL);
#else
	LOC_SpiStatus=NOK;
#endif

	/*******Selecting the clock phase sample or setup*******/
#if (CPHA_LEADING==LEADING_SAMPLE)
	CLR_BIT(SPCR,SPCR_CPHA);
#elif (CPHA_LEADING==LEADING_SETUP)
	SET_BIT(SPCR,SPCR_CBHA);
#else
	LOC_SpiStatus=NOK;
#endif

	/*****************Selecting the clock Rate *********************/

#if (SPI_CLK_RATE==FOSC_4)

	CLR_BIT(SPCR,SPCR_SPR0);
	CLR_BIT(SPCR,SPCR_SPR1);
	CLR_BIT(SPSR,SPSR_SPI2X);

#elif (SPI_CLK_RATE==FOSC_16)

SET_BIT(SPCR,SPCR_SPR0);
CLR_BIT(SPCR,SPCR_SPR1);
CLR_BIT(SPSR,SPSR_SPI2X);

#elif (SPI_CLK_RATE==FOSC_64)

CLR_BIT(SPCR,SPCR_SPR0);
SET_BIT(SPCR,SPCR_SPR1);
CLR_BIT(SPSR,SPSR_SPI2X);

#elif (SPI_CLK_RATE==FOSC_128)

SET_BIT(SPCR,SPCR_SPR0);
SET_BIT(SPCR,SPCR_SPR1);
CLR_BIT(SPSR,SPSR_SPI2X);

#elif (SPI_CLK_RATE==FOSC_D_2)

CLR_BIT(SPCR,SPCR_SPR0);
CLR_BIT(SPCR,SPCR_SPR1);
SET_BIT(SPSR,SPSR_SPI2X);

#elif (SPI_CLK_RATE==FOSC_D_8)

SET_BIT(SPCR,SPCR_SPR0);
CLR_BIT(SPCR,SPCR_SPR1);
SET_BIT(SPSR,SPSR_SPI2X);

#elif (SPI_CLK_RATE==FOSC_D_32)

CLR_BIT(SPCR,SPCR_SPR0);
SET_BIT(SPCR,SPCR_SPR1);
SET_BIT(SPSR,SPSR_SPI2X);

#elif (SPI_CLK_RATE==FOSC_D_64)

SET_BIT(SPCR,SPCR_SPR0);
SET_BIT(SPCR,SPCR_SPR1);
SET_BIT(SPSR,SPSR_SPI2X);

#else
	LOC_SpiStatus=NOK;
#endif


	/*enable*/
	SET_BIT(SPCR,SPCR_SPE);

return LOC_SpiStatus;
}

uint8 SPI_vidTransfer(uint8 Copy_u8TxData,uint8 * Copy_u8RxData)
{
	STD_Fun_t LOC_SpiStatus=OK;
	SPDR = Copy_u8TxData;
	while(!(GET_BIT(SPSR,SPSR_SPIF)));
	SET_BIT(SPSR,SPSR_SPIF);
	*Copy_u8RxData = SPDR;

	return LOC_SpiStatus;
}

void __vector__12(void )
{
	if(pvidCallBackPtrSpi != NULL)
	{
		pvidCallBackPtrSpi();
	}
	else
	{

	}
}
