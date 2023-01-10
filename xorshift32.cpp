#include "color.h"
#include "xorshift32.h"
#include <avr/io.h>

extern uint32_t shift_enc;
extern HSV hsv_current, hsv_target;

union HSV_32state {
    HSV hsv;
    uint32_t bits;
};

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
    HSV_32state s;
    s.bits = xorshift32(shift_enc);
    shift_enc = s.bits;
    hsv_current = hsv_target;
    hsv_target = s.hsv;
}