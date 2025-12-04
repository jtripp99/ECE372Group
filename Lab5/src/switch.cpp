// Description: This file implements the initialization of an external
// switch.
//----------------------------------------------------------------------//

#include "switch.h"
#include <avr/io.h>

/*
 * Initializes pull-up resistor on PB3 and sets it into input mode
 */
void initSwitchPB4(){
    DDRB &= ~(1<<DDB4); // I/P
    PORTB |= (1<<PORTB4); //Pull Up Resistor
    PCICR |= (1 << PCIE0); // enable PCINT 0 - 7
    PCMSK0 |= (1 << PCINT4); // enable PCINT4
}
