/*
 * test_median.c
 *
 * Created: 13.11.2012 13:45:06
 *  Author: pburkhar
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "include/uart.h"

char text1[] = "Hallo Welt!";
char text[]= "Nich schon wieder!";

uint8_t counter = 0;
uint8_t adc[]={4, 3, 5, 2, 1};


void init(void)
{
	DDRB = 0b01111111;
	DDRC  = 0x00;
	PORTC &= ~(1<<PC0);
	init_uart();
	
	return;		
}



// void median(void)
// {
	
	
void swap(uint8_t *a, uint8_t *b) 
{
    uint8_t temp;
 
    temp = *a;
    *a = *b;
    *b = temp; 
	
	return; 
}


		
		
	
void median(void)		
{

if(adc[0] > adc[1])
{
	swap(adc[0], adc[1]);
}

if(adc[2] > adc[3])
{
	swap(adc[2], adc[3]);
}

if(adc[1] > adc[3])
{
	swap(adc[0], adc[2]);
	swap(adc[1], adc[3]);
}

if(adc[4] < adc[1])
{
	if(adc[4] < adc[0])
{
	swap(adc[0], adc[4]);
	swap(adc[4], adc[1]);
	swap(adc[4], adc[3]);
}
	else if(adc[4] < adc [3])
	{
		swap(adc[3], adc[3]);
}	}

if(adc[2] < adc[1])
{	if(adc[2] < adc[0])
	{
		swap(adc[0], adc[2]);
		swap(adc[1], adc[2]);
	}		
	else if(adc[2] > adc[3])
	{
		swap(adc[2], adc[3]);
	}
}		

		}




int main(void)
{
	init();
	uint8_t i;
	
    while(1)
    {
        for(i=0;i<5;i++) uartputc(adc[i]);
		median();	 
    }
}