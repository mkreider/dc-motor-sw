/**
 * @@file uart.c
 *
 *
 * @@brief UART functions. Init, read chars, write chars, write 8/16b uints
 * 
 *  blabla
 */


#include <avr/io.h>
#include "uart.h"


// Kommentierung einfügen und pflegen sodass man es lesen kann >> DANKE!!
//  >>>>>>>> bitte !
// ändern für MEGA 32A

/**
 * @@brief Initialises the UART on an ATMEGA32 to 57600 baud, 8N1 
 *
 *
 */
void init_uart()
{
	UCSRB			=		(1<<RXEN)  | (1<<TXEN);						//! RXEN and TXEN Enabled.
	UCSRC			=		(1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);		//! Asynchron, no parity, 1 stop bit, 8 bit size, no CK.	
	UBRRL			=		0x08;										//! Baud rate 115,2k at 16Mhz crystal oscillator
	
}

/**
 * @brief Writes a string to the serial console
 *
 * @param[in] text The c string to write
 *
 */
void uartputs(const char* text)								//! nicht veränderbar wegen char das * ist zum anzeigen das es ein pointer ist
{
	char *ptext;											//! Kopie des orginals
	ptext = (char*)text;

	
	while (*ptext != 0x00)									//! soll aufhören wenn es 0x00 erreicht hat
	{
		uartputc(*(ptext++));								//! damit alles angezeigt werden soll ++ 
	}
}

/**
 * @ brief Writes a single character to the serial console
 *
 * @@param[in] chr The char to write
 *
 */

void uartputc(char chr)				
{
	while(!((UCSRA)&(1<<UDRE)));
	UDR=chr;
}

/**
 * @@brief Writes a 8/16 bit unsigned int as ASCII to the serial console
 *
 * @@param[in] num The unisgned int to write
 *
 */
void uartput_uint16(uint16_t num)
{
	uint16_t div	=	10000;
	uint16_t erg;											//! erg_ ergebnis
	uint8_t  fn = 1;										//! fn= führende null
		
	while (div)
	{
		erg = (num/div);
		if(erg != 0) fn = 0; 
		if((!fn)|(div==1)) uartputc((char)(erg+48));		//! ausgabe der zahl
		
		num %= div;
		div /= 10;
	}
}	

/**
 * @@brief Fetches a single character from the serial console. Waits until char is received.
 *
 * @ return Unsigned char received from console
 *
 */
uint8_t uart_getc(void)
{
	while (!(UCSRA & (1<<RXC)));							//! wait until chars are available		UCSRA und RXC !!
    return UDR;												//! give char from UDR to the caller
}

/**
 * @@brief Fetches a single character from the serial console. Returns immediatley. 
 *
 * @ return Unsigned char received from console or Zero if RX buffer was empty
 *
 */
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


