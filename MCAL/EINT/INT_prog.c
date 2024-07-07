/*
 * INT_prog.c
 *
 *  Created on: Oct 23, 2023
 *      Author: aya
 */

#include "../../LIB/errorState.h"
#include  "../../LIB/types.h"

#include "INT_priv.h"
#include "INT_config.h"
#include "Interrupt.h"


//static volatile void (* EINT_pfunINT[3])(void)={NULL,NULL,NULL};

static volatile void (* EINT_pfunINT[3])(void *)={NULL,NULL,NULL};

static volatile void* EINT_ApvoidINT[3]={NULL,NULL,NULL};


ES_t EINT_enuInit(EINT_t* Copy_pstrEINT)
{
	ES_t Local_enuErrorstate=ES_NOK;

	if(Copy_pstrEINT!=NULL)
	{
		u8 Local_u8Iter=0;
		for(Local_u8Iter=0;Local_u8Iter<3;Local_u8Iter++)
		{
			if(Copy_pstrEINT[Local_u8Iter].EINT_u8State==EINT_ENABLED)
			{
				switch(Local_u8Iter)
				{
				case 0:
					GICR |=(1<<6);//set bit6 to 1
					switch(Copy_pstrEINT[Local_u8Iter].EINT_u8SenceLevel)
					{
					case EINT_LOW_LEVEL:
						MCUCR&=~(1<<1);
						MCUCR&=~(1<<0);
						break;
					case EINT_ANY_LOG_CHANGE:
						MCUCR&=~(1<<1);
						MCUCR |=(1<<0);
						break;
					case EINT_FALLING_EDGE:
						MCUCR |=(1<<1);
						MCUCR&=~(1<<0);
						break;
					case EINT_RISING_EDGE:
						MCUCR |=(1<<1);
						MCUCR |=(1<<0);
						break;
					}
					Local_enuErrorstate=ES_OK;
					break;
				case 1:
					GICR |=(1<<7);//set bit7 to 1
					switch(Copy_pstrEINT[Local_u8Iter].EINT_u8SenceLevel)
					{
					case EINT_LOW_LEVEL:
						MCUCR&=~(1<<3);
						MCUCR&=~(1<<2);
						break;
					case EINT_ANY_LOG_CHANGE:
						MCUCR&=~(1<<3);
						MCUCR |=(1<<2);
						break;
					case EINT_FALLING_EDGE:
						MCUCR |=(1<<3);
						MCUCR&=~(1<<2);
						break;
					case EINT_RISING_EDGE:
						MCUCR |=(1<<3);
						MCUCR |=(1<<2);
						break;
					}
					Local_enuErrorstate=ES_OK;
					break;
				case 2:
					GICR |=(1<<5);//set bit5 to 1
					switch(Copy_pstrEINT[Local_u8Iter].EINT_u8SenceLevel)
					{
					case EINT_FALLING_EDGE:
						MCUCSR&=~(1<<6);
						break;
					case EINT_RISING_EDGE:
						MCUCSR |=(1<<6);
						break;
					}
					Local_enuErrorstate=ES_OK;
					break;
				}
			}
		}
	}
	else
	{
		Local_enuErrorstate=ES_NULL_POINTER;
	}

	return Local_enuErrorstate;
}

ES_t EINT_enuEnableINT(u8 Copy_u8ID)
{
	ES_t Local_enuErrorstate=ES_NOK;

	if(Copy_u8ID<3)
	{
		switch(Copy_u8ID)
		{
		case 0:
			GICR |=(1<<6);
			Local_enuErrorstate=ES_OK;
			break;
		case 1:
			GICR |=(1<<7);
			Local_enuErrorstate=ES_OK;
			break;
		case 2:
			GICR |=(1<<5);
			Local_enuErrorstate=ES_OK;
			break;
		}
	}
	else
	{
		Local_enuErrorstate=ES_OUT_OF_RANGE;
	}

	return Local_enuErrorstate;
}

ES_t EINT_enuDisableINT(u8 Copy_u8ID)
{
	ES_t Local_enuErrorstate=ES_NOK;

	if(Copy_u8ID<3)
	{
		switch(Copy_u8ID)
		{
		case 0:
			GICR &=~(1<<6);
			Local_enuErrorstate=ES_OK;
			break;
		case 1:
			GICR &=~(1<<7);
			Local_enuErrorstate=ES_OK;
			break;
		case 2:
			GICR &=~(1<<5);
			Local_enuErrorstate=ES_OK;
			break;
		}
	}
	else
	{
		Local_enuErrorstate=ES_OUT_OF_RANGE;
	}

	return Local_enuErrorstate;
}

ES_t EINT_enuSelectSenceLevel(u8 Copy_u8ID , u8 Copy_u8SenceLevel)
{
	ES_t Local_enuErrorstate=ES_NOK;

	if(Copy_u8ID<3)
	{
		switch(Copy_u8ID)
		{
		case 0:
			switch(Copy_u8SenceLevel)
			{
			case EINT_LOW_LEVEL:
				MCUCR&=~(1<<1);
				MCUCR&=~(1<<0);
				break;
			case EINT_ANY_LOG_CHANGE:
				MCUCR&=~(1<<1);
				MCUCR |=(1<<0);
				break;
			case EINT_FALLING_EDGE:
				MCUCR |=(1<<1);
				MCUCR&=~(1<<0);
				break;
			case EINT_RISING_EDGE:
				MCUCR |=(1<<1);
				MCUCR |=(1<<0);
				break;
			}
			Local_enuErrorstate=ES_OK;
			break;
		case 1:
			switch(Copy_u8SenceLevel)
			{
			case EINT_LOW_LEVEL:
				MCUCR&=~(1<<3);
				MCUCR&=~(1<<2);
				break;
			case EINT_ANY_LOG_CHANGE:
				MCUCR&=~(1<<3);
				MCUCR |=(1<<2);
				break;
			case EINT_FALLING_EDGE:
				MCUCR |=(1<<3);
				MCUCR&=~(1<<2);
				break;
			case EINT_RISING_EDGE:
				MCUCR |=(1<<3);
				MCUCR |=(1<<2);
				break;
			}
			Local_enuErrorstate=ES_OK;
			break;
		case 2:
			switch(Copy_u8SenceLevel)
			{
			case EINT_FALLING_EDGE:
				MCUCSR&=~(1<<6);
				break;
			case EINT_RISING_EDGE:
				MCUCSR |=(1<<6);
				break;
			}
			Local_enuErrorstate=ES_OK;
			break;
		}
	}
	else
	{
		Local_enuErrorstate=ES_OUT_OF_RANGE;
	}

	return Local_enuErrorstate;
}

ES_t EINT_enuCallBack(void *(Copy_pfun)(void *),void *Copy_pvoid,u8 Copy_u8ID)
{
	ES_t Local_enuErrorState=ES_NOK;

	if(Copy_pfun!=NULL)
	{
		if(Copy_u8ID<3)
		{
			EINT_pfunINT[Copy_u8ID]=Copy_pfun;
			EINT_ApvoidINT[Copy_u8ID]=Copy_pvoid;
			Local_enuErrorState=ES_OK;
		}
		else
		{
			Local_enuErrorState=ES_OUT_OF_RANGE;
		}
	}
	else
	{
		Local_enuErrorState=ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}

ISR(VECT_INT0)
{
	if(EINT_pfunINT[0]!=NULL)
	{
		EINT_pfunINT[0](EINT_ApvoidINT[0]);
	}
}
ISR(VECT_INT1)
{
	if(EINT_pfunINT[1]!=NULL)
	{
		EINT_pfunINT[1](EINT_ApvoidINT[1]);
	}
}
ISR(VECT_INT2)
{
	if(EINT_pfunINT[2]!=NULL)
	{
		EINT_pfunINT[2](EINT_ApvoidINT[2]);
	}
}



/*
ES_t EINT_enuCallBack(void *(Copy_pfun)(void),u8 Copy_u8ID)
{
	ES_t Local_enuErrorState=ES_NOK;

	if(Copy_pfun!=NULL)
	{
		EINT_pfunINT[Copy_u8ID]=Copy_pfun;
		Local_enuErrorState=ES_OK;
	}
	else
	{
		Local_enuErrorState=ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}

ISR(VECT_INT0)
{
	if(EINT_pfunINT[0]!=NULL)
	{
		EINT_pfunINT[0]();
	}
}
ISR(VECT_INT1)
{
	if(EINT_pfunINT[1]!=NULL)
	{
		EINT_pfunINT[1]();
	}
}
ISR(VECT_INT2)
{
	if(EINT_pfunINT[2]!=NULL)
	{
		EINT_pfunINT[2]();
	}
}
*/











