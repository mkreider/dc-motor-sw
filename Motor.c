/**
 * @file motor.c
 *
 *
 * @brief Control functions for the <Chip type> motor driver
 */

/*
 * Copyright (c) YYYY Author.
 *
 */

#include <avr/io.h>
#include "defines.h"
#include "Motor.h"

void Motor_stop(void)									//! motor stop function
{
	SET_DRV_SLEEP;										//! set the Driver into sleep mode
	MOTOR_BREAK;										//! Motor Driver on break --> Sleep have to be activated for fast decay mode	
	TURN_OFF(PORT_DIR_A_LED , DIR_A_LED );				//! turn off direction LED A
	TURN_OFF(PORT_DIR_B_LED , DIR_B_LED );				//! turn off direction LED B
	return;
}

void Motor_FW(void)										//! motor forward function
{
	SET_DRV_ARM;										//! set the Driver to status armed
	SET_GO_A;											//! motor drives to A
	return;
}

void Motor_RE(void)										//! motor reverse function
{
	SET_DRV_ARM;										//! set the Driver to status armed
	SET_GO_B;											//! motor drives to B	
	return;
}

void MOTOR_DIR (void)									//! check which motor rotation direction is in use
{
	if(GET_JMP_MOT_DIR)									//! check if motor dir bit is set		
	{
		DBPRINT("Turn Right");
	}
	 else
	 {
		DBPRINT("Turn Left");
	 }		
	return;
}

void MOTOR_TYPE(void)									//! check which motor type is connected
{
	if(GET_JMP_MOT_TYPE)								//! check if motor dir bit is set
	{
		DBPRINT("Typ A");
		//MOTOR_TYPE_CHECK = 1;
	}
		 
	else
	{
		DBPRINT("Typ B");
		//MOTOR_TYPE_CHECK = 0;
	}	
	return;
}
