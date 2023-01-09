#ifndef PWM_H
#include <avr/io.h>
#define NORMALIZE // whether or not to apply exponential normalization to the PWM signals. Should use for production but disable if you want faster prototype uploads while developing 

void setup_pwm();
void rgb(uint8_t rgb[3]);
void hsv(uint8_t hsv[3]);
void set_three_channel_duty(uint8_t r, uint8_t g, uint8_t b);
#endif // !PWM_H
