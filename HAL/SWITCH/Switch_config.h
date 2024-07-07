/*
 * Switch_config.h
 *
 *  Created on: Jul 23, 2023
 *      Author: aya
 */

#ifndef SWITCH_CONFIG_H_
#define SWITCH_CONFIG_H_

#define SW_NUM 3

typedef struct
{
	u8 SW_PortID;
	u8 SW_PinID;
	u8 SW_Status;
}SW_t;

#endif /* SWITCH_CONFIG_H_ */
