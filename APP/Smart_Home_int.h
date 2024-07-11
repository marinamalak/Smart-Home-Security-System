/*
 * Smart_Home.h
 *
 *  Created on: Jul 8, 2024
 *      Author: Admin
 */

#ifndef APP_SMART_HOME_INT_H_
#define APP_SMART_HOME_INT_H_

ES_t Smart_Home_enuInit(void);

ES_t APP_enuStart();

ES_t Login(void);

ES_t CHECK_temp(void);

ES_t CHECK_gas(void);

ES_t CHECK_windowAttack(void);

ES_t CHECK_packageThief(void);

ES_t UART(void);

#endif /* APP_SMART_HOME_INT_H_ */
