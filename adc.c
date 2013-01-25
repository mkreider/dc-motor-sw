
#include <avr/io.h>

void ADC_init (void)
{
	uint16_t wert;
	
	ADMUX	= (1<<REFS0);									//! voltage reference , avcc with 5Volt is set
	ADCSRA	= (1<<ADPS1)|(1<<ADPS0);						//! division factor between XTAL freq and adc input clock, set to 8
	ADCSRA |= (1<<ADEN);									//! adc enable bit
	
	ADCSRA |= (1<<ADSC);									//! if this bit is set, the adc conversion will start
	
	
// 	while (ADCSRA & (1<<ADSC)){}							
// 	wert	= ADCW;
	
	return;
}

uint16_t ADC_Read (uint8_t channel)
{
	ADMUX	= (ADMUX & ~(0x0F)) | (channel & 0x0F);
	ADCSRA |= (1<<ADSC);
	while (ADCSRA & (1<<ADSC)){}
		
	return ADCW;	
}  