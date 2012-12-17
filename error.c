#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include "defines.h"
#include "Int.h"
// Interrupts deaktivieren 
// Schleife bis reset
// LED Blinken / UART ausgabe --> Error

void error_modul (void)
{
	cli();
	
	STOP();				// Motor Stop mit Fast decay aufrufen 
		
	if (error_reg = ERR_NFAULT)
	{
		uartputs("ERROR VIA NFAULT\n error1: OVERHEAT\n error2: VOLTAGE+/-\n OVER CURRENT\n"); break;
	}
	
	if (error_reg = ERR_U_DRV_FUSE)
	{
		uartputs("DRIVER-FUSE FAULT\n"); break;
	}
	
	if (error_reg = ERR_I_DRV)
	{
		uartputs("DRIVER OVER CURRENT\n"); break;
	}
	
	if (error_reg = ERR_U_24V)
	{
		uartputs("BOARD UNDER VOLTAGE (<= 19V)\n"); break;
	}
	
	if (error_reg = ERR_LIMITS)
	{
		uartputs("UNEXPECTED INPUT(ERROR 404 BRAIN NOT FOUND\n"); break;
	}
	
	if (error_reg = ERR_ORDER)
	{
		uartputs("WRONG INPUT ORDER\n"); break;
	}
	
	uartputs("TRY TO RESTART\n IF THE ERROR STILL EXCIST CALL SOMEONE HOW KNOWS WHAT HE DOES OKEY? IDIOT !! "); break;
	
	while (error_reg !=0)																										//ERROR_LED
	{
		WDT_reset ();
		PORTD (1<<PD5);
		_delay_ms(490);																											// 
		PORTD (0<<PD5);
	}
	
	return;
}