/*
 * test_median.c
 *
 * Created: 13.11.2012 13:45:06
 *  Author: pburkhar
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

char text1[] = "Hallo Welt!";
char text[]= "Nich schon wieder!";

uint8_t counter = 0;
//uint8_t adc []={1, 2, 3, 4, 5};   
uint8_t adc[]={4, 3, 5, 2, 1};	
/*uint8_t	adc[]={5, 6, 7};*/
uint8_t x;

void init(void)
{
	DDRB = 0b01111111;
	DDRC  = 0x00;
	PORTC &= ~(1<<PC0);
	init_uart();
	
	return;		
}

void swap(uint8_t *a, uint8_t *b) 
{
    uint8_t temp;
 
    temp = *a;
    *a = *b;
    *b = temp; 
	
	return; 
}

// void median(void)
// {
	
	

//### BUBBLESORT ###__________________________________________


 
void Bubble_Sort_Long(void)
{
/*	uint8_t timer = 0;*/
/*	for(timer=0;timer<5;timer++)*/
/*	{*/
	if(adc[0]>adc[1]) swap(&adc[0], &adc[1]);
	if(adc[1]>adc[2]) swap(&adc[1], &adc[2]);
	if(adc[2]>adc[3]) swap(&adc[2], &adc[3]);
	if(adc[3]>adc[4]) swap(&adc[3], &adc[4]);
/*	if(adc[0]>adc[4]) swap(adc[4], adc[0]);*/
/*	}*/
	return;	
}

		
	
void median(void)		
{
//### NEUE SCHLEIFE (3 Zahlen) ###____________________________________

	if(adc[0]<adc[1])
	{	if(adc[0]<adc[2])
		{	if(adc[1]<adc[2])
			{	x = adc[1];				
			}
			else if(adc[1]>adc[2])
			{	x = adc[2];				
			}						
		}				
	}


	if(adc[0]>adc[1])
	{	if(adc[1]<adc[2])
		{	if(adc[0]<adc[2])
			{	x = adc[0];
			}
			else if(adc[0]>adc[2])
			{	x = adc[2];				
			}			
		}			
	}


	if(adc[0]>adc[2])
	{	if(adc[1]>adc[2])
		{	if(adc[0]<adc[1])
			{	x = adc[0];				
			}			
			else if(adc[0]>adc[1])
			{	x = adc[1];			
			}
		}	
		return;		
	}
	

//### ALTE SCHLEIFE (3 ZAHLEN) ###_______________________________	
	
	
// 	if(adc[0]<adc[1])
// 	{	if(adc[1]<adc[2])
// 		{	if(adc[0]<adc[2])
// 			{	x = adc[1];
// 			}			
// 		}			
// 	}
// 	
// 	
// 	if(adc[0]<adc[1])
// 	{	if(adc[1]>adc[2])
// 		{	if(adc[0]<adc[2])
// 			{	x = adc[2];
// 			}			
// 		}			
// 	}
// 	
// 	
// 	
// 	if(adc[0]>adc[1])
// 	{	if(adc[1]<adc[2])
// 		{	if(adc[0]<adc[2])
// 			{	x = adc[0];		
// 			}			
// 		}		
// 	}
// 	
// 		
// 		if(adc[0]>adc[1])
// 	{	if(adc[1]<adc[2])
// 		{	if(adc[0]>adc[2])
// 			{	x = adc[2];
// 			}			
// 		}			
// 	}
// 		
// 		
// 		if(adc[0]<adc[1])
// 	{	if(adc[1]>adc[2])
// 		{	if(adc[0]>adc[2])
// 			{	x = adc[0];
// 			}			
// 		}			
// 	}
// 	
// 		
// 	if(adc[0]>adc[1])
// 	{	if(adc[1]>adc[2])
// 		{	if(adc[0]>adc[2])
// 			{	x = adc[1];
// 			}			
// 		}			
// 	}

//### ALTE SWAP-SCHLEIFE###___________________________
/*
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
*/
		}








int main(void)
{
	init();
	uint8_t i;
/*	int t;*/
/*	int temp;*/
	uint8_t timer;
    while(1)
    {
        _delay_ms(1000);
	
		for(i=0;i<5;i++) uartputc(adc[i]);
		 uartputc('\n');
/*		median();*/	
		for(timer=0;timer<5;timer++) Bubble_Sort_Long();
		//Bubble_Sort_Long();
		//swap(&adc[0], &adc[1]);
		//uartputc(temp);
		//uartputc(x);
		uartputc(adc[2]);
		uartputc('\n');
		uartputc('\n');
    }
}