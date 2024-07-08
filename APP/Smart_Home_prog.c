/*
 * Smart_Home_prog.c
 *
 *  Created on: Jul 8, 2024
 *      Author: Admin
 */

#include "../LIB/errorState.h"
#include "../LIB/types.h"

#include "../MCAL/DIO/DIO_int.h"

#include "../HAL/KEYPAD/Keypad_int.h"
#include "../HAL/KEYPAD/Keypad_config.h"
#include "../HAL/LCD/LCD_int.h"
#include "../HAL/LCD/LCD_config.h"

#include "Smart_Home_config.h"

ES_t Smart_Home_enuInit(void)
{
	ES_t Loca_ErrorState =ES_NOK;

	Loca_ErrorState =DIO_enuInit();
	Loca_ErrorState =KEYPAD_enuInit();
	Loca_ErrorState =LCD_enuInit();

	return Loca_ErrorState;

}

ES_t Login(void)
{
	ES_t Loca_ErrorState =ES_NOK;

	u8 key,i=0;
	u32 value=0;

	for(i=0; i<4; i++)
	{
		key = KEYPAD_u8GetPressedKey();
		  if(key != KPD_NO_PRESSED_KEY)
		  {
			  value= value*10+key;
			  LCD_enuClearLcd();
		  }
	  while(key == KPD_NO_PRESSED_KEY );
		  LCD_enuDisplayNum(key);
	}
	if (value == pass)
	{
		//open door
		DIO_enuSetPinDirection(DIO_u8PORTA,DIO_u8PIN1,DIO_u8OUTPUT);
		DIO_enuSetPinValue(DIO_u8PORTA,DIO_u8PIN1,DIO_u8HIGH);
		value =0;
	}else
	{

	}
	return Loca_ErrorState;
}
