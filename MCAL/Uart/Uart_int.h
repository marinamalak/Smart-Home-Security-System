

#ifndef MCAL_UART_UART_INT_H_
#define MCAL_UART_UART_INT_H_

ES_t Uart_enuInit(void);

ES_t Uart_enuSendChar(u8 Copy_u8Char);

ES_t Uart_enuRecieveChar(u8* Copy_pu8Char);

ES_t Uart_enuSendString(const char* Copy_pcData);

ES_t Uart_enuRecieveString(char* Copy_pcData);

#endif /* MCAL_UART_UART_INT_H_ */
