#if !defined(TIMING_H)
#define TIMING_H
#define TIMER_FREQ 48

#include <avr/interrupt.h>
#include "modes.h"

void setup_timer();
void disable_timer();

#endif // TIMING_H
