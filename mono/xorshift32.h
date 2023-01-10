#if !defined(XORSHIFT_H)
#define XORSHIFT_H

#include "color.h"
union HSV_32state {
    HSV hsv;
    uint32_t bits;
};


void rand_shift();

#endif // XORSHIFT_H
