/*
 * INT_config.c
 *
 *  Created on: Oct 23, 2023
 *      Author: aya
 */

#include "../../LIB/errorState.h"
#include  "../../LIB/types.h"

#include "INT_priv.h"
#include "INT_config.h"

EINT_t EINT_tstrEINTcofig[3]={
		{EINT_ENABLED,EINT_FALLING_EDGE},
		{EINT_ENABLED,EINT_ANY_LOG_CHANGE},
		{EINT_ENABLED,EINT_RISING_EDGE}

};

