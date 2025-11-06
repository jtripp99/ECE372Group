#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void timer1_init() {

TCCR1A |= (1 << WGM11); // CTC mode

TCCR1B |= (1 << CS12) | (1 << CS10); // prescaler 128

TCNT1 = 0; // initialize counter

OCR1A = 62500; // compare value for 1s at 16MHz with prescaler 128

}

void s_delay(int delay) {
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