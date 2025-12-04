#include <avr/io.h>
#include "i2c.h"
#include "rtc.h"
#include <Arduino.h>

//DS1307 I2C address
#define RTC_ADDRESS 0x68

//DS1307 register addresses
#define RTC_REG_SECONDS 0x00
#define RTC_REG_MINUTES 0x01
#define RTC_REG_HOURS   0x02

//convert decimal to BCD format
static int decToBcd(int val) {
    return ((val / 10) << 4 | (val % 10));
}

//convert BCD to decimal
static int bcdToDec(int val) {
    return ((val >> 4) * 10 + (val & 0x0F));
}

//initialize rtc
void rtc_init() {

    //read seconds register
    //NOTE: this requires the i2c read_from fn to return data rather than void
    int seconds = Read_from(RTC_ADDRESS, RTC_REG_SECONDS);

    //clear CH (clock halt) bit (bit 7) to enable the rtc
    seconds &= ~(1 << 7);

    //write seconds register to the rtc
    StartI2C_Trans(RTC_ADDRESS);
    Write(RTC_REG_SECONDS);
    Write(seconds);
    StopI2C_Trans();
}

void rtc_setTime(int hour, int minute, int second) {

    //error testing
    if (second < 0 || second > 59) {
        Serial.print("seconds out of range");
    }
    if (minute < 0 || minute > 59) {
        Serial.print("minutes out of range");
    }
    if (hour < 0 || hour > 23) {
        Serial.print("hour out of range");
    }

    int second_bcd = decToBcd(second) & 0x7F; //clear CH bit from value
    int minute_bcd = decToBcd(minute) & 0x7F; //clear CH bit
    int hour_bcd = decToBcd(hour) & 0x3F; //need bit 6 = 0 to set 24 hour mode

    //start writing to seconds register, DS1307 increments automatically
    StartI2C_Trans(RTC_ADDRESS);
    Write(RTC_REG_SECONDS);
    Write(second_bcd);
    Write(minute_bcd);
    Write(hour_bcd);
    StopI2C_Trans();

}

void rtc_getTime(int* hour, int* minute, int* second) {
    
    //read (BCD) values from rtc register
    int sec = Read_from(RTC_ADDRESS, RTC_REG_SECONDS) & 0x7F; //clear CH bit
    int min = Read_from(RTC_ADDRESS, RTC_REG_MINUTES) & 0x7F;
    int hr = Read_from(RTC_ADDRESS, RTC_REG_HOURS) & 0x3F; //set 24h format

    //convert values to decimal and update variables
    *second = bcdToDec(sec);
    *minute = bcdToDec(min);
    *hour = bcdToDec(hr);
}