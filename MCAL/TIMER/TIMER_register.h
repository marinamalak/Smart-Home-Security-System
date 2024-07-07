/*
 * TIMER0_register.h
 *
 *  Created on: Jan 28, 2024
 *      Author: aya
 */

#ifndef MCAL_TIMER0_TIMER_REGISTER_H_
#define MCAL_TIMER0_TIMER_REGISTER_H_

#define TCCR0              *((volatile u8*)0x53)  //Timer0 control register
#define TCCR0_WGM00        6         //Waveform generation mode bit0
#define TCCR0_WGM01        3         //Waveform generation mode bit0
#define TCCR0_CS02         2         //prescaler bit2
#define TCCR0_CS01         1         //prescaler bit1
#define TCCR0_CS00         0         //prescaler bit0
#define TCCR0_COM00        4         /*Compare Match Output Mode */
#define TCCR0_COM01        5

#define OCR0               *((volatile u8*)0x5c)       //Output compare register 0

//TCNT
#define TCNT0   *((volatile u8*)0x52)

//TIMSK

#define TIMSK              *((volatile u8*)0x59)      //Timer/Counter Interrupt Mask
#define TIMSK_TOIE0        0       // Timer/Counter0 Overflow Interrupt Enable
#define TIMSK_OCIE0        1      //Timer/Counter0 Compare Match Interrupt Enable
#define TIMSK_TICIE1       5     // Timer/Counter1, Input Capture Interrupt Enable


#define TCCR1A              *((volatile u8*)0x4f)  //Timer1A control register
#define TCCR1A_WGM10        0                  //Waveform Generation Mode
#define TCCR1A_WGM11        1
#define TCCR1A_COM1B0       4                  //Compare Output Mode for Compare unit B
#define TCCR1A_COM1B1       5
#define TCCR1A_COM1A0       6                  //Compare Output Mode for Compare unit A
#define TCCR1A_COM1A1       7

#define TCCR1B              *((volatile u8*)0x4e)  //Timer1B control register
#define TCCR1B_CS10         0                  //Clock Select //PRESCALER
#define TCCR1B_CS11         1
#define TCCR1B_CS12         2
#define TCCR1B_WGM12        3                  //Waveform Generation Mode
#define TCCR1B_WGM13        4
#define TCCR1B_ICES1        6                  // Input Capture Edge Select
#define TCCR1B_ICNC1        7                  // Input Capture Noise Canceler

#define OCR1AH	*((volatile u8*) 0x4b)
#define OCR1AL	*((volatile u8*) 0x4a)

#define OCR1A	*((volatile u16*) 0x4a)

#define OCR1BH	*((volatile u8*) 0x49)
#define OCR1BL	*((volatile u8*) 0x48)

#define OCR1B	*((volatile u16*) 0x48)

#define ICR1H	*((volatile u8*) 0x47)
#define ICR1L	*((volatile u8*) 0x46)

#define ICR1	*((volatile u16*) 0x46)


#define TCNT1H	*((volatile u8*) 0x4d)
#define TCNT1L	*((volatile u8*) 0x4c)

#define TCNT1	*((volatile u16*) 0x4c)


//TIFR
#define TIFR   *((volatile u8*)0x58)    //Timer/Counter Interrupt Flag
#define TIFR_TOV0           0       // Timer/Counter0 Overflow Flag

//WATCH DOG
#define WDTCR	*((volatile u8*) 0x41)
#define WDTCR_WDTOE      4   // Watchdog Turn-off Enable
#define WDTCR_WDE        3   // Watchdog Enable
#define WDTCR_WDP2       2   // Watchdog Timer Prescaler
#define WDTCR_WDP1       1
#define WDTCR_WDP0       0


#endif /* MCAL_TIMER0_TIMER_REGISTER_H_ */
