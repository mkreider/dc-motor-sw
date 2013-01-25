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
	if(measrdy > 4)									//! if measrdy greater/bigger/taller/higher/larger then 4 do ... 
		{
			if(medU24 < THRES_UNDERVOLTAGE)			//! if voltage is under 19V then do... 			
			{
				CLR_PWR_LED;						//! Set Power LED off
				error_reg |= ERR_U_24V;				//! Set bit 4 of the error register
				error_modul ();						//! Call error module and Run an error process	
			}
		}
		
	if (GET_JMP_MOT_TYPE)							//! Check which motor type is already in use
	{
			if (medIDrv > 5000)						//! if current is over .... then do...
			{
				error_reg |= ERR_I_DRV;				//! Set bit 3 of the error register
				error_modul();						//! Call error module and Run an error process
			}
			
	}
	if (~GET_JMP_MOT_TYPE)
	{
		if (medIDrv > 5000)							//! if current is over .... then do...
			{
				error_reg |= ERR_I_DRV;				//! Set bit 3 of the error register
				error_modul();						//! Call error module and Run an error process
			}
	}
		
		
		return;
}


void error_limits_check (void) 
{
	if (GET_LIMIT_A && GET_LIMIT_B)					//! Check limit switches		
		{											 		
		error_reg |= ERR_LIMITS;					//!	Set bit 5 of the error register
		error_modul ();								//! Call error module and Run an error process
		}			
}

void error_nfault_check (void)
{
	 if (GET_NFAULT)								//! Check nFAULT from the motor driver								
 	{
 		error_reg |= ERR_NFAULT;					//! Set bit 1 of the error register if a nFault error occurs
	}
}

void error_modul (void)
{
	cli();																														//! Global Interrupt Enable off
	wdt_reset();																												//! Watchdog Reset
	Motor_stop();																												//! Motor stop  
		
	if (error_reg & ERR_NFAULT)																									//! UART output at nFault error
	{
		uartputs("ERROR VIA NFAULT\r\n error1: OVERHEAT\r\n error2: VOLTAGE+/-\r\n error3: OVER CURRENT\r\n");
	}
	
	if (error_reg & ERR_U_DRV_FUSE)																								//! UART output by defective motor fuse
	{
		uartputs("DRIVER-FUSE FAULT\r\n");
	}
	
	if (error_reg & ERR_I_DRV)																									//! UART output by over current
	{
		uartputs("DRIVER OVER CURRENT\r\n");
	}
	
	if (error_reg & ERR_U_24V)																									//! UART output by under voltage (24V side) <= 19V
	{
		uartputs("BOARD UNDER VOLTAGE (<= 19V)\r\n");
		uartputs("TRY TO RESTART\n IF THE ERROR STILL PERSISTS CALL SUPPORT! ");
		while(1)																												//! loop
		{
		wdt_reset();	
		PORTD |= ((1<<PD5) | (1<<PD6));																							//! Power LED & Error LED on			
		_delay_ms(500);																											//! 500ms delay
		wdt_reset();																											//! Watchdog Reset 
		PORTD &= ~((1<<PD5) | (1<<PD6));																						//! Power LED & Error LED off
		_delay_ms(500);																											//! 500ms delay
		}
	}
	
	if (error_reg & ERR_LIMITS)																									//! UART output by both limits
	{
		uartputs("BOTH LIMIT SWITCHES PRESSED! BROKEN SWITCH?\r\n");
	}
	
	if (error_reg & ERR_ORDER)																									//! UART output by input order
	{
		uartputs("WRONG INPUT ORDER\r\n");
	}
	
	if (error_reg & ERR_WATCHDOG)																								//! UART output by overtime error
	{
		uartputs("PROGRAMM TIMED OUT\r\n");
	}
	
	uartputs("TRY TO RESTART\n IF THE ERROR STILL PERSISTS CALL SUPPORT! ");													//! Finishing text of error output
		
	while (error_reg !=0)																										//! While Error Reg unequal 0 do ... 
	{
		wdt_reset();																											//! Watchdog reset
		PORTD |= (1<<PD5);																										//! Error LED on			
		_delay_ms(500);																											//! 500ms delay
		wdt_reset();																											//! Watchdog Reset 
		PORTD &= ~(1<<PD5);																										//! Error LED off
		_delay_ms(500);
	}
	
	
}