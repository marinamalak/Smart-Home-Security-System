/*
 * TIMER1_int.h
 *
 *  Created on: Feb 10, 2024
 *      Author: aya
 */

#ifndef MCAL_TIMER_TIMER1_TIMER1_INT_H_
#define MCAL_TIMER_TIMER1_TIMER1_INT_H_

ES_t TIMER1_enuInit(void);

ES_t TIMER1_enuSetChannelACTC(u16 Copy_u16OCR1AValue);

ES_t TIMER1_enuSetChannelBCTC(u16 Copy_u16OCR1AValue);

ES_t TIMER1_enuSetICR(u16 Copy_u16ICR1Value);

ES_t TIMER1_enuSetTimerValue(u16 Copy_u16Value);

ES_t TIMER1_enuReadTimerValue(u16 *Copy_pu16Value);

ES_t TIMER1_enuCallBack(void (*Copy_PfunCallBack)(void*) , void * Copy_PvidParameter,u8 Copy_CallBackSource);


//CALLBACK SOURCES
#define TIMER1_CTC_A_INTERRUPT						0
#define TIMER1_CTC_B_INTERRUPT						1
#define TIMER1_OVF_INTERRUPT						2


#endif /* MCAL_TIMER_TIMER1_TIMER1_INT_H_ */
