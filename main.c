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



// uint16_t adc_c[];
// 	adc_c[]=adc[];
uint16_t adc_c []={ 9, 8, 7, 5, 6};

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
	uint16_t testcnt=0;
	uint16_t errorcnt=0;
	
	uint16_t a,b,c,d,e;
	uint8_t i;
	uint16_t adc[5];
	uint16_t original[5];	
	
	init();
	uartputs("Testausgabe");
	
	for(a=0;a<5;a++)
			for(b=0;b<5;b++)
				for(c=0;c<5;c++)
					for(d=0;d<5;d++)
						for(e=0;e<5;e++)
						{
							adc[0] = a;
							adc[1] = b;
							adc[2] = c;
							adc[3] = d;
							adc[4] = e;
							
							for(i=0;i<5;i++) {original[i]=adc[i];}
		
							median(&adc[0]);
							if(sortCheck(&adc[0],5)) 
							{
								uartputs("Fehler\n");
								for(i=0;i<5;i++) {uartput_uint16(original[i]); uartputc(' ');}
								uartputc('\n');
								for(i=0;i<5;i++) {uartput_uint16(adc[i]); uartputc(' ');}
								uartputc('\n');	
							    errorcnt++;
							}			
							testcnt++;
							
						}
	
	uartputs("Test fertig, ");
	uartput_uint16(errorcnt);
	uartputs("Fehler, ");	
	uartput_uint16(testcnt);
	uartputs(" Faelle getestet.\n");					
		
    while(1)
    {	
		
        
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
