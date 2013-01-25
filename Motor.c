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

void Motor_stop(void)
{

	SET_DRV_SLEEP;								// set the Driver into sleep mode
	MOTOR_BREAK;								// Motor Driver on break --> Sleep have to be activated for fast decay mode	
	TURN_OFF(PORT_DIR_A_LED , DIR_A_LED );
	TURN_OFF(PORT_DIR_B_LED , DIR_B_LED );
	return;
}

void Motor_FW(void)
{
	
	SET_DRV_ARM;								// set the Driver into sleep mode
	SET_GO_A;
																											// Error LED on			
							// Motor Driver on break --> Sleep have to be activated for fast decay mode	
	return;
}

void Motor_RE(void)
{
	SET_DRV_ARM;								// set the Driver into sleep mode
	SET_GO_B;
									// Motor Driver on break --> Sleep have to be activated for fast decay mode	
	return;
}

void MOTOR_DIR (void)
{
	if(GET_JMP_MOT_DIR)		
	{
		DBPRINT("Turn Right");
		//MOTOR_DIR_CHECK = 1;
	}
	 else
	 {
		DBPRINT("Turn Left");
		//MOTOR_DIR_CHECK = 0;
	 }		
	return;
}

void MOTOR_TYPE(void)
{
	if(GET_JMP_MOT_TYPE)   
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
