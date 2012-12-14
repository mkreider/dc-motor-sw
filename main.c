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
#include "defines.h"
#include "adc.h"
#include "median.h"
#include "uart.h"
#include "int.h"
#include "error.h"
#include "remote.h"




	
						
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
	
	//TODO
	//Abfrage des Watchdog flags - gab es einen Watchdog reset? wenn ja -> error
	
	
	
	//* Inputs / Outputs	
	DDR_ADC = U_FUSE_ADC | I_DRV_ADC | U_5V_ADC;						
	DDRB = 0b11011111;					
	DDRC = 0b00000000;
	DDRD = 0b11000111;		
	
	// Pull-Ups???
	PORT_ADC = 0;
	PORTC = NFAULT;						
	
	
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
