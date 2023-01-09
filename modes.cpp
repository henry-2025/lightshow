#include "modes.h"
#include "PWM.h"
#include "xorshift32.h"
#include <avr/io.h>

extern bool updating;
extern uint8_t rgb_current[3];
extern uint8_t rgb_target[3];
extern int mode;


#define NUM_MODES 4 // the modes are 

void random_sweep() {
    if (updating)
    {
        updating = 0;
        for (int i = 0; i < 3; i++)
        {
            if (rgb_current[i] > rgb_target[i])
            {
                rgb_current[i]--;
                updating = 1;
            }
            else if (rgb_current[i] < rgb_target[i])
            {
                rgb_current[i]++;
                updating = 1;
            }
        }
        rgb(rgb_current);
    } else {
        rand_shift();
        updating = 1;
    }
}


void hue_sweep() {

}

void red() {
}

void constant_color() {

}

void(*update_funcs[NUM_MODES])() = {random_sweep, hue_sweep, red, constant_color};

void iter() {
    update_funcs[mode]();
}