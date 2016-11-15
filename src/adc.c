#include "adc.h"

void adc_init(void) {
    // Set Voltage Reference to AVcc, default channel is ADC0
    ADMUX = (1 << REFS0);

    // Enable ADC with prescaler set to 128
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t adc_read(void) {
    // Start single conversion
    ADCSRA |= (1 << ADSC);

    // Wait till conversion is complete
    while (ADCSRA & (1 << ADSC));

    // Return data
    return (ADC);
}
