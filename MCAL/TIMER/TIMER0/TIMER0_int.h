/*
 * TIMER0_int.h
 *
 *  Created on: Dec 9, 2023
 *      Author: aya
 */

#ifndef TIMER0_INT_H_
#define TIMER0_INT_H_

ES_t TIMER0_enuInit(void);

ES_t TIMER0_enuDelayMilliSecond(void (*Copy_PfunCallBack)(void*) , void * Copy_PvidParameter , u32 Copy_u32StartDelay , u32 Copy_u32StopTime);

ES_t TIMER0_enuGeneratePWM(u8 Copy_u8DutyCycle); // take duty cycle as (integer)%

ES_t TIMER0_enuCallBackOVF(void (*Copy_PfunCallBack)(void*) , void * Copy_PvidParameter);

ES_t TIMER0_enuCallBackCTC(void (*Copy_PfunCallBack)(void*) , void * Copy_PvidParameter);

ES_t TIMER0_enuSetPreload(u8 Copy_u8Preload);

ES_t TIMER0_enuSetCTC(u8 Copy_u8OCR0Value);

ES_t TIMER0_enuEnableOVFINTERRUPT(void);

ES_t TIMER0_enuEnableCTCINTERRUPT(void);

ES_t TIMER0_enuSetAsychDelay(u32 Copy_u8Time ,void(*Copy_pfunApp)(void*),void* Parameter); //Time in ms

ES_t TIMER0_enuSetSychDelay(u32 Copy_u8Time);//Time in ms










#endif /* TIMER0_INT_H_ */
