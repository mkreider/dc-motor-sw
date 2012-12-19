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

ringbuffer rbUFuse;
ringbuffer rbU24;
ringbuffer rbIDrv;

extern uint8_t error_reg;
extern uint8_t pRBstart;
						
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
	
	
	//Output
	DDR_DRV				|= DRV_EN | DRV_MODE | DRV_PHASE | DRV_SLEEP;
	DDR_SIGNAL_A_OUT	|= SIGNAL_A_OUT;
	DDR_SIGNAL_B_OUT	|= SIGNAL_B_OUT;
	DDR_LIMIT_A_OUT		|= LIMIT_A_OUT;
	DDR_LIMIT_B_OUT		|= LIMIT_B_OUT;
	DDR_DIR_A_LED		|= DIR_A_LED;
	DDR_DIR_B_LED		|= DIR_B_LED;
	DDR_ERR_LED			|= DIR_ERR_LED;
														
	//Pullups
	PORT_LOC_RMT		|= LOC_RMT; 
	PORT_NFAULT			|= NFAULT;
	PORT_LIMIT_A		|= LIMIT_A;
	PORT_LIMIT_B		|= LIMIT_B;
	PORT_JMP_MOT_TYPE	|= JMP_MOT_TYPE;
	PORT_JMP_MOT_DIR	|= JMP_MOT_DIR;
	
	
	
	
	
	DDRB = 0b11011111;					
	DDRC = 0b00000000;
	DDRD = 0b11000111;
			
	MOTOR_BREAK;
	SET_DRV_SLEEP;								// setzen des Motortreibers in den Sleep Modus												// Pull-Ups???
					
	
    
		
						
	if (WDRF == 1)								//* Watchdog Flag Prüfung
		{
			error_reg |= ERR_WATCHDOG;					// Wenn ein Watchdog Reset vorlag dann setze Pin 6 des Error Registers auf 1
			MCUCSR = ~(1<<WDRF);						// Lösche das Flag wieder
		}
		
	init_uart();								//* Rufe UART init auf
	ADC_init ();								//* Rufe ADC init auf
	
	rbInit(&rbUFuse);							//Init ringbuffers for median
	rbInit(&rbU24);
	rbInit(&rbIDrv);
	
									
	//Interrupt_init();							//* Rufe Interrupt init auf
	//WDT_init ();								//* Rufe Watchdog Init auf
	
	
	
	return;		
}




int main(void)
{
	init();										//* Rufe init auf
	
	uartputs("PROGRAMM INITIALISIERT!!\n");
	uartputs("...\n");
	uartputs("...\n");
	uartputs("...\n");
	uartputs("Bereit...\n");
	
	
	
	
	//rbInsert(rbIDrv, ADC_Read(0));				<<<--- kommt in die Interrupt
	
	
	
    while(1)
    {				 	
		
		if (GET_NFAULT)								//* nFault Prüfung						
		{													
			error_reg |= ERR_NFAULT;					// Wenn nFault Fehler meldet dann setze Pin1 des Error Registers auf 1 
		}
		
	
		if (error_reg !=  0)							//* Fehlererkennung
		{													// Wenn ein Fehler vorliegt dann rufe  das Error-Modul auf
			error_modul ();									// Wenn nicht dann gehe weiter
															// erstelllen bzw abändern
		}
		
	 /*
		 uint16_t medDrv = median(&rbIDrv->mem);
		 uint16_t medDrv = median(&rbU24->mem);
		 uint16_t medDrv = median(rbUFuse->mem);
	*/	
		 
		 
		 if(PINA & (1<<PA4))						//* Steuerwahl
		{												// Wenn Umschalter auf High schaltet dann rufe das Remote-Modul auf
			remote_modul ();							// Wenn nicht dann gehe weiter				
		}		
		
		
		if (GET_LIMIT_A && GET_LIMIT_B)					//* Endschalter abfrage
		{												// Falls beide Endschalter gedrückt, dann führe Fehler verarbeitung aus.
			error_reg |= ERR_LIMITS;
			error_modul (); 
		}
		
										
		if (!(GET_LIMIT_A))
		{
			if (!(GET_LIMIT_B))							// Wenn nicht 0 --> LIMIT_B = 1, deswegen kann nur nach A gefahren werden.
			{
				if (GET_BUTTON_A)
				{
					// Fahre richtung A
					uartputs("Fahre Richtung A\r\n");
				}
				
				if (GET_BUTTON_B)
				{
					// Fahre richtung B
					uartputs("Fahre Richtung B\r\n");	
				}
			}
			if (GET_BUTTON_A)
				{
					// Fahre richtung A
					uartputs("Fahre Richtung A\r\n");
				}
			
		}
		
				
		
		if (GET_LIMIT_A && !(GET_LIMIT_B))
		{
				if (BUTTON_B == 1)
				{
					// Fahre richtung B
					uartputs("Fahre Richtung B\r\n");	
				}
				
				
						
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
