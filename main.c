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
#include "remote.h"

//Makros/defines werden im allgemeinen komplett grossgeschrieben,
//macht die unterscheidung von variablen einfacher. 

//die koennen mehr als nur Pins einen Namen geben:

//#define  SleepDriver PB5

//Motor Driver nfault pin
#define PIN_NFAULT   	PINC
#define PORT_NFAULT  	PORTC
#define DDR_NFAULT   	DDRC
#define NFAULT       	(1<<PC7)

#define GET_NFAULT   	PIN_NFAULT & NFAULT

//Motor driver sleep
#define PIN_DRV_SLEEP	PINB
#define PORT_DRV_SLEEP	PORTB
#define DDR_DRV_SLEEP 	DDRB
#define DRV_SLEEP 	(1<<PB5)

#define SET_DRV_SLEEP 	PORT_DRV_SLEEP |=  DRV_SLEEP
#define SET_DRV_ARM  	PORT_DRV_SLEEP &= ~DRV_SLEEP	
			
//Error codes		
#define ERR_0		0x01
#define ERR_NFAULT      0x02
#define ERR_2      	0x04
#define ERR_3      	0x08
#define ERR_4      	0x10
#define ERR_5      	0x20
#define ERR_6      	0x40
#define ERR_7      	0x80


	
						
						//* Notizen:
						
							//  Power-Up Timer im Init nötig?
							//  Jedes Interrupt routinen mit Abfrage zu nFault beenden.
							// 	Fehlermeldung über RGB LED blinken realisieren				
							//	"Motorerkennung" überarbeiten
							//	Mit defines arbeiten --> siehe "SLeepTreiber"
							//  "Richtung" (siehe Schaltplan) einpflegen
		
		
		
		
		
void init(void)			
{			
								//* Einfügen der benötigten Konstanten und Variablen
	uint8_t error_reg = 0x00;				// Error Register zur Fehlererkennung								
	
	
	DDRA = 0b01110000;					//* Inputs / Outputs		
	DDRB = 0b11011111;					// Pull-Ups???
	DDRC = 0b00000000;
	DDRD = 0b11000111;		
	
	
	SET_DRV_SLEEP;						// setzen des Motortreibers in den Sleep Modus						
		
	init_uart();						//* Rufe UART init auf
	ADC_init ();						//* Rufe ADC init auf
	Interrupt_init();					//* Rufe Interrupt init auf
	
	
	return;		
}




int main(void)
{
	init();							//* Rufe init auf
		

    while(1)
    {	
		
		
	if (GET_NFAULT)						//* nFault Prüfung						
	{							// Wenn nFault Fehler meldet dann setze Pin1 des Error Registers auf 1 
		error_reg |= ERR_NFAULT;
	}
		
	
	if (error !=  0)					//* Fehlererkennung
	{							// Wenn ein Fehler vorliegt dann rufe  das Error-Modul auf
		error_modul ();					// Wenn nicht dann gehe weiter
		// erstelllen bzw abändern
	}
		
	

	//funktioniert so nicht. Wenn dann if(PINA & (1<<PA4)) oder eben per Makro
 	
	if (PA4 == 1)						//* Steuerwahl
	{							// Wenn Umschalter auf High schaltet dann rufe das Remote-Modul auf
		remote_modul ();				// Wenn nicht dann gehe weiter				
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
