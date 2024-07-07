/*
 * TWI_config.h
 *
 *  Created on: May 2, 2024
 *      Author: aya
 */

#ifndef MCAL_I2C_TWI_TWI_CONFIG_H_
#define MCAL_I2C_TWI_TWI_CONFIG_H_


#define IIC_MODE           IIC_MASTER

#define IIC_CLOCK_SPEED            100000ul

#define IIC_PRES                   1ul

#define IIC_NODE_ADDRESS          5// 2      // 2>>119

#define IIC_GENERAL_CALL           IIC_NOT_RECOG      // 0/1

#endif /* MCAL_I2C_TWI_TWI_CONFIG_H_ */
