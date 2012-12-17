#ifndef _DEFINES_H_
#define _DEFINES_H_

//Makros/defines werden im allgemeinen komplett grossgeschrieben,
//macht die unterscheidung von variablen einfacher. 

//die koennen mehr als nur Pins einen Namen geben:

//#define  SleepDriver PB5

//Motor Driver nfault pin
#define PIN_NFAULT   	PINC
#define PORT_NFAULT  	PORTC
#define DDR_NFAULT   	DDRC
#define NFAULT       	(1<<PC7)

#define GET_NFAULT   	PIN_NFAULT & NFAULT

//Motor driver sleep
#define PIN_DRV_SLEEP	PINB
#define PORT_DRV_SLEEP	PORTB
#define DDR_DRV_SLEEP 	DDRB
#define DRV_SLEEP 		(1<<PB5)

#define SET_DRV_SLEEP 	PORT_DRV_SLEEP |=  DRV_SLEEP
#define SET_DRV_ARM  	PORT_DRV_SLEEP &= ~DRV_SLEEP	
		
//PORTA Pins
#define PIN_ADC			PINA
#define U_FUSE_ADC		(1<<PA7)
#define I_DRV_ADC		(1<<PA6)
#define	U_24V_ADC		(1<<PA5)
#define LOC_RMT			(1<<PA4)

//* BRAKE
//PORTB = (0<<PB7)|(1<<PB4);					// Motor-Treiber auf Brake 

		
			
//*	Error codes								// LSB
#define ERR_NFAULT		0x01				// BIT 1
#define ERR_U_DRV_FUSE	0x02				// BIT 2
#define ERR_I_DRV 		0x04				// BIT 3
#define ERR_U_24V		0x08				// BIT 4
#define ERR_LIMITS 		0x10				// BIT 5
#define ERR_ORDER		0x20				// BIT 6
#define ERR_6      		0x40				// BIT 7
#define ERR_7      		0x80				// BIT 8
											// MSB
											
uint8_t error_reg;							// Error Register zur Fehlererkennung												
											
#endif