/*
 * Smart_Home_priv.h
 *
 *  Created on: Jul 8, 2024
 *      Author: Admin
 */

#ifndef APP_SMART_HOME_PRIV_H_
#define APP_SMART_HOME_PRIV_H_


//Alarm States
#define NORMAL        0
#define FIRE          1
#define GAS           2
#define ATTACK        3
#define THIEF         4


static ES_t OPEN_Door(void);
static ES_t LED_Indicators(void);
static ES_t Alarm_ON(void);
static ES_t Alarm_OFF(void);
static void Read_Sensors(void);
static ES_t Compare(u8* str1 ,u8* str2);

#endif /* APP_SMART_HOME_PRIV_H_ */
