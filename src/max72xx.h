#include "spi.h"

#define DISP_ALL        15
#define DISP_4          8
#define DISP_3          4
#define DISP_2          2
#define DISP_1          1

#define OP_NOOP         0
#define OP_DIGIT0       1
#define OP_DIGIT1       2
#define OP_DIGIT2       3
#define OP_DIGIT3       4
#define OP_DIGIT4       5
#define OP_DIGIT5       6
#define OP_DIGIT6       7
#define OP_DIGIT7       8
#define OP_DECODEMODE   9
#define OP_INTENSITY    10
#define OP_SCANLIMIT    11
#define OP_SHUTDOWN     12
#define OP_DISPLAYTEST  15

void init_display(void);

void clear_display(uint8_t device);

void draw_buffer(uint8_t buffer[8][4]);

void transfer_data(uint8_t data[4][2]);

void send_command(uint8_t device, uint8_t opcode, uint8_t payload);
