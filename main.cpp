#include <avr/io.h>
#include "PWM.h"
#include "timing.h"
#include "color.h"
#include "xorshift32.h"

bool updating = 0;
int mode = 0;
uint8_t r;
HSV hsv_current;
RGB rgb_current, rgb_target;
uint32_t shift_enc = 0xbf9ebb52;

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