﻿/*
 * IncFile1.h
 *
 * Created: 05.11.2012 10:43:17
 *  Author: therz
 */ 


#ifndef ADC_H_
#define ADC_H_
/** Initialise Analog/Digital Converter */ 
void ADC_init (void);
/** Returns single read from adc channel */ 
uint16_t ADC_Read (uint8_t channel);


#endif /* ADC_H_ */
