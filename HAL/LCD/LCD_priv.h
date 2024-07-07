/*
 * LCD_priv.h
 *
 *  Created on: Aug 8, 2023
 *      Author: aya
 */

#ifndef LCD_PRIV_H_
#define LCD_PRIV_H_

#define EIGHT_BIT  5
#define FOUR_BIT   9

#define LCD_MASK_BIT  1

static inline void LCD_invidSendCommand(u8 Copy_u8Command);

static void LCD_vidLatch(u8 Copy_u8Data);


u32 POWER_u32PowerNumbers(u32 Copy_u32Number , u8 Copy_u8Power);


u8 Array_u8Num[] = {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39};





#define		EIGHT_BIT_MODE		0x38
#define		FOUR_BIT_MODE		0x28

#define		CLEAR_DISPLAY					0x01

#define 	RETURN_HOME						0x02

#define 	DECREMENT_CURSOR_TO_LEFT		0x04
#define 	INCREMENT_CURSOR_TO_RIGHT		0x06

#define 	SHIFT_DISPLAY_TO_RIGHT			0x05
#define 	SHIFT_DISPLAY_TO_LEFT			0x07


#define 	DISPLAY_OFF_CURSOR_OFF			0x08
#define 	DISPLAY_OFF_CURSOR_ON			0x0A
#define 	DISPLAY_ON_CURSOR_OFF			0x0C
#define 	DISPLAY_ON_CURSOR_BLINK			0x0E


#define 	SHIFT_CURSOR_POSITION_TO_LEFT	0x10
#define 	SHIFT_CURSOR_POSITION_TO_RIGHT	0x14

#define 	SHIFT_ENTRIE_DISPLAY_TO_LEFT	0x18
#define 	SHIFT_ENTRIE_DISPLAY_TO_RIGHT	0x1C

#define 	FORCE_CURSOR_START_FIRST_LINE	0x80
#define 	FORCE_CURSOR_START_SECOND_LINE	0xC0

#define     GO_TO_CGRAM						0x40



#define 	LCD_ZERO		0
#define 	LCD_ONE			1
#define 	LCD_TWO			2
#define 	LCD_THREE		3
#define 	LCD_FOUR		4
#define 	LCD_FIVE		5
#define 	LCD_SIX			6
#define 	LCD_SEVEN		7
#define 	LCD_EIGHT		8
#define 	LCD_TEN			10

#endif /* LCD_PRIV_H_ */
