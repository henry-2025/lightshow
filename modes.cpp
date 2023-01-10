#include "modes.h"
#include "PWM.h"
#include "xorshift32.h"
#include "fast_hsv2rgb.h"
#include "color.h"
#include "control.h"
#include <stdlib.h>
#include <avr/io.h>

extern int light_mode;
extern State s_current, s_next;

void random_sweep()
{
    if (s_current.updating)
    {
        s_current.updating = 0;
        int tmp = (s_current.rgb.r < s_next.rgb.r) - (s_current.rgb.r > s_next.rgb.r);
        s_current.rgb.r += tmp;
        s_current.updating |= tmp;

        tmp = (s_current.rgb.g < s_next.rgb.g) - (s_current.rgb.g > s_next.rgb.g);
        s_current.rgb.g += tmp;
        s_current.updating |= tmp;

        tmp = (s_current.rgb.b < s_next.rgb.b) - (s_current.rgb.b > s_next.rgb.b);
        s_current.rgb.b += tmp;
        s_current.updating |= tmp;

        rgb(s_current.rgb);
    }
    else
    {
        rand_shift();
        s_current.updating = 1;
    }
}

void hsv_sweep()
{

    if (++s_current.hsv.h == HSV_HUE_STEPS)
    {
        s_current.hsv.h = 0;
    }
    hsv(s_current.hsv);
}

void red()
{
    rgb(s_current.rgb);
}

void constant_color()
{
    hsv(s_current.hsv);
}

void (*update_funcs[NUM_MODES])() = {random_sweep, hsv_sweep, red, constant_color};

void iter()
{
    poll_button();
    update_funcs[s_current.mode]();
}