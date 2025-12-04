#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void timer1_init() {

TCCR1A |= (1 << WGM11); // CTC mode

TCCR1B |= (1 << CS11) | (1 << CS10); // prescaler 64

TCNT1 = 0; // initialize counter

OCR1A = 249; // set compare value for 1ms at 16MHz with prescaler 64
}

void ms_delay(int delay) {
TCNT1 = 0; // reset counter
int counter = 0; // initialize counter variable
TIFR1 |= (1 << OCF1A); // clear compare match flag
while (counter < delay) { //while the counter is less than the delay
    if (TIFR1 & (1 << OCF1A)) { // check if compare match occurred
        counter++; // increment counter
        TIFR1 |= (1 << OCF1A); // clear compare match flag
    }
  }
}