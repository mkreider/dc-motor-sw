#ifndef _UART_H_
#define _UART_H_

void uartputc(char wort);
void uartput_uint16(uint16_t zahl);
void init_uart(void);
void uartputs(const char* text);
uint8_t uart_getc(void);
uint8_t uart_getc_nowait(void);

#endif