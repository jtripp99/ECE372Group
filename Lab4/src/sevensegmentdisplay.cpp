#include "sevensegmentdisplay.h"


//initialize 7 seg display
void init7Seg() {

    DDRC |= 0xFF;  //initialize pins C0-C7 to output
    PORTC |= 0x00; //set all pins to zero
}

void setNum(int num) {
    //set correct pins on 7 seg display for each number
    switch (num) {
        case 0:
            PORTC = 0x3F;
            break;
        case 1:
            PORTC = 0x06;
            break;
        case 2:
            PORTC = 0x5B;
            break;
        case 3:
            PORTC = 0x4F;
            break;
        case 4:
            PORTC = 0x66;
            break;
        case 5:
            PORTC = 0x6D;
            break;
        case 6:
            PORTC = 0x7D;
            break;
        case 7:
            PORTC = 0x07;
            break;
        case 8:
            PORTC = 0x7F;
            break;
        case 9:
            PORTC = 0x6F;
            break;
        default:
            PORTC = 0x00;
            break;
    }
}