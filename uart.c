#include <avr/io.h>



void uartputs(const char* text)	//nicht veränderbar wegen char das * ist zum anzeigen das es ein pointer ist
{
	char *ptext;	// Kopie des orginals
	ptext = text;

	
	while (*ptext != 0x00)				//soll aufhören wenn es 0x00 erreicht hat
	{
		uartputc(*(ptext++));		// damit alles angezeigt werden soll ++ 
	}
}

void uartputc(char wort)				
{
	while(!((UCSR0A)&(1<<UDRE0)));
	UDR0=wort;
}

void uartput_uint16(uint16_t zahl)
{
	uint16_t div	=	10000;
	uint16_t erg;							//erg_ ergebnis
	uint8_t  fn = 1;						//fn= führende null
	
	while (div)
	{
		erg = (zahl/div);
		if(erg != 0) fn = 0; 
		if((!fn)|(div==1)) uartputc((char)(erg+48));		//ausgabe der zahl
		
		zahl %= div;
		div /= 10;
	}
}	

void init_uart()
{
	UCSR0B			=		(1<<RXEN0)  | (1<<TXEN0);		// RXEN und TXEN Enabled.
	UCSR0C			=		(1<<UCSZ01) | (1<<UCSZ00);		// Asynchron, no parity, 1 stop bit, 8 bit size, no CK.	
	UBRR0			=		0x08;							// Baud rate 57.6k
}	