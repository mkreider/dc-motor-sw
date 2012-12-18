#ifndef _DEFINES_H_
#define _DEFINES_H_

//Makros/defines werden im allgemeinen komplett grossgeschrieben,
//macht die unterscheidung von variablen einfacher. 




//Motor driver sleep / Enable / Phase / Mode
#define PORT_DRV		PORTB
#define DDR_DRV 		DDRB
#define DRV_SLEEP 		(1<<PB5)
#define DRV_EN 			(1<<PB7)
#define DRV_PASE 		(1<<PB6)
#define DRV_MODE 		(1<<PB4)
#define MOTOR_BREAK		PORT_DRV = (PORT_DRV & ~DRV_EN) | DRV_MODE
#define SET_DRV_SLEEP 	PORT_DRV |=  DRV_SLEEP
#define SET_DRV_ARM  	PORT_DRV &= ~DRV_SLEEP	

//Motor stop input
#define PIN_MOTOR_STOP   PINB
#define DDR_MOTOR_STOP   DDRB
#define PORT_MOTOR_STOP  PORTB
#define MOTOR_STOP 		 (1<<PB2)
#define GET_MOTOR_STOP	 PIN_MOTOR_STOP & MOTOR_STOP

//Signal A output
#define DDR_SIGNAL_A_OUT   DDRA
#define PORT_SIGNAL_A_OUT  PORTA
#define SIGNAL_A_OUT 	  (1<<PA3)

//Signal B output
#define DDR_SIGNAL_B_OUT   DDRB
#define PORT_SIGNAL_B_OUT  PORTB
#define SIGNAL_B_OUT 	   (1<<PB3)


//Limit A output
#define DDR_LIMIT_A_OUT   DDRB
#define PORT_LIMIT_A_OUT  PORTB
#define LIMIT_A_OUT		 (1<<PB1)

//Limit B output
#define DDR_LIMIT_B_OUT   DDRB
#define PORT_LIMIT_B_OUT  PORTB
#define LIMIT_B_OUT		 (1<<PB0)




//Motor Driver nfault pin
#define PIN_NFAULT   		PINC
#define PORT_NFAULT  		PORTC
#define DDR_NFAULT   		DDRC
#define NFAULT       		(1<<PC7)
#define GET_NFAULT   		PIN_NFAULT & NFAULT

// Limit A input
#define PIN_LIMIT_A			PIND
#define PORT_LIMIT_A		PORTD
#define	LIMIT_A				(1<<PD2)
#define GET_LIMIT_A			PIN_LIMIT_A & LIMIT_A

//Limit B input
#define PIN_LIMIT_B			PIND
#define PORT_LIMIT_B		PORTD
#define LIMIT_B				(1<<PD3)
#define GET_LIMIT_B			PIN_LIMIT_B & LIMIT_B

//Jumpers for Motor type and direction
#define DDR_JMP_MOT_TYPE	DDRC
#define PIN_JMP_MOT_TYPE	PINC
#define PORT_JMP_MOT_TYPE	PORTC
#define JMP_MOT_TYPE		(1<<PC7)
#define GET_JMP_MOT_TYPE	PIN_JMP_MOT_TYPE & JMP_MOT_TYPE

#define DDR_JMP_MOT_DIR		DDRC
#define PIN_JMP_MOT_DIR		PINC
#define PORT_JMP_MOT_DIR	PORTC
#define JMP_MOT_DIR			(1<<PC6)
#define GET_JMP_MOT_DIR		PIN_JMP_MOT_DIR & JMP_MOT_DIR



		
//ADC Pins
#define DDR_ADC			DDRA
#define PIN_ADC			PINA
#define U_FUSE_ADC		(1<<PA7)
#define I_DRV_ADC		(1<<PA6)
#define	U_24V_ADC		(1<<PA5)


#define PIN_DLOC_RMT	PINA
#define PORT_LOC_RMT	PORTA
#define DDR_LOC_RMT	 	DDRA
#define LOC_RMT			(1<<PA4)



		
			
//*	Error codes								// LSB
#define ERR_NFAULT		0x01				// BIT 1
#define ERR_U_DRV_FUSE	0x02				// BIT 2
#define ERR_I_DRV 		0x04				// BIT 3
#define ERR_U_24V		0x08				// BIT 4
#define ERR_LIMITS 		0x10				// BIT 5
#define ERR_ORDER		0x20				// BIT 6
#define ERR_WATCHDOG	0x40				// BIT 7
#define ERR_7      		0x80				// BIT 8
											// MSB


//* Buttons

#define BUTTON_A		(1<<PC4)
#define BUTTON_B		(1<<PC5)
 											
uint8_t error_reg;							// Error Register zur Fehlererkennung												
uint8_t pRBstart;											
#endif