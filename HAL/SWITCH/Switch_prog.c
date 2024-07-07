/*
 * Switch_prog.c
 *
 *  Created on: Jul 23, 2023
 *      Author: aya
 */

#include "../../LIB/types.h"
#include "../../LIB/errorState.h"

#include "Switch_config.h"
#include "Switch_priv.h"

#include "../../MCAL/DIO/DIO_int.h"

ES_t Switch_enuInit(SW_t * copy_AstrSwitchs)
{
	ES_t Local_enuErrorState = ES_NOK ;

	if(copy_AstrSwitchs !=NULL)
	{
		u8 Local_u8Iterator=0;
		for(Local_u8Iterator=0;Local_u8Iterator<SW_NUM;Local_u8Iterator++)
		{
			Local_enuErrorState=DIO_enuSetPinDirection(copy_AstrSwitchs[Local_u8Iterator].SW_PortID,copy_AstrSwitchs[Local_u8Iterator].SW_PinID,DIO_u8INPUT);
			Local_enuErrorState=DIO_enuSetPinValue(copy_AstrSwitchs[Local_u8Iterator].SW_PortID,copy_AstrSwitchs[Local_u8Iterator].SW_PinID,copy_AstrSwitchs[Local_u8Iterator].SW_Status);
		}
	}
	else
	{
		Local_enuErrorState=ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}

ES_t Switch_enuGetState(SW_t * copy_AstrSwitchs,u8 * copy_pu8SwState)
{
	ES_t Local_enuErrorState = ES_NOK ;

	if(copy_AstrSwitchs !=NULL && copy_pu8SwState !=NULL)
	{
		Local_enuErrorState=DIO_enuGetPinValue(copy_AstrSwitchs->SW_PortID,copy_AstrSwitchs->SW_PinID,copy_pu8SwState);
	}

	return Local_enuErrorState;
}
