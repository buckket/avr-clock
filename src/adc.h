#ifndef AVR_CLOCK_ADC_H
#define AVR_CLOCK_ADC_H

#include <avr/io.h>

void adc_init(void);

uint16_t adc_read(void);

#endif //AVR_CLOCK_ADC_H
