// Description: This file implements the initialization of an external interrupt
// switch.
//----------------------------------------------------------------------//

#include "switch.h"
#include <avr/io.h>

/*
 * Initializes pull-up resistor on PD0 and sets it into input mode
 */
void initSwitchPD0(){
    DDRD &= ~(1<<DDD0); // I/P
    PORTD |= (1<<PORTD0); //Pull Up Resistor

    EICRA &= ~(1<<ISC01);
    EICRA |= (1<<ISC00);

    EIFR = (1<<INTF0);
    EIMSK |= (1<<INT0);
}