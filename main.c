/*
 * main.c
 *
 * Created: 13.11.2012 13:45:06
 *
 * Last edited on: 21.11.2012 P.B.
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"
#include "median.h"
#include "uart.h"
#include <stdio.h>



uint16_t adc []= { 9, 8, 7, 5, 6};
// uint16_t adc_c[];
// 	adc_c[]=adc[];
uint16_t adc_c []={ 9, 8, 7, 5, 6};
uint8_t i;
uint16_t adca[4];

void init(void)
{
	DDRB = 0b01111111;
	DDRC  = 0x00;
	PORTC &= ~(1<<PC0);
	init_uart();
	
	return;		
}


#include "adc.h"
#include "median.h"

int main(void)
{
	init();
	//uint16_t adc[]={5, 4, 3, 2, 1};
	
		
    while(1)
    {	
		
        uartputs("Testausgabe");
		uartputc('\n');
		for(i=0;i<5;i++) {uartput_uint16(adc_c[i]); uartputc(' ');}
			
		median(&adc[0]);
		//bubblesort(*adc, 5);
		//new_bubblesort();
		
		uartputc('\n');
		for(i=0;i<5;i++) {uartput_uint16(adc[i]); uartputc(' ');}
		uartputc('\n');
		uartput_uint16(adc[2]);
		uartputc('\n'); 
		uartputc('\n');
		_delay_ms(3000);
		//TODO:: Please write your application code 

		}
		}    
        

    





// 
// // char text() = "Achtung Ueberstrom";
// 
// void output (const char* text())				//nicht veränderbar wegen char das * ist zum anzeigen das es ein pointer ist
// {
// 	while (*text!=0x00)							//soll aufhören wenn es 0x00 erreicht hat
// 	{
// 		uartputc (*(text++));		// damit alles angezeigt werden soll ++ 
// 	}
// }
