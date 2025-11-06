#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void timer0_init() {
TCCR0A |= (1 << WGM01); // CTC mode

TCCR0B |= (1 << CS01) | (1 << CS00); // prescaler 64

TCNT0 = 0; // initialize counter

OCR0A = 249; // compare value for 1ms at 16MHz with no prescaler

//OCR0B = 3; // compare value for 1us at 16MHz with no prescaler

// TIMSK0 |= (1 << OCIE0A); // enable interupts for timer
}

void ms_delay(int delay) {
TCNT0 = 0; // reset counter
int counter = 0; // initialize counter variable
TIFR0 |= (1 << OCF0A); // clear compare match flag
while (counter < delay) { //while the counter is less than the delay
    if (TIFR0 & (1 << OCF0A)) { // check if compare match occurred
        counter++; // increment counter
        TIFR0 |= (1 << OCF0A); // clear compare match flag
    }
  }
}

/*void us_delay(int delay) {
TCNT0 = 0; // reset counter
int counter = 0; // initialize counter variable
TIFR0 |= (1 << OCF0B); // clear compare match flag
while (counter < delay) { //while the counter is less than the delay
    if (TIFR0 & (1 << OCF0B)) { // check if compare match occurred
        counter++; // increment counter
        TIFR0 |= (1 << OCF0B); // clear compare match flag
    }
  }
}*/