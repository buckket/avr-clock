#include "sleep.h"

void enter_sleep(void) {
    // Reset Watchdog timer, so we always sleep the same amount of time
    //wdt_reset();

    // STANDBY keeps oscillator running (3.6mA vs 3.1mA)
    //set_sleep_mode(SLEEP_MODE_STANDBY);
    set_sleep_mode(SLEEP_MODE_IDLE);

    // Set SE bit
    sleep_enable();

    // Really go to sleep now
    sleep_cpu();

    // Remove SE bit
    sleep_disable();
}
