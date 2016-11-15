#include "spi.h"

void spi_init_master(void) {
    // Set SCK, MOSI and SS as outputs
    DDRB |= (1 << DDB5) | (1 << DDB3) | (1 << DDB2);

    // Pull SS high
    PORTB |= (1 << DDB2);

    // Enable SPI (mode 0, master, f/4)
    SPCR = (1 << SPE) | (1 << MSTR);
}

uint8_t spi_tranceiver(uint8_t data) {
    // Write data
    SPDR = data;

    // Wait till transmission is complete
    while (!(SPSR & (1 << SPIF)));

    // Return received data
    return (SPDR);
}
