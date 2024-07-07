/*
 * TWI_priv.h
 *
 *  Created on: May 2, 2024
 *      Author: aya
 */

#ifndef MCAL_I2C_TWI_TWI_PRIV_H_
#define MCAL_I2C_TWI_TWI_PRIV_H_


#define F_CPU    8000000UL
#define BITRATE(IIC_SPEED)           ((F_CPU -16ul*IIC_SPEED)/(2ul*IIC_SPEED*IIC_PRES))

#define IIC_MASTER            0
#define IIC_SLAVE             1

//IIC_GENERAL_CALL
#define IIC_RECOG             1
#define IIC_NOT_RECOG         0


#define TWBR           *((volatile u8 *)0x20)         // TWI Bit Rate Register –


#define TWCR           *((volatile u8 *)0x56)          //TWI Control Register –
#define TWCR_TWINT     7           // TWI Interrupt Flag
#define TWCR_TWEA      6           // TWI Enable Acknowledge Bit
#define TWCR_TWSTA     5           // TWI START Condition Bit
#define TWCR_TWSTO     4           // TWI STOP Condition Bit
#define TWCR_TWWC      3           // TWI Write Collision Flag
#define TWCR_TWEN      2           // TWI Enable Bit
#define TWCR_TWIE      0           // TWI Interrupt Enable


#define TWSR           *((volatile u8 *)0x21)          // TWI Status Register –
#define TWSR_TWS       3            // TWI Status
#define TWSR_TWPS1     1            // TWI Prescaler Bits
#define TWSR_TWPS0     0

#define TWDR           *((volatile u8 *)0x23)          // TWI Data Register –


#define TWAR           *((volatile u8 *)0x22)         // TWI (Slave) Address Register
#define TWAR_TWA        1          // TWI (Slave) Address Register
#define TWAR_TWGCE      0          // TWI General Call Recognition Enable Bit








#endif /* MCAL_I2C_TWI_TWI_PRIV_H_ */
