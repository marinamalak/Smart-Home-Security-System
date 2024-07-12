/*
 * TWI_prog.c
 *
 *  Created on: May 2, 2024
 *      Author: aya
 */

#include "../../LIB/errorState.h"
#include "../../LIB/types.h"

#include "TWI_priv.h"
#include "TWI_config.h"


ES_t IIC_enuInit(void)
{
	ES_t Local_enuErrorState=ES_NOK;

#if IIC_MODE==IIC_MASTER

	//set clock
	TWBR = (u8) BITRATE(IIC_CLOCK_SPEED);

	//Select prescaler
#if IIC_PRES==1ul
	TWSR &=~(1<<TWSR_TWPS0);
	TWSR &=~(1<<TWSR_TWPS1);

#elif IIC_PRES==4ul
	TWSR |= (1<<TWSR_TWPS0);
	TWSR &=~(1<<TWSR_TWPS1);

#elif IIC_PRES==16ul
	TWSR &=~(1<<TWSR_TWPS0);
	TWSR |= (1<<TWSR_TWPS1);

#elif IIC_PRES==64ul
	TWSR |= (1<<TWSR_TWPS0);
	TWSR |= (1<<TWSR_TWPS1);

#endif

	// SET Master address
	TWAR &=~(1<<0);
	TWAR = (IIC_NODE_ADDRESS<<1) | IIC_GENERAL_CALL;

	//Clear flag
	TWCR |= (1<<TWCR_TWINT);

	// Enable IIC
	TWCR |= (1<<TWCR_TWEN);

	Local_enuErrorState=ES_OK;


#elif IIC_MODE==IIC_SLAVE

	// SET slave address
	TWAR &=~(1<<0);
	TWAR = (IIC_NODE_ADDRESS<<1) | IIC_GENERAL_CALL;

	//Clear flag
	TWCR |= (1<<TWCR_TWINT);

	// Enable IIC
	TWCR |= (1<<TWCR_TWEN);

	Local_enuErrorState=ES_OK;

#else

#error "IIC mode selection is wrong"
#endif


	return Local_enuErrorState;
}

ES_t IIC_enuStartCondition(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	// Transmit start condition
	TWCR = (1 << TWCR_TWSTA) | (1 << TWCR_TWEN) | (1 << TWCR_TWINT);

	// Wait for start condition to be executed
	while (!(TWCR & (1 << TWCR_TWINT)));

	// Check the status of the TWI operation
	if ((TWSR & 0xF8) == 0x08)
	{
		// Start condition transmitted successfully
		Local_enuErrorState = ES_OK;
	}

	/*TWCR |=(1<<TWCR_TWSTA);
	//Clear flag
	TWCR |= (1<<TWCR_TWINT);
	//wait on flag
	while(!((TWCR>>TWCR_TWINT)&1));


	//check start condition state
	if((TWSR & 0xF8)==0x08)    //Master transmit
	{
		Local_enuErrorState=ES_OK;
	}*/

	return Local_enuErrorState;
}

ES_t IIC_enuRepeatedStartCondition(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	TWCR |=(1<<TWCR_TWSTA);
	//Clear flag
	TWCR |= (1<<TWCR_TWINT);
	//wait on flag
	while(!((TWCR>>TWCR_TWINT)&1));

	//check  repeated start condition state
	if((TWSR & 0xF8)==0x10)  //Master transmit
	{

		Local_enuErrorState=ES_OK;
	}
	return Local_enuErrorState;
}

ES_t IIC_enuStopCondition(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	// Transmit stop condition
	TWCR = (1 << TWCR_TWSTO) | (1 << TWCR_TWEN) | (1 << TWCR_TWINT);

	// Wait for stop condition to be executed
	while (TWCR & (1 << TWCR_TWSTO));
	// TWSR == 0x50 --> Data byte transmitted and ACK received
	// TWSR == 0x58 --> Data byte transmitted and NACK received

	// Check the status of the TWI operation
	if ((TWSR & 0xF8) == 0x58 || (TWSR & 0xF8) == 0x50 || (TWSR & 0xF8) == 0x38)
	{
		// Stop condition transmitted successfully
		Local_enuErrorState = ES_OK;
	}

	/*TWCR |=(1<<TWCR_TWSTO);
	//Clear flag
	TWCR |= (1<<TWCR_TWINT);

	Local_enuErrorState=ES_OK;*/

	return Local_enuErrorState;
}

ES_t IIC_enuWriteSlaveAddress(u8 Copy_u8SlaveAddress, u8 Copy_u8Operation)
{
	ES_t Local_enuErrorState=ES_NOK;

	// Check if the address and operation are within valid ranges
	if (Copy_u8SlaveAddress >= 2 && Copy_u8SlaveAddress <= 118 && (Copy_u8Operation == 0 || Copy_u8Operation == 1))
	{
		// Load the slave address and operation (read or write) into the TWI Data Register
		TWDR = (Copy_u8SlaveAddress << 1) | Copy_u8Operation;

		// Clear the TWINT flag to start the transmission of the address
		TWCR = (1 << TWCR_TWEN) | (1 << TWCR_TWINT);

		// Wait until the TWINT flag is set, indicating that the transmission is complete
		while (!(TWCR & (1 << TWCR_TWINT)));

		// Check the status of the TWI operation
		if ((TWSR & 0xF8) == 0x18 && Copy_u8Operation == 0)
		{
			// Master transmit mode and received ACK from slave
			Local_enuErrorState = ES_OK;
		}
		else if ((TWSR & 0xF8) == 0x40 && Copy_u8Operation == 1)
		{
			// Master receive mode and received ACK from slave
			Local_enuErrorState = ES_OK;
		}
		else
		{
			// Address not acknowledged by slave
			Local_enuErrorState = ES_NOK;
		}
	}
	else
	{
		// Address or operation out of range
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	/*if(Copy_u8SlaveAddress>=2 && Copy_u8SlaveAddress<=118 && Copy_u8Operation>=0 && Copy_u8Operation<=1)
	{
		//clear start condition
		TWCR &=~(1<<TWCR_TWSTA);

		TWDR = ((Copy_u8SlaveAddress<<1)|Copy_u8Operation);
		//Clear flag
		TWCR |= (1<<TWCR_TWINT);
		//wait on flag
		while(!((TWCR>>TWCR_TWINT)&1));
		//check   state
		if((TWSR & 0xF8)==0x18 && Copy_u8Operation==0) //SLA+W+ACK //Master transmit
		{
			Local_enuErrorState=ES_OK;
		}
		else if((TWSR & 0xF8)==0x40 && Copy_u8Operation==1) //SLA+R+ACK //Master recieve
		{
			Local_enuErrorState=ES_OK;
		}

	}
	else
	{
		Local_enuErrorState=ES_OUT_OF_RANGE;
	}

	//clear start condition
	TWCR &=~(1<<TWCR_TWSTA);*/

	return Local_enuErrorState;
}

ES_t IIC_enuWriteData(u8 Copy_u8Data)
{
	ES_t Local_enuErrorState=ES_NOK;

	TWDR = Copy_u8Data;
	//Clear flag
	TWCR |= (1<<TWCR_TWINT);
	//wait on flag
	while(!((TWCR>>TWCR_TWINT)&1));
	//check   state
	if((TWSR & 0xF8)==0x28 ) //Data+ACK //Master transmit
	{
		Local_enuErrorState=ES_OK;
	}


	return Local_enuErrorState;
}

ES_t IIC_enuCheckMyAddress(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	//set ACK bit
	TWCR |=(1<<TWCR_TWEA);
	//Clear flag
	TWCR |= (1<<TWCR_TWINT);
	//wait on flag
	while(!((TWCR>>TWCR_TWINT)&1));
	//check state
	if((TWSR & 0xF8)==0xA8 ) //SLA+W+ACK //slave transmit
	{

		Local_enuErrorState=ES_OK;
	}
	else if((TWSR & 0xF8)==0x60 ) //SLA+W+ACK //slave recieve
	{

		Local_enuErrorState=ES_OK;
	}


	return Local_enuErrorState;
}

ES_t IIC_enuReadData(u8 * Copy_pu8Data)
{
	ES_t Local_enuErrorState=ES_NOK;

	//Clear flag
	TWCR |= (1 << TWCR_TWINT);
	//wait on flag
	while (!((TWCR >> TWCR_TWINT) & 1));
	//check   state
	if ((TWSR & 0xF8) == 0x50) //Data+ACK //Master receive
	{
		*Copy_pu8Data = TWDR;
		Local_enuErrorState = ES_OK;
	}
	else if ((TWSR & 0xF8) == 0x58) //Data+NACK //Master receive
	{
		*Copy_pu8Data = TWDR;
		Local_enuErrorState = ES_OK;
	}

	/*//Clear flag
	TWCR |= (1<<TWCR_TWINT);
	//wait on flag
	while(!((TWCR>>TWCR_TWINT)&1));


	//check   state
	if( (TWSR & 0xF8) == 0x58   ) //Data+ not ACK //Master recieve
	{
		*Copy_pu8Data = TWDR;
		Local_enuErrorState=ES_OK;
	}
	else if((TWSR & 0xF8)==0x80 ) //Data+ACK //slave recieve
	{
		*Copy_pu8Data = TWDR;
		Local_enuErrorState=ES_OK;
	}*/


	return Local_enuErrorState;
}






