/*
 * TIMER1_priv.h
 *
 *  Created on: Feb 10, 2024
 *      Author: aya
 */

#ifndef MCAL_TIMER_TIMER1_TIMER1_PRIV_H_
#define MCAL_TIMER_TIMER1_TIMER1_PRIV_H_


#define TIMER1_COMA_CALLBACK						0
#define TIMER1_COMB_CALLBACK						1
#define TIMER1_OVF_CALLBACK							2
#define TIMER1_CALL_BACK							3



//Mode

#define TIMER1_NORMAL							           0

#define TIMER1_PHASE_CORRECT_PWM_8BIT                      1

#define TIMER1_PHASE_CORRECT_PWM_9BIT                      2

#define TIMER1_PHASE_CORRECT_PWM_10BIT                     3

#define TIMER1_COMPARE_MATCH_TOP_OCR1A			           4

#define TIMER1_FAST_PMW_8BIT                               5

#define TIMER1_FAST_PMW_9BIT                               6

#define TIMER1_FAST_PMW_10BIT                              7

#define TIMER1_PHASE_FREQ_CORRECT_TOP_ICR1                 8

#define TIMER1_PHASE_FREQ_CORRECT_TOP_OCR1A                9

#define TIMER1_PHASE_CORRECT_TOP_ICR1                      10

#define TIMER1_PHASE_CORRECT_TOP_OCR1A                     11

#define TIMER1_COMPARE_MATCH_TOP_ICR1			           12

#define TIMER1_FAST_PWM_TOP_ICR1					       14

#define TIMER1_FAST_PWM_TOP_OCR1A					       15


//OC1A/OC1B State

#define TIMER1_NORMAL_DISCONNECT_OC1A_B				25

#define TIMER1_CTC_DISCONNECT_OC1A_B				27

#define TIMER1_CTC_TOGGLE_OC1A_B					29

#define TIMER1_CTC_CLEAR_OC1A_B						31

#define TIMER1_CTC_SET_OC1A_B						33

#define TIMER1_FAST_PMW_CLEAR_CTC_SET_BOTTOM		35  //NON_INVERTING

#define TIMER1_FAST_PMW_SET_CTC_CLEAR_BOTTOM		37   //INVERTING

#define TIMER1_PHASE_CLEAR_CTC_SET_TOP				39

#define TIMER1_PHASE_SET_CTC_CLEAR_TOP				41

//Prescaler

#define TIMER1_NO_CLOCK_SOURCE						0

#define TIMER1_PRESCALER_1							1

#define TIMER1_PRESCALER_8							8

#define TIMER1_PRESCALER_64							64

#define TIMER1_PRESCALER_256						256

#define TIMER1_PRESCALER_1024						1024

#define TIMER1_EXT_CLOCK_FALLING_EDGE				13

#define TIMER1_EXT_CLOCK_RISING_EDGE				15

#endif /* MCAL_TIMER_TIMER1_TIMER1_PRIV_H_ */
