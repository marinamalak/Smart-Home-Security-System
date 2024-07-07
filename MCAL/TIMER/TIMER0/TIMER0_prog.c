/*
 * TIMER0_prog.c
 *
 *  Created on: Dec 9, 2023
 *      Author: aya
 */

#include "../../../LIB/errorState.h"
#include "../../../LIB/types.h"

#include "../../EINT/Interrupt.h"
#include "../TIMER_register.h"

#include "TIMER0_priv.h"
#include "TIMER0_config.h"




volatile u8  TIMER0_u8NumberOfOverflow=0;
volatile u8  TIMER0_u8Preload = 0;
volatile u32 TIMER0_u32StartDelay=0;
volatile u32 TIMER0_u32StopTime=0;
volatile u32 ISR_u32Counter=0;
volatile u32 ISR_u32ActionCounter=1;

static void (*TIMER0_APfunCallBack [TIMER0_CALL_BACK])(void*)= {NULL,NULL,NULL};
static void  *TIMER0_APvidParameter[TIMER0_CALL_BACK]        = {NULL,NULL,NULL};

static u32 Timer0_NumOVF=0;
static u32 Timer0_Preload=0;

ES_t TIMER0_enuInit(void)
{
	ES_t Local_enuErrorState=ES_NOK;

#if TIMER0_PRESCALER == TIMER0_NO_CLOCK_SOURCE
	TCCR0 &=~(1<<TCCR0_CS02);
	TCCR0 &=~(1<<TCCR0_CS01);
	TCCR0 &=~(1<<TCCR0_CS00);
	Local_enuErrorState =ES_OK;
#elif TIMER0_PRESCALER == TIMER0_PRESCALER_1
	TCCR0 &=~(1<<TCCR0_CS02);
	TCCR0 &=~(1<<TCCR0_CS01);
	TCCR0 |= (1<<TCCR0_CS00);
	Local_enuErrorState =ES_OK;
#elif TIMER0_PRESCALER == TIMER0_PRESCALER_8
	TCCR0 &=~(1<<TCCR0_CS02);
	TCCR0 |= (1<<TCCR0_CS01);
	TCCR0 &=~(1<<TCCR0_CS00);
	Local_enuErrorState =ES_OK;
#elif TIMER0_PRESCALER == TIMER0_PRESCALER_64
	TCCR0 &=~(1<<TCCR0_CS02);
	TCCR0 |= (1<<TCCR0_CS01);
	TCCR0 |= (1<<TCCR0_CS00);
	Local_enuErrorState =ES_OK;
#elif TIMER0_PRESCALER == TIMER0_PRESCALER_256
	TCCR0 |= (1<<TCCR0_CS02);
	TCCR0 &=~(1<<TCCR0_CS01);
	TCCR0 &=~(1<<TCCR0_CS00);
	Local_enuErrorState =ES_OK;
#elif TIMER0_PRESCALER == TIMER0_PRESCALER_1024
	TCCR0 |= (1<<TCCR0_CS02);
	TCCR0 &=~(1<<TCCR0_CS01);
	TCCR0 |= (1<<TCCR0_CS00);
	Local_enuErrorState =ES_OK;
#elif TIMER0_PRESCALER == TIMER0_EXT_CLOCK_FALLING_EDGE
	TCCR0 |= (1<<TCCR0_CS02);
	TCCR0 |= (1<<TCCR0_CS01);
	TCCR0 &=~(1<<TCCR0_CS00);
	Local_enuErrorState =ES_OK;
#elif TIMER0_PRESCALER == TIMER0_EXT_CLOCK_RISING_EDGE
	TCCR0 |=(1<<TCCR0_CS02);
	TCCR0 |=(1<<TCCR0_CS01);
	TCCR0 |=(1<<TCCR0_CS00);
	Local_enuErrorState =ES_OK;
#else
#error "Attention!!, your TIMER0_PRESCALER Selection is Wrong...."

#endif

	  // MODE
#if TIMER0_MODE == TIMER0_OVER_FLOW
	TCCR0 &=~(1<<TCCR0_WGM01);
	TCCR0 &=~(1<<TCCR0_WGM00);
	#if TIMER0_OC0_PIN_STATE == TIMER0_OVF_DISCONNECT_OC0
		TCCR0 &=~(1<<TCCR0_COM00);
		TCCR0 &=~(1<<TCCR0_COM01);
		Local_enuErrorState =ES_OK;
	#else
	#error"Attention!!, you must disable OC0_PIN at overflow MODE...."
	#endif

#elif TIMER0_MODE == TIMER0_COMPARE_MATCH
		TCCR0 |=(1<<TCCR0_WGM01);
		TCCR0 &=~(1<<TCCR0_WGM00);
		#if TIMER0_OC0_PIN_STATE == TIMER0_CTC_DISCONNECT_OC0
			TCCR0 &=~(1<<TCCR0_COM00);
			TCCR0 &=~(1<<TCCR0_COM01);
			Local_enuErrorState =ES_OK;
		#elif TIMER0_OC0_PIN_STATE == TIMER0_CTC_TOGGLE_OC0
			TCCR0 |=(1<<TCCR0_COM00);
			TCCR0 &=~(1<<TCCR0_COM01);
			Local_enuErrorState =ES_OK;
		#elif TIMER0_OC0_PIN_STATE == TIMER0_CTC_CLEAR_OC0
			TCCR0 &=~(1<<TCCR0_COM00);
			TCCR0 |=(1<<TCCR0_COM01);
			Local_enuErrorState =ES_OK;
		#elif TIMER0_OC0_PIN_STATE == TIMER0_CTC_SET_OC0
			TCCR0 |=(1<<TCCR0_COM00);
			TCCR0 |=(1<<TCCR0_COM01);
			Local_enuErrorState =ES_OK;
		#else
		#error"Attention!!, OC0_PIN state is wrong or the mode is not CTC...."
		#endif

#elif TIMER0_MODE == TIMER0_PHASE_CORRECT_PWM
		TCCR0 &=~(1<<TCCR0_WGM01);
		TCCR0 |=(1<<TCCR0_WGM00);
		#if TIMER0_OC0_PIN_STATE == TIMER0_PHASE_CLEAR_CTC_SET_TOP
			TCCR0 &=~(1<<TCCR0_COM00);
			TCCR0 |=(1<<TCCR0_COM01);
			Local_enuErrorState =ES_OK;
		#elif TIMER0_OC0_PIN_STATE == TIMER0_PHASE_SET_CTC_CLEAR_TOP
			TCCR0 |=(1<<TCCR0_COM00);
			TCCR0 |=(1<<TCCR0_COM01);
			Local_enuErrorState =ES_OK;
		#else
		#error"Attention!!, OC0_PIN state is wrong or the mode is not Phase Correct PWM...."
		#endif

#elif TIMER0_MODE == TIMER0_FAST_PWM
		TCCR0 |=(1<<TCCR0_WGM01);
		TCCR0 |=(1<<TCCR0_WGM00);
		#if TIMER0_OC0_PIN_STATE == TIMER0_FAST_PMW_CLEAR_CTC_SET_TOP
			TCCR0 &=~(1<<TCCR0_COM00);
			TCCR0 |=(1<<TCCR0_COM01);
			Local_enuErrorState =ES_OK;
		#elif TIMER0_OC0_PIN_STATE == TIMER0_FAST_PMW_SET_CTC_CLEAR_TOP
			TCCR0 |=(1<<TCCR0_COM00);
			TCCR0 |=(1<<TCCR0_COM01);
			Local_enuErrorState =ES_OK;
		#else
		#error"Attention!!, OC0_PIN state is wrong or the mode is not Fast PWM...."
		#endif
#else
#error "Attention!!, your TIMER0_MODE Selection is Wrong...."
#endif

	return Local_enuErrorState;
}

ES_t  TIMER0_enuSetCTC(u8 Copy_u8OCR0Value)
{
	ES_t Local_enuErrorState=ES_NOK;

	OCR0 =Copy_u8OCR0Value;
	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}

ES_t  TIMER0_enuSetPreload(u8 Copy_u8Preload)
{
	ES_t Local_enuErrorState=ES_NOK;

	TCNT0 =Copy_u8Preload;
	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}


ES_t TIMER0_enuDelayMilliSecond(void (*Copy_PfunCallBack)(void*) , void * Copy_PvidParameter , u32 Copy_u32StartDelay , u32 Copy_u32StopTime)
{
	ES_t Local_enuErrorState=ES_NOK;

#if TIMER0_PRESCALER == TIMER0_NO_CLOCK_SOURCE && TIMER0_MODE == TIMER0_OVER_FLOW
	#warning"Attention!!, TIMER0_PRESCALER is disabled so delay function has no effect..."

#elif (TIMER0_PRESCALER == TIMER0_PRESCALER_1 || TIMER0_PRESCALER == TIMER0_PRESCALER_8) && TIMER0_MODE == TIMER0_OVER_FLOW
	u16 Local_u16Counts= (TIMER0_F_CPU / TIMER0_PRESCALER); //f(timer)
	f32 Local_f32OVF_Counts = ((f32)Local_u16Counts / TIMER0_OVF_COUNTS);  //frequency
	TIMER0_u8NumberOfOverflow = ((u8)Local_f32OVF_Counts +1);  // take the integar number
	Local_f32OVF_Counts = Local_f32OVF_Counts - ((u32)Local_f32OVF_Counts) ; // take the float part
	TIMER0_u8Preload = TIMER0_OVF_COUNTS - (Local_f32OVF_Counts * TIMER0_OVF_COUNTS); // calculate preload
	TIMER0_enuSetPreload(TIMER0_u8Preload); // set preload

	TIMER0_u32StartDelay = Copy_u32StartDelay;
	TIMER0_u32StopTime = Copy_u32StopTime;
	TIMER0_APfunCallBack [TIMER0_DELAY_CALLBACK] = Copy_PfunCallBack;
	TIMER0_APvidParameter[TIMER0_DELAY_CALLBACK] = Copy_PvidParameter;
	Local_enuErrorState=ES_OK;

#elif (TIMER0_PRESCALER == TIMER0_PRESCALER_1 || TIMER0_PRESCALER == TIMER0_PRESCALER_8 || TIMER0_PRESCALER == TIMER0_PRESCALER_64 || TIMER0_PRESCALER == TIMER0_PRESCALER_256 || TIMER0_PRESCALER == TIMER0_PRESCALER_1024) && TIMER0_MODE == TIMER0_COMPARE_MATCH
#warning "Be ensure that OCR0_REG is assigned before Calling delay function...."
	if (OCR0>0)
	{
		u16 Local_u16Counts= (TIMER0_F_CPU / TIMER0_PRESCALER); //f(timer)
		f32 Local_f32OVF_Counts = ((f32)Local_u16Counts / (OCR0+1)); //frequency
		if ((Local_f32OVF_Counts - ((u32)Local_f32OVF_Counts)) > 0 ) //check if there is a float part
		{
			TIMER0_u8NumberOfOverflow = ((u8)Local_f32OVF_Counts +1); // take the integar number
			Local_f32OVF_Counts = Local_f32OVF_Counts - ((u32)Local_f32OVF_Counts) ;
			TIMER0_u8Preload = (OCR0+1) - (Local_f32OVF_Counts * (OCR0+1));// calculate preload
			TIMER0_enuSetPreload(TIMER0_u8Preload); // set preload
		}
		else
		{
			TIMER0_u8NumberOfOverflow = ((u8)Local_f32OVF_Counts);
			Local_f32OVF_Counts = Local_f32OVF_Counts - ((u32)Local_f32OVF_Counts) ;
		}

		TIMER0_u32StartDelay = Copy_u32StartDelay;
		TIMER0_u32StopTime = Copy_u32StopTime;
		TIMER0_APfunCallBack [TIMER0_DELAY_CALLBACK] = Copy_PfunCallBack;
		TIMER0_APvidParameter[TIMER0_DELAY_CALLBACK] = Copy_PvidParameter;
		Local_enuErrorState=ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
#else
#warning "Attention!!, Delay function has no effect at this mode or prescaler...."
#warning "To take high accuracy on Delay function, Choose OVF mode and one or eight prescaler OR CTC mode , 64 prescaler and OCR0 = 124"
#endif

	return Local_enuErrorState;
}

ES_t TIMER0_enuGeneratePWM(u8 Copy_u8DutyCycle)
{
	ES_t Local_enuErrorState=ES_NOK;

#if   TIMER0_MODE == TIMER0_PHASE_CORRECT_PWM

	#if   TIMER0_OC0_PIN_STATE == TIMER0_PHASE_CLEAR_CTC_SET_TOP
		u8 Local_u8OCR_Value = (TIMER0_PHASE_COUNTS * (f32)((f32)Copy_u8DutyCycle /(TIMER0_PERCENTAGE_RATIO * TIMER0_FIXED_NUM_TWO)));
		TIMER0_enuSetCTC(Local_u8OCR_Value);
		Local_enuErrorState = ES_OK;

	#elif TIMER0_OC0_PIN_STATE == TIMER0_PHASE_SET_CTC_CLEAR_TOP
		u8 Local_u8OCR_Value = (TIMER0_PHASE_COUNTS / TIMER0_FIXED_NUM_TWO)-(TIMER0_PHASE_COUNTS * (f32)((f32)Copy_u8DutyCycle /(TIMER0_PERCENTAGE_RATIO * TIMER0_FIXED_NUM_TWO)));
		TIMER0_enuSetCTC(Local_u8OCR_Value);
		Local_enuErrorState = ES_OK;

	#else
	#error"Attention!!, OC0_PIN state is wrong or the mode is not Phase Correct PWM...."
	#endif
#elif TIMER0_MODE == TIMER0_FAST_PWM
	#if   TIMER0_OC0_PIN_STATE == TIMER0_FAST_PMW_CLEAR_CTC_SET_TOP
		u8 Local_u8OCR_Value = ((f32)Copy_u8DutyCycle/TIMER0_PERCENTAGE_RATIO) * (f32)TIMER0_OVF_COUNTS;
		TIMER0_enuSetCTC(--Local_u8OCR_Value);
		Local_enuErrorState = ES_OK;

	#elif TIMER0_OC0_PIN_STATE == TIMER0_FAST_PMW_SET_CTC_CLEAR_TOP
		u8 Local_u8OCR_Value = TIMER0_OVF_COUNTS - (TIMER0_OVF_COUNTS * ((f32)Copy_u8DutyCycle /TIMER0_PERCENTAGE_RATIO));
		TIMER0_enuSetCTC(--Local_u8OCR_Value);
		Local_enuErrorState = ES_OK;

	#else
	#error"Attention!!, OC0_PIN state is wrong or the mode is not Fast PWM...."
	#endif
#else
#warning "Attention!!, Generation of PWM doesn't work at this mode...."
#endif

	return Local_enuErrorState;
}

ES_t TIMER0_enuCallBackOVF(void (*Copy_PfunCallBack)(void*) , void * Copy_PvidParameter)
{
	ES_t Local_enuErrorState=ES_NOK;

	if(Copy_PfunCallBack!=NULL)
	{
		TIMER0_APfunCallBack [TIMER0_OVF_CALLBACK] = Copy_PfunCallBack;
		TIMER0_APvidParameter[TIMER0_OVF_CALLBACK] = Copy_PvidParameter;
		Local_enuErrorState =ES_OK;
	}
	else
	{
		Local_enuErrorState =ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}

ES_t TIMER0_enuCallBackCTC(void (*Copy_PfunCallBack)(void*) , void * Copy_PvidParameter)
{
	ES_t Local_enuErrorState=ES_NOK;

	if(Copy_PfunCallBack!=NULL)
	{

		TIMER0_APfunCallBack [TIMER0_CTC_CALLBACK] = Copy_PfunCallBack;
		TIMER0_APvidParameter[TIMER0_CTC_CALLBACK] = Copy_PvidParameter;
		Local_enuErrorState=ES_OK;
	}
	else
	{
		Local_enuErrorState =ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}




ES_t TIMER0_enuEnableOVFINTERRUPT(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	TIMSK |=(1<<TIMSK_TOIE0);
	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}

ES_t TIMER0_enuEnableCTCINTERRUPT(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	TIMSK |=(1<<TIMSK_OCIE0);
	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}


ES_t TIMER0_enuSetAsychDelay(u32 Copy_u8Time ,void(*Copy_pfunApp)(void*),void* Parameter)
{
	ES_t Local_enuErrorState=ES_NOK;

	f32 Local_f32OVFTime=256 *((f32)TIMER0_PRESCALER/TIMER0_F_CPU);

	f32 Local_f32NumOVF = (Copy_u8Time)/(Local_f32OVFTime);

	if((Local_f32NumOVF-(u32)Local_f32NumOVF) != 0.0)
	{
		u32 Local_u32NumOVF =(u32)Local_f32NumOVF +1;
		Local_f32NumOVF = Local_f32NumOVF-(u32)Local_f32NumOVF;
		u8 Local_u8Preload =256 - (Local_f32NumOVF * 256);
		Timer0_NumOVF =Local_u32NumOVF;
		Timer0_Preload =Local_u8Preload;
		TCNT0 =Local_u8Preload;
	}
	else
	{
		Timer0_NumOVF =(u32)Local_f32NumOVF;
	}

	if(Copy_pfunApp!=NULL)
	{
		TIMER0_APfunCallBack[TIMER0_OVF_CALLBACK]=Copy_pfunApp;
		TIMER0_APvidParameter[TIMER0_OVF_CALLBACK]=Parameter;
	}
	else
	{
		Local_enuErrorState=ES_NULL_POINTER;
	}

	TIMSK |=(1<<0);


	return Local_enuErrorState;
}

ES_t TIMER0_enuSetSychDelay(u32 Copy_u8Time)
{
	ES_t Local_enuErrorState=ES_NOK;

	TIMSK &=~(1<<0);
	f32 Local_f32OVFTime=256.0 *((f32)TIMER0_PRESCALER/TIMER0_F_CPU);

	f32 Local_f32NumOVF = (Copy_u8Time)/(Local_f32OVFTime);

	if((Local_f32NumOVF-(u32)Local_f32NumOVF) != 0.0)
	{
		u32 Local_u32NumOVF =(u32)Local_f32NumOVF +1;
		Local_f32NumOVF = Local_f32NumOVF-(u32)Local_f32NumOVF;
		u8 Local_u8Preload =256 - (Local_f32NumOVF * 256);
		TCNT0=Local_u8Preload;
		while(Local_u32NumOVF>0)
		{
			while(((TIFR>>TIFR_TOV0)&1)==0);//wait flag
			TIFR |=(1<<0); // clear it by write one
			Local_u32NumOVF--;

		}
	}
	else
	{
		u32 Local_u32NumOVF =(u32)Local_f32NumOVF;
		while(Local_u32NumOVF>0)
		{
			while(((TIFR>>TIFR_TOV0)&1)==0);
			TIFR |=(1<<0);
			Local_u32NumOVF--;

		}
	}


	return Local_enuErrorState;
}



ISR(VECT_TIMER0_OVF)
{
	if (TIMER0_APfunCallBack[TIMER0_DELAY_CALLBACK] != NULL && (ISR_u32Counter == (TIMER0_u8NumberOfOverflow * TIMER0_u32StartDelay)) && (ISR_u32ActionCounter * TIMER0_u32StartDelay) <= TIMER0_u32StopTime)
	{
		ISR_u32ActionCounter++;
		TIMER0_APfunCallBack[TIMER0_DELAY_CALLBACK](TIMER0_APvidParameter[TIMER0_DELAY_CALLBACK]);
		ISR_u32Counter=0;
	}
	else
	{
		ISR_u32Counter++;
		if ( ((ISR_u32Counter % TIMER0_u8NumberOfOverflow) ==0 ) && TIMER0_u8Preload !=0 )
		{
			TIMER0_enuSetPreload(TIMER0_u8Preload);
		}
	}

	if (TIMER0_APfunCallBack[TIMER0_OVF_CALLBACK] != NULL)
	{
		TIMER0_APfunCallBack[TIMER0_OVF_CALLBACK](TIMER0_APvidParameter[TIMER0_OVF_CALLBACK]);
	}

}

ISR(VECT_TIMER0_CTC)
{
	/*
	if (TIMER0_APfunCallBack[TIMER0_DELAY_CALLBACK] != NULL && ISR_u32Counter == TIMER0_u8NumberOfOverflow * TIMER0_u32StartDelay && (ISR_u32ActionCounter * TIMER0_u32StartDelay) <= TIMER0_u32StopTime)
	{
		ISR_u32ActionCounter++;
		TIMER0_APfunCallBack[TIMER0_DELAY_CALLBACK](TIMER0_APvidParameter[TIMER0_DELAY_CALLBACK]);
		ISR_u32Counter=0;
	}
	else
	{
		ISR_u32Counter++;
		if ( (!(ISR_u32Counter % TIMER0_u8NumberOfOverflow)) && TIMER0_u8Preload )
		{
			TIMER0_enuSetPreload(TIMER0_u8Preload);
		}
	}
	*/

	if (TIMER0_APfunCallBack[TIMER0_CTC_CALLBACK] != NULL)
	{
		TIMER0_APfunCallBack[TIMER0_CTC_CALLBACK](TIMER0_APvidParameter[TIMER0_CTC_CALLBACK]);
	}
}




















