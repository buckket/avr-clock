#include "sleep.h"

void enter_sleep(void) {
    // Reset Watchdog timer, so we always sleep the same amount of time
    wdt_reset();

    // STANDBY keeps oscillator running (3.6mA vs 3.1mA)
    set_sleep_mode(SLEEP_MODE_STANDBY);

    // Set SE bit and enable interrupts
    sleep_enable();
    sei();

    // Really go to sleep now
    sleep_cpu();

    // Disable interrupts and remove SE bit
    cli();
    sleep_disable();
}
