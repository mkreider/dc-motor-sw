// /*
//  * test_median.c
//  *
//  * Created: 13.11.2012 13:45:06
//  *  Author: pburkhar
//  */ 
// #include <avr/io.h>
// #include <util/delay.h>
// #include "uart.h"
// /*#include "median.h"*/
// 
// char text1[] = "Hallo Welt!";
// char text[]= "Nich schon wieder!";
// uint8_t rep[]={0};
// uint8_t counter = 0;
// uint16_t adc []={400, 1278, 2890, 1554, 9876};   
// uint8_t x;
// uint16_t c;
// uint8_t t=0;
// uint16_t k=1500;
// 
// void init(void)
// {
// 	DDRB = 0b01111111;
// 	DDRC  = 0x00;
// 	PORTC &= ~(1<<PC0);
// 	init_uart();
// 	
// 	return;		
// }
// 
// 
// void swap(uint16_t *a, uint16_t *b) 
// {
//     uint16_t temp;
//  
//     temp = *a;
//     *a = *b;
//     *b = temp; 
// 	
// 	return; 
// }
// 
// 
// void median(void)
// {
// 	if(adc[0] > adc[1])
// {
// 	swap(&adc[0], &adc[1]);
// }
// 
// if(adc[2] > adc[3])
// {
// 	swap(&adc[2], &adc[3]);
// }
// 
// if(adc[1] > adc[3])
// {
// 	swap(&adc[0], &adc[2]);
// 	swap(&adc[1], &adc[3]);
// }
// 
// if(adc[4] < adc[1])
// {
// 	if(adc[4] < adc[0])
// {
// 	swap(&adc[0], &adc[4]);
// 	swap(&adc[4], &adc[1]);
// 	swap(&adc[4], &adc[3]);
// }
// }
// 	else 
// 	if(adc[4] < adc [3])
// 	{
// 		swap(&adc[4], &adc[3]);
// 	}
// 
// if(adc[2] < adc[1]) swap(&adc[2], &adc[1]);
// if(adc[2] < adc[0])	swap(&adc[2], &adc[0]);
// {	if(adc[2] < adc[0])
// 	{
// 		swap(&adc[0], &adc[2]);
// 		swap(&adc[1], &adc[2]);  //swap(&adc[1], &adc[2]);
// 	}	
// 	}		
// 	else 
// 	if(adc[2] > adc[3])
// 	{
// 		swap(&adc[2], &adc[3]);
// 	}
// 
// /*if(adc[1] > adc[2]) swap(&adc[1], &adc[2]);*/
// return;
// 		}
// 
// 
// void compare(uint16_t adc_I)
// {
// 			/*uartputc('\n');*/
// 		if(adc_I>=k)
// 		{	if(t<=2) ++t;}
// 		if(adc_I<k)
// 		{	if(t>0) --t;}
// 		uartputs("Ueberstromcounter:");
// 		uartputc(' ');
// 		uartputc(t);
// 		if(t>=3) 
// 		{	
// 			uartputc('\n');
// 			uartputs("Warnung, Ueberstrom!");
// 			uartputc(' ');
// 		}	
// 		return;		
// }
// 
// 
// int main(void)
// {
// 	init();
// 	uint8_t i;
// 
// /*	int temp;*/
// /*	uint8_t timer*/;
//     while(1)
//     {
// 		uartputc('\n');		
// 		uartputs("Array:");
// 		uartputc(' ');
// 		for(i=0;i<5;i++) {uartput_uint16(adc[i]); uartputc(' ');}
// 		 uartputc('\n');
// 		uartputs("Median:");
// 		uartputc(' ');
// 		uartput_uint16(adc[2]);
// 		uartputc('\n');
// 		compare(adc[2]);
// 		median();	
// 		uartputc('\n');
// 		uartputc('\n');
// 		_delay_ms(3000);
//     }
// }