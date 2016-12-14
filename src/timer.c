#include "timer.h"

void setup_timer(void) {
    // 16-bit timer (TIMER1)
    TCCR1A = 0; // Set for normal timer operation
    TCCR1B = (1 << CS11) | (1 << CS10); // Set presacler to F_CPU/64
    TIMSK1 = (1 << TOIE1); // Enable timer interrupt
}

ISR(TIMER1_OVF_vect) {
    // NOP
}
