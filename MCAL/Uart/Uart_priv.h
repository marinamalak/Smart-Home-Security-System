
#ifndef MCAL_UART_UART_PRIV_H_
#define MCAL_UART_UART_PRIV_H_

#define BUAD(BAUD_VAL)  (u16)((8000000ul/(SPEED_MODE*8*BAUDRATE))-1)

#define NORMAL  2
#define DOUBLE  1

#define TRANSMITTER  1
#define RECIEVER     2
#define TRANSCIEVER  3

#define FIVE    5
#define SIX     6
#define SEVEN   7
#define EIGHT   8
#define NINE    9

#define NO_PARITY    0
#define ODD_PARITY   1
#define EVEN_PARITY  2

#define ONE_STOP_BIT    5
#define TWO_STOP_BIT    6

#define ASYNC  1
#define SYNC   5

#define UDR *((volatile u8*)0x2c)

#define UCSRA *((volatile u8*)0x2b)

#define UCSRB *((volatile u8*)0x2a)

#define UCSRC *((volatile u8*)0x40)

#define UBRRL *((volatile u8*)0x29)

#define UBRRH *((volatile u8*)0x40)



#endif /* MCAL_UART_UART_PRIV_H_ */
