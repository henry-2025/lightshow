#include <avr/io.h>
#include "PWM.h"
#include "timing.h"

bool updating = 0;
int mode = 0;
uint8_t rgb_current[3];
uint8_t rgb_target[3];
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