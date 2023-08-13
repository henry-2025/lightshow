#if !defined(COLOR_H)
#define COLOR_H
#include <avr/io.h>

struct RGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct HSV {
    uint16_t h;
    uint8_t s;
    uint8_t v;
};

struct State {
    int mode;
    RGB rgb;
    HSV hsv;
    bool updating;
};

#define NORMALIZE // whether or not to apply exponential normalization to the PWM signals. Should use for production but disable if you want faster prototype uploads while developing 
void rgb(RGB);
void hsv(HSV);


#endif // COLOR_H
