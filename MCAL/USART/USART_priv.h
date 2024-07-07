/*
 * USART_priv.h
 *
 *  Created on: Feb 21, 2024
 *      Author: aya
 */

#ifndef MCAL_USART_USART_PRIV_H_
#define MCAL_USART_USART_PRIV_H_

#define F_CPU    1000000UL
#define BUAD(BUAD_VAL)         (u16)(F_CPU/(SPEED_MODE*8*BUAD_VAL)-1)

//speed mode
#define NORMAL_SPEED       2
#define DOUBLE_SPEED       1

//USART_MODE
#define TRANSMITTER        8
#define RECIEVER           16
#define TRANSCIEVER        24

//DATA_LEN
#define NINE_BIT           7
#define EIGHT_BIT          3
#define SEVEN_BIT          2
#define SIX_BIT            1
#define FIVE_BIT           0

//PARITY_STATE
#define NO_PARITY          0
#define EVEN_PARITY        2
#define ODD_PARITY         3

//STOP_STATE
#define ONE_STOP_BIT        0
#define TWO_STOP_BIT        1

//CLOCK_MODE
#define ASYNCH             0
#define SYNCH              1


/*
//operating mode
#define Asynch_Normal_Mode             1
#define Asynch_Double_Speed_Mode       2
#define Synch_Master_Mode        3
*/




#define UBRRL  *((volatile u8 *)0x29)  //USART Baud Rate Registers
#define UBRRH  *((volatile u8 *)0x40)

#define UCSRC  *((volatile u8 *)0x40)  //USART Control and Status Register C
#define UCSRC_URSEL    7        // Register Select
#define UCSRC_UMSEL    6        // USART Mode Select
#define UCSRC_UPM1     5        // Parity Mode
#define UCSRC_UPM0     4
#define UCSRC_USBS     3        // Stop Bit Select
#define UCSRC_UCSZ1    2        // Character Size
#define UCSRC_UCSZ0    1
#define UCSRC_UCPOL    0        // Clock Polarity

#define UCSRB   *((volatile u8 *)0x2A)  //USART Control and Status Register B
#define UCSRB_RXCIE     7         // RX Complete Interrupt Enable
#define UCSRB_TXCIE     6         // TX Complete Interrupt Enable
#define UCSRB_UDRIE     5         // USART Data Register Empty Interrupt Enable
#define UCSRB_RXEN      4         // Receiver Enable
#define UCSRB_TXEN      3         // Transmitter Enable
#define UCSRB_UCSZ2     2         // Character Size
#define UCSRB_RXB8      1         // Receive Data Bit 8
#define UCSRB_TXB8      0         // Transmit Data Bit 8

#define UCSRA   *((volatile u8 *)0x2B)   //USART Control and Status Register A
#define UCSRA_RXC       7         // USART Receive Complete
#define UCSRA_TXC       6         // USART Transmit Complete
#define UCSRA_UDRE      5         // USART Data Register Empty
#define UCSRA_FE        4         // Frame Error
#define UCSRA_DOR       3         // Data OverRun
#define UCSRA_PE        2         // Parity Error
#define UCSRA_U2X       1         // Double the USART Transmission Speed
#define UCSRA_MPCM      0         // Multi-processor Communication Mode


#define UDR   *((volatile u8 *)0x2C)      //USART I/O Data Register

#endif /* MCAL_USART_USART_PRIV_H_ */
