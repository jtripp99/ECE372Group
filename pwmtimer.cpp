// Author:   Jack Nettles      
// Net ID:  23831611
// Date:          
// Assignment:     Lab 4
//
// Description: This file implements functions that utilize the timers
//----------------------------------------------------------------------//

#include <Arduino.h>
#include <avr/io.h>

/* Initialize timer 0, you should not turn the timer on here.
* You will need to use CTC mode */
void initTimer0(){
    //1. CTC MODE 010 WGM2 = 0, WGM1 = 1 WGM0 = 0
    TCCR0A &= ~(1<<WGM00);
    TCCR0A |= (1<<WGM01);
    TCCR0A &= ~(1<<WGM02);

    //dont turn on timer here... skip here and put into delay_ms
    // if turned on here it would begin counting immedietly

    //3. Counting Reg
    TCNT0 = 0;

    //4. Compare Value (changes the delay) counting starts from zero...
    OCR0A = 0;

    //enable ISR flag
    //TIMSK0 |= (1 << TOIE0);

    //start at zero end at 249... gives 1 ms delay
}

/* This delays the program an amount specified by unsigned int delay.
* Use timer 0. Keep in mind that you need to choose your prescalar wisely
* such that your timer is precise to 1 millisecond and can be used for
* 100-200 milliseconds
*/


void initTimer1(){
    //1. CTC MODE 010 WGM3 = 0, WGM2 = 1 WGM1 = 0 WGM1 = 0
    TCCR1A &= ~((1<<WGM11)|(1<<WGM10));
    TCCR1B |= (1<<WGM12);
    TCCR1B &= ~(1<<WGM13);

    //dont turn on timer here... skip here and put into delay_ms
    // if turned on here it would begin counting immedietly

    //3. Counting Reg
    TCNT1 = 0;

    //4. Compare Value (changes the delay) counting starts from zero
    //ends at 1 microsecond with a prescaler of eight
    OCR1A = 0;

    //enable ISR flag
    //TIMSK0 |= (1 << TOIE0);

    //start at zero end at 249... gives 1 ms delay
}


void delayMs(unsigned int delay){
        //make sure counter starts from zero
    TCNT0 = 0;
    unsigned int counter = 0;
    TIFR0 |= (1 << OCF0A); // Resets Flag to zero
    //sends a command to the microcontroller to put flag down

    //start timer
    // 2. Choose prescaler = 64 (011)
    TCCR0B |= (1<<CS00); //Can write rest, dont need to as it is already set to zero
    TCCR0B |= (1<<CS01);
    TCCR0B &= ~(1<<CS02);
    
    OCR0A = 249;


    while(counter<delay){
        //if flag raised
        if(TIFR0&(1<<OCF0A)){
            //increment counter and turn off flag
            counter++;
            TIFR0 |= (1 << OCF0A);
        }
    }
    //turn off timer
    TCCR0B &= ~((1<<CS00) | (1<<CS01) | (1<<CS02));
}

void delayUs(unsigned int delay){
        //make sure counter starts from zero
    TCNT1 = 0;
    unsigned int counter = 0;
    TIFR1 |= (1 << OCF1A); // Resets Flag to zero
    //sends a command to the microcontroller to put flag down

    //start timer
    // 2. Choose prescaler =  1024 (101)
    //Can write rest, dont need to as it is already set to zero
    TCCR1B |= ((1<<CS10) | (1<<CS12));
    TCCR1B &= ~(1<<CS11);

    //Counts... 15624
    OCR1A = 15624;

    //wait for a compare match 

    while(counter<delay){
        //Sets the timer flag to 1
        TIFR1 |= (1 << OCF1A); //logic 1 is flag down
        
        //Set the timer register to 0
        TCNT1 = 0;

        //while flag is down do not do anything
        while(!(TIFR1 & (1 << OCF1A))); //!number is equivalent to number != 0
        //when while loop breaks, (0 & 1) = 0, which IS equal to 0.

        counter++; //1 microsecond delay as been achieved, go to next microsecond
    }

    //turn off timer
    TCCR1B &= ~((1<<CS10)|(1<<CS11)|(1<<CS12));
}
