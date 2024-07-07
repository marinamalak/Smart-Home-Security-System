/*
 * WDT_int.h
 *
 *  Created on: Feb 10, 2024
 *      Author: aya
 */

#ifndef MCAL_TIMER_WATCHDOG_WDT_INT_H_
#define MCAL_TIMER_WATCHDOG_WDT_INT_H_

//WATCH DOG FUNCTION

ES_t WDT_enuSleep(u8 Copy_u8SleepTime);

ES_t WDT_enuEnable(void);

ES_t WDT_enuDisable(void);

//WATCH DOG SLEEP TIME

#define SLEEP_TIME_16_MS            0 //0b00000000
#define SLEEP_TIME_32_MS            1 //0b00000001
#define SLEEP_TIME_65_MS            2 //0b00000010
#define SLEEP_TIME_130_MS           3 //0b00000011
#define SLEEP_TIME_260_MS           4 //0b00000100
#define SLEEP_TIME_520_MS           5 //0b00000101
#define SLEEP_TIME_1000_MS          6 //0b00000110
#define SLEEP_TIME_2100_MS          7 //0b00000111

#endif /* MCAL_TIMER_WATCHDOG_WDT_INT_H_ */
