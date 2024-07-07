/*
 * LM35_config.c
 *
 *  Created on: Nov 6, 2023
 *      Author: aya
 */

#include "../../LIB/errorState.h"
#include "../../LIB/types.h"

#include "../../MCAL/DIO/DIO_int.h"

#include "LM35_priv.h"
#include "LM35_config.h"

TR_t LM35_AstrLM35Config[CH_NUM]={
		{DIO_u8PIN2,NOT_CONNECTED},
		{DIO_u8PIN7,NOT_CONNECTED}
};
