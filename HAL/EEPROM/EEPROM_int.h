/*
 * EEPROM_int.h
 *
 *  Created on: Jun 24, 2024
 *      Author: aya
 */

#ifndef HAL_EEPROM_EEPROM_INT_H_
#define HAL_EEPROM_EEPROM_INT_H_

ES_t EEPROM_enuInit(void);

ES_t EEPROM_enuWriteData(u16 Copy_u16Address , u8 Copy_u8Data);

ES_t EEPROM_enuReadData(u16 Copy_u16Address , u8 *Copy_u8Data);



#endif /* HAL_EEPROM_EEPROM_INT_H_ */
