/*
Group 7: Maitham Taleb, Jack Tripp, Jack Nettle, Joe, Chris Hampton.
Date: 11/01/2025
Course: Microprocessor organization
Description: Main program file for changing speed and direction of a DC motor using
a switch and potentiometer.
*/


#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer0.h"
#include "timer1.h"
#include "sevensegmentdisplay.h"
#include "switch.h"
#include "adc.h"
#include "pwm.h"



typedef enum button_states {
  wait_press, debounce_press, wait_release, debounce_release
} stateType;
stateType state = wait_press;

//volatile int count;
volatile int delay_ms;
//volatile state debounce_state = wait_press;



int main() {
    sei(); // Enable global interrupts
    //initial
    unsigned int result = 0;
    float voltage = 0;

    while(1){
        //read in voltage each loop
        result = ADCL;
        result += (ADCH) << 8;
        //Voltage_k = k * (VHigh/# of levels)
        voltage = result * (4.586/1024.0); // 5 v from your kit reads~4.586

    switch(state) {
        case wait_press:
            break;
        case debounce_press:
            ms_delay(1); //Timer 0
            state = wait_release;
            break;
        case wait_release:
            break;
        case debounce_release:
            //Turn off motor
            
            //disable interrupts during countdown
            cli();
                                            
            //10s Countdown
            for (int i=9; i>=0; i--) {
                //Display 'i' on seven segment
                setNum(i);  
                //Wait 1s (Timer 1)
                s_delay(1);
            }

            //enable interrupts
            sei();
            state = wait_press;
            break;
    }

    }
    return 0;

}        


ISR(INT0_vect){
    if(state == wait_press){
        state = debounce_press; // Transition to debounce_press state
    }
    else if(state == wait_release){
        state = debounce_release; // Transition to debounce_release state
    }
}




