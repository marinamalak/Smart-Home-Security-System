/*
 * Switch_int.h
 *
 *  Created on: Jul 23, 2023
 *      Author: aya
 */

#ifndef SWITCH_INT_H_
#define SWITCH_INT_H_



ES_t Switch_enuInit(SW_t * copy_AstrSwitchs);

ES_t Switch_enuGetState(SW_t * copy_AstrSwitchs,u8 * copy_pu8SwState);

#endif /* SWITCH_INT_H_ */
