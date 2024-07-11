/******************************************************************/
/******************************************************************/
/************************  Author:Marina Malak  *******************/
/************************  Layer :MCAL          *******************/
/************************  SWC :  UART         *******************/
/************************  Version:1.00         *******************/
/******************************************************************/
/******************************************************************/

#include "../../LIB/errorState.h"
#include "../../LIB/types.h"
#include "../../LIB/Interrupt.h"

#include "../../MCAL/DIO/DIO_int.h"

#include "Uart_config.h"
#include "Uart_priv.h"

ES_t Uart_enuInit(void)
{
	ES_t Local_enuErrorState =ES_NOK;
    u8 Local_u8UCSRC=0;

 #if SPEED_MODE == NORMAL
    UCSRA &=~(1<<1);
 #elif SPEED_MODE == DOUBLE
    UCSRA |=(1<<1);
 #endif

#if DATA_LEN == EIGHT
    Local_u8UCSRC|=(1<<2);
    Local_u8UCSRC|=(1<<1);
#endif

#if PARITY_STATE == NO_PARITY
    Local_u8UCSRC &=~(1<<4);
    Local_u8UCSRC &=~(1<<5);
#elif PARITY_STATE ==ODD_PARITY
    Local_u8UCSRC |=(1<<4);
    Local_u8UCSRC |=(1<<5);
#elif PARITY_STATE ==EVEN_PARITY
    Local_u8UCSRC &=~(1<<4);
    Local_u8UCSRC |=(1<<5);
#endif

#if STOP_STATE == ONE_STOP_BIT
    Local_u8UCSRC &=~(1<<3);
#elif STOP_STATE == TWO_STOP_BIT
	Local_u8UCSRC |=(1<<3);
#endif

#if CLOCK_MODE == ASYNC
    Local_u8UCSRC &=~(1<<6);
#elif CLOCK_MODE == SYNC
    Local_u8UCSRC |=(1<<6);
#endif

 #if UART_MODE == TRANSCIEVER
	UCSRB|=(1<<4); //Receiver Enable
	UCSRB|=(1<<3); //Transmitter Enable
 #elif UART_MODE ==TRANSMITTER
	UCSRB|=(1<<3); //Transmitter Enable
 #elif UART_MODE ==RECIEVER
	UCSRB|=(1<<4); //Receiver Enable
#endif

    Local_u8UCSRC|=(1<<7);
	UCSRC=Local_u8UCSRC; //because access of this register is different

	u16 Local_u16UBRR = (u16)BUAD(BAUDRATE);

	Local_u16UBRR&=~(1<<15); // To use UBRR
	UBRRL=(u8)Local_u16UBRR;
	UBRRH =(Local_u16UBRR>>8);

	return Local_enuErrorState;
}

ES_t Uart_enuSendChar(u8 Copy_u8Char)
{
	ES_t Local_enuErrorState =ES_NOK;
	while(!((UCSRA >>5)&1));
	UDR=Copy_u8Char;

	return Local_enuErrorState;
}

ES_t Uart_enuRecieveChar(u8* Copy_pu8Char)
{
	ES_t Local_enuErrorState =ES_NOK;

	if(Copy_pu8Char != NULL)
	{
	while(!((UCSRA >>7)&1));
	*Copy_pu8Char=UDR;
	}
	else
	{
		Local_enuErrorState =ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}

ES_t Uart_enuSendString(const char* Copy_pcData)
{
	ES_t Local_enuErrorState =ES_NOK;

	if(Copy_pcData != NULL)
	{
		while(*Copy_pcData != '\0')
		{
			while(!((UCSRA >>5)&1));
			UDR=*Copy_pcData;
			Copy_pcData++;
		}
	}
	else
	{
		Local_enuErrorState =ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}

ES_t Uart_enuRecieveString(char* Copy_pcData)
{
	ES_t Local_enuErrorState =ES_NOK;

	u8 Local_u8Data=0 , Local_u8Index=0;
	u8 Local_u8Termination=0;

	if(Copy_pcData != NULL)
	{
		while(!((UCSRA >>7)&1));
		Local_u8Termination=UDR;

	   while(1)
	   {
			while(!((UCSRA >>7)&1));
			Local_u8Data=UDR;

			if(Local_u8Data == Local_u8Termination)
			{
				 Copy_pcData[Local_u8Index]='\0';
				 break;
			}
			else
			{
				Copy_pcData[Local_u8Index]=Local_u8Data;
				Local_u8Index++;
			}
	   }
	}
	else
	{
		Local_enuErrorState =ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}


