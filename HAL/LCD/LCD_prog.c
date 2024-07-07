/*
 * LCD_prog.c
 *
 *  Created on: Aug 8, 2023
 *      Author: aya
 */

#include "../../LIB/types.h"
#include "../../LIB/errorState.h"

#include "../../MCAL/DIO/DIO_int.h"

#include "LCD_config.h"
#include "LCD_priv.h"

#include "util/delay.h"

ES_t LCD_enuInit(void)
{
	ES_t Local_enuErrorState=ES_NOK;
	_delay_ms(35);
	DIO_enuSetPinDirection(RS_PORT,RS_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(RW_PORT,RW_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(EN_PORT,EN_PIN,DIO_u8OUTPUT);

	DIO_enuSetPinDirection(D7_PORT,D7_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(D6_PORT,D6_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(D5_PORT,D5_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(D4_PORT,D4_PIN,DIO_u8OUTPUT);

	//FUNCTION SET
#if LCD_MODE==EIGHT_BIT
	DIO_enuSetPinDirection(D3_PORT,D3_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(D2_PORT,D2_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(D1_PORT,D1_PIN,DIO_u8OUTPUT);
	DIO_enuSetPinDirection(D0_PORT,D0_PIN,DIO_u8OUTPUT);

	//FUNCTION SET
	LCD_invidSendCommand(EIGHT_BIT_MODE);

	Local_enuErrorState=ES_OK;

#elif LCD_MODE==FOUR_BIT
	LCD_invidSendCommand(FOUR_BIT_MODE);
	Local_enuErrorState=ES_OK;
#else
	Local_enuErrorState=ES_OUT_OF_RANGE;
#error"your LCD_MODE has a wrong selection"
#endif

	_delay_ms(1);
	//display on/off
	//LCD_invidSendCommand(0x0f);
	LCD_invidSendCommand(DISPLAY_ON_CURSOR_BLINK);
	_delay_ms(1);
	//display clear
	LCD_invidSendCommand(CLEAR_DISPLAY);
	_delay_ms(2);
	//Entry mode set
	LCD_invidSendCommand(INCREMENT_CURSOR_TO_RIGHT);

	_delay_ms(1);
	LCD_invidSendCommand(FORCE_CURSOR_START_FIRST_LINE);


	return Local_enuErrorState;
}

ES_t LCD_enuDisplayChar(u8 Copy_u8Data)
{
	ES_t Local_enuErrorState=ES_NOK;

	//set RS as data
	Local_enuErrorState=DIO_enuSetPinValue(RS_PORT,RS_PIN,DIO_u8HIGH);

	LCD_vidLatch(Copy_u8Data);

	return Local_enuErrorState;
}

ES_t LCD_enuDisplayString(u8 *Copy_pu8Data)
{
	ES_t Local_enuErrorState=ES_NOK;

	/*u8 Local_u8Counter;
	for(Local_u8Counter=0;Copy_pu8Data;Local_u8Counter++)
	{
		Local_enuErrorState=LCD_enuDisplayChar(Copy_pu8Data[Local_u8Counter]);
	}*/
	while(*Copy_pu8Data)
		{
			LCD_enuDisplayChar(*Copy_pu8Data);
			if (!(*(Copy_pu8Data+1))) {Local_enuErrorState =ES_OK;}
			Copy_pu8Data++;
		}

	return Local_enuErrorState;
}

ES_t LCD_enuSendCommand(u8 Copy_u8Command)
{
	ES_t Local_enuErrorState=ES_NOK;

	//set RS as command
	Local_enuErrorState=DIO_enuSetPinValue(RS_PORT,RS_PIN,DIO_u8LOW);

	LCD_vidLatch(Copy_u8Command);

	return Local_enuErrorState;
}

ES_t LCD_enuGoToPosition (u8 Copy_u8Row , u8 Copy_u8Col)
{
	ES_t Local_enuErrorState=ES_NOK;

	u8 Local_u8RowLocation [] = {FORCE_CURSOR_START_FIRST_LINE,FORCE_CURSOR_START_SECOND_LINE};

	LCD_enuSendCommand(Local_u8RowLocation[Copy_u8Row-1]+(Copy_u8Col-1));

	Local_enuErrorState=ES_OK;

	return Local_enuErrorState;
}

ES_t LCD_enuDisplayNum(u8 Copy_u8Num)
{
	ES_t Local_enuErrorState=ES_NOK;

	if(Copy_u8Num>=0 && Copy_u8Num<=9)
	{
		LCD_enuDisplayChar(0x30+Copy_u8Num);
	}
	else
	{
		u8 Local_u8Iterator=0;
		u32 Local_u8Divisor=10;

		while(1)
		{
			if((Copy_u8Num/Local_u8Divisor)==0)
			{
				for(u8 Local_u8Iter=0; Local_u8Iter<=Local_u8Iterator ;Local_u8Iter++)
				{
					Local_u8Divisor=Local_u8Divisor/10;
					if((Copy_u8Num/Local_u8Divisor)>=0  && (Copy_u8Num/Local_u8Divisor)<=9 )
					{
						//LCD_enuDisplayChar(Array_u8Num[(Copy_u8Num/Local_u8Divisor)]);
						//LCD_enuDisplayChar('0'+(Copy_u8Num/Local_u8Divisor));
						LCD_enuDisplayChar(0x30+(Copy_u8Num/Local_u8Divisor));
					}
					Copy_u8Num= Copy_u8Num % Local_u8Divisor;
				}
				break;
			}
			else
			{
				Local_u8Divisor=Local_u8Divisor*10;
				Local_u8Iterator++;
			}
		}
	}

		Local_enuErrorState=ES_OK;

		return Local_enuErrorState;
}

ES_t LCD_enuSendSpecialNumber(u32 Copy_u32Number)
{
	ES_t error_enuState = ES_NOK;

	u8 Local_u8Iteration , Local_u8NumOfDigits=LCD_ZERO;
	u32 Local_u32Reminder , Local_u8PowerTen ;
	Local_u32Reminder=Copy_u32Number;

	for (Local_u8Iteration = LCD_ONE ;  ; Local_u8Iteration++)
	{
		Copy_u32Number=Local_u32Reminder;
		Local_u8PowerTen=POWER_u32PowerNumbers( LCD_TEN , Local_u8Iteration);
		Copy_u32Number /= Local_u8PowerTen;

		if (! (Copy_u32Number))
		{
			Local_u8NumOfDigits=Local_u8Iteration;
			break;
		}
	}

	for (Local_u8Iteration = Local_u8NumOfDigits ; Local_u8Iteration > LCD_ZERO ;Local_u8Iteration--)
	{
		Copy_u32Number=Local_u32Reminder;
		Local_u8PowerTen=POWER_u32PowerNumbers( LCD_TEN , Local_u8Iteration - LCD_ONE);

		Local_u32Reminder  %= Local_u8PowerTen;

		Copy_u32Number /= (Local_u8PowerTen);

		LCD_enuDisplayChar(Copy_u32Number+'0');
	}
	error_enuState = ES_OK;

	return error_enuState;
}

u32 POWER_u32PowerNumbers(u32 Copy_u32Number , u8 Copy_u8Power)
{
	u32 Local_u32Result = LCD_ONE ;
	u8 Local_u8Iteration ;

	for (Local_u8Iteration = LCD_ONE ; Local_u8Iteration <= Copy_u8Power ; Local_u8Iteration++)
	{
		Local_u32Result *=Copy_u32Number ;
	}

	return Local_u32Result ;
}


static void LCD_vidLatch(u8 Copy_u8Data)
{
	//set EN as low
		DIO_enuSetPinValue(EN_PORT,EN_PIN,DIO_u8LOW);
		//set RW as write operation
		DIO_enuSetPinValue(RW_PORT,RW_PIN,DIO_u8LOW);
		//write data
		DIO_enuSetPinValue(D7_PORT,D7_PIN,((Copy_u8Data>>7)&LCD_MASK_BIT));
		DIO_enuSetPinValue(D6_PORT,D6_PIN,((Copy_u8Data>>6)&LCD_MASK_BIT));
		DIO_enuSetPinValue(D5_PORT,D5_PIN,((Copy_u8Data>>5)&LCD_MASK_BIT));
		DIO_enuSetPinValue(D4_PORT,D4_PIN,((Copy_u8Data>>4)&LCD_MASK_BIT));
#if LCD_MODE==EIGHT_BIT
		DIO_enuSetPinValue(D3_PORT,D3_PIN,((Copy_u8Data>>3)&LCD_MASK_BIT));
		DIO_enuSetPinValue(D2_PORT,D2_PIN,((Copy_u8Data>>2)&LCD_MASK_BIT));
		DIO_enuSetPinValue(D1_PORT,D1_PIN,((Copy_u8Data>>1)&LCD_MASK_BIT));
		DIO_enuSetPinValue(D0_PORT,D0_PIN,((Copy_u8Data>>0)&LCD_MASK_BIT));
#elif LCD_MODE==FOUR_BIT
	/*	DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8HIGH);
		_delay_us(1);
		DIO_enuSetPinValue(EN_PORT , EN_PIN , DIO_u8LOW);
		_delay_ms(50);  */
#else
#error"your LCD_MODE has a wrong selection"
#endif

		//enable latch
		DIO_enuSetPinValue(EN_PORT,EN_PIN,DIO_u8HIGH);
		_delay_ms(10);
		DIO_enuSetPinValue(EN_PORT,EN_PIN,DIO_u8LOW);

		// solve prob of freq of atmega bigger than lcd (appear in real time)
		_delay_ms(10);
}

static inline void LCD_invidSendCommand(u8 Copy_u8Command)
{

	//set RS as command
	DIO_enuSetPinValue(RS_PORT,RS_PIN,DIO_u8LOW);
	//set EN as low
	DIO_enuSetPinValue(EN_PORT,EN_PIN,DIO_u8LOW);
	//set RW as write operation
	DIO_enuSetPinValue(RW_PORT,RW_PIN,DIO_u8LOW);
	//write data
	DIO_enuSetPinValue(D7_PORT,D7_PIN,((Copy_u8Command>>7)&LCD_MASK_BIT));
	DIO_enuSetPinValue(D6_PORT,D6_PIN,((Copy_u8Command>>6)&LCD_MASK_BIT));
	DIO_enuSetPinValue(D5_PORT,D5_PIN,((Copy_u8Command>>5)&LCD_MASK_BIT));
	DIO_enuSetPinValue(D4_PORT,D4_PIN,((Copy_u8Command>>4)&LCD_MASK_BIT));
	DIO_enuSetPinValue(D3_PORT,D3_PIN,((Copy_u8Command>>3)&LCD_MASK_BIT));
	DIO_enuSetPinValue(D2_PORT,D2_PIN,((Copy_u8Command>>2)&LCD_MASK_BIT));
	DIO_enuSetPinValue(D1_PORT,D1_PIN,((Copy_u8Command>>1)&LCD_MASK_BIT));
	DIO_enuSetPinValue(D0_PORT,D0_PIN,((Copy_u8Command>>0)&LCD_MASK_BIT));

	//enable latch
	DIO_enuSetPinValue(EN_PORT,EN_PIN,DIO_u8HIGH);
	_delay_ms(10);
	DIO_enuSetPinValue(EN_PORT,EN_PIN,DIO_u8LOW);


}

ES_t LCD_enuClearLcd()
{
	ES_t Local_enuErrorState=ES_NOK;

	Local_enuErrorState=LCD_enuSendCommand(CLEAR_DISPLAY);


	return Local_enuErrorState;
}
