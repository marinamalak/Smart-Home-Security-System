/*
 * TWI_int.h
 *
 *  Created on: May 2, 2024
 *      Author: aya
 */

#ifndef MCAL_I2C_TWI_TWI_INT_H_
#define MCAL_I2C_TWI_TWI_INT_H_

ES_t IIC_enuInit(void);

ES_t IIC_enuStartCondition(void);

ES_t IIC_enuRepeatedStartCondition(void);

ES_t IIC_enuStopCondition(void);

ES_t IIC_enuWriteSlaveAddress(u8 Copy_u8SlaveAddress, u8 Copy_u8Operation);

ES_t IIC_enuWriteData(u8 Copy_u8Data);

ES_t IIC_enuCheckMyAddress(void);

ES_t IIC_enuReadData(u8 * Copy_pu8Data);

#endif /* MCAL_I2C_TWI_TWI_INT_H_ */
