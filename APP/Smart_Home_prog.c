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

#include "../MCAL/ADC/ADC_int.h"

#include "../MCAL/Uart/Uart_int.h"

#include "../HAL/EEPROM/EEPROM_int.h"

//#include "../MCAL/TIMER/TIMER0/TIMER0_int.h"

#include "../HAL/LM35/LM35_config.h"
#include "../HAL/LM35/LM35_int.h"

#include <util/delay.h>

#include "Smart_Home_priv.h"
#include "Smart_Home_config.h"


extern TR_t LM35_AstrLM35Config[2];


u8 Alarm_State=0;
u32 Password = PASS;
f32 Temp_value ,IntermidiateValue = 0;
static volatile u8 GAS_detect=0 , Window_State=0 ,Package_State=0;
static volatile u16 EEPROM_Address=0x00;

//static  volatile u8 APP_TIMER0_u8Counter=0;



ES_t Smart_Home_enuInit(void)
{
	ES_t Local_enuErrorState =ES_NOK;

	Local_enuErrorState = DIO_enuInit();
	Local_enuErrorState = KEYPAD_enuInit();
	Local_enuErrorState = LCD_enuInit();
	Local_enuErrorState = Uart_enuInit();
	Local_enuErrorState = EEPROM_enuInit();

	/*
	TIMER0_enuInit();
	TIMER0_enuSetPreload(106);
	GIE_enuDisable();*/


	//UART PIN
	Local_enuErrorState=DIO_enuSetPinDirection(DIO_u8PORTD,DIO_u8PIN0,DIO_u8INPUT);
	Local_enuErrorState=DIO_enuSetPinDirection(DIO_u8PORTD,DIO_u8PIN1,DIO_u8OUTPUT);

	Local_enuErrorState = ADC_enuEnable();
	Local_enuErrorState = LM35_enuInit(LM35_AstrLM35Config);
	Local_enuErrorState = ADC_enuEnableTriggeringMode(ADC_FREE_RUNNING );
	Local_enuErrorState = ADC_enuStartConversion();
	Local_enuErrorState=LM35_enuGetTemp(& Temp_value);

	//Door >> output
	 Local_enuErrorState = DIO_enuSetPinDirection(DIO_u8PORTA,DIO_u8PIN1,DIO_u8OUTPUT);
	 Local_enuErrorState = DIO_enuSetPinValue(DIO_u8PORTA,DIO_u8PIN1,DIO_u8LOW);

	 //Fire Alarm >> output
	 Local_enuErrorState = DIO_enuSetPinDirection(DIO_u8PORTA,DIO_u8PIN3,DIO_u8OUTPUT);
	 Local_enuErrorState=DIO_enuSetPinValue(DIO_u8PORTA,DIO_u8PIN3,DIO_u8LOW);

	 /*// Window >> output
	 Local_enuErrorState = DIO_enuSetPinDirection(DIO_u8PORTD,DIO_u8PIN4,DIO_u8OUTPUT);
	 Local_enuErrorState=DIO_enuSetPinValue(DIO_u8PORTD,DIO_u8PIN4,DIO_u8LOW);*/

	 //Buzzer >> output
	 Local_enuErrorState = DIO_enuSetPinDirection(DIO_u8PORTD,DIO_u8PIN2,DIO_u8OUTPUT);
	 Local_enuErrorState=DIO_enuSetPinValue(DIO_u8PORTD,DIO_u8PIN2,DIO_u8LOW);

	 //GAS sensor PIN
	 DIO_enuSetPinDirection(DIO_u8PORTD,DIO_u8PIN3,DIO_u8INPUT);

	 // Package PIN
	 DIO_enuSetPinDirection(DIO_u8PORTA,DIO_u8PIN4,DIO_u8INPUT);


	 // window PIN
	 DIO_enuSetPinDirection(DIO_u8PORTA,DIO_u8PIN0,DIO_u8INPUT);



	return Local_enuErrorState;

}

//Timer
/*ES_t APP_enuStart()
{
	ES_t Local_enuErrorState=ES_NOK;

	TIMER0_enuCallBackOVF(Read_Sensors,NULL);
	CHECK_temp();
	CHECK_gas();
	CHECK_windowAttack();
	CHECK_packageThief();
	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}*/

//Timer
/*static void Read_Sensors()
{
	APP_TIMER0_u8Counter++;

	if(APP_TIMER0_u8Counter==152)
	{
		//Read LM35
		ADC_enuStartConversion();
		LM35_enuGetTemp(& Temp_value);

		//Read Gas
		DIO_enuGetPinValue(DIO_u8PORTD,DIO_u8PIN3,&GAS_detect);

		// Read Tilt and Vibration sensor
		DIO_enuGetPinValue(DIO_u8PORTA,DIO_u8PIN0,&Window_State);

		// Read PIR & vibration sensor
		DIO_enuGetPinValue(DIO_u8PORTA,DIO_u8PIN4,&Package_State);

		TIMER0_enuSetPreload(106);
		APP_TIMER0_u8Counter=0;

	}

}*/

ES_t Login(void)
{
	ES_t Local_enuErrorState =ES_NOK;

	u8 key,i=0;
	u16 value=0;

	LCD_enuClearLcd();
	LCD_enuDisplayString("Pass=");

	for(i=0; i<4; i++)
	{
		key = KEYPAD_u8GetPressedKey();
		  if(key != KPD_NO_PRESSED_KEY)
		  {
			  value= value*10+(key-'0');
			  LCD_enuDisplayChar('*');
		  }
		  if(key == KPD_NO_PRESSED_KEY)
		  {
			  i--;
		  }

	}
	if (value == Password)
	{
		LCD_enuClearLcd();
		LCD_enuDisplayString("OPEN DOOR");
		//open door
		Local_enuErrorState=OPEN_Door();

		// EEPROM
		Local_enuErrorState =EEPROM_enuWriteData(EEPROM_Address,'L');
		//_delay_ms(150);
		EEPROM_Address++;

		value =0;
		Local_enuErrorState=ES_OK;
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


	u8 Local_u8Value = (u8) Temp_value;

	if(IntermidiateValue != Temp_value)
	{
		LCD_enuClearLcd();
		LCD_enuDisplayString("T=");
		Local_enuErrorState =LCD_enuDisplayNum(Temp_value);

		if(Local_u8Value>=60)
		{
			// EEPROM
			Local_enuErrorState =EEPROM_enuWriteData(EEPROM_Address,'F');
			_delay_ms(150);
			EEPROM_Address++;
			Local_enuErrorState =EEPROM_enuWriteData(EEPROM_Address,((Local_u8Value/100) +'0' ));
			_delay_ms(150);
			EEPROM_Address++;
			Local_enuErrorState =EEPROM_enuWriteData(EEPROM_Address,(((Local_u8Value/10)%10) +'0'));
			_delay_ms(150);
			EEPROM_Address++;
			Local_enuErrorState =EEPROM_enuWriteData(EEPROM_Address,((Local_u8Value%10) +'0' ));
			_delay_ms(150);
			EEPROM_Address++;
		}

		IntermidiateValue = Temp_value;
	}


	if(Local_u8Value >=60 )
	{
		Alarm_State = FIRE;
		LED_Indicators();
		// Fire Alarm
		Local_enuErrorState = Alarm_ON();

	}
	else if( !(Alarm_State ==ATTACK  || Alarm_State ==GAS || Alarm_State ==THIEF ))
	{
		Alarm_State = NORMAL;
		LED_Indicators();
		Local_enuErrorState = Alarm_OFF();
	}


	return Local_enuErrorState;
}


ES_t CHECK_gas(void)
{
	ES_t Local_enuErrorState =ES_NOK;


	static u8 Last_state=0;

	DIO_enuGetPinValue(DIO_u8PORTD,DIO_u8PIN3,&GAS_detect);


	if(GAS_detect==1)
	{
		LCD_enuGoToPosition(1,8);
		LCD_enuDisplayString("LEAKAGE");

		// EEPROM
		if(Last_state != GAS_detect)
		{
			Local_enuErrorState =EEPROM_enuWriteData(EEPROM_Address,'G');
			//_delay_ms(150);
			EEPROM_Address++;
			Last_state = GAS_detect;
		}

		Alarm_State = GAS;
		LED_Indicators();
		Local_enuErrorState = Alarm_ON();
	}
	else
	{
		Last_state=0;
		LCD_enuGoToPosition(1,8);
		LCD_enuDisplayString("NORMAL ");
		if( !(Alarm_State ==ATTACK  || Alarm_State ==THIEF || Alarm_State ==FIRE ))
		{
			Alarm_State = NORMAL;
			LED_Indicators();
			Local_enuErrorState = Alarm_OFF();
		}
	}

	return Local_enuErrorState;
}

ES_t CHECK_windowAttack(void)
{
	ES_t Local_enuErrorState =ES_NOK;

	static u8 Last_state=0;

	DIO_enuGetPinValue(DIO_u8PORTA,DIO_u8PIN0,&Window_State);

	if(Window_State==1 )
	{
		LCD_enuGoToPosition(2,1);
		LCD_enuDisplayString("ATTACK");

		// EEPROM
		if(Last_state != Window_State)
		{
			Local_enuErrorState =EEPROM_enuWriteData(EEPROM_Address,'W');
			//_delay_ms(150);
			EEPROM_Address++;
			Last_state = Window_State;
		}

		Alarm_State = ATTACK;
		LED_Indicators();
		Local_enuErrorState = Alarm_ON();
	}
	else
	{
		Last_state=0;
		LCD_enuGoToPosition(2,1);
		LCD_enuDisplayString("NORMAL");
		if( !(Alarm_State ==THIEF  || Alarm_State ==GAS || Alarm_State ==FIRE ))
		{
			Alarm_State = NORMAL;
			LED_Indicators();
			Local_enuErrorState = Alarm_OFF();
		}
	}

	return Local_enuErrorState;
}

ES_t CHECK_packageThief(void)
{
	ES_t Local_enuErrorState =ES_NOK;


	static u8 Last_state=0;

	DIO_enuGetPinValue(DIO_u8PORTA,DIO_u8PIN4,&Package_State);

	if(Package_State==1 )
	{
		LCD_enuGoToPosition(2,8);
		LCD_enuDisplayString("THIEF ");

		// EEPROM
		if(Last_state != Package_State)
		{
			Local_enuErrorState =EEPROM_enuWriteData(EEPROM_Address,'P');
			//_delay_ms(150);
			EEPROM_Address++;
			Last_state = Package_State;
		}

		Alarm_State = THIEF;
		LED_Indicators();
		Local_enuErrorState = Alarm_ON();
	}
	else
	{
		Last_state=0;
		LCD_enuGoToPosition(2,8);
		LCD_enuDisplayString("NORMAL");
		if( !(Alarm_State ==ATTACK  || Alarm_State ==GAS || Alarm_State ==FIRE ))
		{
			Alarm_State = NORMAL;
			LED_Indicators();
			Local_enuErrorState = Alarm_OFF();
		}
	}

	return Local_enuErrorState;
}

static ES_t LED_Indicators(void)
{
	ES_t Local_enuErrorState =ES_NOK;

	switch(Alarm_State)
	{
	case FIRE:
		Local_enuErrorState=DIO_enuSetPinValue(DIO_u8PORTA,DIO_u8PIN3,DIO_u8HIGH);
		break;
	/*case GAS:
	//	Local_enuErrorState=DIO_enuSetPinValue(DIO_u8PORTA,DIO_u8PIN5,DIO_u8HIGH);
		break;
	case ATTACK:
		Local_enuErrorState=DIO_enuSetPinValue(DIO_u8PORTD,DIO_u8PIN4,DIO_u8HIGH);
		break;*/
	case NORMAL:
		Local_enuErrorState=DIO_enuSetPinValue(DIO_u8PORTA,DIO_u8PIN3,DIO_u8LOW);
		//Local_enuErrorState=DIO_enuSetPinValue(DIO_u8PORTA,DIO_u8PIN5,DIO_u8LOW);
		//Local_enuErrorState=DIO_enuSetPinValue(DIO_u8PORTD,DIO_u8PIN4,DIO_u8LOW);
		break;
	}

	return Local_enuErrorState;
}





static ES_t OPEN_Door(void)
{
	ES_t Local_enuErrorState =ES_NOK;

	Local_enuErrorState=DIO_enuSetPinValue(DIO_u8PORTA,DIO_u8PIN1,DIO_u8HIGH);
	_delay_ms(1000);
	Local_enuErrorState=DIO_enuSetPinValue(DIO_u8PORTA,DIO_u8PIN1,DIO_u8LOW);

	return Local_enuErrorState;
}

static ES_t Alarm_ON(void)
{
	ES_t Local_enuErrorState =ES_NOK;

	Local_enuErrorState=DIO_enuSetPinValue(DIO_u8PORTD,DIO_u8PIN2,DIO_u8HIGH);

	return Local_enuErrorState;
}


static ES_t Alarm_OFF(void)
{
	ES_t Local_enuErrorState =ES_NOK;

	Local_enuErrorState=DIO_enuSetPinValue(DIO_u8PORTD,DIO_u8PIN2,DIO_u8LOW);

	return Local_enuErrorState;
}

ES_t UART(void)
{
	ES_t Local_enuErrorState =ES_NOK;

	u8 Data[20];
	static u8 counter =1;

	if(counter == 1)
	{
     Uart_enuSendString("welcome to your smart home \r\n");
     Uart_enuSendString("EEPROM CONTENT \r\n");
     counter++;
	}


	static u16 Last_ubdate=0;

	u8 Local_u8Data=0, Local_u8Value =(u8)Temp_value;

	if(EEPROM_Address > Last_ubdate)
	{
		Uart_enuSendString("EEPROM Ubdates CONTENT \r\n");

		for( u16 i=0;i<EEPROM_Address;i++)
		{
			EEPROM_enuReadData(i,&Local_u8Data);
			Uart_enuSendChar(Local_u8Data);
			switch(Local_u8Data)
			{
			case 'L':
				Uart_enuSendString(" ->> Correct Login");
				break;
			case 'F':
				Uart_enuSendString(" ->> Fire >> T=");
				for(int j=0;j<3;j++)
				{
					i++;
					EEPROM_enuReadData(i,&Local_u8Data);
					Uart_enuSendChar(Local_u8Data);
				}
				break;
			case 'G':
				Uart_enuSendString(" ->> Gas Leakage");
				break;
			case 'W':
				Uart_enuSendString(" ->> Window attack");
				break;
			case 'P':
				Uart_enuSendString(" ->> Package Theft");
				break;

			}
			Uart_enuSendString("\r\n");
		}
		Last_ubdate=EEPROM_Address;

	}


	return Local_enuErrorState;

}

ES_t Compare(u8* str1 ,u8* str2)
{
	ES_t Local_enuErrorState =ES_NOK;
	u8 i=0;
	for(;str1[i]!='\0' && str2[i]!='\0';i++)
	{
		if(str1[i] != str2[i])
		{
			break;
		}
	}
	if(str1[i]==0 && str2[i]==0)
	{
		Local_enuErrorState=ES_OK;
		return Local_enuErrorState ;
	}
	//Local_enuErrorState=ES_OK; >> this line who give error
	return Local_enuErrorState ;
}







