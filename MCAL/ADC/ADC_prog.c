/*
 * ADC_prog.c
 *
 *  Created on: Nov 2, 2023
 *      Author: aya
 */
#include "../../LIB/errorState.h"
#include  "../../LIB/types.h"

#include "ADC_config.h"
#include "ADC_priv.h"

#include "../EINT/Interrupt.h"


static void (*ADC_pfunISRFun)(void *)=NULL;
static void *ADC_pvidISRParameter =NULL;

ES_t ADC_enuInit(void)
{
	 ES_t Local_enuErrorState=ES_NOK;

	 //PRESCALER
#if ADC_PRES==PRES_2
	 ADCSRA &=~(1<<2);
	 ADCSRA &=~(1<<1);
	 ADCSRA &=~(1<<0);
	 Local_enuErrorState=ES_OK;
#elif ADC_PRES==PRES_4
	 ADCSRA &=~(1<<2);
	 ADCSRA |=(1<<1);
	 ADCSRA &=~(1<<0);
	 Local_enuErrorState=ES_OK;
#elif ADC_PRES==PRES_8
	 ADCSRA &=~(1<<2);
	 ADCSRA |=(1<<1);
	 ADCSRA |=(1<<0);
	 Local_enuErrorState=ES_OK;
#elif ADC_PRES==PRES_16
	 ADCSRA |=(1<<2);
	 ADCSRA &=~(1<<1);
	 ADCSRA &=~(1<<0);
	 Local_enuErrorState=ES_OK;
#elif ADC_PRES==PRES_32
	 ADCSRA |=(1<<2);
	 ADCSRA &=~(1<<1);
	 ADCSRA |=(1<<0);
	 Local_enuErrorState=ES_OK;
#elif ADC_PRES==PRES_64
	 ADCSRA |=(1<<2);
	 ADCSRA |=(1<<1);
	 ADCSRA &=~(1<<0);
	 Local_enuErrorState=ES_OK;
#elif ADC_PRES==PRES_128
	 ADCSRA |=(1<<2);
	 ADCSRA |=(1<<1);
	 ADCSRA |=(1<<0);
	 Local_enuErrorState=ES_OK;
#else
	 Local_enuErrorState=ES_OUT_OF_RANGE;
#error"your ADC_PRES has a wrong selection"
#endif

	 //REFERENCE VOLTAGE
#if ADC_REF_VOLT==AREF_REF
	 ADMUX &=~(1<<7);
	 ADMUX &=~(1<<6);
	 Local_enuErrorState=ES_OK;
#elif ADC_REF_VOLT==AVCC_REF
	 ADMUX &=~(1<<7);
	 ADMUX |=(1<<6);
	 Local_enuErrorState=ES_OK;
#elif ADC_REF_VOLT==INTERNAL
	 ADMUX |=(1<<7);
	 ADMUX |=(1<<6);
	 Local_enuErrorState=ES_OK;
#else
	 Local_enuErrorState=ES_OUT_OF_RANGE;
#error"your ADC_REF_VOLT has a wrong selection"
#endif

	 //ADJUSTEMENT
#if ADC_ADJ==RIGHT_ADJ
	 ADMUX &=~(1<<5);
	 Local_enuErrorState=ES_OK;
#elif ADC_ADJ==LEFT_ADJ
	 ADMUX |=(1<<5);
	 Local_enuErrorState=ES_OK;
#else
	 Local_enuErrorState=ES_OUT_OF_RANGE;
#error"your ADC_ADJ has a wrong selection"
#endif


	 return Local_enuErrorState;
}

ES_t ADC_enuStartConversion(void)
{
	 ES_t Local_enuErrorState=ES_NOK;

	 ADCSRA |=(1<<6);
	 Local_enuErrorState=ES_OK;

	 return Local_enuErrorState;
}

ES_t ADC_enuPollingSystem(void)
{
	 ES_t Local_enuErrorState=ES_NOK;

	 while(((ADCSRA >>4)&1)==0); //WAIT FOR FLAG (ADIF)
	 ADCSRA |=(1<<4);   //CLEAR FLAG
	 Local_enuErrorState=ES_OK;

	 return Local_enuErrorState;
}

ES_t ADC_enuReadHighValue(u8 *Copy_pu8Value)
{
	 ES_t Local_enuErrorState=ES_NOK;

#if ADC_ADJ==RIGHT_ADJ
	 *Copy_pu8Value =(ADCL >>2);
	 *Copy_pu8Value |=(ADCH <<6);
	 Local_enuErrorState=ES_OK;
#elif ADC_ADJ==LEFT_ADJ
	 *Copy_pu8Value =ADCH;
	 Local_enuErrorState=ES_OK;
#else
	 Local_enuErrorState=ES_OUT_OF_RANGE;
#error"your ADC_ADJ has a wrong selection"
#endif

	 return Local_enuErrorState;
}

ES_t ADC_enuRead(u16 *Copy_pu16Value)
{
	 ES_t Local_enuErrorState=ES_NOK;

#if ADC_ADJ==RIGHT_ADJ
	 *Copy_pu16Value =ADCL;
	 *Copy_pu16Value |=((u16)ADCH <<8);
	 Local_enuErrorState=ES_OK;
#elif ADC_ADJ==LEFT_ADJ
	 *Copy_pu16Value =(ADCL>>6);
	 *Copy_pu16Value |=(ADCH<<2); ///
	 Local_enuErrorState=ES_OK;
#else
	 Local_enuErrorState=ES_OUT_OF_RANGE;
#error"your ADC_ADJ has a wrong selection"
#endif

	 return Local_enuErrorState;
}

ES_t ADC_enuCallBack(void(Copy_pfunAppFun)(void*),void *Copy_pvidAppParameter)
{
	 ES_t Local_enuErrorState=ES_NOK;

	 if(Copy_pfunAppFun!=NULL)
	 {
		 ADC_pfunISRFun=Copy_pfunAppFun;
		 ADC_pvidISRParameter=Copy_pvidAppParameter;
		 Local_enuErrorState=ES_OK;
	 }
	 else
	 {
		 Local_enuErrorState=ES_NULL_POINTER;
	 }

	 return Local_enuErrorState;
}

ES_t ADC_enuSelectChannel(u8 Copy_u8ChannelID)
{
	 ES_t Local_enuErrorState=ES_NOK;

	 if(Copy_u8ChannelID<32)
	 {
		 ADMUX &=~ 0x1F;  //clear bits 4 3 2 1 0 >> 0b00011111 ~ 0b11100000
		 ADMUX |=Copy_u8ChannelID;
		 Local_enuErrorState=ES_OK;
	 }
	 else
	 {
		 Local_enuErrorState=ES_OUT_OF_RANGE;
	 }

	 return Local_enuErrorState;
}

ES_t ADC_enuEnableTriggeringMode(u8 Copy_u8TriggeringSource)
{
	 ES_t Local_enuErrorState=ES_NOK;

	 ADCSRA &=~(1<<5); //CLOSE AUTO_TRIGEERING TO SELECT TRIGGER SOURCE

	 switch(Copy_u8TriggeringSource)
	 {
	 case FREE_RUNNING:
		 SFIOR &=~(1<<7);
		 SFIOR &=~(1<<6);
		 SFIOR &=~(1<<5);
		 Local_enuErrorState=ES_OK;
		 break;
	 case ANALOG_COMPARATOR:
		 SFIOR &=~(1<<7);
		 SFIOR &=~(1<<6);
		 SFIOR |=(1<<5);
		 Local_enuErrorState=ES_OK;
		 break;
	 case EXT_INT0_REQ:
		 SFIOR &=~(1<<7);
		 SFIOR |=(1<<6);
		 SFIOR &=~(1<<5);
		 Local_enuErrorState=ES_OK;
		 break;
	 case TIM_COUNT_0_COMPARE_MATCH:
		 SFIOR &=~(1<<7);
		 SFIOR |=(1<<6);
		 SFIOR |=(1<<5);
		 Local_enuErrorState=ES_OK;
		 break;
	 case TIM_COUNT_0_OVERFLOW:
		 SFIOR |=(1<<7);
		 SFIOR &=~(1<<6);
		 SFIOR &=~(1<<5);
		 Local_enuErrorState=ES_OK;
		 break;
	 case TIM_COUNT_1_COMPARE_MATCH:
		 SFIOR |=(1<<7);
		 SFIOR &=~(1<<6);
		 SFIOR |=(1<<5);
		 Local_enuErrorState=ES_OK;
		 break;
	 case TIM_COUNT_1_OVERFLOW:
		 SFIOR |=(1<<7);
		 SFIOR |=(1<<6);
		 SFIOR &=~(1<<5);
		 Local_enuErrorState=ES_OK;
		 break;
	 case TIM_COUNT_1_CAP_EVENT:
		 SFIOR |=(1<<7);
		 SFIOR |=(1<<6);
		 SFIOR |=(1<<5);
		 Local_enuErrorState=ES_OK;
		 break;
	 default:
		 Local_enuErrorState=ES_OUT_OF_RANGE;
		 break;
	 }
	 ADCSRA |=(1<<5);

	 return Local_enuErrorState;
}

ES_t ADC_enuDisableTriggeringMode(void)
{
	 ES_t Local_enuErrorState=ES_NOK;

	 ADCSRA &=~(1<<5);
	 Local_enuErrorState=ES_OK;

	 return Local_enuErrorState;
}

ES_t ADC_enuEnableInterruptMode(void)
{
	 ES_t Local_enuErrorState=ES_NOK;

	 ADCSRA |=(1<<3);
	 Local_enuErrorState=ES_OK;

	 return Local_enuErrorState;
}

ES_t ADC_enuDisableInterruptMode(void)
{
	 ES_t Local_enuErrorState=ES_NOK;

	 ADCSRA &=~(1<<3);
	 Local_enuErrorState=ES_OK;

	 return Local_enuErrorState;
}

ES_t ADC_enuEnable(void)
{
	 ES_t Local_enuErrorState=ES_NOK;

	 ADCSRA |=(1<<7);
	 Local_enuErrorState=ES_OK;

	 return Local_enuErrorState;
}

ES_t ADC_enuDisable(void)
{
	 ES_t Local_enuErrorState=ES_NOK;

	 ADCSRA &=~(1<<7);
	 Local_enuErrorState=ES_OK;

	 return Local_enuErrorState;
}


ISR(VECT_ADC)
{
	if(ADC_pfunISRFun!=NULL)
	{
		ADC_pfunISRFun(ADC_pvidISRParameter);
	}

}






