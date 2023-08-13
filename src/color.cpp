#include "color.h"
#include "PWM.h"
#include "fast_hsv2rgb.h"

#ifdef NORMALIZE
#include <math.h>

inline uint8_t normalize(uint8_t c)
{
    return exp(c * 0.021745) - 1;
}

void rgb(RGB in)
{
    set_three_channel_duty(normalize(in.r), normalize(in.g), normalize(in.b));
}

#else

void rgb(RGB in)
{
    set_three_channel_duty(in.r, in.g, in.b);
}
#endif

void hsv(HSV in) {
	RGB r;
	fast_hsv2rgb_8bit(in.h, in.s, in.v, &(r.r), &(r.g), &(r.b));
	rgb(r);
}
