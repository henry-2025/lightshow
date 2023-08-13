#include "control.h"
#include "modes.h"
#include "color.h"
#include "fast_hsv2rgb.h"
#include "timing.h"
#include <avr/io.h>

#define SECONDS(s) (TIMER_FREQ * s)
#define SELECT_TIME 1

extern State s_current, s_next;

// for managing everything about the menu state
struct
{
    bool pressed = false;
    bool ascending = false;
    int count_held;
} menu;

void setup_control()
{
    // set input and pullup on port D 2 (int0). not going to poll here
    DDRD &= ~(1 << DDD2);
    PORTD |= (1 << PD2);
}

void button_down()
{
    if (!menu.pressed)
    {
        menu.pressed = true;
        menu.count_held = 0;
        if (++s_current.mode == NUM_MODES)
        {
            s_current.mode = 0;
        }
        switch (s_current.mode)
        {
        case MODE_RED:
            s_current.rgb = RGB{.r = 255, .g = 0, .b = 0};
            break;
        case MODE_HSV_SWEEP:
            s_current.hsv = HSV{.h = 0, .s = 255, .v = 255};
            break;
        default:
            break;
        }
    }
    else
    {
        if (++menu.count_held > SECONDS(SELECT_TIME))
        {
            if (s_current.mode == MODE_CONSTANT)
            {
                if (++s_current.hsv.h == HSV_HUE_STEPS)
                    s_current.hsv.h = 0;
            }
            else if (s_current.mode == MODE_RED)
            {
                s_current.rgb.r += menu.ascending - !menu.ascending;
                menu.ascending ^= (s_current.rgb.r == 0 || s_current.rgb.r == 255);
            }
            else if (s_current.mode == MODE_HSV_SWEEP)
            {
                s_current.hsv.v += menu.ascending - !menu.ascending;
                menu.ascending ^= (s_current.hsv.v == 0 || s_current.hsv.v == 255);
            }
        }
    }
}

void button_up()
{
    if (menu.pressed)
    {
        menu.pressed = false;
    }
}

void poll_button()
{
    if (PIND & (1 << PIND2))
    {
        button_up();
    }
    else
    {
        button_down();
    }
}
