/*
 * TIMER0_priv.h
 *
 *  Created on: Dec 9, 2023
 *      Author: aya
 */

#ifndef TIMER0_PRIV_H_
#define TIMER0_PRIV_H_




#define TIMER0_F_CPU								8000
#define TIMER0_OVF_COUNTS							256
#define TIMER0_PHASE_COUNTS							510
#define TIMER0_PERCENTAGE_RATIO						100.0
#define TIMER0_FIXED_NUM_TWO						2.0


//CALLBACK
#define TIMER0_DELAY_CALLBACK						0
#define TIMER0_OVF_CALLBACK							1
#define TIMER0_CTC_CALLBACK							2
#define TIMER0_CALL_BACK							3

//Prescaler

#define TIMER0_NO_CLOCK_SOURCE						0

#define TIMER0_PRESCALER_1							1

#define TIMER0_PRESCALER_8							8

#define TIMER0_PRESCALER_64							64

#define TIMER0_PRESCALER_256						256

#define TIMER0_PRESCALER_1024						1024

#define TIMER0_EXT_CLOCK_FALLING_EDGE				13

#define TIMER0_EXT_CLOCK_RISING_EDGE				15


//Mode

#define TIMER0_OVER_FLOW							17

#define TIMER0_COMPARE_MATCH						19

#define TIMER0_PHASE_CORRECT_PWM					21

#define TIMER0_FAST_PWM								23


//OC0 State

#define TIMER0_OVF_DISCONNECT_OC0					25

#define TIMER0_CTC_DISCONNECT_OC0					27

#define TIMER0_CTC_TOGGLE_OC0						29

#define TIMER0_CTC_CLEAR_OC0						31

#define TIMER0_CTC_SET_OC0							33

#define TIMER0_FAST_PMW_CLEAR_CTC_SET_TOP			35

#define TIMER0_FAST_PMW_SET_CTC_CLEAR_TOP			37

#define TIMER0_PHASE_CLEAR_CTC_SET_TOP				39

#define TIMER0_PHASE_SET_CTC_CLEAR_TOP				41
















#endif /* TIMER0_PRIV_H_ */
