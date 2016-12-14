#ifndef AVR_CLOCK_UART_H
#define AVR_CLOCK_UART_H

#include <avr/io.h>

void uart_init(void);

void uart_transmit(uint8_t data);

void uart_puts(char *string);

#endif // AVR_CLOCK_UART_H
