#include "max72xx.h"

void init_display(void) {
    send_command(DISP_ALL, OP_SCANLIMIT, 7);
    send_command(DISP_ALL, OP_DECODEMODE, 0);
    send_command(DISP_ALL, OP_DISPLAYTEST, 0);
    clear_display(DISP_ALL);
    send_command(DISP_ALL, OP_SHUTDOWN, 1);
}

void clear_display(uint8_t device) {
    for (uint8_t row = 1; row < 9; ++row) {
        send_command(device, row, 0);
    }
}

void draw_buffer(uint8_t buffer[8][4]) {
    uint8_t data[4][2];
    for (uint8_t row = 1; row < 9; ++row) {
        for (uint8_t display = 0; display < 4; ++display) {
            data[display][0] = row;
            data[display][1] = buffer[row - 1][display];
        }
        transfer_data(data);
    }
}

void transfer_data(uint8_t data[4][2]) {
    // Pull SS low to start transmission
    PORTB &= ~(1 << DDB2);
    for (uint8_t i = 4; i > 0; --i) {
        spi_tranceiver(data[i - 1][0]);
        spi_tranceiver(data[i - 1][1]);
    }
    // Pull SS high to end transmission
    PORTB |= (1 << DDB2);
}

void send_command(uint8_t device, uint8_t opcode, uint8_t payload) {
    uint8_t data[4][2];
    for (uint8_t i = 0; i < 4; i++) {
        if (device & (1 << i)) {
            data[i][0] = opcode;
            data[i][1] = payload;
        } else {
            data[i][0] = 0;
            data[i][1] = 0;
        }
    }
    transfer_data(data);
}
