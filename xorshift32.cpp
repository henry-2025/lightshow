#include <avr/io.h>

extern uint32_t shift_enc;
extern uint8_t rgb_current[3], rgb_target[3];

// RNG
// xorshift for RNG
uint32_t xorshift32(uint32_t x) {
    x ^= x << 13;
    x ^= x << 17;
    x ^= x << 5;
    return x;
}

// use xorshift to compute random rgb values
void rand_shift() {
    for(int i = 0; i < 3; i++) {
        rgb_current[i] = rgb_target[i];
    }
    shift_enc = xorshift32(shift_enc);
    for(int i = 0; i < 3; i++) {
        rgb_target[i] = shift_enc >> (i*8);
    }
}