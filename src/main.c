#include <avr/power.h>
#include <avr/interrupt.h>

#include "spi.h"
#include "twi.h"
#include "max72xx.h"
#include "clock.h"
#include "timer.h"
#include "sleep.h"
#include "ds3231.h"


time_struct *pclock;


void setup(void) {
    //setup_watchdog();
    setup_timer();
    adc_init();
    uart_init();
    spi_init_master();
    twi_init();
    init_display();
}

int main(void) {
    setup();

    time_struct clock_time;
    pclock = &clock_time;

    rtc_read_time(pclock);
    rtc_enable_sqw();

    enable_clock_interrupt();
    sei();

    // Set intensity and thus enable display
    send_command(DISP_ALL, OP_INTENSITY, 8);

    while (1) {
        draw_clock(pclock);
        adjust_brightness();
        enter_sleep();
    }
}

ISR(INT0_vect) {
    increment_time(pclock);
}
