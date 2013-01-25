/**
 * @file main.c
 *
 *
 * @brief Projekt DC Motorsteuerung
 */

/*
 *
 * Tim Herz 
 * Nadja Fischer
 * Philip Burkhard 
 * Burak Karadeniz 
 *
 * GSI Helmholtszzentrum für Schwerionenforschung GmbH
 * 64291 Darmstadt
 * Planckstraße 1
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
#include "remote.h"

						//* ToDo:
							

							//Spiegelung (Motorrichtung)
							//Motortyp (Stromgrenzen)
							//Entprellroutine
							//Remote
							//Kommentierung
							
							//Interrupts
							

							
							//	MOTOR_DIR & MOTOR_TYPE CHECK >>> ohne funktion >> Error: "IF WITHOUT EXPRESSION" 
		
		
/**
 * @brief Initialises IOs, Motor driver, watchdog, UART, filtered ADC
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
		
uint8_t Go_BA;		
	
	while(1)
    {				 	
		UPRINT("\f");										// Terminal form feed
		DBPRINT("\f");										// Terminal form feed
		
	
	 //error_median_check();
	 error_limits_check();
	 error_nfault_check();
	 
	 if (error_reg != 0)	error_modul ();					//* Fault detection			//Fehlererkennung
															// Call "error_modul" if an error occurs		//Wenn ein Fehler vorliegt dann rufe  das Error-Modul auf
											
		



			
		
		UPRINTN(lastLimit);													//give out the last pressed limit switch to the remote console
		UPRINT(" Lastlimit\r\n");
	
		
	
		if(GET_LIMIT_A) TURN_ON(PORT_LMT_A_LED, LMT_A_LED);					//check if  limit switch A is pressed and show it by LED on the front panel
		else			TURN_OFF(PORT_LMT_A_LED, LMT_A_LED);				//if limit switch A is not pressed, light off the limit LED for limit switch A
				
		if(GET_LIMIT_B) TURN_ON(PORT_LMT_B_LED, LMT_B_LED);					//check if  limit switch B is pressed and show it by LED on the front panel
		else			TURN_OFF(PORT_LMT_B_LED, LMT_B_LED);				//if limit switch B is not pressed, light off the limit LED for limit switch B
	
		if(GET_MOTOR_STOP)													//if the motor stop button is pressed... 
		{																	
			Go_BA = 0;												//... set Go_A=0 and Go_B=0, ...
			Motor_stop();													//... call the "motorstop()" routine...
			TURN_OFF(PORT_DIR_A_LED , DIR_A_LED );							//... and light off both direction LED's
			TURN_OFF(PORT_DIR_B_LED , DIR_B_LED );
		}
		else																//if the motor stop button is not press, than check different status of the A/B buttons and limit switches
		{
			Go_BA = remote_modul();
			UPRINT("go_BA ");
			UPRINTN(Go_BA);	
			UPRINT("\r\n");
				
			if (GET_LIMIT_A && !(GET_LIMIT_B))								//Limit switch A is pressed, Limit switch B is not pressed		//Endschalter A gedrueckt, Endschalter B nicht gedreuckt
			{
					DBPRINT("LA=1 LB=0\r\n");								//print out to the remote console which limit switch is pressed
				
					if (Go_BA == GO_TO_B)												//if button B is pressed... 
					{
						// Fahre richtung B
						Motor_RE();											//... call "Motor_RE" routine for driving the motor to B
					
					
						TURN_ON(PORT_DIR_B_LED , DIR_B_LED );				//turn on the LED for driving to B
						TURN_OFF(PORT_DIR_A_LED , DIR_A_LED );				//turn off the LED for driving A, if the motor was driving to A but not reached it before the driving direction was switched
					
						UPRINT("Fahre Richtung B\r\n");						//print out the driving direction int the remote console
					}
					if (Go_BA == GO_TO_A)												//if button A is pressed, call "Motor_stop", because the motor can't drive to A, if the limit switch A is pressed
					{
						Go_BA &= ~GO_TO_A;
						Motor_stop();
				
						TURN_OFF(PORT_DIR_A_LED , DIR_A_LED );				//light off both direction LED's
						TURN_OFF(PORT_DIR_B_LED , DIR_B_LED );
					
						UPRINT("\r\n Stop bei A\r\n");						//print out to the remote console that he motor stops/stand still	
					}
				
			}
		
			if (!(GET_LIMIT_A) && GET_LIMIT_B)								//limit switch B is pressed, but limit switch A is not pressed			//Endschalter B gedrueckt, Endschalter A nicht gedrueckt
			{						
					DBPRINT("LA=0 LB=1\r\n");								//print out which limit switch is pressed to the remote console 
			
					if (Go_BA == GO_TO_A)												//Fahre A
					{
						// Fahre richtung A
						Motor_FW();
					
										
						TURN_ON(PORT_DIR_A_LED , DIR_A_LED );
						TURN_OFF(PORT_DIR_B_LED , DIR_B_LED );
					
						UPRINT("Fahre Richtung A\r\n");	
					}
					if (Go_BA == GO_TO_B)								//Fahre B
					{
						Go_BA &= ~GO_TO_B;
						Motor_stop();
					
						TURN_OFF(PORT_DIR_A_LED , DIR_A_LED );
						TURN_OFF(PORT_DIR_B_LED , DIR_B_LED );
					
						UPRINT("\r\n Stop bei B\r\n");	
					}
			}
		
			if (!(GET_LIMIT_A) && !(GET_LIMIT_B))			//Kein Endschalter betaetigt
			{
					DBPRINT("LA=0 LB=0\r\n");
				
					if (Go_BA == GO_TO_A)
					{
						// Fahre richtung A
						Motor_FW();
						TURN_ON(PORT_DIR_A_LED , DIR_A_LED );
						TURN_OFF(PORT_DIR_B_LED , DIR_B_LED );
					
						UPRINT("Fahre Richtung A\r\n");
					}
					else if (Go_BA == GO_TO_B)
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
