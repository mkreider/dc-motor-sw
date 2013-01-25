#ifndef _UART_H_
#define _UART_H_

/**
 * @brief Writes a single character to the serial console
 *
 * @param[in] chr The char to write
 *
 */
void uartputc(char chr);

/**
 * @brief Writes a string to the serial console
 *
 * @param[in] text The c string to write
 *
 */
void uartputs(const char* text);


/**
 * @brief Writes a 8/16 bit unsigned int as ASCII to the serial console
 *
 * @param[in] num The unisgned int to write
 *
 */
void uartput_uint16(uint16_t num);

/**
 * @brief Initialises the UART on an ATMEGA32 to 57600 baud, 8N1 
 *
 *
 */
void init_uart(void);


/**
 * @brief Fetches a single character from the serial console. Waits until char is received.
 *
 * @retval Unsigned char received from console
 *
 */
uint8_t uart_getc(void);

/**
 * @brief ???
 *
 */
void test_uartgetc(void);

/**
 * @brief Fetches a single character from the serial console. Checks RX buffer and returns immediately.
 *
 * @retval Return 0 if RX was empty, else the char code
 *
 */
uint8_t uart_getc_nowait(void);

#endif
