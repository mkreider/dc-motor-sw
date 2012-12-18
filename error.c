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
	cli();																														// Global Interrupt Enable ausschalten
	WDT_reset();
	stop();																														// Motor Stop mit Fast decay aufrufen 
		
	if (error_reg & ERR_NFAULT)																									// UART Ausgabe bei Fehler auf NFAULT
	{
		uartputs("ERROR VIA NFAULT\n error1: OVERHEAT\n error2: VOLTAGE+/-\n OVER CURRENT\n");
	}
	
	if (error_reg & ERR_U_DRV_FUSE)																								// UART Ausgabe bei defekter Motorsicherung
	{
		uartputs("DRIVER-FUSE FAULT\n");
	}
	
	if (error_reg & ERR_I_DRV)																									// UART Ausgabe bei Überstrom
	{
		uartputs("DRIVER OVER CURRENT\n");
	}
	
	if (error_reg & ERR_U_24V)																									// UART Ausgabe bei Unterspannung (24V Seite) <= 19V
	{
		uartputs("BOARD UNDER VOLTAGE (<= 19V)\n");
	}
	
	if (error_reg & ERR_LIMITS)																									// UART Ausgabe bei 2 Endlagen gleichzeitig
	{
		uartputs("UNEXPECTED INPUT(ERROR 404 BRAIN NOT FOUND\n");
	}
	
	if (error_reg & ERR_ORDER)																									// UART Ausgabe bei Ablauf-Fehler
	{
		uartputs("WRONG INPUT ORDER\n");
	}
	
	if (error_reg & ERR_WATCHDOG)
	{
		uartputs("PROGRAMM TIMED OUT\n");
	}
	
	uartputs("TRY TO RESTART\n IF THE ERROR STILL EXCIST CALL SOMEONE HOW KNOWS WHAT HE DOES OKEY? IDIOT !! ");					// Endtext Error-Modul
	
	while (error_reg !=0)																										//ERROR_LED
	{
		WDT_reset();																											// Watchdog reset
		PORTD |= (1<<PD5);																										// Einschalten der Fehler LED			
		_delay_ms(500);																											// 500ms Verzögerung 
		PORTD &= ~(1<<PD5);																										// Ausschalten der Fehler LED
	}
	
	return;
}