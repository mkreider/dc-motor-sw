/*
 * Projekt DC Motorsteuerung
 *
 * Projektleiter: Herz Tim
 * Nadja Fischer
 * Burkhard Philip 
 * Karadeniz Burak
 *
 * GSI Helmholtszzentrum f�r Schwerionenforschung GmbH
 * 64291 Darmstadt
 * Planckstra�e 1
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

ringbuffer rbUFuse;
ringbuffer rbU24;
ringbuffer rbIDrv;

extern uint8_t error_reg;
extern uint8_t pRBstart;
						
						//* Notizen:
							
							//* Software
							
							//  Power-Up Timer im Init n�tig?
							//  Jedes Interrupt routinen mit Abfrage zu nFault beenden.
							// 	Fehlermeldung �ber UART/Blinkende Gelbe LED				
							//	"Motorerkennung" �berarbeiten
							//	Mit defines arbeiten 
							//  "Richtung" (siehe Schaltplan) einpflegen
							//	Abfrage des Watchdog flags - gab es einen Watchdog reset? wenn ja -> error
							//  EXT. QUARZ einstellen
							
							//* Hardware
							
							//	Layout �ndern --> RGB LED tauschen (LED gb)
							//	 
		
		
		
		
		
void init(void)			
{			
												//* Einf�gen der ben�tigten Konstanten und Variablen
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
		
						
	if (WDRF ==1)								//* Watchdog Flag Pr�fung
		{
			error_reg |= ERR_WATCHDOG;					// Wenn ein Watchdog Reset vorlag dann setze Pin 6 des Error Registers auf 1
			MCUCSR = ~(1<<WDRF);						// L�sche das Flag wieder
		}
		
	init_uart();								//* Rufe UART init auf
	ADC_init ();								//* Rufe ADC init auf
	
	rbInit(rbUFuse);							//Init ringbuffers for median
	rbInit(rbU24);
	rbInit(rbIDrv);
	
									
	Interrupt_init();							//* Rufe Interrupt init auf
	WDT_init ();								//* Rufe Watchdog Init auf
	
	
	
	return;		
}




int main(void)
{
	init();										//* Rufe init auf
	uartputc("PROGRAMM INITIALISIERT!!\n");
	uartputc("...\n");
	uartputc("...\n");
	uartputc("...\n");
	uartputc(" Ich bin Breit...\n");
	
	
	
	
	
	//rbInsert(rbIDrv, ADC_Read(0));
	
	//uint16_t medDrv = median(rbIDrv->mem);
	
    while(1)
    {				 	
		
		if (GET_NFAULT)								//* nFault Pr�fung						
		{													
			error_reg |= ERR_NFAULT;					// Wenn nFault Fehler meldet dann setze Pin1 des Error Registers auf 1 
		}
		
	
		if (error_reg !=  0)							//* Fehlererkennung
		{													// Wenn ein Fehler vorliegt dann rufe  das Error-Modul auf
			error_modul ();									// Wenn nicht dann gehe weiter
															// erstelllen bzw ab�ndern
		}
		
	 	
		 median ();
		  
		 
		 if(PINA & (1<<PA4))						//* Steuerwahl
		{												// Wenn Umschalter auf High schaltet dann rufe das Remote-Modul auf
			remote_modul ();							// Wenn nicht dann gehe weiter				
		}		
		
		
		if (LIMIT_A & LIMIT_B == 1)					//* Endschalter abfrage
		{												// Falls beide Endschalter gedr�ckt, dann f�hre Fehler verarbeitung aus.
			error_reg |= ERR_LIMITS;
			error_modul (); 
		}
		
										
		if (LIMIT_A == 0)
		{
			if (LIMIT_B == 0)							// Wenn nicht 0 --> LIMIT_B = 1, deswegen kann nur nach A gefahren werden.
			{
				if (BUTTON_A == 1)
				{
					// Fahre richtung A
				}
				
				if (BUTTON_B == 1)
				{
					// Fahre richtung B
				}
			}
			if (BUTTON_A == 1)
				{
					// Fahre richtung A
				}
			
		}
		
				
		
		if (LIMIT_A == 1)
		{
			if (LIMIT_B == 0)
			{
				if (BUTTON_B == 1)
				{
					// Fahre richtung B
				}
				
				
			}			
		}
		
    }    
        
		
		
}
    






// 
// // char text() = "Achtung Ueberstrom";
// 
// void output (const char* text())				//nicht ver�nderbar wegen char das * ist zum anzeigen das es ein pointer ist
// {
// 	while (*text!=0x00)							//soll aufh�ren wenn es 0x00 erreicht hat
// 	{
// 		uartputc (*(text++));		// damit alles angezeigt werden soll ++ 
// 	}
// }
