/*
 * Interrupt.h
 *
 *  Created on: Oct 23, 2023
 *      Author: aya
 */

#ifndef MCAL_EINT_INTERRUPT_H_
#define MCAL_EINT_INTERRUPT_H_

#define ISR(VECT_NUM)      void VECT_NUM(void)__attribute__((signal));\
	                       void VECT_NUM (void)

#define VECT_INT0          __vector_1
#define VECT_INT1          __vector_2
#define VECT_INT2          __vector_3

#define VECT_ADC           __vector_16

#define VECT_TIMER0_OVF          __vector_11
#define VECT_TIMER0_CTC          __vector_10

#define VECT_TIMER1_ICU          __vector_6
#define VECT_TIMER1_COMA         __vector_7
#define VECT_TIMER1_COMB         __vector_8
#define VECT_TIMER1_OVF          __vector_9

#endif /* MCAL_EINT_INTERRUPT_H_ */
