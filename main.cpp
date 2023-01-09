#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
volatile uint8_t updating = 0;
volatile float delta, step;
uint8_t rgb_start[3] = {0, 0, 0};
uint8_t rgb_target[3] = {255, 0, 255};

// #define NORMALIZE

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

#ifdef NORMALIZE // just for faster upload since we have to use math lib
#include <math.h>

inline uint8_t normalize(uint8_t c)
{
    return exp(c * 0.021745) - 1;
}

void rgb(uint8_t r, uint8_t g, uint8_t b)
{
    set_three_channel_duty(normalize(r), normalize(g), normalize(b));
}

#else

void rgb(uint8_t r, uint8_t g, uint8_t b)
{
    set_three_channel_duty(r, g, b);
}
#endif

void setup_timer()
{
    TCCR2A |= (1 << WGM21);
    TCCR2B |= (1 << CS21);
    OCR2A = 100; // set the 8-bit timer to run at 1250Hz
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

    uint8_t rgb_current[3];

    for (int i = 0; i < 3; i++)
    {
        rgb_current[i] = (rgb_target[i] - rgb_start[i]) * step + rgb_start[i];
    }

    rgb(rgb_current[0], rgb_current[1], rgb_current[2]);
    if ((step += 1 / (delta * 255)) > 1)
    {
        step = 0;
    }
}

int counter = 0;

int main(void)
{
    DDRB |= (1 << DDB1);
    setup_timer();
    sei();
    while (1);
}

ISR(TIMER2_COMPA_vect)
{
    cli();
    if (++counter > 1250)
    {
        counter = 0;
        PORTB ^= (1 << PORTB1);
    }
    sei();
}