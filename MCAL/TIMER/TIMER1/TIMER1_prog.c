/*
 * TIMER1_prog.c
 *
 *  Created on: Feb 10, 2024
 *      Author: aya
 */

#include "../../../LIB/errorState.h"
#include "../../../LIB/types.h"

#include "../../EINT/Interrupt.h"

#include "../TIMER_register.h"

#include "TIMER1_config.h"
#include "TIMER1_priv.h"


static void (*TIMER1_APfunCallBack [TIMER1_CALL_BACK])(void*)= {NULL,NULL,NULL};
static void  *TIMER1_APvidParameter[TIMER1_CALL_BACK]        = {NULL,NULL,NULL};


ES_t  TIMER1_enuInit(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	//MODE

#if TIMER1_MODE == TIMER1_NORMAL
	TCCR1A &=~(1<<TCCR1A_WGM10);
	TCCR1A &=~(1<<TCCR1A_WGM11);
	TCCR1B &=~(1<<TCCR1B_WGM12);
	TCCR1B &=~(1<<TCCR1B_WGM13);
	#if TIMER1_OC1A_B_PIN_STATE == TIMER1_NORMAL_DISCONNECT_OC1A_B
			TCCR1A &=~(1<<TCCR1A_COM1A0);
			TCCR1A &=~(1<<TCCR1A_COM1A1);
			TCCR1A &=~(1<<TCCR1A_COM1B0);
			TCCR1A &=~(1<<TCCR1A_COM1B1);
			Local_enuErrorState =ES_OK;
		#else
		#error"Attention!!, you must disable OC1A_B_PIN at NORMAL MODE...."
		#endif

#elif TIMER1_MODE==TIMER1_PHASE_CORRECT_PWM_8BIT
	TCCR1A |= (1<<TCCR1A_WGM10);
	TCCR1A &=~(1<<TCCR1A_WGM11);
	TCCR1B &=~(1<<TCCR1B_WGM12);
	TCCR1B &=~(1<<TCCR1B_WGM13);

#elif TIMER1_MODE==TIMER1_PHASE_CORRECT_PWM_9BIT
	TCCR1A &=~(1<<TCCR1A_WGM10);
	TCCR1A |= (1<<TCCR1A_WGM11);
	TCCR1B &=~(1<<TCCR1B_WGM12);
	TCCR1B &=~(1<<TCCR1B_WGM13);

#elif TIMER1_MODE==TIMER1_PHASE_CORRECT_PWM_10BIT
	TCCR1A |= (1<<TCCR1A_WGM10);
	TCCR1A |= (1<<TCCR1A_WGM11);
	TCCR1B &=~(1<<TCCR1B_WGM12);
	TCCR1B &=~(1<<TCCR1B_WGM13);

#elif TIMER1_MODE==TIMER1_COMPARE_MATCH_TOP_OCR1A
	TCCR1A &=~(1<<TCCR1A_WGM10);
	TCCR1A &=~(1<<TCCR1A_WGM11);
	TCCR1B |= (1<<TCCR1B_WGM12);
	TCCR1B &=~(1<<TCCR1B_WGM13);
		#if TIMER1_OC1A_B_PIN_STATE == TIMER1_CTC_DISCONNECT_OC1A_B
			TCCR1A &=~(1<<TCCR1A_COM1A0);
			TCCR1A &=~(1<<TCCR1A_COM1A1);
			TCCR1A &=~(1<<TCCR1A_COM1B0);
			TCCR1A &=~(1<<TCCR1A_COM1B1);
			Local_enuErrorState =ES_OK;
        #elif TIMER1_OC1A_B_PIN_STATE == TIMER1_CTC_TOGGLE_OC1A_B
			TCCR1A |= (1<<TCCR1A_COM1A0);
			TCCR1A &=~(1<<TCCR1A_COM1A1);
			TCCR1A |= (1<<TCCR1A_COM1B0);
			TCCR1A &=~(1<<TCCR1A_COM1B1);
			Local_enuErrorState =ES_OK;
		#elif TIMER1_OC1A_B_PIN_STATE == TIMER1_CTC_CLEAR_OC1A_B
			TCCR1A &=~(1<<TCCR1A_COM1A0);
			TCCR1A |= (1<<TCCR1A_COM1A1);
			TCCR1A &=~(1<<TCCR1A_COM1B0);
			TCCR1A |= (1<<TCCR1A_COM1B1);
			Local_enuErrorState =ES_OK;
		#elif TIMER1_OC1A_B_PIN_STATE == TIMER1_CTC_SET_OC1A_B
			TCCR1A |= (1<<TCCR1A_COM1A0);
			TCCR1A |= (1<<TCCR1A_COM1A1);
			TCCR1A |= (1<<TCCR1A_COM1B0);
			TCCR1A |= (1<<TCCR1A_COM1B1);
			Local_enuErrorState =ES_OK;
		#else
		#error"Attention!!, OC1A_B_PIN state is wrong or the mode is not CTC...."
		#endif

#elif TIMER1_MODE==TIMER1_FAST_PMW_8BIT
	TCCR1A |= (1<<TCCR1A_WGM10);
	TCCR1A &=~(1<<TCCR1A_WGM11);
	TCCR1B |= (1<<TCCR1B_WGM12);
	TCCR1B &=~(1<<TCCR1B_WGM13);

#elif TIMER1_MODE==TIMER1_FAST_PMW_9BIT
	TCCR1A &=~(1<<TCCR1A_WGM10);
	TCCR1A |= (1<<TCCR1A_WGM11);
	TCCR1B |= (1<<TCCR1B_WGM12);
	TCCR1B &=~(1<<TCCR1B_WGM13);

#elif TIMER1_MODE==TIMER1_FAST_PMW_10BIT
	TCCR1A |= (1<<TCCR1A_WGM10);
	TCCR1A |= (1<<TCCR1A_WGM11);
	TCCR1B |= (1<<TCCR1B_WGM12);
	TCCR1B &=~(1<<TCCR1B_WGM13);

#elif TIMER1_MODE==TIMER1_PHASE_FREQ_CORRECT_TOP_ICR1
	TCCR1A &=~(1<<TCCR1A_WGM10);
	TCCR1A &=~(1<<TCCR1A_WGM11);
	TCCR1B &=~(1<<TCCR1B_WGM12);
	TCCR1B |= (1<<TCCR1B_WGM13);
		#if TIMER1_OC1A_B_PIN_STATE == TIMER1_PHASE_CLEAR_CTC_SET_TOP
			TCCR1A &=~(1<<TCCR1A_COM1A0);
			TCCR1A |= (1<<TCCR1A_COM1A1);
			TCCR1A &=~(1<<TCCR1A_COM1B0);
			TCCR1A |= (1<<TCCR1A_COM1B1);
			Local_enuErrorState =ES_OK;
		#elif TIMER1_OC1A_B_PIN_STATE == TIMER1_PHASE_SET_CTC_CLEAR_TOP
			TCCR1A |= (1<<TCCR1A_COM1A0);
			TCCR1A |= (1<<TCCR1A_COM1A1);
			TCCR1A |= (1<<TCCR1A_COM1B0);
			TCCR1A |= (1<<TCCR1A_COM1B1);
			Local_enuErrorState =ES_OK;
		#else
		#error"Attention!!, OC1A_B_PIN state is wrong or the mode is not PHASE & FREQUENCY CORRECT PWM...."
		#endif

#elif TIMER1_MODE==TIMER1_PHASE_FREQ_CORRECT_TOP_OCR1A
	TCCR1A |= (1<<TCCR1A_WGM10);
	TCCR1A &=~(1<<TCCR1A_WGM11);
	TCCR1B &=~(1<<TCCR1B_WGM12);
	TCCR1B |= (1<<TCCR1B_WGM13);
		#if TIMER1_OC1A_B_PIN_STATE == TIMER1_PHASE_CLEAR_CTC_SET_TOP
			TCCR1A &=~(1<<TCCR1A_COM1A0);
			TCCR1A |= (1<<TCCR1A_COM1A1);
			TCCR1A &=~(1<<TCCR1A_COM1B0);
			TCCR1A |= (1<<TCCR1A_COM1B1);
			Local_enuErrorState =ES_OK;
		#elif TIMER1_OC1A_B_PIN_STATE == TIMER1_PHASE_SET_CTC_CLEAR_TOP
			TCCR1A |= (1<<TCCR1A_COM1A0);
			TCCR1A |= (1<<TCCR1A_COM1A1);
			TCCR1A |= (1<<TCCR1A_COM1B0);
			TCCR1A |= (1<<TCCR1A_COM1B1);
			Local_enuErrorState =ES_OK;
		#else
		#error"Attention!!, OC1A_B_PIN state is wrong or the mode is not PHASE & FREQUENCY CORRECT PWM...."
		#endif

#elif TIMER1_MODE==TIMER1_PHASE_CORRECT_TOP_ICR1
	TCCR1A &=~(1<<TCCR1A_WGM10);
	TCCR1A |= (1<<TCCR1A_WGM11);
	TCCR1B &=~(1<<TCCR1B_WGM12);
	TCCR1B |= (1<<TCCR1B_WGM13);
		#if TIMER1_OC1A_B_PIN_STATE == TIMER1_PHASE_CLEAR_CTC_SET_TOP
			TCCR1A &=~(1<<TCCR1A_COM1A0);
			TCCR1A |= (1<<TCCR1A_COM1A1);
			TCCR1A &=~(1<<TCCR1A_COM1B0);
			TCCR1A |= (1<<TCCR1A_COM1B1);
			Local_enuErrorState =ES_OK;
		#elif TIMER1_OC1A_B_PIN_STATE == TIMER1_PHASE_SET_CTC_CLEAR_TOP
			TCCR1A |= (1<<TCCR1A_COM1A0);
			TCCR1A |= (1<<TCCR1A_COM1A1);
			TCCR1A |= (1<<TCCR1A_COM1B0);
			TCCR1A |= (1<<TCCR1A_COM1B1);
			Local_enuErrorState =ES_OK;
		#else
		#error"Attention!!, OC1A_B_PIN state is wrong or the mode is not PHASE CORRECT PWM...."
		#endif

#elif TIMER1_MODE==TIMER1_PHASE_CORRECT_TOP_OCR1A
	TCCR1A |= (1<<TCCR1A_WGM10);
	TCCR1A |= (1<<TCCR1A_WGM11);
	TCCR1B &=~(1<<TCCR1B_WGM12);
	TCCR1B |= (1<<TCCR1B_WGM13);
    	#if TIMER1_OC1A_B_PIN_STATE == TIMER1_PHASE_CLEAR_CTC_SET_TOP
			TCCR1A &=~(1<<TCCR1A_COM1A0);
			TCCR1A |= (1<<TCCR1A_COM1A1);
			TCCR1A &=~(1<<TCCR1A_COM1B0);
			TCCR1A |= (1<<TCCR1A_COM1B1);
			Local_enuErrorState =ES_OK;
		#elif TIMER1_OC1A_B_PIN_STATE == TIMER1_PHASE_SET_CTC_CLEAR_TOP
			TCCR1A |= (1<<TCCR1A_COM1A0);
			TCCR1A |= (1<<TCCR1A_COM1A1);
			TCCR1A |= (1<<TCCR1A_COM1B0);
			TCCR1A |= (1<<TCCR1A_COM1B1);
			Local_enuErrorState =ES_OK;
		#else
		#error"Attention!!, OC1A_B_PIN state is wrong or the mode is not PHASE CORRECT PWM...."
		#endif

#elif TIMER1_MODE==TIMER1_COMPARE_MATCH_TOP_ICR1
	TCCR1A &=~(1<<TCCR1A_WGM10);
	TCCR1A &=~(1<<TCCR1A_WGM11);
	TCCR1B |= (1<<TCCR1B_WGM12);
	TCCR1B |= (1<<TCCR1B_WGM13);
		#if TIMER1_OC1A_B_PIN_STATE == TIMER1_CTC_DISCONNECT_OC1A_B
			TCCR1A &=~(1<<TCCR1A_COM1A0);
			TCCR1A &=~(1<<TCCR1A_COM1A1);
			TCCR1A &=~(1<<TCCR1A_COM1B0);
			TCCR1A &=~(1<<TCCR1A_COM1B1);
			Local_enuErrorState =ES_OK;
        #elif TIMER1_OC1A_B_PIN_STATE == TIMER1_CTC_TOGGLE_OC1A_B
			TCCR1A |= (1<<TCCR1A_COM1A0);
			TCCR1A &=~(1<<TCCR1A_COM1A1);
			TCCR1A |= (1<<TCCR1A_COM1B0);
			TCCR1A &=~(1<<TCCR1A_COM1B1);
			Local_enuErrorState =ES_OK;
		#elif TIMER1_OC1A_B_PIN_STATE == TIMER1_CTC_CLEAR_OC1A_B
			TCCR1A &=~(1<<TCCR1A_COM1A0);
			TCCR1A |= (1<<TCCR1A_COM1A1);
			TCCR1A &=~(1<<TCCR1A_COM1B0);
			TCCR1A |= (1<<TCCR1A_COM1B1);
			Local_enuErrorState =ES_OK;
		#elif TIMER1_OC1A_B_PIN_STATE == TIMER1_CTC_SET_OC1A_B
			TCCR1A |= (1<<TCCR1A_COM1A0);
			TCCR1A |= (1<<TCCR1A_COM1A1);
			TCCR1A |= (1<<TCCR1A_COM1B0);
			TCCR1A |= (1<<TCCR1A_COM1B1);
			Local_enuErrorState =ES_OK;
		#else
		#error"Attention!!, OC1A_B_PIN state is wrong or the mode is not CTC...."
		#endif

#elif TIMER1_MODE == TIMER1_FAST_PWM_TOP_ICR1
	TCCR1A &=~(1<<TCCR1A_WGM10);
	TCCR1A |= (1<<TCCR1A_WGM11);
	TCCR1B |= (1<<TCCR1B_WGM12);
	TCCR1B |= (1<<TCCR1B_WGM13);
		#if TIMER1_OC1A_B_PIN_STATE == TIMER1_FAST_PMW_CLEAR_CTC_SET_BOTTOM
			TCCR1A &=~(1<<TCCR1A_COM1A0);
			TCCR1A |= (1<<TCCR1A_COM1A1);
			TCCR1A &=~(1<<TCCR1A_COM1B0);
			TCCR1A |= (1<<TCCR1A_COM1B1);
			Local_enuErrorState =ES_OK;
		#elif TIMER1_OC1A_B_PIN_STATE == TIMER1_FAST_PMW_SET_CTC_CLEAR_BOTTOM
			TCCR1A |= (1<<TCCR1A_COM1A0);
			TCCR1A |= (1<<TCCR1A_COM1A1);
			TCCR1A |= (1<<TCCR1A_COM1B0);
			TCCR1A |= (1<<TCCR1A_COM1B1);
			Local_enuErrorState =ES_OK;
		#else
		#error"Attention!!, OC1A_B_PIN state is wrong or the mode is not Fast PWM...."
		#endif

#elif TIMER1_MODE == TIMER1_FAST_PWM_TOP_OCR1A
	TCCR1A |= (1<<TCCR1A_WGM10);
	TCCR1A |= (1<<TCCR1A_WGM11);
	TCCR1B |= (1<<TCCR1B_WGM12);
	TCCR1B |= (1<<TCCR1B_WGM13);
		#if TIMER1_OC1A_B_PIN_STATE == TIMER1_FAST_PMW_CLEAR_CTC_SET_BOTTOM
			TCCR1A &=~(1<<TCCR1A_COM1A0);
			TCCR1A |= (1<<TCCR1A_COM1A1);
			TCCR1A &=~(1<<TCCR1A_COM1B0);
			TCCR1A |= (1<<TCCR1A_COM1B1);
			Local_enuErrorState =ES_OK;
		#elif TIMER1_OC1A_B_PIN_STATE == TIMER1_FAST_PMW_SET_CTC_CLEAR_BOTTOM
			TCCR1A |= (1<<TCCR1A_COM1A0);
			TCCR1A |= (1<<TCCR1A_COM1A1);
			TCCR1A |= (1<<TCCR1A_COM1B0);
			TCCR1A |= (1<<TCCR1A_COM1B1);
			Local_enuErrorState =ES_OK;
		#else
		#error"Attention!!, OC1A_B_PIN state is wrong or the mode is not Fast PWM...."
		#endif
#else
#error "Attention!!, your TIMER1_MODE Selection is Wrong...."
#endif

			//PRESCALER

#if TIMER1_PRESCALER == TIMER1_NO_CLOCK_SOURCE
	TCCR1B &=~(1<<TCCR1B_CS12);
	TCCR1B &=~(1<<TCCR1B_CS11);
	TCCR1B &=~(1<<TCCR1B_CS10);
	Local_enuErrorState =ES_OK;
#elif TIMER1_PRESCALER == TIMER1_PRESCALER_1
	TCCR1B &=~(1<<TCCR1B_CS12);
	TCCR1B &=~(1<<TCCR1B_CS11);
	TCCR1B |= (1<<TCCR1B_CS10);
	Local_enuErrorState =ES_OK;
#elif TIMER1_PRESCALER == TIMER1_PRESCALER_8
	TCCR1B &=~(1<<TCCR1B_CS12);
	TCCR1B |= (1<<TCCR1B_CS11);
	TCCR1B &=~(1<<TCCR1B_CS10);
	Local_enuErrorState =ES_OK;
#elif TIMER1_PRESCALER == TIMER1_PRESCALER_64
	TCCR1B &=~(1<<TCCR1B_CS12);
	TCCR1B |= (1<<TCCR1B_CS11);
	TCCR1B |= (1<<TCCR1B_CS10);
	Local_enuErrorState =ES_OK;
#elif TIMER1_PRESCALER == TIMER1_PRESCALER_256
	TCCR1B |= (1<<TCCR1B_CS12);
	TCCR1B &=~(1<<TCCR1B_CS11);
	TCCR1B &=~(1<<TCCR1B_CS10);
	Local_enuErrorState =ES_OK;
#elif TIMER1_PRESCALER == TIMER1_PRESCALER_1024
	TCCR1B |= (1<<TCCR1B_CS12);
	TCCR1B &=~(1<<TCCR1B_CS11);
	TCCR1B |= (1<<TCCR1B_CS10);
	Local_enuErrorState =ES_OK;
#elif TIMER1_PRESCALER == TIMER1_EXT_CLOCK_FALLING_EDGE
	TCCR1B |= (1<<TCCR1B_CS12);
	TCCR1B |= (1<<TCCR1B_CS11);
	TCCR1B &=~(1<<TCCR1B_CS10);
	Local_enuErrorState =ES_OK;
#elif TIMER1_PRESCALER == TIMER1_EXT_CLOCK_RISING_EDGE
	TCCR1B |=(1<<TCCR1B_CS12);
	TCCR1B |=(1<<TCCR1B_CS11);
	TCCR1B |=(1<<TCCR1B_CS10);
	Local_enuErrorState =ES_OK;
#else
#error "Attention!!, your TIMER1_PRESCALER Selection is Wrong...."

#endif

	return Local_enuErrorState;
}

ES_t  TIMER1_enuSetChannelACTC(u16 Copy_u16OCR1AValue)
{
	ES_t Local_enuErrorState=ES_NOK;

	OCR1A=Copy_u16OCR1AValue;
	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}
ES_t  TIMER1_enuSetChannelBCTC(u16 Copy_u16OCR1AValue)
{
	ES_t Local_enuErrorState=ES_NOK;

	OCR1B=Copy_u16OCR1AValue;
	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}

ES_t  TIMER1_enuSetICR(u16 Copy_u16ICR1Value)
{
	ES_t Local_enuErrorState=ES_NOK;

	ICR1=Copy_u16ICR1Value;
	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}

ES_t TIMER1_enuSetTimerValue(u16 Copy_u16Value)
{
	ES_t Local_enuErrorState=ES_NOK;

	TCNT1=Copy_u16Value;
	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}

ES_t  TIMER1_enuReadTimerValue(u16 *Copy_pu16Value)
{
	ES_t Local_enuErrorState=ES_NOK;

	if(Copy_pu16Value!=NULL)
	{
		*Copy_pu16Value=TCNT1;
		Local_enuErrorState=ES_OK;
	}
	else
	{
		Local_enuErrorState=ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}


ES_t TIMER1_enuCallBack(void (*Copy_PfunCallBack)(void*) , void * Copy_PvidParameter,u8 Copy_CallBackSource)
{
	ES_t Local_enuErrorState=ES_NOK;

	if(Copy_PfunCallBack!=NULL)
	{
		switch(Copy_CallBackSource)
		{
		case TIMER1_OVF_CALLBACK:
			TIMER1_APfunCallBack[TIMER1_OVF_CALLBACK]=Copy_PfunCallBack;
			TIMER1_APvidParameter[TIMER1_OVF_CALLBACK]=Copy_PvidParameter;
			Local_enuErrorState=ES_OK;
			break;
		case TIMER1_COMA_CALLBACK:
			TIMER1_APfunCallBack[TIMER1_COMA_CALLBACK]=Copy_PfunCallBack;
			TIMER1_APvidParameter[TIMER1_COMA_CALLBACK]=Copy_PvidParameter;
			Local_enuErrorState=ES_OK;
			break;
		case TIMER1_COMB_CALLBACK:
			TIMER1_APfunCallBack[TIMER1_COMB_CALLBACK]=Copy_PfunCallBack;
			TIMER1_APvidParameter[TIMER1_COMB_CALLBACK]=Copy_PvidParameter;
			Local_enuErrorState=ES_OK;
			break;
		default:
			Local_enuErrorState=ES_OUT_OF_RANGE;
			break;
		}
	}
	else
	{
		Local_enuErrorState =ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}






ISR(VECT_TIMER1_COMA)
{
	if(TIMER1_APfunCallBack[TIMER1_COMA_CALLBACK]!=NULL)
	{
		TIMER1_APfunCallBack[TIMER1_COMA_CALLBACK](TIMER1_APvidParameter[TIMER1_COMA_CALLBACK]);
	}
}

ISR(VECT_TIMER1_COMB)
{
	if(TIMER1_APfunCallBack[TIMER1_COMB_CALLBACK]!=NULL)
	{
		TIMER1_APfunCallBack[TIMER1_COMB_CALLBACK](TIMER1_APvidParameter[TIMER1_COMB_CALLBACK]);
	}
}

ISR(VECT_TIMER1_OVF)
{
	if(TIMER1_APfunCallBack[TIMER1_OVF_CALLBACK]!=NULL)
	{
		TIMER1_APfunCallBack[TIMER1_OVF_CALLBACK](TIMER1_APvidParameter[TIMER1_OVF_CALLBACK]);
	}
}

