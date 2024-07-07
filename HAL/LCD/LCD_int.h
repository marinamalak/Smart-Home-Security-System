/*
 * LCD_int.h
 *
 *  Created on: Aug 8, 2023
 *      Author: aya
 */

#ifndef LCD_INT_H_
#define LCD_INT_H_

ES_t LCD_enuInit(void);

ES_t LCD_enuDisplayChar(u8 Copy_u8Data);

ES_t LCD_enuSendCommand(u8 Copy_u8Command);

ES_t LCD_enuDisplayString(u8 *Copy_pu8Data);

ES_t LCD_enuGoToPosition (u8 Copy_u8Row , u8 Copy_u8Col);

ES_t LCD_enuDisplayNum(u8 Copy_u8Num);


ES_t LCD_enuSendSpecialNumber(u32 Copy_u32Number);


ES_t LCD_enuClearLcd(void);

#endif /* LCD_INT_H_ */
