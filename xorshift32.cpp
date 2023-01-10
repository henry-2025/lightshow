#include "color.h"
#include "xorshift32.h"
#include <avr/io.h>

extern uint32_t shift_enc;
extern HSV hsv_current;
extern HSV_32state hsv_target;

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
    hsv_current = hsv_target.hsv;
    hsv_target.bits = xorshift32(hsv_target.bits);
}