#include <avr/io.h>
#include "PWM.h"
#include "timing.h"
#include "color.h"

bool updating = 0;
int mode = 0;
HSV hsv_current = {
    0,
    255,
    255
};
HSV hsv_target;
uint32_t shift_enc = 2447869310;

int main(void)
{
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