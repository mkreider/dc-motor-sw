/*
 * Stop.c
 *
 * Created: 17.12.2012 10:19:25
 *  Author: Tim Herz / Burak Karadeniz
 */ 
#include <avr/io.h>
#include "defines.h"
#include "stop.h"

void Motor_stop (void)
{
	SET_DRV_SLEEP;								// setzen des Motortreibers in den Sleep Modus
	MOTOR_BREAK;								// Motor-Treiber auf Brake --> Um fast decay bei DRV8800 zu verwenden, muss Sleep Aktiviert sein.	
	return;
}