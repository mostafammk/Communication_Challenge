#include"REG_Lib.h"
#include"DIO_interface.h"
#include"Utilize.h"
/*FUNC TO SET PIN VALUE*/
void DIO_SetPinValue(uint8 u8PortIdCopy , uint8 u8PinIdCopy, uint8 u8PinValCopy)
{

	switch(u8PortIdCopy)/*SWITCH CASE TO KNOW WHICH PORT WE USE*/
	{


	case PORT_A :
		if(u8PinValCopy==1)
		{

			SET_BIT(PORTA,u8PinIdCopy);
		}
		else
		{
			CLR_BIT(PORTA,u8PinIdCopy);

		}
		break;

	case PORT_B :
		if(u8PinValCopy==1)
		{

			SET_BIT(PORTB,u8PinIdCopy);
		}
		else
		{
			CLR_BIT(PORTB,u8PinIdCopy);

		}
		break;

	case PORT_C :
		if(u8PinValCopy==1)
		{

			SET_BIT(PORTC,u8PinIdCopy);
		}
		else
		{
			CLR_BIT(PORTC,u8PinIdCopy);

		}
		break;

	case PORT_D :
		if(u8PinValCopy==1)
		{

			SET_BIT(PORTD,u8PinIdCopy);
		}
		else
		{
			CLR_BIT(PORTD,u8PinIdCopy);

		}
		break;


	default:
		break;/* do nothing */
	}


}
/*FUNC TO GET PIN VALUE*/
uint8 DIO_GetPinValue(uint8 u8PortIdCopy, uint8 u8PinIdCopy)
{
	uint8 pinValueReturn;
	switch(u8PortIdCopy)/*SWITCH CASE TO KNOW WHICH PORT WE USE*/
	{


	case PORT_A : pinValueReturn=GET_BIT(PINA,u8PinIdCopy);

	break;

	case PORT_B : pinValueReturn=GET_BIT(PINB,u8PinIdCopy);

	break;

	case PORT_C : pinValueReturn=GET_BIT(PINC,u8PinIdCopy);

	break;

	case PORT_D : pinValueReturn=GET_BIT(PIND,u8PinIdCopy);

	break;


	default:
		break;/* do nothing */
	}
	return pinValueReturn ;

}



/*FUNC TO SET PIN DIRECTION*/
void DIO_SetPinDirection (uint8 u8PortIdCopy, uint8 u8PinIdCopy, uint8 u8PinDirCopy)
{
	switch(u8PortIdCopy)/*SWITCH CASE TO KNOW WHICH PORT WE USE*/
	{


	case PORT_A :
		if(u8PinDirCopy==OUTPUT)
		{

			SET_BIT(DDRA,u8PinIdCopy);
		}
		else if(u8PinDirCopy==INPUT)

		{
			CLR_BIT(DDRA,u8PinIdCopy);

		}

		break;

	case PORT_B :
		if(u8PinDirCopy==OUTPUT)
		{

			SET_BIT(DDRB,u8PinIdCopy);
		}

		else if(u8PinDirCopy==INPUT)

		{
			CLR_BIT(DDRB,u8PinIdCopy);

		}

		break;

	case PORT_C :
		if(u8PinDirCopy==OUTPUT)
		{

			SET_BIT(DDRC,u8PinIdCopy);
		}

		else if(u8PinDirCopy==INPUT)

		{
			CLR_BIT(DDRC,u8PinIdCopy);

		}

		break;

	case PORT_D :
		if(u8PinDirCopy==OUTPUT)
		{

			SET_BIT(DDRD,u8PinIdCopy);
		}

		else if(u8PinDirCopy==INPUT)

		{
			CLR_BIT(DDRD,u8PinIdCopy);

		}

		break;


	default:
		break;/* do nothing */
	}

}

void DIO_SetPortDirection (uint8 u8PortId, uint8 u8PortDir)
{

	switch (u8PortId)
	{
	case     PORT_A: DDRA = u8PortDir;
	break;
	case     PORT_B: DDRB = u8PortDir;
	break;
	case     PORT_C: DDRC = u8PortDir;
	break;
	case     PORT_D: DDRD = u8PortDir;
	break;
	default:  /* do nothing */
		break;
	}
}

void DIO_SetPortValue (uint8 u8PortId, uint8 u8PortVal)
{

	switch (u8PortId)
	{
	case     PORT_A: PORTA = u8PortVal;
	break;
	case     PORT_B: PORTB = u8PortVal;
	break;
	case     PORT_C: PORTC = u8PortVal;
	break;
	case     PORT_D: PORTD = u8PortVal;
	break;
	default:  /* do nothing */
		break;
	}
}



