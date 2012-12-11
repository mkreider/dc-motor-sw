
#include <avr/io.h>

void ADC_init (void)
{
	uint16_t wert;
	
	ADMUX	= (0<<REFS1)|(1<<REFS0);
	ADCSRA	= (1<<ADPS1)|(1<<ADPS0); 
	ADCSRA |= (1<<ADEN);
	
	ADCSRA |= (1<<ADSC);
	
	
	while (ADCSRA & (1<<ADSC)){}
	wert	= ADCW;
	
	return;
}

uint16_t ADC_Read (uint8_t channel)
{
	ADMUX	= (ADMUX & ~(0x0F)) | (channel & 0x0F);
	ADCSRA |= (1<<ADSC);
	while (ADCSRA & (1<<ADSC)){}
		
	return ADCW;	
}  