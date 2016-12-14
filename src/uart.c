#include "uart.h"

#define BAUD 9600
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)

void uart_init(void) {
    // Set baud rate
    UBRR0H = (BAUDRATE >> 8);
    UBRR0L = (BAUDRATE & 0xFF);

    // Enable transmitter
    UCSR0B = (1 << TXEN0);

    // Set default data format (8N1)
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
}

void uart_transmit(uint8_t data) {
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)));

    // Put data into buffer, send the data
    UDR0 = data;

    // Wait till data transfer is complete
    while (!(UCSR0A & (1 << TXC0)));

    // Clear flag
    UCSR0A |= (1 << TXC0);
}

void uart_puts(char *string) {
    while (*string) {
        uart_transmit((uint8_t) *string);
        string++;
    }
}
