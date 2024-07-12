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

#define F_CPU 8000000UL

int main(void)
{


	Smart_Home_enuInit();
	while(1)
	{
		if(Login()==ES_OK)
		{

				LCD_enuClearLcd();
				LCD_enuDisplayString("Status");
				_delay_ms(150);
				LCD_enuClearLcd();


			while(1)
			{
				CHECK_temp();
				CHECK_temp();
				CHECK_gas();
				CHECK_windowAttack();
				CHECK_packageThief();
				UART();
			}

		}
		else
		{
			LCD_enuClearLcd();
			continue;
		}

	}

	return 0;
}







