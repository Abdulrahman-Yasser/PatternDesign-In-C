/*
 * RTC_I2C_DS1307_Types.h
 *
 *  Created on: Mar 14, 2023
 *      Author: Abdu
 */

#ifndef RTC_I2C_DS1307_STATIC_INC_RTC_I2C_DS1307_TYPES_H_
#define RTC_I2C_DS1307_STATIC_INC_RTC_I2C_DS1307_TYPES_H_

#include "../General_Common/Platform_Types.h"

#define RTC_DS1307_USED_24_MODE     0
#define RTC_DS1307_USED_12_MODE     1

typedef struct{
    uint8 seconds;
    uint8 minutes;
    uint8 hours;
    uint8 AM_PM;
}RTC_DS1307_TimeFrame_Type;


typedef struct{
    uint8 date;
    uint8 day;
    uint8 month;
    uint8 year;
}RTC_DS1307_DateFrame_Type;


#endif /* RTC_I2C_DS1307_STATIC_INC_RTC_I2C_DS1307_TYPES_H_ */
