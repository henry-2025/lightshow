#include "PWM.h"
#include <avr/io.h>


void setup_pwm()
{
    // pins are PB1 (OC1A) (blue), PD5 (OC0B) (green) and PD6 (OC0A) (red). figure out the relevant order next

    DDRB |= (1 << DDB1);
    DDRD |= (1 << DDD5) | (1 << DDD6);

    // Configure counter 0: For OC0B and OC0A, configure fast pwm mode, set each output to clear OC0x at bottom, set at compare match
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00);
    TCCR0B |= (1 << CS00);

    // configure counter 1: for OC1A, configure fast pwm in 8-bit mode, set OC1A to clear at bottom, set at compare match
    TCCR1A |= (1 << COM1A1) | (1 << WGM10);
    TCCR1B |= (1 << CS10);

    // set counter registers to off
    OCR0A = 0;
    OCR0B = 0;

    OCR1A = 0;
}


void set_three_channel_duty(uint8_t r, uint8_t g, uint8_t b)
{
    OCR0A = r;
    OCR0B = g;
    OCR1A = b;
}