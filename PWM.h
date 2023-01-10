#ifndef PWM_H
#include <avr/io.h>

void setup_pwm();
void set_three_channel_duty(uint8_t r, uint8_t g, uint8_t b);
#endif // !PWM_H
