#include <util/delay.h>


#include "spi.h"
#include "max72xx.h"
#include "clock.h"
#include "watchdog.h"
#include "sleep.h"

void setup(void) {
    setup_watchdog();
    adc_init();
    spi_init_master();
    init_display();
}

int main(void) {
    setup();



    // Set intensity and thus enable display
    send_command(DISP_ALL, OP_INTENSITY, 8);

    draw_clock(20, 14, 30);

    uint8_t minutes = 0;
    while (1) {
        for (uint8_t i = 0; i < 60; ++i) {
            draw_clock(20, minutes % 60, i);
            adjust_brightness();
            enter_sleep();
        }
        minutes++;
    }

    /*
    while (1) {
        for (int i = 0; i < 16; ++i) {
            send_command(DISP_ALL, OP_INTENSITY, i);
            _delay_ms(500);
        }
    }
    */

    /*
    while (1) {
        for (int i = 1; i < 9; ++i) {
            if (i != 1) {
                send_command(15, i - 1, 0);
            }
            send_command(15, i, 255);
            _delay_ms(40);
        }
        for (int i = 8; i > 0; --i) {
            if (i != 8) {
                send_command(15, i + 1, 0);
            }
            send_command(15, i, 255);
            _delay_ms(40);
        }
    }
    */
    return 1;
}
