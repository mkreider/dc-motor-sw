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



void init(void)
{	
	//DDRA = 0b00000111;			//I/O's fuer die DC-Motorsteuerung
	//DDRB = 0b11111111;			// Pull-Ups???
	//DDRC = 0b00001110;
	//DDRD = 0b00000011;		
								
	
	
	DDRB = 0b01111111;				
	DDRC  = 0x00;
	PORTC &= ~(1<<PC0);
	init_uart();
	
	return;		
}



int main(void)
{
	init();
	uartputs("Hallo Welt\n");
	uint8_t tmp;			
	uint8_t cin;
		
	
    while(1)
    {	
		
		//TODO:: Please write your application code
		//uartputc(uart_getc());
		
		cin = uart_getc();
		uartputc('\f');
		
		uartputs("Count ");
		uartput_uint16(tmp++);
		uartputs("\n\r"); 
		
		switch(cin)
		{
			case 'a': uartputs("Forward\n\r"); break;
			case 'b': uartputs("Reverse\n\r"); break;
			case 'c': uartputs("Stop\n\r"); break;
			default: uartputs("Unknown\n\r");break;
		}
		
		cin = 0x00;
	}    
        
}
    





// 
// // char text() = "Achtung Ueberstrom";
// 
// void output (const char* text())				//nicht ver�nderbar wegen char das * ist zum anzeigen das es ein pointer ist
// {
// 	while (*text!=0x00)							//soll aufh�ren wenn es 0x00 erreicht hat
// 	{
// 		uartputc (*(text++));		// damit alles angezeigt werden soll ++ 
// 	}
// }
