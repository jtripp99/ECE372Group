#ifndef RTC_H
#define RTC_H


//initialize DS1307 rtc
void rtc_init();

//set time (24h format)
void rtc_setTime(int hour, int minute, int second);

//get time (24h format)
void rtc_getTime(int* hour, int* minute, int* second);

#endif