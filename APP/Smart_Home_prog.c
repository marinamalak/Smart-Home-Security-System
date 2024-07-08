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

#include <util/delay.h>

#include "Smart_Home_config.h"


u32 Password=PASS;


static ES_t OPEN_Door(void);


ES_t Smart_Home_enuInit(void)
{
	ES_t Local_enuErrorState =ES_NOK;

	Local_enuErrorState =DIO_enuInit();
	Local_enuErrorState =KEYPAD_enuInit();
	Local_enuErrorState =LCD_enuInit();
	//Door >> output
	DIO_enuSetPinDirection(DIO_u8PORTA,DIO_u8PIN1,DIO_u8OUTPUT);

	return Local_enuErrorState;

}

ES_t Login(void)
{
	ES_t Local_enuErrorState =ES_NOK;

	u8 key,i=0;
	u16 value=0;


	//NOTE: keypad return char value

	LCD_enuClearLcd();
	LCD_enuDisplayString("Pass=");

	for(i=0; i<4; i++)
	{
		key = KEYPAD_u8GetPressedKey();
		  if(key != KPD_NO_PRESSED_KEY)
		  {
			  value= value*10+(key-'0');
			  LCD_enuDisplayChar('*');
			 // LCD_enuDisplayChar(key);
		  }
		  if(key==KPD_NO_PRESSED_KEY)
		  {
			  i--;
		  }

	}
	if (value == Password)
	{
		//open door
		Local_enuErrorState=OPEN_Door();
		value =0;
		//Local_enuErrorState=ES_OK;
	}else
	{
		LCD_enuClearLcd();
		LCD_enuDisplayString("Wrong Password");
		_delay_ms(1000);
		Local_enuErrorState=ES_NOK;

	}
	return Local_enuErrorState;
}






static ES_t OPEN_Door(void)
{
	ES_t Local_enuErrorState =ES_NOK;

	Local_enuErrorState=DIO_enuSetPinValue(DIO_u8PORTA,DIO_u8PIN1,DIO_u8HIGH);
	_delay_ms(5000);
	Local_enuErrorState=DIO_enuSetPinValue(DIO_u8PORTA,DIO_u8PIN1,DIO_u8LOW);

	return Local_enuErrorState;
}












