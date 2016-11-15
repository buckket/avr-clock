#include "clock.h"

uint16_t last_sensor_reading = 0xFFFF;

void draw_clock(uint8_t hours, uint8_t minutes, uint8_t seconds) {
    uint8_t frame[8][4];

    uint8_t digit_1 = hours / 10;
    uint8_t digit_2 = hours % 10;
    uint8_t digit_3 = minutes / 10;
    uint8_t digit_4 = minutes % 10;
    uint8_t pixel_count = pgm_read_byte(&pixels[seconds]);

    for (uint8_t i = 0; i < 8; ++i) {
        frame[i][3] = pgm_read_byte(&digits[digit_1][i]);
        frame[i][2] = pgm_read_byte(&digits[digit_2][i]);
        frame[i][1] = pgm_read_byte(&digits[digit_3][i]);
        frame[i][0] = pgm_read_byte(&digits[digit_4][i]);
    }

    uint8_t k = 0;
    for (uint8_t j = 0; j < pixel_count; ++j) {
        frame[7][3 - k] |= (1 << (7 - (j % 8)));
        if ((j + 1) % 8 == 0 && j > 0) {
            k++;
        }
    }

    draw_buffer(frame);
}

void adjust_brightness(void) {
    uint16_t sensor_reading = adc_read();
    if (abs(sensor_reading - last_sensor_reading) >= 10 | last_sensor_reading > 1023) {
        last_sensor_reading = sensor_reading;
        uint8_t brightness = (sensor_reading) * (15 - 1) / (512) + 1;
        send_command(DISP_ALL, OP_INTENSITY, brightness);
    }
}
