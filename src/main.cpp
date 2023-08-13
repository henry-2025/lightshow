#include <avr/io.h>
#include "PWM.h"
#include "timing.h"
#include "color.h"
#include "control.h"
#include "xorshift32.h"

State s_current, s_next;
uint32_t shift_enc = 2447869310;

int main(void)
{
    s_current.hsv = HSV {.h = 0, .s = 255, .v = 0};
    setup_timer();
    setup_pwm();
    setup_control();
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