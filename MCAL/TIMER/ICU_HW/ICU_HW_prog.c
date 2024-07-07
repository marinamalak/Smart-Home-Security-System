/*
 * ICU_HW_prog.c
 *
 *  Created on: Feb 10, 2024
 *      Author: aya
 */

#include "../../../LIB/errorState.h"
#include "../../../LIB/types.h"

#include "../TIMER_register.h"

#include "../../EINT/Interrupt.h"

#include "ICU_HW_priv.h"
#include "ICU_HW_config.h"

static void (*ICU_PvCallBackFunc) (void*)=NULL;
static void *ICU_PvCallBackParameter=NULL;

ES_t ICU_enuInit(void)
{
	ES_t Local_enuErrorState=ES_NOK;

#if ICU_TRIGGER_SOURCE==ICU_RISING_EDGE
	TCCR1B |= (1<<TCCR1B_ICES1);
	Local_enuErrorState=ES_OK;
#elif ICU_TRIGGER_SOURCE==ICU_FALLING_EDGE
	TCCR1B &=~(1<<TCCR1B_ICES1);
	Local_enuErrorState=ES_OK;
#else
#error "Attention!!, your ICU_TRIGGER_SOURCE Selection is Wrong...."

#endif


	return Local_enuErrorState;
}

ES_t ICU_enuEnableINTERRUPT(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	TIMSK |=(1<<TIMSK_TICIE1);
	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}

ES_t ICU_enuDisableINTERRUPT(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	TIMSK &=~(1<<TIMSK_TICIE1);
	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}

ES_t ICU_enuSetTriggerEdge(u8 Copy_u8Edge)
{
	ES_t Local_enuErrorState=ES_NOK;

	if(Copy_u8Edge==ICU_RISING_EDGE)
	{
		TCCR1B |= (1<<TCCR1B_ICES1);
		Local_enuErrorState=ES_OK;
	}
	else if(Copy_u8Edge==ICU_FALLING_EDGE)
	{
		TCCR1B &=~(1<<TCCR1B_ICES1);
		Local_enuErrorState=ES_OK;
	}
	else
	{
		Local_enuErrorState=ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}

ES_t ICU_enuReadInputCapture(u16 *Copy_pu16Value)
{
	ES_t Local_enuErrorState=ES_NOK;

	*Copy_pu16Value=ICR1;
	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}


ES_t ICU_enuCallBack(void (*Copy_PfunCallBack)(void*) , void * Copy_PvidParameter)
{
	ES_t Local_enuErrorState=ES_NOK;

	if(Copy_PfunCallBack!=NULL)
	{

		ICU_PvCallBackFunc  = Copy_PfunCallBack;
		ICU_PvCallBackParameter = Copy_PvidParameter;
		Local_enuErrorState=ES_OK;
	}
	else
	{
		Local_enuErrorState =ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}


ISR(VECT_TIMER1_ICU)
{
	if (ICU_PvCallBackFunc != NULL)
	{
		ICU_PvCallBackFunc(ICU_PvCallBackParameter);
	}
}
