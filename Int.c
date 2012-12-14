#include <avr/io.h>
#include <avr/interrupt.h>


#define EL1				INT0_vect	
#define EL2				INT1_vect
#define STOPP			INT2_vect 
#define TI2				TIMER2_OVF_vect
#define TI1				TIMER1_OVF_vect
#define TI0				TIMER0_OVF_vect


void Interrupt_init (void)
{
	GICR = (1<<INT1) | (1<<INT0) | (1<<INT2);
	sei();
	
}


void WDT_init (void)
{
	WDTCR = (1<<WDE) | (1<<WDP2) | (1<<WDP1) (1<<WDP0);
	
}


void WDT_reset (void)
{
	WDTCR = (1<<WDTOE) 
	WDTCR = (0<<WDE);
	WDTCR = (1<<WDE) | (0<<WDTOE);
	
}