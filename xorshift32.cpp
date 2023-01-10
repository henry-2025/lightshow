#include "color.h"
#include "xorshift32.h"
#include <avr/io.h>

extern uint32_t shift_enc;
extern RGB rgb_current, rgb_target;

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
    rgb_current = rgb_target;
    shift_enc = xorshift32(shift_enc);

    rgb_target.r = shift_enc;
    rgb_target.g = shift_enc >> 8;
    rgb_target.b = shift_enc >> 16;
}