#include <avr/io.h>
#include <avr/interrupt.h>

#define NORMALIZE // whether or not to apply exponential normalization to the PWM signals. Should use for production but disable if you want faster prototype uploads while developing 

volatile bool updating = 0;
uint8_t rgb_current[3];
uint8_t rgb_target[3];
uint32_t shift_enc = 2447869310;


// xorshift for RNG
uint32_t xorshift32(uint32_t x) {
    x ^= x << 13;
    x ^= x << 17;
    x ^= x << 5;
    return x;
}

// use xorshift to compute random rgb values
void rand_shift() {
    for(int i = 0; i < 3; i++) {
        rgb_current[i] = rgb_target[i];
    }
    shift_enc = xorshift32(shift_enc);
    for(int i = 0; i < 3; i++) {
        rgb_target[i] = shift_enc >> (i*8);
    }
}
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


#ifdef NORMALIZE
#include <math.h>

inline uint8_t normalize(uint8_t c)
{
    return exp(c * 0.021745) - 1;
}

void rgb(uint8_t rgb[3])
{
    set_three_channel_duty(normalize(rgb[0]), normalize(rgb[1]), normalize(rgb[2]));
}

#else

void rgb(uint8_t rgb[3])
{
    set_three_channel_duty(rgb[0], rgb[1], rgb[2]);
}
#endif

void setup_timer()
{
    TCCR2A |= (1 << WGM21);
    TCCR2B |= (1 << CS22) | (1 << CS21);
    OCR2A = 100; // set the 8-bit timer to run at 48Hz
    TIMSK2 |= (1 << OCIE2A);
}

void iter()
{
    // if (updating)
    // {
    //     if (current_step == comp)
    //     {
    //         if (++rgb_iter < rgb_iter_max)
    //         {
    //             for (int i = 0; i < 3; i++)
    //             {
    //                 rgb_start[i] = rgb_target[i];
    //                 rgb_target[i] = rgb_array[rgb_iter][i];
    //             }
    //         } else {
    //             rgb_iter = 0;
    //         }
    //     }
    //     update_state();
    // }
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

int main(void)
{
    setup_timer();
    setup_pwm();
    updating = 0;
    sei();
    while (1)
        ;
}

ISR(TIMER2_COMPA_vect)
{
    cli();
    iter();
    sei();
}