#include <avr/io.h>
#include "led.h"

void led_init() {
    DDRD |= (1 << DDD0);  //initialize pin D0 to output
}

void led_on() {
    PORTD |= (1 << PORTD0);
}

void led_off() {
    PORTD &= ~(1 << PORTD0);
}