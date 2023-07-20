/*
 * RTC_I2C_DS3231_Types.h
 *
 *  Created on: Mar 14, 2023
 *      Author: Abdu
 */

#ifndef RTC_I2C_DS3231_STATIC_INC_RTC_I2C_DS3231_TYPES_H_
#define RTC_I2C_DS3231_STATIC_INC_RTC_I2C_DS3231_TYPES_H_

#include "../General_Common/Platform_Types.h"

typedef struct{
    uint8 seconds;
    uint8 minutes;
    uint8 hours;
    uint8 day_date;
}RTC_DS3231_TimeAlarmFrame;


typedef struct{
    uint8 seconds;
    uint8 minutes;
    uint8 hours;
    uint8 day;
    uint8 date;
    uint8 month;
    uint8 year;
}RTC_DS3231_TimeFrame;

typedef enum{
    RTC_DS3231_Alarm_Once_Per_Second = 15,
    RTC_DS3231_Alarm_Once_Per_Minute = 14,
    RTC_DS3231_Alarm_Once_Per_Hour = 12,
    RTC_DS3231_Alarm_Once_Per_Day = 8,
    RTC_DS3231_Alarm_Once_Per_week = 16,
    RTC_DS3231_Alarm_Once_Per_Month = 0
}RTC_DS3231_Alarm_Type;



#endif /* RTC_I2C_DS3231_STATIC_INC_RTC_I2C_DS3231_TYPES_H_ */
