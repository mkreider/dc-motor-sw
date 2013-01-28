#ifndef _UART_H_
#define _UART_H_


void uartputc(char chr);

void uartputs(const char* text);

void uartput_uint16(uint16_t num);

void init_uart(void);

uint8_t uart_getc(void);

uint8_t uart_getc_nowait(void);

#endif
