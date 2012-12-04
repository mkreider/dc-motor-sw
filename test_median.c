/*
 * test_median.c
 *
 * Created: 13.11.2012 13:45:06
 *
 * Last edited on: 29.11.2012 Mathias Kreider
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"
#include "median.h"
#include "uart.h"
#include <stdio.h>





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
	uint16_t arrayA[5];
	uint16_t arrayB[5];	
	
	init();
	uartputs("Testausgabe");
	
	for(a=0;a<5;a++)
			for(b=0;b<5;b++)
				for(c=0;c<5;c++)
					for(d=0;d<5;d++)
						for(e=0;e<5;e++)
						{
							arrayA[0] = a;
							arrayA[1] = b;
							arrayA[2] = c;
							arrayA[3] = d;
							arrayA[4] = e;
							
							arrayB[0] = a;
							arrayB[1] = b;
							arrayB[2] = c;
							arrayB[3] = d;
							arrayB[4] = e;
						
		
							median(&arrayA[0]);
							new_bubblesort(&arrayB[0],5);
							
							if(sortCheck(&arrayA[0],&arrayB[0],5)) 
							{
								uartputs("Fehler\n");
								for(i=0;i<5;i++) {uartput_uint16(arrayA[i]); uartputc(' ');}
								uartputc('\n');
								for(i=0;i<5;i++) {uartput_uint16(arrayB[i]); uartputc(' ');}
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
		
		check_v24();
			
// 		if((UCSR0A & (1<<RXEN0)))
// 		{
// 			uart_getc();
// 			uartputs(UDR0); uartputc(' ');
// 			uartputc('\n');
// 		}
// 		
		//uart_getc();
		//uartput_uint16(uart_getc);
		//_delay_ms(500);
		//uartputs("uart_getc()\n");
        
		//TODO:: Please write your application code 

	}    
        
}
    





