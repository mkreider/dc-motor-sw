/*
 * Projekt DC Motorsteuerung
 *
 * Herz Tim
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
 * Last edited on: 22.01.2013
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/wdt.h>
#include "defines.h"
#include "adc.h"
#include "median.h"
#include "uart.h"
#include "int.h"
#include "error.h"
#include "remote.h"
#include "Motor.h"

						
						//* ToDo:
							

							//Spiegelung (Motorrichtung)
							//Motortyp
							//Interrupts
							//Entprellroutine
							//Remote
					
							//Kommentierung
							
							
							//  Power-Up Timer im Init nötig?		
							//  EXT. QUARZ einstellen
							
							//	MOTOR_DIR & MOTOR_TYPE CHECK >>> ohne funktion >> Error: "IF WITHOUT EXPRESSION" 
		
		
/**		
  *	
  */
void init(void)		//! Initialisation for Ports, Uart, ADC, IRQ and Watchdog	
{			
													//* Einfügen der benötigten Konstanten und Variablen
	error_reg = 0x00;								// Error Register zur Fehlererkennung							
	
	
	//Output										//defining the Outputs
	DDR_DRV				|= DRV_EN | DRV_MODE | DRV_PHASE | DRV_SLEEP;
	DDR_LIMIT_A_OUT		|= LIMIT_A_OUT;
	DDR_LIMIT_B_OUT		|= LIMIT_B_OUT;
	DDR_DIR_A_LED		|= DIR_A_LED;
	DDR_DIR_B_LED		|= DIR_B_LED;
	DDR_ERR_LED			|= DIR_ERR_LED;
	DDR_PWR_LED			|= PWR_LED;
	
	
	SET_PWR_LED;													
	MOTOR_BREAK;								//* Engine on brake
			
							
	if (MCUCSR & (1<<WDRF))						//* Checking the watchdog-flag
	{
		error_reg |= ERR_WATCHDOG;				// If a watchdog reset occurs, set the bit 6 of the error register high	
				MCUCSR = ~(1<<WDRF);			// Delete the watchdog flag			
	}
		
	
	init_uart();								// Call the UART init		//Rufe UART init auf
	ADC_init ();								// Call the ADC init		//Rufe ADC init auf
	
	pRbUFuse= &rbUFuse;
	pRbU24	= &rbU24;
	pRbIDrv = &rbIDrv;
	
	rbInit(pRbUFuse);							// Init ring buffers for median
	rbInit(pRbU24);
	rbInit(pRbIDrv);
								
	Interrupt_init();							// Call Interrupt init		//Rufe Interrupt init auf
	WDT_init ();								// Call watchdog init		//Rufe Watchdog Init auf
	
	return;		
}

int main(void)
{
	init();													//* Call init		//Rufe init auf
		
	uint8_t Go_A=0;											//! Drive Command memory for direction A
	uint8_t Go_B=0;											//! Drive Command memory for direction B
	uint8_t key;											//! Char code from keyboard, currently used for remote ctrl
	
	while(1)
    {				 	
		UPRINT("\f");										// Terminal form feed
		DBPRINT("\f");										// Terminal form feed
		
	
	 //error_median_check();
	 error_limits_check();
	 error_nfault_check();
	 
	 if (error_reg != 0)	error_modul ();					//* Fault detection			//Fehlererkennung
															// Call "error_modul" if an error occurs		//Wenn ein Fehler vorliegt dann rufe  das Error-Modul auf
											
		


		if(GET_REMOTE_SWITCH)								//If the remote switch is set (PA4) the move direction can be remote controlled by pressing a or b...
		{													//... on the keyboard of the PC which is connected through the UART with the motor control board
			UPRINT("Modus: Remote\r\n");
			key = uart_getc_nowait();						//defining "key" with a key-input through the uart
			UPRINT("Key: ");								//print out a probably pressed key on the remote console
			UPRINTN(key);
			UPRINT("\r\n");
			
			if(key == 'a')									//If key "a" was pressed during remote mode, set Go_a=1 and Go_B=0
			{
				Go_A = 1;
				Go_B = 0;	
			}
			
			else if(key == 'b')								//If key "b" was pressed during remote mode, set Go_a=0 and Go_B=1
			{
				Go_A = 0;
				Go_B = 1;	
			}
			
			
			
			remote_modul ();								//unnecessary in the current version
		}	
				
		else												//If the remote mode is deactivated, the direction buttons must be pressed direct at the front panel
		{
			UPRINT("Modus: Local\r\n\r\n");
			
			if(GET_BUTTON_A && GET_BUTTON_B) {Go_A = 0; Go_B = 0;}			//if both direction buttons are pressed simultaneously, Go_A and GO_B are 0, the motor stands still
			if(GET_BUTTON_A) {Go_A = 1; Go_B = 0;}							//if switch A is pressed, set Go_a=1 and Go_B=0 for driving the motor to A
			if(GET_BUTTON_B) {Go_A = 0; Go_B = 1;}							//if switch A is pressed, set Go_a=1 and Go_B=0 for driving the motor to B
					 
				 	
		}
			
		
		UPRINTN(lastLimit);													//give out the last pressed limit switch to the remote console
		UPRINT(" Lastlimit\r\n");
	
		
	
		if(GET_LIMIT_A) TURN_ON(PORT_LMT_A_LED, LMT_A_LED);					//check if  limit switch A is pressed and show it by LED on the front panel
		else			TURN_OFF(PORT_LMT_A_LED, LMT_A_LED);				//if limit switch A is not pressed, light off the limit LED for limit switch A
				
		if(GET_LIMIT_B) TURN_ON(PORT_LMT_B_LED, LMT_B_LED);					//check if  limit switch B is pressed and show it by LED on the front panel
		else			TURN_OFF(PORT_LMT_B_LED, LMT_B_LED);				//if limit switch B is not pressed, light off the limit LED for limit switch B
	
		if(GET_MOTOR_STOP)													//if the motor stop button is pressed... 
		{																	
			Go_A = 0; Go_B = 0;												//... set Go_A=0 and Go_B=0, ...
			Motor_stop();													//... call the "motorstop()" routine...
			TURN_OFF(PORT_DIR_A_LED , DIR_A_LED );							//... and light off both direction LED's
			TURN_OFF(PORT_DIR_B_LED , DIR_B_LED );
		}
		else																//if the motor stop button is not press, than check different status of the A/B buttons and limit switches
		{
			
					
			if (GET_LIMIT_A && !(GET_LIMIT_B))								//Limit switch A is pressed, Limit switch B is not pressed		//Endschalter A gedrueckt, Endschalter B nicht gedreuckt
			{
					DBPRINT("LA=1 LB=0\r\n");								//print out to the remote console which limit switch is pressed
				
					if (Go_B)												//if button B is pressed... 
					{
						// Fahre richtung B
						Motor_RE();											//... call "Motor_RE" routine for driving the motor to B
					
					
						TURN_ON(PORT_DIR_B_LED , DIR_B_LED );				//turn on the LED for driving to B
						TURN_OFF(PORT_DIR_A_LED , DIR_A_LED );				//turn off the LED for driving A, if the motor was driving to A but not reached it before the driving direction was switched
					
						UPRINT("Fahre Richtung B\r\n");						//print out the driving direction int the remote console
					}
					if (Go_A)												//if button A is pressed, call "Motor_stop", because the motor can't drive to A, if the limit switch A is pressed
					{
						Go_A = 0;
						Motor_stop();
				
						TURN_OFF(PORT_DIR_A_LED , DIR_A_LED );				//light off both direction LED's
						TURN_OFF(PORT_DIR_B_LED , DIR_B_LED );
					
						UPRINT("\r\n Stop bei A\r\n");						//print out to the remote console that he motor stops/stand still	
					}
				
			}
		
			if (!(GET_LIMIT_A) && GET_LIMIT_B)								//limit switch B is pressed, but limit switch A is not pressed			//Endschalter B gedrueckt, Endschalter A nicht gedrueckt
			{						
					DBPRINT("LA=0 LB=1\r\n");								//print out which limit switch is pressed to the remote console 
			
					if (Go_A)												//Fahre A
					{
						// Fahre richtung A
						Motor_FW();
					
										
						TURN_ON(PORT_DIR_A_LED , DIR_A_LED );
						TURN_OFF(PORT_DIR_B_LED , DIR_B_LED );
					
						UPRINT("Fahre Richtung A\r\n");	
					}
					if (Go_B)								//Fahre B
					{
						Go_B = 0;
						Motor_stop();
					
						TURN_OFF(PORT_DIR_A_LED , DIR_A_LED );
						TURN_OFF(PORT_DIR_B_LED , DIR_B_LED );
					
						UPRINT("\r\n Stop bei B\r\n");	
					}
			}
		
			if (!(GET_LIMIT_A) && !(GET_LIMIT_B))			//Kein Endschalter betaetigt
			{
					DBPRINT("LA=0 LB=0\r\n");
				
					if (Go_A)
					{
						// Fahre richtung A
						Motor_FW();
						TURN_ON(PORT_DIR_A_LED , DIR_A_LED );
						TURN_OFF(PORT_DIR_B_LED , DIR_B_LED );
					
						UPRINT("Fahre Richtung A\r\n");
					}
					else if (Go_B)
					{
						// Fahre richtung B
						Motor_RE();
						TURN_ON(PORT_DIR_B_LED , DIR_B_LED );
						TURN_OFF(PORT_DIR_A_LED , DIR_A_LED );
					
					
						UPRINT("Fahre Richtung B\r\n");
					
	
					}
			}
		}		
		

		 medIDrv	= median(&pRbIDrv->mem[0]);
		 medU24		= median(&pRbU24->mem[0]);
		 medUFuse	= median(&pRbUFuse->mem[0]);
	     DBPRINT("\r\n\r\nMedian output:\r\n");		 
		 DBPRINTN((medIDrv*24)/20);
		 DBPRINT("\t mA medIDrv \r\n");
		 DBPRINTN(medU24*24);
		 DBPRINT("\t mV medU24 \r\n");
		 DBPRINTN(medUFuse*24);
		 DBPRINT("\t mV medUFuse \r\n");
		
		
		
		 DBPRINT("\r\n\r\nMotor:\r\n");
		 DBPRINT("Typ\tStatus\tMotorDirection\tSLEEP\tENABLE\tPHASE\tMODE\r\n");
		 
		 MOTOR_TYPE();
		 
		 DBPRINT("\t");
		 		 
		 if			( (PORT_DRV & ~DRV_EN) && (PORT_DRV & DRV_MODE) )		DBPRINT("BRAKE"); // Motor BRAKE
		 else if	(!(PORT_DRV & DRV_SLEEP))				DBPRINT("SLEEP"); // Motor SLEEP
		 else if	((PORT_DRV & DRV_SLEEP))				DBPRINT("ARMED"); // Motor ARMED
		 else		DBPRINT("Unknown"); // ?
		 
		 DBPRINT("\t");
		 		 
		 MOTOR_DIR();
		 
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
		
		wdt_reset();	
		
				
		_delay_ms(222);
    }    
        
	
		
}
