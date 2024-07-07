/*
 * USART_prog.c
 *
 *  Created on: Feb 21, 2024
 *      Author: aya
 */

#include "../../LIB/errorState.h"
#include "../../LIB/types.h"


#include "USART_priv.h"
#include "USART_config.h"


ES_t USART_enuInit()//u16 Copy_u16baud
{
	ES_t Local_enuErrorState=ES_NOK;

#if SPEED_MODE==NORMAL_SPEED
	UCSRA &=~(1<<UCSRA_U2X);
	Local_enuErrorState=ES_OK;
#elif SPEED_MODE==DOUBLE_SPEED
	UCSRA |=(1<<UCSRA_U2X);
	Local_enuErrorState=ES_OK;
#else

#error "SPEED mode selection is wrong"
#endif

#if USART_MODE==TRANSCIEVER
	UCSRB |=(3<<UCSRB_TXEN);
	Local_enuErrorState=ES_OK;
#elif USART_MODE==TRANSMITTER
	UCSRB |=(1<<UCSRB_TXEN);
	Local_enuErrorState=ES_OK;
#elif USART_MODE==RECIEVER
	UCSRB |=(1<<UCSRB_RXEN);
	Local_enuErrorState=ES_OK;
#else

#error "UART mode selection is wrong"
#endif


	u8 Local_u8UCSRC=0;
#if DATA_LEN==NINE_BIT
	Local_u8UCSRC |=(3<<UCSRC_UCSZ0);
	UCSRB |=(1<<UCSRB_UCSZ2);
	Local_enuErrorState=ES_OK;

#elif DATA_LEN==EIGHT_BIT
	Local_u8UCSRC |=(3<<UCSRC_UCSZ0);
	UCSRB &=~(1<<UCSRB_UCSZ2);
	Local_enuErrorState=ES_OK;

#elif DATA_LEN==SEVEN_BIT
	Local_u8UCSRC &=~(1<<UCSRC_UCSZ0);
	Local_u8UCSRC |=(1<<UCSRC_UCSZ1);
	UCSRB &=~(1<<UCSRB_UCSZ2);
	Local_enuErrorState=ES_OK;

#elif DATA_LEN==SIX_BIT
	Local_u8UCSRC |=(1<<UCSRC_UCSZ0);
	Local_u8UCSRC &=~(1<<UCSRC_UCSZ1);
	UCSRB &=~(1<<UCSRB_UCSZ2);
	Local_enuErrorState=ES_OK;

#elif DATA_LEN==FIVE_BIT
	Local_u8UCSRC &=~(1<<UCSRC_UCSZ0);
	Local_u8UCSRC &=~(1<<UCSRC_UCSZ1);
	UCSRB &=~(1<<UCSRB_UCSZ2);
	Local_enuErrorState=ES_OK;

#else

#error "UART DATA Length  selection is wrong"
#endif


#if PARITY_STATE==NO_PARITY
	Local_u8UCSRC &=~(3<<UCSRC_UPM0);
	Local_enuErrorState=ES_OK;

#elif PARITY_STATE==EVEN_PARITY
	Local_u8UCSRC &=~(1<<UCSRC_UPM0);
	Local_u8UCSRC |=(1<<UCSRC_UPM1);
	Local_enuErrorState=ES_OK;

#elif PARITY_STATE==ODD_PARITY
	Local_u8UCSRC |=(3<<UCSRC_UPM0);
	Local_enuErrorState=ES_OK;

#else

#error "UART PARITY State  selection is wrong"
#endif


#if STOP_STATE==ONE_STOP_BIT
	Local_u8UCSRC &=~(1<<UCSRC_USBS);
	Local_enuErrorState=ES_OK;

#elif STOP_STATE==TWO_STOP_BIT
	Local_u8UCSRC |=(1<<UCSRC_USBS);
	Local_enuErrorState=ES_OK;

#else

#error "UART STOP State  selection is wrong"
#endif


#if CLOCK_MODE==ASYNCH
	Local_u8UCSRC &=~(1<<UCSRC_UMSEL);
	Local_enuErrorState=ES_OK;

#elif CLOCK_MODE==SYNCH
	Local_u8UCSRC |=(1<<UCSRC_UMSEL);
	Local_enuErrorState=ES_OK;

#else

#error "UART CLOCK MODE  selection is wrong"
#endif


	Local_u8UCSRC |=(1<<UCSRC_URSEL);
	UCSRC = Local_u8UCSRC;

	u16 Local_u16UBRR = BUAD(BAUDRATE);

	Local_u16UBRR &=~(1<<15); //URSEL=0 to select UBRRH

	UBRRL =(u8)Local_u16UBRR; // I think there are error here
	UBRRH =(Local_u16UBRR>>8);
	Local_enuErrorState=ES_OK;


	return Local_enuErrorState;
}


ES_t USART_enuSendChar(u8 Copy_u8data)
{
	ES_t Local_enuErrorState=ES_NOK;

	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UCSRA_UDRE)));

	UDR = Copy_u8data;

	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}

ES_t USART_enuRecieveChar(u8 *Copy_pu8data)
{
	ES_t Local_enuErrorState=ES_NOK;


	if (Copy_pu8data!=NULL)
	{
		/* Wait for data to be received */
		while ( !(UCSRA & (1<<UCSRA_RXC)) );

		*Copy_pu8data = UDR;

		Local_enuErrorState=ES_OK;
	}
	else
	{
		Local_enuErrorState=ES_NULL_POINTER;
	}

	return Local_enuErrorState;
}

ES_t USART_enuSendString(const char *Copy_pcData)
{
	ES_t Local_enuErrorState=ES_NOK;

	while(*Copy_pcData != '\0')
	{
		/* Wait for empty transmit buffer */
		while ( !( UCSRA & (1<<UCSRA_UDRE)));

		UDR = *Copy_pcData;
		Copy_pcData++;
	}

	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}

/* Enter  >> \r=13  , \n */

ES_t USART_enuRecieveString(char *Copy_pcData)
{
	ES_t Local_enuErrorState=ES_NOK;

	u8 Local_u8Data=0,Local_u8Index=0;
	/* //  Receive using Enter
	while(1)
	{
		/* Wait for data to be received *
		while ( !(UCSRA & (1<<UCSRA_RXC)) );

		Local_u8Data = UDR;

		if(Local_u8Data =='\r'  || Local_u8Data == '\n')
		{
			Copy_pcData[Local_u8Index]='\0';
			break;
		}
		else
		{
			Copy_pcData[Local_u8Index]=Local_u8Data;
			Local_u8Index++;
		}
	}*/


	// Receive using first char user send

	/* Wait for data to be received */
	while ( !(UCSRA & (1<<UCSRA_RXC)) );

	u8 Local_u8Exit=UDR;

	while(1)
	{
		/* Wait for data to be received */
		while ( !(UCSRA & (1<<UCSRA_RXC)) );

		Local_u8Data = UDR;

		if(Local_u8Data ==Local_u8Exit)
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

	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}


ES_t USART_enuTransmit(u16 Copy_u16data)
{
	ES_t Local_enuErrorState=ES_NOK;
/*
	///* Wait for empty transmit buffer *
	while ( !( UCSRA & (1<<UCSRA_UDRE)) );

	/* Put data into buffer, sends the data *
	UDR = Copy_data;
*/

	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UCSRA_UDRE)));

	/* Copy 9th bit to TXB8 */
	UCSRB &= ~(1<<UCSRB_TXB8);
	if ( Copy_u16data & 0x0100 )
	{
		UCSRB |= (1<<UCSRB_TXB8);
	}
	/* Put data into buffer, sends the data */
	UDR = Copy_u16data;

	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}

ES_t USART_enuRecieve(u16 *Copy_pu16data)
{
	ES_t Local_enuErrorState=ES_NOK;

	/* Wait for data to be received */
	while ( !(UCSRA & (1<<UCSRA_RXC)) );
	/*  9th bit, then data */

	*Copy_pu16data = (UCSRB &(1<<UCSRB_RXB8));
	*Copy_pu16data= (*Copy_pu16data<<8) |UDR ;
	//*Copy_data= UDR;


	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}

ES_t USART_enuEnableTransmitter(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	UCSRB |=(1<<UCSRB_TXEN);
	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}



ES_t USART_enuEnableReceiver(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	UCSRB |=(1<<UCSRB_RXEN);
	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}


