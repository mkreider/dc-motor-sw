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
 * Last edited on: 17.12.2012
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "defines.h"
#include "adc.h"
#include "median.h"
#include "uart.h"
#include "int.h"
#include "error.h"
#include "remote.h"

extern uint8_t error_reg;
						
						//* Notizen:
							
							//* Software
							
							//  Power-Up Timer im Init nötig?
							//  Jedes Interrupt routinen mit Abfrage zu nFault beenden.
							// 	Fehlermeldung über UART/Blinkende Gelbe LED				
							//	"Motorerkennung" überarbeiten
							//	Mit defines arbeiten 
							//  "Richtung" (siehe Schaltplan) einpflegen
							//	Abfrage des Watchdog flags - gab es einen Watchdog reset? wenn ja -> error
							//  EXT. QUARZ einstellen
							
							//* Hardware
							
							//	Layout ändern --> RGB LED tauschen (LED gb)
							//	 
		
		
		
		
		
void init(void)			
{			
												//* Einfügen der benötigten Konstanten und Variablen
	error_reg = 0x00;								// Error Register zur Fehlererkennung							
	
												//* Inputs / Outputs	
	DDRA = U_FUSE_ADC | I_DRV_ADC | U_24V_ADC | LOC_RMT;						
	DDRB = 0b11011111;					
	DDRC = 0b00000000;
	DDRD = 0b11000111;
			
	
	SET_DRV_SLEEP;								// setzen des Motortreibers in den Sleep Modus												// Pull-Ups???
	PORTA = 0;					
	PORTB = (0<<PB7)|(1<<PB4);					// Motor-Treiber auf Brake 
    //PORTC = NFAULT;							// Fehler setzen direkt beim Start--> nicht schlau!!
		
						
	
		
	init_uart();								//* Rufe UART init auf
	ADC_init ();								//* Rufe ADC init auf
	Interrupt_init();							//* Rufe Interrupt init auf
	WDT_init ();								//* Rufe Watchdog Init auf
		
	return;		
}




int main(void)
{
	init();										//* Rufe init auf
	// Aktiv--> an UART (Ausgabe)(Selbstzerstörung Aktiviert)	

    while(1)
    {	
	// WATCHDOG TEST 	
		
		if (GET_NFAULT)								//* nFault Prüfung						
		{													
			error_reg |= ERR_NFAULT;					// Wenn nFault Fehler meldet dann setze Pin1 des Error Registers auf 1 
		}
		
	
		if (error_reg !=  0)							//* Fehlererkennung
		{													// Wenn ein Fehler vorliegt dann rufe  das Error-Modul auf
			error_modul ();									// Wenn nicht dann gehe weiter
															// erstelllen bzw abändern
		}
		
	

	 	
		 if(PINA & (1<<PA4))						//* Steuerwahl
		{												// Wenn Umschalter auf High schaltet dann rufe das Remote-Modul auf
			remote_modul ();							// Wenn nicht dann gehe weiter				
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
