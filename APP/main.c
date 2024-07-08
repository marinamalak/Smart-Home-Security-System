/*
 * main.c
 *
 *  Created on: Jul 8, 2024
 *      Author: admin
 */


#include "../LIB/errorState.h"
#include "../LIB/types.h"

#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/DIO/DIO_priv.h"
#include "../MCAL/I2C_TWI/TWI_int.h"

#include "../HAL/EEPROM/EEPROM_int.h"

#include "../HAL/LCD/LCD_int.h"
#include "../HAL/LCD/LCD_config.h"

#include "../HAL/KEYPAD/Keypad_int.h"
#include "../HAL/KEYPAD/Keypad_config.h"

#include "Smart_Home_int.h"

#include <util/delay.h>

int main(void)
{


	Smart_Home_enuInit();

	while(1)
	{

		//Login();
		if(Login()==ES_OK)
		{
				LCD_enuClearLcd();
				LCD_enuDisplayString("status=");
			while(1)
			{
				CHECK_temp();
			}


			//_delay_ms(100000);
			//break;

		}
		else
		{
			continue;
		}

	}

	return 0;
}







