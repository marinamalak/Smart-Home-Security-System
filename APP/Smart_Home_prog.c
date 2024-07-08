/*
 * Smart_Home_prog.c
 *
 *  Created on: Jul 8, 2024
 *      Author: Admin
 */

#include "../LIB/errorState.h"
#include "../LIB/types.h"

#include "../MCAL/DIO/DIO_int.h"

#include "../MCAL/GIE/GIE_int.h"

#include "../HAL/KEYPAD/Keypad_int.h"
#include "../HAL/KEYPAD/Keypad_config.h"

#include "../HAL/LCD/LCD_int.h"
#include "../HAL/LCD/LCD_config.h"

#include "../MCAL/EINT/INT_config.h"
#include "../MCAL/EINT/INT_int.h"

#include "../MCAL/ADC/ADC_int.h"

#include "../HAL/LM35/LM35_config.h"
#include "../HAL/LM35/LM35_int.h"

#include <util/delay.h>

#include "Smart_Home_config.h"


extern EINT_t EINT_tstrEINTcofig[3];

extern TR_t LM35_AstrLM35Config[2];


u8 Read_temp_Flag =0;
u32 Password=PASS;
f32 Temp_value ,IntermidiateValue = 0;;


static ES_t OPEN_Door(void);
static void Read_Temp(void*p);
static ES_t Fire_Alarm_ON(void);
static ES_t Fire_Alarm_OFF(void);


ES_t Smart_Home_enuInit(void)
{
	ES_t Local_enuErrorState =ES_NOK;

	Local_enuErrorState = DIO_enuInit();
	Local_enuErrorState = KEYPAD_enuInit();
	Local_enuErrorState = LCD_enuInit();

	//Interrupt PIN
	DIO_enuSetPinDirection(DIO_u8PORTD,DIO_u8PIN2,DIO_u8INPUT);

/*	Local_enuErrorState = EINT_enuInit(EINT_tstrEINTcofig);
	Local_enuErrorState = EINT_enuSelectSenceLevel(0,FALLING_EDGE);
	Local_enuErrorState = EINT_enuEnableINT(0); */

	Local_enuErrorState = ADC_enuEnable();
	Local_enuErrorState = LM35_enuInit(LM35_AstrLM35Config);
	Local_enuErrorState = ADC_enuEnableTriggeringMode(ADC_FREE_RUNNING );//ADC_EXT_INT0_REQ);
	//Local_enuErrorState = ADC_enuEnableInterruptMode();
	//Local_enuErrorState = ADC_enuCallBack(Read_Temp ,&Temp_value);
	Local_enuErrorState = ADC_enuStartConversion();
	LM35_enuGetTemp(& Temp_value);

	//Door >> output
	 Local_enuErrorState = DIO_enuSetPinDirection(DIO_u8PORTA,DIO_u8PIN1,DIO_u8OUTPUT);

	 //Fire Alarm >> output
	 Local_enuErrorState = DIO_enuSetPinDirection(DIO_u8PORTA,DIO_u8PIN3,DIO_u8OUTPUT);


	 //Buzzer >> output
	 Local_enuErrorState = DIO_enuSetPinDirection(DIO_u8PORTD,DIO_u8PIN4,DIO_u8OUTPUT);





	Local_enuErrorState = GIE_enuEnable();

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


 ES_t CHECK_temp(void)
{
	ES_t Local_enuErrorState=ES_NOK;


	Local_enuErrorState = ADC_enuStartConversion();
	Local_enuErrorState =LM35_enuGetTemp(& Temp_value);

/*
	if(Read_temp_Flag==1)
	{
		LCD_enuDisplayNum(Temp_value);
		LCD_enuDisplayChar(0xDF);
		LCD_enuDisplayChar('C');
		Read_temp_Flag=0;
	}
*/




	if(IntermidiateValue != Temp_value)
	{
		LCD_enuClearLcd();
		Local_enuErrorState =LCD_enuDisplayNum(Temp_value);
		IntermidiateValue = Temp_value;
	}

	u8 Local_u8Value = (u8) Temp_value;

	if(Local_u8Value >=60 )
	{
		// Fire Alarm
		Local_enuErrorState = Fire_Alarm_ON();

	}
	else
	{
		Local_enuErrorState = Fire_Alarm_OFF();
	}


	return Local_enuErrorState;
}






static void Read_Temp(void*p)
{
	LCD_enuClearLcd();
	LM35_enuGetTemp((f32 *)p);
	Read_temp_Flag = 1;
	//flag=1;
}




static ES_t OPEN_Door(void)
{
	ES_t Local_enuErrorState =ES_NOK;

	Local_enuErrorState=DIO_enuSetPinValue(DIO_u8PORTA,DIO_u8PIN1,DIO_u8HIGH);
	_delay_ms(5000);
	Local_enuErrorState=DIO_enuSetPinValue(DIO_u8PORTA,DIO_u8PIN1,DIO_u8LOW);

	return Local_enuErrorState;
}

static ES_t Fire_Alarm_ON(void)
{
	ES_t Local_enuErrorState =ES_NOK;

	Local_enuErrorState=DIO_enuSetPinValue(DIO_u8PORTA,DIO_u8PIN3,DIO_u8HIGH);
	Local_enuErrorState=DIO_enuSetPinValue(DIO_u8PORTD,DIO_u8PIN4,DIO_u8HIGH);



	return Local_enuErrorState;
}


static ES_t Fire_Alarm_OFF(void)
{
	ES_t Local_enuErrorState =ES_NOK;

	Local_enuErrorState=DIO_enuSetPinValue(DIO_u8PORTA,DIO_u8PIN3,DIO_u8LOW);
	Local_enuErrorState=DIO_enuSetPinValue(DIO_u8PORTD,DIO_u8PIN4,DIO_u8LOW);




	return Local_enuErrorState;
}










