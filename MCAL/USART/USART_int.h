/*
 * USART_int.h
 *
 *  Created on: Feb 21, 2024
 *      Author: aya
 */

#ifndef MCAL_USART_USART_INT_H_
#define MCAL_USART_USART_INT_H_

ES_t USART_enuInit();//u16 Copy_baud

ES_t USART_enuSendChar(u8 Copy_u8data);

ES_t USART_enuRecieveChar(u8 *Copy_pu8data);

ES_t USART_enuSendString(const char *Copy_pcData);

ES_t USART_enuRecieveString(char *Copy_pcData);



ES_t USART_enuTransmit(u16 Copy_u16data);

ES_t USART_enuRecieve(u16 *Copy_u16data);

ES_t USART_enuEnableTransmitter(void);

ES_t USART_enuEnableReceiver(void);

#endif /* MCAL_USART_USART_INT_H_ */
