// Description: This file implements turnOnLED and initLED to control
// the LEDs.
//----------------------------------------------------------------------//


#include <avr/io.h>
#include <util/delay.h>
#include "led.h"

/* Initialize PD0, PD1, PD2, and PD3 to outputs
*/
void initLED(){
    DDRD |= (1<<DDD0);  //pin43 (21 on controller)
    DDRD |= (1<<DDD1);  //pin44 (20 on controller)
    DDRD |= (1<<DDD2);  //pin45 (19 on controller)
    DDRD |= (1<<DDD3);  //pin46 (18 on controller)
}

/* This must be one line of code.
* In this function you will be giving a number "num" which will be represented
* in binary by four LEDs. You must effectively assign the lowest four bits of
* "num" to the appropriate bits of PORTD.
*/
void turnOnLEDWithChar(unsigned char num){
    PORTD = (PORTD & 0xF0) | (num & 0x0F); //sets the first four bits to zero, sets the last four bits to num
}
