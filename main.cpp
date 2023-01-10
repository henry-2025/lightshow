#include <avr/io.h>
#include "PWM.h"
#include "timing.h"
#include "color.h"
#include "xorshift32.h"

bool updating = 0;
int mode = 0;
HSV hsv_current;
HSV_32state hsv_target;

int main(void)
{
    hsv_target.bits = 0x4b8c8132; // random seed
    setup_timer();
    setup_pwm();
    updating = 0;
    sei();
    while (1)
        ;
}

// main timing interrupt
ISR(TIMER2_COMPA_vect)
{
    cli();
    iter();
    sei();
}