/*
 * TimeMarkedData.h
 *
 *  Created on: Apr 18, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_SERVER_TIMEMARKEDDATA_TIMEMARKEDDATA_H_
#define APP_HAL_PATTERNS_SERVER_TIMEMARKEDDATA_TIMEMARKEDDATA_H_

#include "Common/Std_Types.h"

#include "HAL_Layer/RTC_I2C_DS1307/Static/inc/RTC_I2C_DS1307_Types.h"

struct TimeMarkedData{
    RTC_DS1307_TimeFrame_Type time;
    RTC_DS1307_DateFrame_Type date;
    uint8 temperature_value;
};

void TimeMarkedData_Init(struct TimeMarkedData* me);


#endif /* APP_HAL_PATTERNS_SERVER_TIMEMARKEDDATA_TIMEMARKEDDATA_H_ */
