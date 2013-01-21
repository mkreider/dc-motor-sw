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

void Interrupt_init (void)
{
	GICR	= (1<<INT2);// | (1<<INT0) | (1<<INT1);					//Activate Int0..Int2
	MCUCR	= (1<<ISC11) | (1<<ISC10) | (1<<ISC01) | (1<<ISC00); //Trigger Int0 and Int1 on rising edge
	
	TIMSK	= (1<<OCIE1A);	//Activate Timer1 Output Compare Interrupt
	TCCR1B	= (1<<WGM12) | (1<<CS11); //CLear on compare match, 8Mhz / Prescale 8 -> f = 1 MHz, T_Cnt = 1µs
	OCR1A	= 3000; //set interval to 3ms
	
	sei();
	
}


void WDT_init (void)
{
	WDTCR = (1<<WDE) | (1<<WDP2) | (1<<WDP1);
	
}


ISR(TIMER1_COMPA_vect)
{
	if(measrdy < 5) measrdy++;
	
	rbInsert(pRbIDrv, ADC_Read(I_DRV_ADC_CH));	
	rbInsert(pRbU24,  ADC_Read(U_24V_ADC_CH));
	rbInsert(pRbUFuse, ADC_Read(U_FUSE_ADC_CH));
	
}



