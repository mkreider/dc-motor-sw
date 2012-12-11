/*
 * Projekt DC Motorsteuerung
 *
 * Projektleiter: Herz Tim
 * Nadja Fischer
 * Burkhard Philip 
 * Karadeniz Burak
 *
 * GSI Helmholtszzentrum für Schwerionenforschung GmbH
 * 64291 Darmstadt
 * Planckstraße 1
 * 
 
 * main.c
  
 * Created: 13.11.2012 13:45:06
 *
 * Last edited on: 21.11.2012 P.B.
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "adc.h"
#include "median.h"
#include "uart.h"
#include "int.h"
#include "error.h"

		
		
		
						//* Notizen:
						
							//  Power-Up Timer im Init nötig?
							//  Jedes Interrupt routinen mit Abfrage zu nFault beenden.
							// 	Fehlermeldung über RGB LED blinken realisieren				
		
		
		
		
		
		
		
void init(void)			
{			
										//* Einfügen der benötigten Konstanten und Variablen
	uint8_t error = 0x00;						// Error Register zur Fehlererkennung								
	
	
	DDRA = 0b01110000;					//* Inputs / Outputs		
	DDRB = 0b11011111;							// Pull-Ups???
	DDRC = 0b00000000;
	DDRD = 0b11000111;		
	
	
	PORTB |= (1<<PB5)					//* Sleep Mode
												// setzen des Moter Treibers in den Sleep Modus						
		
	init_uart();						//* Rufe UART init auf
	ADC_init ();						//* Rufe ADC init auf
	
	
	if (PINC & (1<<PC7))				//* Motorerkennung //
	{											// Wenn Motor vorhanden dann rufe Interrupt init auf	
	Interrupt_init ();							// Wenn nicht dann setze Pin0 des Error Registers auf 1
	}											
	else
	{
	 error |= (1<<0);							
	}
	
	
	return;		
}




int main(void)
{
	init();								//* Rufe init auf
		

    while(1)
    {	
		
		
	if (PC7 > 0)						//* nFault Prüfung						
	{											// Wenn nFault Fehler meldet dann setze Pin1 des Error Registers auf 1 
		error |= (1<<1)
	}
		
	
	if (error >  0)						//* Fehlererkennung
	{											// Wenn ein Fehler vorliegt dann rufe Error init auf
		error_init ();							// Wenn nicht dann gehe weiter
	}
		
		
	if (PA4 == 1)
	{
		// Remote Vorgang
	} 
	else
	{
		// local Vorgang
	}			

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
