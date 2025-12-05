#include <Arduino.h>

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "i2c.h"
#include "rtc.h"
#include "led.h"
#include "soundsensor.h"
#include "timer.h"

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
    Serial.begin(9600);
    while(1) {

        // //printing value of sound sensor state machine
        // Serial.print("Sound Sensor State: ");
        // Serial.println((PINB &(1 << PINB4)) ? 1 : 0);

        if (PINB &(1 << PINB4)) {
            Serial.print("Sound Detected\n");
        }
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

    }
    return 0;
}
ISR(PCINT0_vect){
    if(soundstate == wait_sound){
        Serial.print("Sound Detected in ISR\n");
        soundstate = debounce_sound; // Transition to debounce_press state
    }
    else if(soundstate == wait_no_sound){
        Serial.print("No Longer Detected\n");
        soundstate = debounce_no_sound; // Transition to debounce_release state
    }
}
