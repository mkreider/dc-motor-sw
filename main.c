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

uint16_t medIDrv;
uint16_t medU24;
uint16_t medUFuse;
volatile uint8_t lastLimit;

						
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
	
	SET_PWR_LED;													
	MOTOR_BREAK;								//* Motor auf Bremse 
			
							
	if (WDRF == 1)								//* Watchdog Flag Prüfung
		{
			error_reg |= ERR_WATCHDOG;			// Wenn ein Watchdog Reset vorlag dann setze Pin 6 des Error Registers auf 1
			MCUCSR = ~(1<<WDRF);				// Lösche das Flag wieder
		}
		
	init_uart();								//* Rufe UART init auf
	ADC_init ();								//* Rufe ADC init auf
	
	pRbUFuse= &rbUFuse;
	pRbU24	= &rbU24;
	pRbIDrv = &rbIDrv;
	
	rbInit(pRbUFuse);							//* Init ringbuffers for median
	rbInit(pRbU24);
	rbInit(pRbIDrv);
								
	Interrupt_init();							//* Rufe Interrupt init auf
	//WDT_init ();								//* Rufe Watchdog Init auf
	
	
	
	return;		
}




int main(void)
{
	init();										//* Rufe init auf
	
	uint8_t Go_A;
	uint8_t Go_B;
	
	DBPRINT("PROGRAMM INITIALISIERUNG!!\n");				//  >>>> Delays einfügen um es realer darzustellen
	DBPRINT("...\n");										//	>>>> Oder entfernen. 
	DBPRINT("...\n");										//	>>>> Hat keinen Zweck. Dient nur der Optik !!
	DBPRINT("...\n");
	DBPRINT("Bereit...\n");
	 
	
	while(1)
    {				 	
		UPRINT("\f");
		
		
		if (GET_LIMIT_A && GET_LIMIT_B)						//* Endschalter abfrage
		{													//  Falls beide Endschalter gedrückt, dann führe Fehler verarbeitung aus.
			error_reg |= ERR_LIMITS;
			error_modul (); 
		}
		
		
		if (GET_NFAULT)										//* nFault Prüfung						
		{
			error_reg |= ERR_NFAULT;						// Wenn nFault Fehler meldet dann setze Pin1 des Error Registers auf 1 
		}
		
	
		if (error_reg != 0)									//* Fehlererkennung
		{													// Wenn ein Fehler vorliegt dann rufe  das Error-Modul auf
			error_modul ();									// Wenn nicht dann gehe weiter
															// erstelllen bzw abändern
		}
		
	     
		
		
		 
		 
// 		 if(PINA & (1<<PA4))						//* Steuerwahl
// 		{												// Wenn Umschalter auf High schaltet dann rufe das Remote-Modul auf
// 			remote_modul ();							// Wenn nicht dann gehe weiter				
// 		}		
		
		
		if(GET_REMOTE_SWITCH)
		{
			UPRINT("Modus: Remote\r\n");
			Go_A = GET_REMOTE_A;
			Go_B = GET_REMOTE_B;
			remote_modul ();
		}			
		else
		{
			UPRINT("Modus: Local\r\n");
			Go_A = GET_BUTTON_A;
			Go_B = GET_BUTTON_B;
				
		}
			
		DBPRINTN(Go_A);
		DBPRINT(" GoA\r\n");
		DBPRINTN(Go_B);
		DBPRINT(" GoB\r\n\r\n\r\n");
		UPRINTN(lastLimit);
		UPRINT(" Lastlimit\r\n");
	
			
		if (GET_LIMIT_A && !(GET_LIMIT_B))
		{
				DBPRINT("LA=1 LB=0\r\n");	
				if (Go_B)
				{
					// Fahre richtung B
					Motor_RE();
					UPRINT("Fahre Richtung B\r\n");	
				}
		}
		
		if (!(GET_LIMIT_A) && GET_LIMIT_B)
		{
				DBPRINT("LA=0 LB=1\r\n");
				if (Go_A)
				{
					// Fahre richtung A
					Motor_FW();
					UPRINT("Fahre Richtung A\r\n");	
				}
		}
		
		if (!(GET_LIMIT_A) && !(GET_LIMIT_B))
		{
				DBPRINT("LA=0 LB=0\r\n");
				if (Go_A)
				{
					// Fahre richtung A
					Motor_FW();
					UPRINT("Fahre Richtung A\r\n");
				}
				else if (Go_B)
				{
					// Fahre richtung B
					Motor_RE();
					UPRINT("Fahre Richtung B\r\n");
					
	
				}
		}
		
		
	     DBPRINT("\r\n\r\nMedian output:\r\n");
		 medIDrv	= median(&pRbIDrv->mem[0]);
		 medU24		= median(&pRbU24->mem[0]);
		 medUFuse	= median(&pRbUFuse->mem[0]);
		 DBPRINTN(medIDrv);
		 DBPRINT(" medIDrv \r\n");
		 DBPRINTN(medU24);
		 DBPRINT(" medU24 \r\n");
		 DBPRINTN(medUFuse);
		 DBPRINT(" medUFuse \r\n");
		
		
		
		 DBPRINT("\r\n\r\nMotor:\r\n");
		 DBPRINT("Typ\tStatus\t	Motorstatus\tSLEEP\tENABLE\tPHASE\tMODE\r\n");
		 
		 if(GET_JMP_MOT_TYPE)   DBPRINT("Typ A");
		 else					DBPRINT("Typ B");
		 
		 DBPRINT("\t");
		 		 
		 if			((PORT_DRV & ~DRV_EN) | (DRV_MODE))		DBPRINT("BRAKE"); // Motor BRAKE
		 else if	((PORT_DRV & ~DRV_SLEEP))				DBPRINT("SLEEP"); // Motor SLEEP
		 else if	((PORT_DRV &  DRV_SLEEP))				DBPRINT("ARMED"); // Motor ARMED
		 else		DBPRINT("Unknown"); // ?
		 
		 DBPRINT("\t");
		 DBPRINT("\t");
		 		 
		 if			(GET_JMP_MOT_DIR)						DBPRINT("Turn Right");
		 else if	(((PORT_DRV & ~DRV_EN) | (DRV_MODE)))	DBPRINT("STOP"); // Motor BRAKE
		 else												DBPRINT("Turn Left");
		 
		 DBPRINT("\t");
		 DBPRINT("\t");
		 
		 		 		 		 
		 if			(PORT_DRV & DRV_SLEEP)				DBPRINT ("1"); // Motor Sleep
		 else											DBPRINT ("0");
		 
		 DBPRINT("\t");
		 
		 if			(PORT_DRV & DRV_EN)					DBPRINT("1"); // Motor Enable
		 else											DBPRINT("0");
		 
		 DBPRINT("\t");
		 
		 if			(PORT_DRV & DRV_PHASE)				DBPRINT("1"); // Motor Phase
		 else											DBPRINT("0");
		 
		 DBPRINT("\t");
		 
		 if			(PORT_DRV & DRV_MODE)				DBPRINT("1"); // Motor Mode
		 else											DBPRINT("0");
		 
		DBPRINT("\r\n");
				
		
				
		_delay_ms(1000);
    }    
        
	
		
}
