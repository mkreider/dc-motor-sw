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
	
	ADMUX	= (1<<REFS0);									//! voltage reference , avcc with 5Volt is set
	ADCSRA	= (1<<ADPS1)|(1<<ADPS0);						//! division factor between XTAL freq and adc input clock, set to 8
	ADCSRA |= (1<<ADEN);									//! adc enable bit
	
	ADCSRA |= (1<<ADSC);									//! if this bit is set, the adc conversion will start
	
	
// 	while (ADCSRA & (1<<ADSC)){}							
// 	wert	= ADCW;
	
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
