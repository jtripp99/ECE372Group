#include <Arduino.h>

void initPWM_Pins(){//table 17-2, we need fast PWM, mode 15 for variable frequency
    TCCR4A |= (1<<WGM40) | (1<<WGM41);
    TCCR4B |= (1<<WGM42) | (1<<WGM43); 
    // table 17-4, Fast PWM non-inverting mode
    TCCR4A &= ~(1<<COM4C0);
    TCCR4A |= (1<<COM4C1);
    //table 17-6, set prescaler to 1
    TCCR4B |= (1<<CS40);
    DDRH |= (1<<DDH5); //Set Pin 8 on board to output, which is OC4C, PORTH5, PWM}
    //OCR4C FOR DUTY CYCLE????????
    OCR4C=800;
    OCR4A=1600;
}

/*void IncFrequency(unsigned int frequency){
    OCR4A = (16000000 / frequency);
    OCR4AH = OCR4A >> 8;
    OCR4AL = OCR4A;
    OCR4AH = OCR4AH >> 1;
    OCR4AL = OCR4AL >> 1;
}*/

void PWM_On(){
    
    //OCR4A is for Top 
    //Serial.print("Turned On\n");
    DDRH |= (1<<DDH5);
   

}
void PWM_Off(){
    
    //OCR4A is for Top 
    //Serial.print("Turned Off\n");
    DDRH &= ~(1<<DDH5);
   

}