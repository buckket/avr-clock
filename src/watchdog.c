#include "watchdog.h"

void setup_watchdog(void) {
    // Set Watchdog Change Enable (4 cycles) and enable Watchdog
    WDTCSR = (1 << WDCE) | (1 << WDE);

    // Set Watchdog timeout (1s) and enable interrupt mode only
    WDTCSR = (1 << WDIE) | (1 << WDP2) | (1 << WDP1);
}


ISR(WDT_vect) {
    // NOP
}
