/*
 * TimeMarkedData.h
 *
 *  Created on: May 4, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_SERVER_TIMEMARKEDDATA_TIMEMARKEDDATA_H_
#define APP_HAL_PATTERNS_SERVER_TIMEMARKEDDATA_TIMEMARKEDDATA_H_

#include "../../General_Common/DataStructure/Queue/static/inc/Queue.h"
#include "../../General_Common/Compiler.h"
#include "../../General_HAL/RTC_I2C_DS1307/Static/inc/RTC_I2C_DS1307_Types.h"

struct TimeMarkedData{
    RTC_DS1307_TimeFrame_Type time;
    RTC_DS1307_DateFrame_Type date;
    uint8 temperature_value;
};

void TimeMarkedData_Init(struct TimeMarkedData* me);



#endif /* APP_HAL_PATTERNS_SERVER_TIMEMARKEDDATA_TIMEMARKEDDATA_H_ */
