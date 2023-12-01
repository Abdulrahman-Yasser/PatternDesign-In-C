/*
 * TimeMarkedData.h
 *
 *  Created on: May 4, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_SERVER_TIMEMARKEDDATA_TIMEMARKEDDATA_H_
#define APP_HAL_PATTERNS_SERVER_TIMEMARKEDDATA_TIMEMARKEDDATA_H_

#include "Common/DataStructure/Queue/static/inc/Queue.h"
#include "Common/Std_Types.h"
#include "HAL_Layer/RTC_I2C_DS1307/Static/inc/RTC_I2C_DS1307_Types.h"
#include "TimeMarkedData_DataType.h"

void TimeMarkedData_Init(struct TimeMarkedData* me);



#endif /* APP_HAL_PATTERNS_SERVER_TIMEMARKEDDATA_TIMEMARKEDDATA_H_ */
