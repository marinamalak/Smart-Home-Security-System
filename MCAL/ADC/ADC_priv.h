/*
 * ADC_priv.h
 *
 *  Created on: Nov 2, 2023
 *      Author: aya
 */

#ifndef MCAL_ADC_ADC_PRIV_H_
#define MCAL_ADC_ADC_PRIV_H_

#define PRES_2      1
#define PRES_4      2
#define PRES_8      3
#define PRES_16     4
#define PRES_32     5
#define PRES_64     6
#define PRES_128    7

#define AVCC_REF       10
#define AREF_REF       20
#define INTERNAL       30

#define RIGHT_ADJ      99
#define LEFT_ADJ       88

#define FREE_RUNNING                 1
#define ANALOG_COMPARATOR            2
#define EXT_INT0_REQ                     3
#define TIM_COUNT_0_COMPARE_MATCH    4
#define TIM_COUNT_0_OVERFLOW         5
#define TIM_COUNT_1_COMPARE_MATCH    6
#define TIM_COUNT_1_OVERFLOW         7
#define TIM_COUNT_1_CAP_EVENT        8


#define ADMUX         *((u8*)0x27)
#define ADCSRA        *((u8*)0x26)
#define ADCH          *((volatile u8*)0x25)
#define ADCL          *((volatile u8*)0x24)

#define SFIOR         *((u8*)0x50)



#endif /* MCAL_ADC_ADC_PRIV_H_ */
