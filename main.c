/*
 * main.c
 *
 * Created: 13.11.2012 13:45:06
  */ 

#include <avr/io.h>
#include "adc.h"
#include "median.h"

int main(void)
{
    while(1)
    {
        
    }
}

char text() = "Achtung Ueberstrom"

void output (const char* text())				//nicht veränderbar wegen char das * ist zum anzeigen das es ein pointer ist
{
	while (*text!=0x00)							//soll aufhören wenn es 0x00 erreicht hat
	{
		uartputc (*(text++));		// damit alles angezeigt werden soll ++ 
	}
}