#include <avr/io.h>
#include "uart.h"


// Kommentierung einfügen und pflegen sodass man es lesen kann >> DANKE!!
// ändern für MEGA 32A


void uartputs(const char* text)	//nicht veränderbar wegen char das * ist zum anzeigen das es ein pointer ist
{
	char *ptext;	// Kopie des orginals
	ptext = (char*)text;

	
	while (*ptext != 0x00)				//soll aufhören wenn es 0x00 erreicht hat
	{
		uartputc(*(ptext++));		// damit alles angezeigt werden soll ++ 
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


uint8_t uart_getc(void)
{
	while (!(UCSRA & (1<<RXC)));   // wait until chars are available		UCSRA und RXC !!
    return UDR;                   // give char from UDR to the caller
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


void init_uart()
{
	UCSRB			=		(1<<RXEN)  | (1<<TXEN); //(1<<TXEN0); //(1<<RXEN0)  | (1<<TXEN0);		// RXEN und TXEN Enabled.
	UCSRC			=		(1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);		// Asynchron, no parity, 1 stop bit, 8 bit size, no CK.	
	UBRRL			=		0x08;							// Baud rate 57.6k
	
	//UCSR0B			|=		(1<<RXEN0);
}	

	uint8_t tmp;			
	uint8_t cin;


void test_uartgetc(void)
{
		cin = uart_getc();
		uartputc('\f');
		
		uartputs("Count ");
		uartput_uint16(tmp++);
		uartputs("\n\r"); 
		
		switch(cin)
		{
		  /*case 'a': uartputs("Forward\n\r"); break;
			case 'b': uartputs("Reverse\n\r"); break;
			case 'c': uartputs("Stop\n\r"); break;
			case 'd': uartputs("Overcurrent\n\r"); break;
			case 'e': uartputs("Kann das ding Sondergedingens? ä ö ü $ öäü\n\r"); break;
			case 'f': uartputs("Feierabend!\n\r"); break;
			case 'g': uartputs("Work Work!\n\r"); break;
			case 'h': uartputs("Ich bin blind, nicht taub!\n\r"); break;
			case 'i': uartputs("Kling Glöckchen klingelingeling!\n\r"); break;
			case 'j': uartputs("Fischers Fritz fischt frische Fische.\n\r"); break;
			case 'k': uartputs("Dönertier. \n\r"); break;
			case 'l': uartputs("Nonsense \n\r"); break;
			case 'm': uartputs("STARCRAFT II FTW \n\r"); break;
			case 'n': uartputs("Ich fahr heute alleine und DU bleibst länger hier :p ... da kommste heut ja kaum zum SC II zoggen *auslach* :> \n\r"); break;
			default: uartputs("Unknown\n\r");break;
		*/}
		
		cin = 0x00;
		//return;
}