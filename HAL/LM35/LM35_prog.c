/*
 * LM35_prog.c
 *
 *  Created on: Nov 6, 2023
 *      Author: aya
 */
#include "../../LIB/errorState.h"
#include  "../../LIB/types.h"

#include "../../MCAL/DIO/DIO_int.h"

#include "../../MCAL/ADC/ADC_int.h"

#include "LM35_priv.h"
#include "LM35_config.h"





ES_t LM35_enuInit(TR_t *Copy_pstrLM)
{
	ES_t Local_enuErrorState=ES_NOK;


	if(Copy_pstrLM!=NULL)
	{

		if(Copy_pstrLM->TR_u8PosPinID!=NOT_CONNECTED)
		{
			Local_enuErrorState=DIO_enuSetPinDirection(DIO_u8PORTA,Copy_pstrLM->TR_u8PosPinID,DIO_u8INPUT);
			Local_enuErrorState=ADC_enuInit();
			Local_enuErrorState=ADC_enuSelectChannel(Copy_pstrLM->TR_u8PosPinID);

		}
		if(Copy_pstrLM->TR_u8NegPinID!=NOT_CONNECTED)
		{
			Local_enuErrorState=DIO_enuSetPinDirection(DIO_u8PORTA,Copy_pstrLM->TR_u8NegPinID,DIO_u8INPUT);
			//NOT available for LM35
		}

	}
	else
	{
		Local_enuErrorState=ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}

ES_t LM35_enuGetTemp(f32 * Copy_pf32Temp)
{
	ES_t Local_enuErrorState=ES_NOK;

	u16 Local_u16ADCread=0;
	ADC_enuRead(&Local_u16ADCread);
	*Copy_pf32Temp=((Local_u16ADCread*4.88)/10.00);

	return Local_enuErrorState;
}


