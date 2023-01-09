#ifndef PWM_H
#include <avr/io.h>
// setup 8-bit pwm
void setup_pwm();
void rgb(uint8_t r, uint8_t g, uint8_t b);
void set_three_channel_duty(uint8_t r, uint8_t g, uint8_t b);
#endif // !PWM_H
