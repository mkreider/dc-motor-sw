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
	SET_DRV_SLEEP;								// set the Driver into sleep mode
	MOTOR_BREAK;								// Motor Driver on break --> Sleep have to be activated for fast decay mode	
	return;
}