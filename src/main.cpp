#include <Arduino.h>

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "i2c.h"
#include "rtc.h"
#include "led.h"
#include "soundsensor.h"
#include "timer.h"

typedef enum sound_states {
    NORMAL, ISTOOLOUD
} sound_stateType;
tilt_stateType tiltState = NORMAL;

typedef enum button_states {
  wait_press, debounce_press, wait_release, debounce_release
} stateType;
stateType state = wait_press;

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}