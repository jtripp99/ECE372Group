#ifndef PWM_H
#define PWM_H

void initPWM_Pins();
void IncFrequency(unsigned int frequency);
void changeDutyCycle(float voltageSignal);

#endif