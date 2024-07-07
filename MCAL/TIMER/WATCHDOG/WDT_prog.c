/*
 * WDT_prog.c
 *
 *  Created on: Feb 10, 2024
 *      Author: aya
 */


#include "../../../LIB/errorState.h"
#include "../../../LIB/types.h"

#include "../TIMER_register.h"

#include "WDT_config.h"
#include "WDT_priv.h"


ES_t WDT_enuSleep(u8 Copy_u8SleepTime)
{
	ES_t Local_enuErrorState=ES_NOK;

	if(Copy_u8SleepTime<8)
	{

		WDTCR &= 0b11111000;//Clear prescaler bits

		WDTCR |=Copy_u8SleepTime;//Set required prescaler

		Local_enuErrorState=ES_OK;
	}
	else
	{
		Local_enuErrorState=ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}

ES_t WDT_enuEnable(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	WDTCR |=(1<<WDTCR_WDE);
	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}

ES_t WDT_enuDisable(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	WDTCR |=0b00011000;//In the same operation, write a logic one to WDTOE and WDE

	WDTCR =0; //Within the next four clock cycles, write a logic 0 to WDE
	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}
