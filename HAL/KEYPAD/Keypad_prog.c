/*
 * Keypad_prog.c
 *
 *  Created on: Aug 26, 2023
 *      Author: Marina
 */
#include "../../LIB/types.h"
#include "../../LIB/errorState.h"

#include "../../MCAL/DIO/DIO_int.h"
#include "../LCD/LCD_int.h"

#include "Keypad_config.h"
#include "Keypad_priv.h"

ES_t KEYPAD_enuInit(void)
{
	ES_t Local_ErrorState =ES_NOK;

  	Local_ErrorState= DIO_enuSetPinDirection(KPD_PORT,KPD_COLUMN0_PIN,DIO_u8OUTPUT);
  	Local_ErrorState= DIO_enuSetPinDirection(KPD_PORT,KPD_COLUMN1_PIN,DIO_u8OUTPUT);
  	Local_ErrorState= DIO_enuSetPinDirection(KPD_PORT,KPD_COLUMN2_PIN,DIO_u8OUTPUT);
 	Local_ErrorState= DIO_enuSetPinDirection(KPD_PORT,KPD_COLUMN3_PIN,DIO_u8OUTPUT);

 	Local_ErrorState= DIO_enuSetPinDirection(KPD_PORT,KPD_ROW0_PIN,DIO_u8INPUT);
 	Local_ErrorState= DIO_enuSetPinDirection(KPD_PORT,KPD_ROW1_PIN,DIO_u8INPUT);
 	Local_ErrorState= DIO_enuSetPinDirection(KPD_PORT,KPD_ROW2_PIN,DIO_u8INPUT);
 	Local_ErrorState= DIO_enuSetPinDirection(KPD_PORT,KPD_ROW3_PIN,DIO_u8INPUT);

  	Local_ErrorState= DIO_enuSetPinValue(KPD_PORT,KPD_COLUMN0_PIN,DIO_u8HIGH);
  	Local_ErrorState= DIO_enuSetPinValue(KPD_PORT,KPD_COLUMN1_PIN,DIO_u8HIGH);
  	Local_ErrorState= DIO_enuSetPinValue(KPD_PORT,KPD_COLUMN2_PIN,DIO_u8HIGH);
 	Local_ErrorState= DIO_enuSetPinValue(KPD_PORT,KPD_COLUMN3_PIN,DIO_u8HIGH);

 	Local_ErrorState= DIO_enuSetPinValue(KPD_PORT,KPD_ROW0_PIN,DIO_u8PULL_UP);
 	Local_ErrorState= DIO_enuSetPinValue(KPD_PORT,KPD_ROW1_PIN,DIO_u8PULL_UP);
 	Local_ErrorState= DIO_enuSetPinValue(KPD_PORT,KPD_ROW2_PIN,DIO_u8PULL_UP);
 	Local_ErrorState= DIO_enuSetPinValue(KPD_PORT,KPD_ROW3_PIN,DIO_u8PULL_UP);

	return Local_ErrorState;
}

u8 KEYPAD_u8GetPressedKey(void)
{
	        u8 Local_u8PressedKey ,Local_u8ColumnIndex ,Local_u8RowIndex ,Local_u8PinState;

        	Local_u8PressedKey=KPD_NO_PRESSED_KEY;

            static u8 Local_u8ArrKPD[ROW_NUM][COLUMN_NUM]=KPD_ARY_VAL;

        	static u8 Local_u8ArrColumn[COLUMN_NUM]={KPD_COLUMN0_PIN,KPD_COLUMN1_PIN,KPD_COLUMN2_PIN,KPD_COLUMN3_PIN};
            static u8 Local_u8ArrRow[ROW_NUM]={KPD_ROW0_PIN,KPD_ROW1_PIN,KPD_ROW2_PIN,KPD_ROW3_PIN};

            for(Local_u8ColumnIndex=0 ;Local_u8ColumnIndex <COLUMN_NUM ;Local_u8ColumnIndex++)
	          {
            	//Activate column
            	DIO_enuSetPinValue(KPD_PORT,Local_u8ArrColumn[Local_u8ColumnIndex],DIO_u8LOW);

            	for(Local_u8RowIndex=0;Local_u8RowIndex <ROW_NUM ;Local_u8RowIndex++)
        		{
                   //Read the current row
        			 DIO_enuGetPinValue(KPD_PORT,Local_u8ArrRow[Local_u8RowIndex],&Local_u8PinState);
        	      // check if key is press
        	    if(DIO_u8LOW == Local_u8PinState)
        	      {
       			 Local_u8PressedKey=Local_u8ArrKPD[Local_u8RowIndex][Local_u8ColumnIndex];
       		      // polling (busy waiting) until the key is released
       			 while(DIO_u8LOW == Local_u8PinState)
       		   {
       				 DIO_enuGetPinValue(KPD_PORT,Local_u8ArrRow[Local_u8RowIndex],&Local_u8PinState);
       		   }
       			 return Local_u8PressedKey;
        	      }
        		}

        		 // Deactivate current column
        		 DIO_enuSetPinValue(KPD_PORT,Local_u8ArrColumn[Local_u8ColumnIndex],DIO_u8HIGH);
	          }
            return Local_u8PressedKey;
	}

