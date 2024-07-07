/*
 * DIO_prog.c
 *
 *  Created on: Jul 16, 2023
 *      Author: aya
 */



#include "../../LIB/types.h"
#include "../../LIB/errorState.h"

#include "DIO_priv.h"
#include "DIO_config.h"


ES_t DIO_enuInit(void)
{
	ES_t Local_enuErrorstate=ES_NOK;

	DDRA= CONC(PA_PIN7_DIR,PA_PIN6_DIR,PA_PIN5_DIR,PA_PIN4_DIR,PA_PIN3_DIR,PA_PIN2_DIR,PA_PIN1_DIR,PA_PIN0_DIR);
	DDRB= CONC(PB_PIN7_DIR,PB_PIN6_DIR,PB_PIN5_DIR,PB_PIN4_DIR,PB_PIN3_DIR,PB_PIN2_DIR,PB_PIN1_DIR,PB_PIN0_DIR);
	DDRC= CONC(PC_PIN7_DIR,PC_PIN6_DIR,PC_PIN5_DIR,PC_PIN4_DIR,PC_PIN3_DIR,PC_PIN2_DIR,PC_PIN1_DIR,PC_PIN0_DIR);
	DDRD= CONC(PD_PIN7_DIR,PD_PIN6_DIR,PD_PIN5_DIR,PD_PIN4_DIR,PD_PIN3_DIR,PD_PIN2_DIR,PD_PIN1_DIR,PD_PIN0_DIR);

	PORTA= CONC(PA_PIN7_VAL,PA_PIN6_VAL,PA_PIN5_VAL,PA_PIN4_VAL,PA_PIN3_VAL,PA_PIN2_VAL,PA_PIN1_VAL,PA_PIN0_VAL);
	PORTB= CONC(PB_PIN7_VAL,PB_PIN6_VAL,PB_PIN5_VAL,PB_PIN4_VAL,PB_PIN3_VAL,PB_PIN2_VAL,PB_PIN1_VAL,PB_PIN0_VAL);
	PORTC= CONC(PC_PIN7_VAL,PC_PIN6_VAL,PC_PIN5_VAL,PC_PIN4_VAL,PC_PIN3_VAL,PC_PIN2_VAL,PC_PIN1_VAL,PC_PIN0_VAL);
	PORTD= CONC(PD_PIN7_VAL,PD_PIN6_VAL,PD_PIN5_VAL,PD_PIN4_VAL,PD_PIN3_VAL,PD_PIN2_VAL,PD_PIN1_VAL,PD_PIN0_VAL);

	Local_enuErrorstate=ES_OK;

	return Local_enuErrorstate;
}

ES_t DIO_enuSetPortDirection(u8 Copy_u8PortID ,u8 Copy_u8Value)
{
	ES_t Local_enuErrorstate=ES_NOK;

	if( Copy_u8PortID <= DIO_PORTD)
	{
		switch(Copy_u8PortID)
		{
		case DIO_PORTA:
			DDRA=Copy_u8Value;
			break;
		case DIO_PORTB:
			DDRB=Copy_u8Value;
			break;
		case DIO_PORTC:
			DDRC=Copy_u8Value;
			break;
		case DIO_PORTD:
			DDRD=Copy_u8Value;
			break;
		}
		 Local_enuErrorstate=ES_OK;
	}
	else
	{
		Local_enuErrorstate=ES_OUT_OF_RANGE;
	}

	return Local_enuErrorstate;
}

ES_t DIO_enuSetPortValue(u8 Copy_u8PortID ,u8 Copy_u8Value)
{
	ES_t Local_enuErrorstate=ES_NOK;
	if( Copy_u8PortID <= DIO_PORTD)
	{
		switch(Copy_u8PortID)
		{
		case DIO_PORTA:
			PORTA=Copy_u8Value;
			break;
		case DIO_PORTB:
			PORTB=Copy_u8Value;
			break;
		case DIO_PORTC:
			PORTC=Copy_u8Value;
			break;
		case DIO_PORTD:
			PORTD=Copy_u8Value;
			break;
		}
		 Local_enuErrorstate=ES_OK;
	}
	else
	{
		Local_enuErrorstate=ES_OUT_OF_RANGE;
	}


	return Local_enuErrorstate;
}

ES_t DIO_enuTogPortValue(u8 Copy_u8PortID )
{
	ES_t Local_enuErrorstate=ES_NOK;
	if( Copy_u8PortID <= DIO_PORTD)
	{
		switch(Copy_u8PortID)
		{
		case DIO_PORTA:
			PORTA=~PORTA;
			break;
		case DIO_PORTB:
			PORTB=~PORTB;
			break;
		case DIO_PORTC:
			PORTC=~PORTC;
			break;
		case DIO_PORTD:
			PORTD=~PORTD;
			break;
		}
		 Local_enuErrorstate=ES_OK;
	}
	else
	{
		Local_enuErrorstate=ES_OUT_OF_RANGE;
	}


	return Local_enuErrorstate;
}

ES_t DIO_enuGetPortValue(u8 Copy_u8PortID ,u8* Copy_pu8Value)
{
	ES_t Local_enuErrorstate=ES_NOK;

	if(Copy_pu8Value !=NULL)
	{
		if( Copy_u8PortID <= DIO_PORTD)
		{
			switch(Copy_u8PortID)
			{
			case DIO_PORTA:
				*Copy_pu8Value=PINA;
				break;
			case DIO_PORTB:
				*Copy_pu8Value=PINB;
				break;
			case DIO_PORTC:
				*Copy_pu8Value=PINC;
				break;
			case DIO_PORTD:
				*Copy_pu8Value=PIND;
				break;
			}
		}
		else
		{
			Local_enuErrorstate=ES_OUT_OF_RANGE;
		}
	}
	else
	{
		Local_enuErrorstate=ES_NULL_POINTER;
	}


	return Local_enuErrorstate;
}

ES_t DIO_enuSetPinDirection(u8 Copy_u8PortID ,u8 Copy_u8PinID ,u8 Copy_u8Value)
{
	ES_t Local_enuErrorstate=ES_NOK;

	if( Copy_u8PortID <= DIO_PORTD && Copy_u8PinID<=DIO_PIN7 && Copy_u8Value <=OUTPUT )
	{
		switch(Copy_u8PortID)
		{
		case DIO_PORTA:
			DDRA&=~(DIO_MASK_BIT<<Copy_u8PinID);
			DDRA |=(Copy_u8Value<<Copy_u8PinID);
			break;
		case DIO_PORTB:
			DDRB&=~(DIO_MASK_BIT<<Copy_u8PinID);
			DDRB |=(Copy_u8Value<<Copy_u8PinID);
			break;
		case DIO_PORTC:
			DDRC&=~(DIO_MASK_BIT<<Copy_u8PinID);
			DDRC |=(Copy_u8Value<<Copy_u8PinID);
			break;
		case DIO_PORTD:
			DDRD&=~(DIO_MASK_BIT<<Copy_u8PinID);
			DDRD |=(Copy_u8Value<<Copy_u8PinID);
			break;
		}
		 Local_enuErrorstate=ES_OK;
	}
	else
	{
		Local_enuErrorstate=ES_OUT_OF_RANGE;
	}

	return Local_enuErrorstate;
}

ES_t DIO_enuSetPinValue(u8 Copy_u8PortID ,u8 Copy_u8PinID ,u8 Copy_u8Value)
{
	ES_t Local_enuErrorstate=ES_NOK;
	if( Copy_u8PortID <= DIO_PORTD && Copy_u8PinID<=DIO_PIN7 && Copy_u8Value <=OUTPUT )
	{
		switch(Copy_u8PortID)
		{
		case DIO_PORTA:
			PORTA&=~(DIO_MASK_BIT<<Copy_u8PinID);
			PORTA |=(Copy_u8Value<<Copy_u8PinID);
			break;
		case DIO_PORTB:
			PORTB&=~(DIO_MASK_BIT<<Copy_u8PinID);
			PORTB |=(Copy_u8Value<<Copy_u8PinID);
			break;
		case DIO_PORTC:
			PORTC&=~(DIO_MASK_BIT<<Copy_u8PinID);
			PORTC |=(Copy_u8Value<<Copy_u8PinID);
			break;
		case DIO_PORTD:
			PORTD&=~(DIO_MASK_BIT<<Copy_u8PinID);
			PORTD |=(Copy_u8Value<<Copy_u8PinID);
			break;
		}
		 Local_enuErrorstate=ES_OK;
	}
	else
	{
		Local_enuErrorstate=ES_OUT_OF_RANGE;
	}



	return Local_enuErrorstate;
}

ES_t DIO_enuTogPinValue(u8 Copy_u8PortID ,u8 Copy_u8PinID )
{
	ES_t Local_enuErrorstate=ES_NOK;
	if( Copy_u8PortID <= DIO_PORTD && Copy_u8PinID<=DIO_PIN7  )
	{
		switch(Copy_u8PortID)
		{
		case DIO_PORTA:
			PORTA ^=(DIO_MASK_BIT<<Copy_u8PinID);
			break;
		case DIO_PORTB:
			PORTB ^=(DIO_MASK_BIT<<Copy_u8PinID);
			break;
		case DIO_PORTC:
			PORTC ^=(DIO_MASK_BIT<<Copy_u8PinID);
			break;
		case DIO_PORTD:
			PORTD ^=(DIO_MASK_BIT<<Copy_u8PinID);
			break;
		}
		 Local_enuErrorstate=ES_OK;
	}
	else
	{
		Local_enuErrorstate=ES_OUT_OF_RANGE;
	}


	return Local_enuErrorstate;
}

ES_t DIO_enuGetPinValue(u8 Copy_u8PortID ,u8 Copy_u8PinID ,u8* Copy_pu8Value)
{
	ES_t Local_enuErrorstate=ES_NOK;
	if(Copy_pu8Value !=NULL)
	{
		if( Copy_u8PortID <= DIO_PORTD && Copy_u8PinID<=DIO_PIN7 )
		{
			switch(Copy_u8PortID)
			{
			case DIO_PORTA:
				*Copy_pu8Value=!((PINA & (DIO_MASK_BIT << Copy_u8PinID)) == 0);
				break;
			case DIO_PORTB:
				*Copy_pu8Value=!((PINB & (DIO_MASK_BIT << Copy_u8PinID)) == 0);
				break;
			case DIO_PORTC:
				*Copy_pu8Value=!((PINC & (DIO_MASK_BIT << Copy_u8PinID)) == 0);
				break;
			case DIO_PORTD:
				*Copy_pu8Value=!((PIND & (DIO_MASK_BIT << Copy_u8PinID)) == 0);
				break;
			}
		}
		else
		{
			Local_enuErrorstate=ES_OUT_OF_RANGE;
		}
	}
	else
	{
		Local_enuErrorstate=ES_NULL_POINTER;
	}


	return Local_enuErrorstate;
}

