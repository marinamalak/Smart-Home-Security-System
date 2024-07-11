/*
 * Interrupt.h
 *
 *  Created on: Oct 20, 2023
 *      Author: Admin
 */

#ifndef HAL_INTERRUPT_H_
#define HAL_INTERRUPT_H_

#define  ISR(VECT_NUM)   void VECT_NUM (void) __attribute__ ((signal));\
                         void VECT_NUM (void)

/*EXTI Request 0*/
#define   VECT_INT0                 __vector_1

/*EXTI Request 1*/
#define   VECT_INT1                 __vector_2

/*EXTI Request 2*/
#define   VECT_INT2                 __vector_3

/*TIMER2 Compare Match*/
#define   VECT_TIMER2_COMP          __vector_4

/*TIMER2 OverFlow*/
#define   VECT_TIMER2_OVF           __vector_5

/*TIMER1 Capture Event*/
#define   VECT_TIMER1_CAPT          __vector_6

/*TIMER1 Compare Match A*/
#define   VECT_TIMER1_COMPA         __vector_7

/*TIMER1 Compare Match B*/
#define   VECT_TIMER1_COMPB         __vector_8

/*TIMER1 OverFlow*/
#define   VECT_TIMER1_OVF           __vector_9

/*TIMER0 Compare Match*/
#define   VECT_TIMER0_COMP          __vector_10

/*TIMER0 OverFlow*/
#define   VECT_TIMER0_OVF           __vector_11

/*SPI Serial Transfer Complete*/
#define   VECT_SPI_STC              __vector_12

/*USART RX Complete*/
#define   VECT_USART_RXC            __vector_13

/*USART Data Register Empty*/
#define   VECT_USART_UDRE           __vector_14

/*USART TX Copmlete*/
#define   VECT_USART_TXC            __vector_15

/*ADC Conversion Complete*/
#define   VECT_ADC                  __vector_16

/*EEPROM Ready*/
#define   VECT_EE_RDY               __vector_17

/*Analog Comparator*/
#define   VECT_ANA_COMP             __vector_18

/*Two_wire Serial Interface*/
#define   VECT_TWI                  __vector_19

/*Store Program Memory Ready*/
#define   VECT_SPM_RDY              __vector_20

#endif /* HAL_INTERRUPT_H_ */
