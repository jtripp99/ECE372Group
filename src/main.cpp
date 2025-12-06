#include <Arduino.h>

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "i2c.h"
#include "rtc.h"
#include "led.h"
#include "soundsensor.h"
#include "timer.h"
#include "lcd.h"

typedef enum button_states {
  wait_press, debounce_press, wait_release, debounce_release
} stateType;
stateType state = wait_press;

typedef enum sound_sensor_states {
    wait_sound, debounce_sound, wait_no_sound, debounce_no_sound
} soundstateType;
soundstateType soundstate = wait_sound;

int main(){
    sei(); // Enable global interrupts
    init_PB4();
    initI2C();
    rtc_init();
    initTimer1(); 
    initLCD();
    int* hour;
    int* minute; 
    int* second;
    
    while(1) {
        
        rtc_getTime(hour, minute, second);

        // //printing value of sound sensor state machine
        // Serial.print("Sound Sensor State: ");
        // Serial.println((PINB &(1 << PINB4)) ? 1 : 0);


        switch(soundstate) {
            case wait_sound:
                break;
            case debounce_sound:
                //ms_delay(1);//Timer 1
                soundstate = wait_no_sound;
                break;
            case wait_no_sound:
                break;
            case debounce_no_sound:
                //ms_delay(1);
                soundstate = wait_sound;

            break;
        }

        switch(state) {
            case wait_press:
                break;
            case debounce_press:
                //ms_delay(1);//Timer 1
                state = wait_release;
                break;
            case wait_release:
                break;
            case debounce_release:
                //ms_delay(1);
                state = wait_press;

            break;
        }

    }
    return 0;
}

ISR(PCINT0_vect){
    if(soundstate == wait_sound){
        soundstate = debounce_sound; // Transition to debounce_press state
    }
    else if(soundstate == wait_no_sound){
        soundstate = debounce_no_sound; // Transition to debounce_release state
    }
}

ISR(PCINT2_vect){
    if(state == wait_press){
        state = debounce_press; // Transition to debounce_release state
    }
    else if(state == wait_release){
        state = debounce_release; // Transition to debounce_release state
    }
}
