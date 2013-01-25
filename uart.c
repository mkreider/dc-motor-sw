/**
 * @file uart.c
 *
 *
 * @brief UART functions for ATMEGA32. Char, str, uint output and char input functions.
 */

/*
 * Copyright (c) YYYY Author.
 *
 */


#include <avr/io.h>
#include "uart.h"


// Kommentierung einfügen und pflegen sodass man es lesen kann >> DANKE!!
// bitte !
// ändern für MEGA 32A


void init_uart()
{
	UCSRB			=		(1<<RXEN)  | (1<<TXEN);						//! RXEN and TXEN Enabled.
	UCSRC			=		(1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);		//! Asynchron, no parity, 1 stop bit, 8 bit size, no CK.	
	UBRRL			=		0x08;										//! Baud rate 115,2k at 16Mhz crystal oscillator
	
}


void uartputs(const char* text)	

{
	char *ptext;											//! Kopie des orginals
	ptext = (char*)text;

	
	while (*ptext != 0x00)									//! soll aufhören wenn es 0x00 erreicht hat
	{
		uartputc(*(ptext++));								//! damit alles angezeigt werden soll ++ 
	}
}

void uartputc(char wort)				
{
	while(!((UCSRA)&(1<<UDRE)));
	UDR=wort;
}

void uartput_uint16(uint16_t zahl)
{
	uint16_t div	=	10000;
	uint16_t erg;											//! erg_ ergebnis
	uint8_t  fn = 1;										//! fn= führende null
		
	while (div)
	{
		erg = (zahl/div);
		if(erg != 0) fn = 0; 
		if((!fn)|(div==1)) uartputc((char)(erg+48));		//! ausgabe der zahl
		
		zahl %= div;
		div /= 10;
	}
}	


uint8_t uart_getc(void)
{
	while (!(UCSRA & (1<<RXC)));   // wait until chars are available		UCSRA und RXC !!
    return UDR;                   	// give char from UDR to the caller

}


uint8_t uart_getc_nowait(void)
{
	if(UCSRA & (1<<RXC))
	{
		return UDR;
	}
	
	else
	{
		return 0;
	}
}



