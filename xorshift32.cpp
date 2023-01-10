#include "color.h"
#include "xorshift32.h"
#include <avr/io.h>

extern uint32_t shift_enc;
extern State s_current, s_next;

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
    s_current.rgb = s_next.rgb;
    shift_enc = xorshift32(shift_enc);

    s_next.rgb.r = shift_enc;
    s_next.rgb.g = shift_enc >> 8;
    s_next.rgb.b = shift_enc >> 16;
}