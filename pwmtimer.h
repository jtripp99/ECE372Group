
#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>

void initTimer0();
void initTimer1(); // for microsecond delay
void delayMs(unsigned int delay);
void delayUs(unsigned int delay); //for microsecond delay

#endif
