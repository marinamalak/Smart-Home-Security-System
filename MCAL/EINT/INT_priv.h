/*
 * INT_priv.h
 *
 *  Created on: Oct 23, 2023
 *      Author: aya
 */

#ifndef MCAL_INT_PRIV_H_
#define MCAL_INT_PRIV_H_

#define EINT_ENABLED    1
#define EINT_DISABLED   0

#define EINT_LOW_LEVEL          1
#define EINT_ANY_LOG_CHANGE     2
#define EINT_RISING_EDGE        3
#define EINT_FALLING_EDGE       4




#define MCUCR    *((volatile u8*)0x55)
#define MCUCSR   *((volatile u8*)0x54)
#define GICR     *((volatile u8*)0x5B)
#define GIFR     *((volatile u8*)0x5A)






#endif /* MCAL_INT_PRIV_H_ */
