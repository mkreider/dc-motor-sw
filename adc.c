/**
 * @file adc.c
 *
 *
 * @brief Analog/Digital Converter functions for ATMEGA32. ADC Initialisation and read with channel select.
 */

/*
 * Copyright (c) YYYY Author.
 *
 */
﻿
#include <avr/io.h>


/**
 * @brief Initialises the ADC to single ended operation with internal voltage reference
 *
 *
 */
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

/**
 * @brief Performs a single readout of the ADC
 *
 * @param[in] ADC channel number 0-7
 *
 * @retval 16 bit ADC sample value
 */
uint16_t ADC_Read (uint8_t channel)
{
	ADMUX	= (ADMUX & (0xF8)) | (channel & 0x07);
	ADCSRA |= (1<<ADSC);
	while (ADCSRA & (1<<ADSC)){}
		
	return ADCW;	
}  
