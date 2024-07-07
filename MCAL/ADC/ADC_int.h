/*
 * ADC_int.h
 *
 *  Created on: Nov 2, 2023
 *      Author: aya
 */

#ifndef MCAL_ADC_ADC_INT_H_
#define MCAL_ADC_ADC_INT_H_

ES_t ADC_enuInit(void);

ES_t ADC_enuStartConversion(void);

ES_t ADC_enuPollingSystem(void);

ES_t ADC_enuReadHighValue(u8 *Copy_pu8Value);

ES_t ADC_enuRead(u16 *Copy_pu16Value);

ES_t ADC_enuCallBack(void(Copy_pfunAppFun)(void*),void *Copy_pvidAppParameter);

ES_t ADC_enuSelectChannel(u8 Copy_u8ChannelID);

ES_t ADC_enuEnableTriggeringMode(u8 Copy_u8TriggeringSource);

ES_t ADC_enuDisableTriggeringMode(void);

ES_t ADC_enuEnableInterruptMode(void);

ES_t ADC_enuDisableInterruptMode(void);

ES_t ADC_enuEnable(void);

ES_t ADC_enuDisable(void);

#define ADC_FREE_RUNNING                 1
#define ADC_ANALOG_COMPARATOR            2
#define ADC_EXT_INT0_REQ                     3
#define ADC_TIM_COUNT_0_COMPARE_MATCH    4
#define ADC_TIM_COUNT_0_OVERFLOW         5
#define ADC_TIM_COUNT_1_COMPARE_MATCH    6
#define ADC_TIM_COUNT_1_OVERFLOW         7
#define ADC_TIM_COUNT_1_CAP_EVENT        8


#endif /* MCAL_ADC_ADC_INT_H_ */
