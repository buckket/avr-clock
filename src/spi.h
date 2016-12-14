#ifndef AVR_CLOCK_SPI_H
#define AVR_CLOCK_SPI_H

#include <avr/io.h>

void spi_init_master(void);

uint8_t spi_tranceiver(uint8_t data);

#endif // AVR_CLOCK_SPI_H
