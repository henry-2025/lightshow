#include "modes.h"
#include "PWM.h"
#include "xorshift32.h"
#include "fast_hsv2rgb.h"
#include "color.h"
#include <stdlib.h>
#include <avr/io.h>

extern bool updating;
extern int mode;
extern HSV hsv_current;
extern RGB rgb_current, rgb_target;
extern uint8_t r;

#define NUM_MODES 4 // the modes are

void random_sweep()
{
    if (updating)
    {
        updating = 0;
        int tmp = (rgb_current.r < rgb_target.r) - (rgb_current.r > rgb_target.r);
        rgb_current.r += tmp;
        updating |= tmp;

        tmp = (rgb_current.g < rgb_target.g) - (rgb_current.g > rgb_target.g);
        rgb_current.g += tmp;
        updating |= tmp;

        tmp = (rgb_current.b < rgb_target.b) - (rgb_current.b > rgb_target.b);
        rgb_current.b += tmp;
        updating |= tmp;

        rgb(rgb_current);
    }
    else
    {
        rand_shift();
        updating = 1;
    }
}

void hue_sweep()
{
    if (++hsv_current.h == HSV_HUE_STEPS)
    {
        hsv_current.h = 0;
    }
    hsv(hsv_current);
}

void red()
{
    rgb(RGB{.r = r, .g = 0, .b = 0});
}

void constant_color()
{
}

void (*update_funcs[NUM_MODES])() = {random_sweep, hue_sweep, red, constant_color};

void iter()
{
    update_funcs[mode]();
}