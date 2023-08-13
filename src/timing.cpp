#include "timing.h"

void setup_timer()
{
    TCCR2A |= (1 << WGM21);
    TCCR2B |= (1 << CS22) | (1 << CS21);
    OCR2A = 1000000 / 256 / TIMER_FREQ; // set the 8-bit timer to run at 39Hz
    TIMSK2 |= (1 << OCIE2A);
}

void disable_timer() {
    TIMSK2 &= (1 << OCIE2A);
}