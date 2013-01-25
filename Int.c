/**
 * @file int.c
 *
 *
 * @brief Provides interrupt routines for timer1 and watchdog
 */

/*
 * Copyright (c) YYYY Author.
 *
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "Motor.h"
#include "uart.h"
#include "median.h"
#include "adc.h"
#include <avr/wdt.h>

extern volatile uint8_t lastLimit;
extern volatile uint8_t measrdy;
extern volatile uint8_t stop;
extern volatile uint8_t Go_A;
extern volatile uint8_t Go_B;

void Interrupt_init (void)
{
	GICR	= (1<<INT2) | (1<<INT1) | (1<<INT2);												//! Activate Int0..Int2			// | (1<<INT0) | (1<<INT1);	
	MCUCR	= (1<<ISC11) | /*(1<<ISC10) | (1<<ISC01) | */(1<<ISC00);	//! Trigger Int0 and Int1 on rising edge
	MCUCSR  = (1<<ISC2);												//! external interrupt INT2 set on rising edge
	
	TIMSK	= (1<<OCIE1A);												//" Activate Timer1 Output Compare Interrupt
	TCCR1B	= (1<<WGM12) | (1<<CS11);									// | (1<<CS10); //! CLear on compare match, 8Mhz / Prescale 8 -> f = 1 MHz, T_Cnt = 1µs
	OCR1A	= 300;														//! set interval to 3ms
	
	sei();
	
}


void WDT_init (void)													//! watchdog initialization
{
	WDTCR = (1<<WDE) | (1<<WDP2) | (1<<WDP1);							//! watchdog enable, timeout time typically ~1sec
	
}


ISR(TIMER1_COMPA_vect)													//! timer interrupt for the measuring
{
	if(measrdy < 5) measrdy++;											//! check median after 4 measurements
	
	rbInsert(pRbIDrv, ADC_Read(I_DRV_ADC_CH));							//! load adc values into the ringbuffer
 	rbInsert(pRbU24,  ADC_Read(U_24V_ADC_CH));
	rbInsert(pRbUFuse, ADC_Read(U_FUSE_ADC_CH));
	
}


ISR(INT2_vect)
{																
	Go_A = 0;
	Go_B = 0; 													//! ... set Go_A=0 and Go_B=0, ...
	Motor_stop();												//! ... call the "motorstop()" routine...
	TURN_OFF(PORT_DIR_A_LED , DIR_A_LED );						//! ... and light off both direction LED's
	TURN_OFF(PORT_DIR_B_LED , DIR_B_LED );
			
}


ISR(INT0_vect)
{
	Go_A = 0;
	Go_B = 0; 													//! ... set Go_A=0 and Go_B=0, ...
	Motor_stop();												//! ... call the "motorstop()" routine...
	TURN_OFF(PORT_DIR_A_LED , DIR_A_LED );						//! ... and light off both direction LED's
	TURN_OFF(PORT_DIR_B_LED , DIR_B_LED );
}


ISR(INT1_vect)
{
	Go_A = 0;
	Go_B = 0; 													//! ... set Go_A=0 and Go_B=0, ...
	Motor_stop();												//! ... call the "motorstop()" routine...
	TURN_OFF(PORT_DIR_A_LED , DIR_A_LED );						//! ... and light off both direction LED's
	TURN_OFF(PORT_DIR_B_LED , DIR_B_LED );
}
