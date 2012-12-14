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
		
//ADC Pins
#define PIN_ADC			PINA
#define PORT_ADC		PORTA
#define DDR_ADC			DDRA
#define U_FUSE_ADC		(1<<PA7)
#define I_DRV_ADC		(1<<PA6)
#define	U_5V_ADC		(1<<PA5)
		
		
			
//Error codes		
#define ERR_0		0x01
#define ERR_NFAULT  0x02
#define ERR_2      	0x04
#define ERR_3      	0x08
#define ERR_4      	0x10
#define ERR_5      	0x20
#define ERR_6      	0x40
#define ERR_7      	0x80

#endif