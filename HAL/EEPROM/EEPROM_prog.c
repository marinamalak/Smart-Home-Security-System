/*
 * EEPROM_prog.c
 *
 *  Created on: Jun 24, 2024
 *      Author: aya
 */

#include "../../LIB/errorState.h"
#include "../../LIB/types.h"

#include "../../MCAL/I2C_TWI/TWI_int.h"

#include "EEPROM_config.h"
#include "EEPROM_priv.h"


ES_t EEPROM_enuInit(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	Local_enuErrorState=IIC_enuInit();

	return Local_enuErrorState;
}

ES_t EEPROM_enuWriteData(u16 Copy_u16Address , u8 Copy_u8Data)
{
	ES_t Local_enuErrorState=ES_NOK;
	u8 Local_u8Address , Local_u8ByteAddress;

#if EEPROM_TYPE==EIGHT_KBIT

	if(Copy_u16Address<1024 && EEPROM_A2_STATE<2)
	{
		Local_u8Address =( (0xA0 | (EEPROM_A2_STATE<<3) | (((Copy_u16Address>>8)& 3)<<1) )>>1 );
		Local_u8ByteAddress= (u8) Copy_u16Address;
	}
	else
	{
		Local_enuErrorState=ES_OUT_OF_RANGE;
	}

#elif EEPROM_TYPE==FOUR_KBIT
	if(Copy_u16Address<1024 && EEPROM_A2_STATE<2 && EEPROM_A1_STATE<2 )
	{
		Local_u8Address =( (0xA0 | (EEPROM_A2_STATE<<3) | (EEPROM_A1_STATE<<2) | (((Copy_u16Address>>8)& 1)<<1) )>>1 );
		Local_u8ByteAddress= (u8) Copy_u16Address;
	}
	else
	{
		Local_enuErrorState=ES_OUT_OF_RANGE;
	}

#elif EEPROM_TYPE==TWO_KBIT
	if(Copy_u16Address<1024 && EEPROM_A2_STATE<2 && EEPROM_A1_STATE<2 && EEPROM_A0_STATE<2 )
	{
		Local_u8Address =( (0xA0 | (EEPROM_A2_STATE<<3) | (EEPROM_A1_STATE<<2) | (EEPROM_A1_STATE<<1) )>>1 );
		Local_u8ByteAddress= (u8) Copy_u16Address;
	}
	else
	{
		Local_enuErrorState=ES_OUT_OF_RANGE;
	}


#else

#error "EEPROM Type selection is wrong"
#endif


	if(ES_OK==IIC_enuStartCondition())
	{
		if(ES_OK==IIC_enuWriteSlaveAddress(Local_u8Address,0))
		{
			if(ES_OK==IIC_enuWriteData(Local_u8ByteAddress))
			{
				if(ES_OK==IIC_enuWriteData(Copy_u8Data))
				{
					Local_enuErrorState=IIC_enuStopCondition();
				}
			}
		}
	}

	return Local_enuErrorState;
}

ES_t EEPROM_enuReadData(u16 Copy_u16Address , u8 *Copy_u8Data)
{
	ES_t Local_enuErrorState=ES_NOK;
	u8 Local_u8Address , Local_u8ByteAddress;

#if EEPROM_TYPE==EIGHT_KBIT

	if(Copy_u16Address<1024 || EEPROM_A2_STATE<2)
	{
		Local_u8Address =( (0xA0 | (EEPROM_A2_STATE<<3) | (((Copy_u16Address>>8)& 3)<<1) )>>1 );
		Local_u8ByteAddress= (u8) Copy_u16Address;
	}
	else
	{
		Local_enuErrorState=ES_OUT_OF_RANGE;
	}

#elif EEPROM_TYPE==FOUR_KBIT
	if(Copy_u16Address<1024 && EEPROM_A2_STATE<2 && EEPROM_A1_STATE<2 )
	{
		Local_u8Address =( (0xA0 | (EEPROM_A2_STATE<<3) | (EEPROM_A1_STATE<<2) | (((Copy_u16Address>>8)& 1)<<1) )>>1 );
		Local_u8ByteAddress= (u8) Copy_u16Address;
	}
	else
	{
		Local_enuErrorState=ES_OUT_OF_RANGE;
	}

#elif EEPROM_TYPE==TWO_KBIT
	if(Copy_u16Address<1024 && EEPROM_A2_STATE<2 && EEPROM_A1_STATE<2 && EEPROM_A0_STATE<2 )
	{
		Local_u8Address =( (0xA0 | (EEPROM_A2_STATE<<3) | (EEPROM_A1_STATE<<2) | (EEPROM_A1_STATE<<1) )>>1 );
		Local_u8ByteAddress= (u8) Copy_u16Address;
	}
	else
	{
		Local_enuErrorState=ES_OUT_OF_RANGE;
	}


#else

#error "EEPROM Type selection is wrong"
#endif

	if(ES_OK==IIC_enuStartCondition())
	{
		if(ES_OK==IIC_enuWriteSlaveAddress(Local_u8Address,0))
		{
			if(ES_OK==IIC_enuWriteData(Local_u8ByteAddress))
			{
				if(ES_OK==IIC_enuRepeatedStartCondition())
				{
					if(ES_OK==IIC_enuWriteSlaveAddress(Local_u8Address,1))
					{
						if(ES_OK==IIC_enuReadData(Copy_u8Data))
						{
							Local_enuErrorState=IIC_enuStopCondition();
						}
					}
				}
			}
		}
	}


	return Local_enuErrorState;
}



// *((u8*)0x37)=Local_u8ByteAddress; //DEBUGGING








