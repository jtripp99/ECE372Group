#include "soundsensor.h"
#include <avr/io.h>

void init_PA0{
     DDRB &= ~(1<<DDB4); // I/P
    PORTB |= (1<<PORTB4); //Pull Up Resistor

     PCICR |= (1 << PCIE0); // enable PCINT 0 - 7
    PCMSK0 |= (1 << PCINT4); // enable PCINT4

}