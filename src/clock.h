#ifndef AVR_CLOCK_CLOCK_H
#define AVR_CLOCK_CLOCK_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "adc.h"
#include "digits.h"
#include "max72xx.h"
#include "uart.h"

typedef struct {
    volatile uint8_t seconds;
    volatile uint8_t minutes;
    volatile uint8_t hours;
} time_struct;

void draw_clock(time_struct *clock);

void adjust_brightness(void);

void increment_time(time_struct *clock);

void enable_clock_interrupt(void);

#endif //AVR_CLOCK_CLOCK_H
