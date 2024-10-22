/*
 * TIMER0_config.h
 *
 *  Created on: Dec 9, 2023
 *      Author: aya
 */

#ifndef TIMER0_CONFIG_H_
#define TIMER0_CONFIG_H_

#define TIMER0_PRESCALER				TIMER0_PRESCALER_1024//TIMER0_PRESCALER_8//  //TIMER0_PRESCALER_1024

#define TIMER0_MODE					    TIMER0_OVER_FLOW//TIMER0_FAST_PWM	 //TIMER0_COMPARE_MATCH	//TIMER0_PHASE_CORRECT_PWM

#define TIMER0_OC0_PIN_STATE			TIMER0_OVF_DISCONNECT_OC0//TIMER0_FAST_PMW_CLEAR_CTC_SET_TOP  //TIMER0_CTC_DISCONNECT_OC0   //TIMER0_CTC_TOGGLE_OC0//TIMER0_PHASE_CLEAR_CTC_SET_TOP







#endif /* TIMER0_CONFIG_H_ */
