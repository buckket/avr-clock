#include "clock.h"

void draw_clock(time_struct *clock) {
    uint8_t frame[8][4];

    uint8_t digit_1 = clock->hours / 10;
    uint8_t digit_2 = clock->hours % 10;
    uint8_t digit_3 = clock->minutes / 10;
    uint8_t digit_4 = clock->minutes % 10;

    uint8_t pixel_count = pgm_read_byte(&pixels[clock->seconds]);

    // Draw digits
    for (uint8_t i = 0; i < 8; ++i) {
        frame[i][3] = pgm_read_byte(&digits[digit_1][i]) >> 1;
        frame[i][2] = pgm_read_byte(&digits[digit_2][i]) >> 0;
        frame[i][1] = pgm_read_byte(&digits[digit_3][i]) >> 2;
        frame[i][0] = pgm_read_byte(&digits[digit_4][i]) >> 1;
    }

    // Draw separator
    uint8_t sep_rows[4] = {1, 2, 4, 5};
    for (uint8_t i = 0; i < 4; i++) {
        frame[sep_rows[i]][2] |= 0x01;
        frame[sep_rows[i]][1] |= 0x80;
    }

    // Draw seconds bar
    uint8_t j = 0;
    for (uint8_t i = 0; i < pixel_count; ++i) {
        frame[7][3 - j] |= (1 << (7 - (i % 8)));
        if ((i + 1) % 8 == 0 && i > 0) {
            j++;
        }
    }

    draw_buffer(frame);
}

uint16_t last_sensor_reading = 0xFFFF;

void adjust_brightness(void) {
    uint16_t sensor_reading = adc_read();

    // DEBUG OUTPUT
    char string_buffer[7];
    sprintf(string_buffer, "%d\r\n", sensor_reading);
    uart_puts(string_buffer);

    if ((abs(sensor_reading - last_sensor_reading) >= 50) | (last_sensor_reading > 1023)) {
        last_sensor_reading = sensor_reading;
        uint8_t brightness = (sensor_reading - 10) * (15 - 1) / (1023 - 10) + 1;
        send_command(DISP_ALL, OP_INTENSITY, brightness);
    }
}

void increment_time(time_struct *clock) {
    clock->seconds = (clock->seconds + 1) % 60;
    if (clock->seconds == 0) {
        clock->minutes = (clock->minutes + 1) % 60;
        if (clock->minutes == 0) {
            clock->hours = (clock->hours + 1) % 24;
        }
    }
}

void enable_clock_interrupt(void) {
    DDRD &= ~(1 << PD2); // Set PD2 as input (INT0)
    PORTD &= ~(1 << PD2); // Enable internal pull-up on PD2

    EICRA = (1 << ISC01) | (1 << ISC00); // The rising edge of INT0 generates an interrupt request
    EIMSK = (1 << INT0); // Enable external interrupt INT0
}
