/**
 * @file error.c
 *
 *
 * @brief Error handling: limit switches, overcurrent, undervoltage, driver errors, watchdog 
 */

/*
 * Copyright (c) YYYY Author.
 *
 */
﻿

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include "defines.h"
#include "Int.h"
#include "uart.h"
#include "Motor.h"
#include "error.h"
#include "median.h"



void error_median_check (void)
{
	if(measrdy > 4)									// if(OVT <= OVR) 
		{
			if(medU24 < THRES_UNDERVOLTAGE)
			{
				CLR_PWR_LED;
				error_reg |= ERR_U_24V;
				error_modul ();
			}
		}
		
		return;
}


void error_limits_check (void) 
{
	if (GET_LIMIT_A && GET_LIMIT_B)				//! Check limit switches		//Endschalter abfrage
		{											//  Run an error process if both limit switches are pressed			//Falls beide Endschalter gedrückt, dann führe Fehler verarbeitung aus.
		error_reg |= ERR_LIMITS;
		error_modul (); 
		}			
}

void error_nfault_check (void)
{
	 if (GET_NFAULT)							//* Check nFAULT form the motor driver		//nFault Prüfung						
 	{
 		error_reg |= ERR_NFAULT;				// Set bit1 of the error register if a nFault error occurs		 //Wenn nFault Fehler meldet dann setze Pin1 des Error Registers auf 1 
 	}
}


void error_modul (void)
{
	cli();																														// Global Interrupt Enable off
	wdt_reset();
	Motor_stop();																												// Motor stop with fast decay 
		
	if (error_reg & ERR_NFAULT)																									// UART output at nFault error
	{
		uartputs("ERROR VIA NFAULT\r\n error1: OVERHEAT\r\n error2: VOLTAGE+/-\r\n error3: OVER CURRENT\r\n");
	}
	
	if (error_reg & ERR_U_DRV_FUSE)																								// UART output by defective motor fuse
	{
		uartputs("DRIVER-FUSE FAULT\r\n");
	}
	
	if (error_reg & ERR_I_DRV)																									// UART output by over current
	{
		uartputs("DRIVER OVER CURRENT\r\n");
	}
	
	if (error_reg & ERR_U_24V)																									// UART output by under voltage (24V side) <= 19V
	{
		uartputs("BOARD UNDER VOLTAGE (<= 19V)\r\n");
		uartputs("TRY TO RESTART\n IF THE ERROR STILL PERSISTS CALL SUPPORT! ");
		while(1)
		{
		wdt_reset();	
		PORTD |= ((1<<PD5) | (1<<PD6));																										// Error LED on			
		_delay_ms(500);
		wdt_reset();																											// 500ms delay 
		PORTD &= ~((1<<PD5) | (1<<PD6));																										// Error LED off
		_delay_ms(500);
		}
	}
	
	if (error_reg & ERR_LIMITS)																									// UART output by both limits
	{
		uartputs("BOTH LIMIT SWITCHES PRESSED! BROKEN SWITCH?\r\n");
	}
	
	if (error_reg & ERR_ORDER)																									// UART output by input order
	{
		uartputs("WRONG INPUT ORDER\r\n");
	}
	
	if (error_reg & ERR_WATCHDOG)																								// UART output by overtime error
	{
		uartputs("PROGRAMM TIMED OUT\r\n");
	}
	
	uartputs("TRY TO RESTART\n IF THE ERROR STILL PERSISTS CALL SUPPORT! ");													// Finishing text error modul
	
	while (error_reg !=0)																										// ERROR_LED
	{
		wdt_reset();																											// Watchdog reset
		PORTD |= (1<<PD5);																										// Error LED on			
		_delay_ms(500);
		wdt_reset();																											// 500ms delay 
		PORTD &= ~(1<<PD5);																										// Error LED off
		_delay_ms(500);
	}
	
	
}
