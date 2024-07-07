/*
 * USART_config.h
 *
 *  Created on: Feb 21, 2024
 *      Author: aya
 */

#ifndef MCAL_USART_USART_CONFIG_H_
#define MCAL_USART_USART_CONFIG_H_

//             NORMAL_SPEED , DOUBLE_SPEED
#define SPEED_MODE       DOUBLE_SPEED// NORMAL_SPEED

//TRANSMITTER ,RECIEVER   ,TRANSCIEVER
#define USART_MODE        TRANSCIEVER

#define BAUDRATE        9600UL

//NINE_BIT ,EIGHT_BIT,SEVEN_BIT,SIX_BIT  ,FIVE_BIT
#define DATA_LEN         EIGHT_BIT

//NO_PARITY  ,EVEN_PARITY,ODD_PARITY
#define PARITY_STATE     NO_PARITY

// ONE_STOP_BIT ,TWO_STOP_BIT
#define STOP_STATE       ONE_STOP_BIT

//  Asynch , synch
#define CLOCK_MODE        ASYNCH




//#define OPERATING_MODE      Asynch_Normal_Mode

//#define F_OSC          (1000000UL)


#endif /* MCAL_USART_USART_CONFIG_H_ */
