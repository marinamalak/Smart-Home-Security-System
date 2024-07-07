/*
 * GIE_prog.c
 *
 *  Created on: Oct 23, 2023
 *      Author: aya
 */

#include "../../LIB/errorState.h"
#include  "../../LIB/types.h"

#include "GIE_priv.h"


ES_t GIE_enuEnable(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	SREG |=(1<<7);
	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}


ES_t GIE_enuDisable(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	SREG &=~(1<<7);
	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}
