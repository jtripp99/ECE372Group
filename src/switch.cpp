// Description: This file implements the initialization of an external
// switch.
//----------------------------------------------------------------------//

#include "switch.h"
#include <avr/io.h>

/*
 * Initializes pull-up resistor on PB3 and sets it into input mode
 */
void initSwitchPB3(){
    //switch connected to PortB3 (pin 50 on board)
    DDRB &= ~(1<<DDB3);  //make input
    PORTB |= (1<<PORTB3); //pull up resistor on
    PCICR |= (1<<PCIE0);    //enable pin change interrupt flag (0-7)
    PCMSK0 |= (1<<PCINT3); //enable pin B3, mask the pins we dont want
}
