#include <avr/io.h>
#include "remote.h"
#include "defines.h"
#include "uart.h"

#include <util/delay.h>
#include <avr/wdt.h>



uint8_t remote_modul (void)
{
			uint8_t Go_A=0;
			uint8_t Go_B=0;
			
			
			
			UPRINT("Modus: ");
			if(GET_REMOTE_SWITCH)
			{
				UPRINT("Remote");
				/*
				
				if(GET_BUTTON_A_RMT && GET_BUTTON_B_RMT) {Go_A = 0; Go_B = 0;}			//if both direction buttons are pressed simultaneously, Go_A and GO_B are 0, the motor stands still
				else
				{
					if(GET_BUTTON_A_RMT) {Go_A = 1; Go_B = 0;}							//if switch A is pressed, set Go_a=1 and Go_B=0 for driving the motor to A
					if(GET_BUTTON_B_RMT) {Go_A = 0; Go_B = 2;}
				}
				*/					
			}						
			else
			{
				UPRINT("Local"); 
			
			UPRINT("Button_A\tButton_B\r\n");
			UPRINTN(GET_BUTTON_A); UPRINT("\t"); UPRINTN(GET_BUTTON_B); UPRINT("\r\n");
			
			Go_A = (GET_BUTTON_A>>2);
			Go_B = GET_BUTTON_B;
			 /*

				if(GET_BUTTON_A) {Go_A = 1; Go_B = 0;}							//if switch A is pressed, set Go_a=1 and Go_B=0 for driving the motor to A
				if(GET_BUTTON_B) {Go_A = 0; Go_B = 2;}
				if(GET_BUTTON_A && GET_BUTTON_B) {Go_A = 0; Go_B = 0;}			//if both direction buttons are pressed simultaneously, Go_A and GO_B are 0, the motor stands still
				*/
										
			}
			UPRINT("\r\n\r\n");
			
			return (Go_B | Go_A);
						
}