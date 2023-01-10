#include "modes.h"
#include "PWM.h"
#include "xorshift32.h"
#include "fast_hsv2rgb.h"
#include "color.h"
#include <stdlib.h>
#include <avr/io.h>

extern bool updating;
extern HSV hsv_current;
extern HSV hsv_target;
extern int mode;

#define NUM_MODES 4 // the modes are

void random_sweep()
{
    if (updating)
    {
        updating = 0;
        int sign;
        sign = (hsv_current.s < hsv_target.s) - (hsv_current.s > hsv_target.s);
        hsv_current.s += sign;
        updating |= sign;

        sign = (hsv_current.v < hsv_target.v) - (hsv_current.v > hsv_target.v);
        hsv_current.v += sign;
        updating |= sign;

        int diff = abs(hsv_current.h - hsv_target.h);
        sign = (hsv_current.h < hsv_target.h) - (hsv_current.h > hsv_target.h);
        sign *= ((diff <= HSV_HUE_STEPS / 2) - (diff > HSV_HUE_STEPS / 2));
        if (sign > 0 && ++hsv_current.h == HSV_HUE_STEPS) {
            hsv_current.h = 0;
        } else if (sign < 0 && --hsv_current.h > HSV_HUE_STEPS) {
            hsv_current.h = HSV_HUE_STEPS - 1;
        }
        updating |= sign;
        hsv(hsv_current);
    }
    else
    {
        rand_shift();
        updating = 1;
    }
    hsv(hsv_current);
}
void hue_sweep()
{
}

void red()
{
}

void constant_color()
{
}

void (*update_funcs[NUM_MODES])() = {random_sweep, hue_sweep, red, constant_color};

void iter()
{
    update_funcs[mode]();
}