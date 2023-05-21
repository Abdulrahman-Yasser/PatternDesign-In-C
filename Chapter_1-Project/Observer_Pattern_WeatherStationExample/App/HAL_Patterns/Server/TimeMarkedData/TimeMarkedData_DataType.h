/*
 * TimeMarkedData_DataType.h
 *
 *  Created on: May 20, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_SERVER_TIMEMARKEDDATA_TIMEMARKEDDATA_DATATYPE_H_
#define APP_HAL_PATTERNS_SERVER_TIMEMARKEDDATA_TIMEMARKEDDATA_DATATYPE_H_

#include "../General_HAL/RTC_I2C_DS1307/Static/inc/RTC_I2C_DS1307_Types.h"
#include "../General_Common/Std_Types.h"

struct TimeMarkedData{
    RTC_DS1307_TimeFrame_Type time;
    RTC_DS1307_DateFrame_Type date;
    uint8 temperature_value;
};



#endif /* APP_HAL_PATTERNS_SERVER_TIMEMARKEDDATA_TIMEMARKEDDATA_DATATYPE_H_ */
