/*
 * ICU_HW_int.h
 *
 *  Created on: Feb 10, 2024
 *      Author: aya
 */

#ifndef MCAL_TIMER_ICU_HW_ICU_HW_INT_H_
#define MCAL_TIMER_ICU_HW_ICU_HW_INT_H_

ES_t ICU_enuInit(void);

ES_t ICU_enuEnableINTERRUPT(void);

ES_t ICU_enuDisableINTERRUPT(void);

ES_t ICU_enuSetTriggerEdge(u8 Copy_u8Edge);

ES_t ICU_enuReadInputCapture(u16 *Copy_pu16Value);

ES_t ICU_enuCallBack(void (*Copy_PfunCallBack)(void*) , void * Copy_PvidParameter);

#define ICU_RISING_EDGE_SELECT                             1
#define ICU_FALLING_EDGE_SELECT                            2

#endif /* MCAL_TIMER_ICU_HW_ICU_HW_INT_H_ */
