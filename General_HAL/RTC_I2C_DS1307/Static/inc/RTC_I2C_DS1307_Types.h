/*
 * RTC_I2C_DS1307_Types.h
 *
 *  Created on: Mar 14, 2023
 *      Author: Abdu
 */

#ifndef RTC_I2C_DS1307_STATIC_INC_RTC_I2C_DS1307_TYPES_H_
#define RTC_I2C_DS1307_STATIC_INC_RTC_I2C_DS1307_TYPES_H_

#include "../../General_Common/Platform_Types.h"

#define RTC_DS1307_USED_24_MODE     0
#define RTC_DS1307_USED_12_MODE     1

typedef struct{
    uint8 seconds;
    uint8 minutes;
    uint8 hours;
}RTC_DS1307_TimeFrame_Type;

typedef enum{
    RTC_Month_JAN = 1, RTC_Month_FEB, RTC_Month_MAR, RTC_Month_APR, RTC_Month_MAY, RTC_Month_JUN, RTC_Month_JUL, RTC_Month_AUG,
    RTC_Month_SEP, RTC_Month_OCT, RTC_Month_NOV, RTC_Month_DEC
}RTC_Month_Type;

typedef enum{
    RTC_Days_SUNDAY = 1, RTC_Days_MONDAY, RTC_Days_TUESDAY, RTC_Days_WEDNESDAY,
    RTC_Days_THURSDAY, RTC_Days_FRIDAY, RTC_Days_SATERDAY
}RTC_Day_Type;

typedef struct{
    uint8 date;
    RTC_Day_Type day;
    RTC_Month_Type month;
    uint8 year;
}RTC_DS1307_DateFrame_Type;


#endif /* RTC_I2C_DS1307_STATIC_INC_RTC_I2C_DS1307_TYPES_H_ */
