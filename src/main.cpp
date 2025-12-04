// Author:        Jack Tripp
// Net ID:        23924580
// Date:          10/16/2025
// Assignment:    Lab 3
//
// Description: This file contains a programmatic overall description of the
// program. It should never contain assignments to special function registers
// for the exception key one-line code such as checking the state of the pin.
//
// Requirements:
//----------------------------------------------------------------------//




#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "led.h"
#include "switch.h"
#include "timer.h"
#include "lcd.h"


/*
 * Define a set of states that can be used in the state machine using an enum.
 */
// typedef enum .......
typedef enum enum_stateType {
    wait_press,
    wait_release,
    debounce_press,
    debounce_release,
} stateType;


// Initialize states.  Remember to use volatile 
//volatile ints for state and delay_ms because they are changed during the pin change interrupt
volatile stateType state = wait_press;
volatile unsigned int delay_ms = 100;


int main(){

  //initialize switch, LED pins, Timer 0 and 1, and LCD pins
  initSwitchPB3();
  initLED();
  sei(); // Enable global interrupts.
  initTimer0();
  initTimer1();
  initLCD();

  moveCursor(0, 0); // moves the cursor to 0,0 position
  writeString("Blinking rate = ");
  moveCursor(1, 0);  // moves the cursor to 1,0 position
  writeString("Fast");

  //code for special characters
  moveCursor(1, 10);
  unsigned char ArrayCh[] = {0x00, 0x04, 0x04, 0x0E, 0x1F, 0x15, 0x04, 0x0E}; //airplane special character
  writeCharacter(0x00);   //special (custom) character
  setCGRAM(0x40);         //look for character values in CGRAM

  //parse through special character array
  unsigned int i = 0;
  while (i <= 7) {
    writeCharacter(ArrayCh[i]);
    i++;
  }

  unsigned char num = 0; //initialize led state to 0

  // while loop
  while (1) {

  //state machine for debouncing switch and changing delay time
    switch (state) {
      case wait_press:
        break;

      case debounce_press:
        delayMs(1);
        state = wait_release;
        break;

      case wait_release:
        break;

      case debounce_release:
        delayMs(1);
        state = wait_press;
        break;
    }

    //call function to light the LEDs corresponding to num
    turnOnLEDWithChar(num);

    //cycle num 0-15, then repeat
    if (num < 16) {
      num++;
    }
    else {
      num = 0;
    }

    //if delay is 'slow', print slow special character (music note)
    if (delay_ms == 200) {
      moveCursor(1, 0);  // moves the cursor to 1,0 position
      writeString("Slow");
      moveCursor(1, 10);
      unsigned char ArrayCh[] = {0x02, 0x03, 0x02, 0x02, 0x02, 0x0E, 0x1E, 0x0E};
      writeCharacter(0x00);
      setCGRAM(0x40);
      unsigned int i = 0;
      while (i <= 7) {
        writeCharacter(ArrayCh[i]);
        i++;
      } 
    }

    //if delay is 'fast', print fast special character (airplane)
    else if (delay_ms == 100) {
      moveCursor(1, 0);  // moves the cursor to 1,0 position
      writeString("Fast");
      moveCursor(1, 10);
      unsigned char ArrayCh1[] = {0x00, 0x04, 0x04, 0x0E, 0x1F, 0x15, 0x04, 0x0E}; //special character array for music note character
      writeCharacter(0x00);
      setCGRAM(0x40);
      unsigned int i = 0;
      while (i <= 7) {
        writeCharacter(ArrayCh1[i]);
        i++;
      } 
    }
    
    //delay LEDs change by delay_ms milliseconds
    delayMs(delay_ms);
  }
 
  return 0;
}
  

/* Implement an Pin Change Interrupt which handles the switch being
* pressed and released. When the switch is pressed and released, the LEDs
* change at twice the original rate. If the LEDs are already changing at twice
* the original rate, it goes back to the original rate.
*/
ISR(PCINT0_vect) {    //that's for portB3 -- PCINT3
  //change states to debounce each time interrupt is active
  if (state == wait_press) {
    state = debounce_press;
    //change delay between 100 and 200 ms each time switch is pressed
    if (delay_ms == 100) {
      delay_ms = 200;
    }
    else if (delay_ms == 200) {
      delay_ms = 100;
    }
  }
  else if (state == wait_release) {
    state = debounce_release;
  }
  //test for debugging
  else {
    Serial.println("State error");
  }
}
