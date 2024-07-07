/*
 * LCD_config.h
 *
 *  Created on: Aug 8, 2023
 *      Author: aya
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_


/*  LCD_MODE  */
#define LCD_MODE EIGHT_BIT

/* control pins */
#define RS_PORT  DIO_u8PORTD
#define RS_PIN   DIO_u8PIN0

#define RW_PORT  DIO_u8PORTD
#define RW_PIN   DIO_u8PIN1

#define EN_PORT  DIO_u8PORTD
#define EN_PIN   DIO_u8PIN3

/* data pins */
#define D7_PORT  DIO_u8PORTC
#define D7_PIN   DIO_u8PIN7

#define D6_PORT  DIO_u8PORTC
#define D6_PIN   DIO_u8PIN6

#define D5_PORT  DIO_u8PORTC
#define D5_PIN   DIO_u8PIN5

#define D4_PORT  DIO_u8PORTC
#define D4_PIN   DIO_u8PIN4

#define D3_PORT  DIO_u8PORTC
#define D3_PIN   DIO_u8PIN3

#define D2_PORT  DIO_u8PORTC
#define D2_PIN   DIO_u8PIN2

#define D1_PORT  DIO_u8PORTC
#define D1_PIN   DIO_u8PIN1

#define D0_PORT  DIO_u8PORTC
#define D0_PIN   DIO_u8PIN0




#endif /* LCD_CONFIG_H_ */
