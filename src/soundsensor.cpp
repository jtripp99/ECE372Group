#include "soundsensor.h"
#include <avr/io.h>

void init_PB1(){
    DDRB &= ~(1<<DDB1); // I/P
    PORTB &= ~(1<<PORTB1); //possibly disable pull-up
    PCICR |= (1 << PCIE0); // enable PCINT 0 - 7
    PCMSK1 |= (1 << PCINT1); // enable PCINT4

}


