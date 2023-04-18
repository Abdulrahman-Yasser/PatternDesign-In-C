/*
 * TimeMarkedData.h
 *
 *  Created on: Apr 18, 2023
 *      Author: Abdu
 */

#ifndef APP_TIMEMARKEDDATA_TIMEMARKEDDATA_H_
#define APP_TIMEMARKEDDATA_TIMEMARKEDDATA_H_

#include "../General_Common/Std_Types.h"

#include "../General_HAL/RTC_I2C_DS1307/Static/inc/RTC_I2C_DS1307_Types.h"

struct TimeMarkedData{
    RTC_DS1307_TimeFrame_Type time;
    RTC_DS1307_DateFrame_Type date;
    uint8 smoke_value;
    uint8 temperature_value;
    uint8 light_value;
};

void TimeMarkedData_Init(struct TimeMarkedData* me);


#endif /* APP_TIMEMARKEDDATA_TIMEMARKEDDATA_H_ */
