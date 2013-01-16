#ifndef _DEFINES_H_
#define _DEFINES_H_

#include "median.h"

#define PRINT 1
#define DEBUG 1
#define PACKAGEDIL 1
 

//Print debug messages depending on DEBUG 1 / 0
#if PRINT
# define UPRINT(x) uartputs(x)
#else
# define UPRINT(x) do {} while (0)
#endif 

#if PRINT
# define UPRINTN(x) uartput_uint16(x)
#else
# define UPRINTN(x) do {} while (0)
#endif 


//Print debug messages depending on DEBUG 1 / 0
#if DEBUG
# define DBPRINT(x) uartputs(x)
#else
# define DBPRINT(x) do {} while (0)
#endif 

#if DEBUG
# define DBPRINTN(x) uartput_uint16(x)
#else
# define DBPRINTN(x) do {} while (0)
#endif 


volatile uint8_t error_reg;				//	Error Register for fault detection 											


volatile ringbuffer rbUFuse;
volatile ringbuffer rbU24;
volatile ringbuffer rbIDrv;
volatile ringbuffer* pRbUFuse;
volatile ringbuffer* pRbU24;  
volatile ringbuffer* pRbIDrv; 

//*******************>>> INPUTS <<< *******************


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//* MOTOR STOP INPUT
#define PIN_MOTOR_STOP   PINB
#define DDR_MOTOR_STOP   DDRB
#define PORT_MOTOR_STOP  PORTB
#define MOTOR_STOP 		 (1<<PB2)
#define GET_MOTOR_STOP	 PIN_MOTOR_STOP & MOTOR_STOP

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//* MOTOR DRIVER NFAULT PIN
#define PIN_NFAULT   	  PINC
#define PORT_NFAULT  	  PORTC
#define DDR_NFAULT   	  DDRC
#define NFAULT       	  (1<<PC1)			// <<<<<<< auf anderen PIN legen
#define GET_NFAULT   	  PIN_NFAULT & NFAULT

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//* INTERRUPT VECT
#define LIMIT_A_IRQ			INT0_vect	
#define LIMIT_B_IRQ			INT1_vect
#define STOPP				INT2_vect 

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//* LIMIT A INPUT
#define PIN_LIMIT_A			PIND
#define PORT_LIMIT_A		PORTD
#define	LIMIT_A				(1<<PD2)
#define GET_LIMIT_A			PIN_LIMIT_A & LIMIT_A


//* LIMIT B INPUT
#define PIN_LIMIT_B			PIND
#define PORT_LIMIT_B		PORTD
#define LIMIT_B				(1<<PD3)
#define GET_LIMIT_B			PIN_LIMIT_B & LIMIT_B

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//* JUMPERS FOR MOTOR TYPE DETECTION
#define DDR_JMP_MOT_TYPE	DDRC
#define PIN_JMP_MOT_TYPE	PINC
#define PORT_JMP_MOT_TYPE	PORTC
#define JMP_MOT_TYPE		(1<<PC7)
#define GET_JMP_MOT_TYPE	PIN_JMP_MOT_TYPE & JMP_MOT_TYPE


//* JUMPERS FOR MOTOR DIRECTION DETECTION
#define DDR_JMP_MOT_DIR		DDRC
#define PIN_JMP_MOT_DIR		PINC
#define PORT_JMP_MOT_DIR	PORTC
#define JMP_MOT_DIR			(1<<PC6)
#define GET_JMP_MOT_DIR		PIN_JMP_MOT_DIR & JMP_MOT_DIR

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//* ADC PINS
#define DDR_ADC			DDRA
#define PIN_ADC			PINA
#define PORT_ADC		PORTA
#define U_FUSE_ADC		(1<<PA7)
#define I_DRV_ADC		(1<<PA6)
#define	U_24V_ADC		(1<<PA5)
#define GET_U_FUSE_ADC	PIN_ADC	& U_FUSE_ADC
#define GET_I_DRV_ADC	PIN_ADC	& I_DRV_ADC
#define GET_U_24V_ADC	PIN_ADC & U_24V_ADC

#define U_FUSE_ADC_CH	7
#define I_DRV_ADC_CH	6
#define U_24V_ADC_CH	5

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//* LOCAL/REMOTE DETECTION
#define PIN_LOC_RMT		PINA
#define PORT_LOC_RMT	PORTA
#define DDR_LOC_RMT	 	DDRA
#define LOC_RMT			(1<<PA4)
#define GET_LOC_RMT		PIN_LOC_RMT & LOC_RMT

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//* DRIVE A
#define DDR_BUTTON_A	DDRC
#define PIN_BUTTON_A	PINC
#define PORT_BUTTON_A	PORTC
#define BUTTON_A	    (1<<PC2)
#define GET_BUTTON_A	PIN_BUTTON_A & BUTTON_A


//* DRIVE B
#define DDR_BUTTON_B	DDRC
#define PIN_BUTTON_B	PINC
#define PORT_BUTTON_B	PORTC
#define BUTTON_B	    (1<<PC1)
#define GET_BUTTON_B	PIN_BUTTON_B & BUTTON_B

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//* REMOTE DRIVE A
#define DDR_REMOTE_A	DDRC
#define PIN_REMOTE_A	PINC
#define PORT_REMOTE_A	PORTC
#define REMOTE_A	    (1<<PC2)			// <<<<<<< auf anderen PIN legen
#define GET_REMOTE_A	PIN_REMOTE_A & REMOTE_A


//* REMOTE DRIVE 
#define DDR_REMOTE_B	DDRC
#define PIN_REMOTE_B	PINC
#define PORT_REMOTE_B	PORTC
#define REMOTE_B	    (1<<PC3)
#define GET_REMOTE_B	PIN_REMOTE_B & REMOTE_B

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define DDR_REMOTE_SWITCH	DDRA
#define PIN_REMOTE_SWITCH	PINA
#define PORT_REMOTE_SWITCH	PORTA
#define REMOTE_SWITCH		(1<<PA4)

#define GET_REMOTE_SWITCH	PIN_REMOTE_SWITCH & REMOTE_SWITCH

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



//*******************>>> OUTPUTS <<< *******************


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//* MOTOR DRIVER SLEEP/ ENABLE / PHASE / MODE
#define PORT_DRV		PORTB
#define DDR_DRV 		DDRB
#define DRV_SLEEP 		(1<<PB5)
#define DRV_EN 			(1<<PB7)
#define DRV_PHASE 		(1<<PB6)
#define DRV_MODE 		(1<<PB4)
#define MOTOR_BREAK		PORT_DRV = (PORT_DRV & ~DRV_EN) | DRV_MODE
#define SET_DRV_ARM  	PORT_DRV |=  DRV_SLEEP
#define SET_DRV_SLEEP 	PORT_DRV &= ~DRV_SLEEP
#define SET_GO_A  		PORT_DRV = (PORT_DRV & ~(DRV_MODE)) | (DRV_EN | DRV_PHASE)   
#define SET_GO_B  		PORT_DRV = (PORT_DRV & ~(DRV_PHASE|DRV_MODE)) | DRV_EN


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//* SIGNAL A OUTPUT
#define DDR_SIGNAL_A_OUT   DDRA
#define PORT_SIGNAL_A_OUT  PORTA
#define SIGNAL_A_OUT 	  (1<<PA3)


//* SIGNAL B OUTPUT
#define DDR_SIGNAL_B_OUT   DDRB
#define PORT_SIGNAL_B_OUT  PORTB
#define SIGNAL_B_OUT 	   (1<<PB3)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~




#if PACKAGEDIL
//* LIMIT A OUTPUT PROTOTYPE
#define DDR_LIMIT_A_OUT   DDRC
#define PORT_LIMIT_A_OUT  PORTC
#define LIMIT_A_OUT		 (1<<PC4)


//* LIMIT B OUTPUT PROTOTYPE
#define DDR_LIMIT_B_OUT   DDRC
#define PORT_LIMIT_B_OUT  PORTC
#define LIMIT_B_OUT		 (1<<PC6)

#else

//* LIMIT A OUTPUT
#define DDR_LIMIT_A_OUT   DDRB
#define PORT_LIMIT_A_OUT  PORTB
#define LIMIT_A_OUT		 (1<<PB1)


//* LIMIT B OUTPUT
#define DDR_LIMIT_B_OUT   DDRB
#define PORT_LIMIT_B_OUT  PORTB
#define LIMIT_B_OUT		 (1<<PB0)

#endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// * MOTOR DIRECTION A
// #define DDR_DIR_B_LED	 DDRA
// #define PORT_DIR_B_LED 	 PORTA
// #define DIR_B_LED		 (1<<PA2)
// 
// * MOTOR DIRECTION B
// #define DDR_DIR_A_LED	DDRA
// #define PORT_DIR_A_LED 	PORTA
// #define DIR_A_LED		(1<<PA1)

//* MOTOR DIRECTION A PROTOTYPE
#define DDR_DIR_B_LED	 DDRA
#define PORT_DIR_B_LED 	 PORTA
#define DIR_B_LED		 (1<<PC5)

//* MOTOR DIRECTION B PROTOTYPE
#define DDR_DIR_A_LED	DDRA
#define PORT_DIR_A_LED 	PORTA
#define DIR_A_LED		(1<<PC3)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//* ERROR LED
#define DDR_ERR_LED		 DDRD
#define PORT_ERR_LED 	 PORTD
#define DIR_ERR_LED		 (1<<PD5)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//* POWER LED
#define DDR_PWR_LED		 DDRD
#define PORT_PWR_LED 	 PORTD
#define PWR_LED			 (1<<PD6)
#define SET_PWR_LED		 PORT_PWR_LED = (PORT_PWR_LED & PWR_LED)	

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//* UART PINS
#define DDR_UART_TX		 DDRD
#define PORT_UART_TX 	 PORTD
#define DIR_UART_TX		 (1<<PD1)

#define DDR_UART_RX		 DDRD
#define PORT_UART_RX 	 PORTD
#define DIR_UART_RX		 (1<<PD0)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



//*******************>>> NC'S & ERROR DEFINES <<< *******************


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//* NOT CONNECTED PINS
#define DDR_NC1			 DDRA
#define PORT_NC1 		 PORTA
#define NC1				 (0<<PA2)

#define DDR_NC2			 DDRC
#define PORT_NC2 		 PORTC
#define NC2 			 (0<<PC0)

#define DDR_NC3			 DDRA
#define PORT_NC3 		 PORTA
#define NC3				 (0<<PD7)

#define DDR_NC4			 DDRA
#define PORT_NC4 		 PORTA
#define NC4				 (0<<PA6)

#define DDR_NC5			 DDRA
#define PORT_NC5 		 PORTA
#define NC5				 (0<<PA4)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	
//*	ERROR CODES								// LSB
#define ERR_NFAULT		0x01				// BIT 1
#define ERR_U_DRV_FUSE	0x02				// BIT 2
#define ERR_I_DRV 		0x04				// BIT 3
#define ERR_U_24V		0x08				// BIT 4
#define ERR_LIMITS 		0x10				// BIT 5
#define ERR_ORDER		0x20				// BIT 6
#define ERR_WATCHDOG	0x40				// BIT 7
#define ERR_7      		0x80				// BIT 8
											// MSB
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 											
										
#endif