/*
 * INT_int.h
 *
 *  Created on: Oct 23, 2023
 *      Author: aya
 */

#ifndef MCAL_INT_INT_H_
#define MCAL_INT_INT_H_

ES_t EINT_enuInit(EINT_t * Copy_pstrEINT);

ES_t EINT_enuEnableINT(u8 Copy_u8ID);

ES_t EINT_enuDisableINT(u8 Copy_u8ID);

ES_t EINT_enuSelectSenceLevel(u8 Copy_u8ID , u8 Copy_u8SenceLevel);

ES_t EINT_enuCallBack(void *(Copy_pfun)(void *), void *Copy_pvoid,u8 Copy_u8ID);

//ES_t EINT_enuCallBack(void *(Copy_pfun)(void),u8 Copy_u8ID);


#define LOW_LEVEL          1
#define ANY_LOG_CHANGE     2
#define RISING_EDGE        3
#define FALLING_EDGE       4


#endif /* MCAL_INT_INT_H_ */
