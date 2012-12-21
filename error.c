#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "Int.h"
#include "uart.h"
#include "Stop.h"
#include "error.h"


extern uint8_t error_reg;

void error_modul (void)
{
	cli();																														// Global Interrupt Enable off
	WDT_reset();
	Motor_stop();																												// Motor stop with fast decay 
		
	if (error_reg & ERR_NFAULT)																									// UART output at nFault error
	{
		uartputs("ERROR VIA NFAULT\n error1: OVERHEAT\n error2: VOLTAGE+/-\n OVER CURRENT\n");
	}
	
	if (error_reg & ERR_U_DRV_FUSE)																								// UART output by defective motor fuse
	{
		uartputs("DRIVER-FUSE FAULT\n");
	}
	
	if (error_reg & ERR_I_DRV)																									// UART output by over current
	{
		uartputs("DRIVER OVER CURRENT\n");
	}
	
	if (error_reg & ERR_U_24V)																									// UART output by under voltage (24V side) <= 19V
	{
		uartputs("BOARD UNDER VOLTAGE (<= 19V)\n");
	}
	
	if (error_reg & ERR_LIMITS)																									// UART output by both limits
	{
		uartputs("UNEXPECTED INPUT(ERROR 404 BRAIN NOT FOUND\n");
	}
	
	if (error_reg & ERR_ORDER)																									// UART output by input order
	{
		uartputs("WRONG INPUT ORDER\n");
	}
	
	if (error_reg & ERR_WATCHDOG)																								// UART output by overtime error
	{
		uartputs("PROGRAMM TIMED OUT\n");
	}
	
	uartputs("TRY TO RESTART\n IF THE ERROR STILL EXCIST CALL SOMEONE HOW KNOWS WHAT HE DOES!! ");								// Finishing text error modul
	
	while (error_reg !=0)																										// ERROR_LED
	{
		WDT_reset();																											// Watchdog reset
		PORTD |= (1<<PD5);																										// Error LED on			
		_delay_ms(500);																											// 500ms delay 
		PORTD &= ~(1<<PD5);																										// Error LED off
	}
	
	return;
}