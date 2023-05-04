/*
 * WeatherData_Queue.h
 *
 *  Created on: Mar 4, 2023
 *      Author: Abdu
 */

/* The Sever */

#ifndef APP_HAL_PATTERNS_SERVER_WEATHERDATA_QUEUE_H_
#define APP_HAL_PATTERNS_SERVER_WEATHERDATA_QUEUE_H_

#include "../../General_Common/DataStructure/Queue/static/inc/Queue.h"
#include "../../General_Common/Compiler.h"
#include "../../General_HAL/RTC_I2C_DS1307/Static/inc/RTC_I2C_DS1307_Types.h"



void WeatherData_Queue_Create(void);

void WeatherData_Queue_Push(struct TimeMarkedData* element);

struct TimeMarkedData* weatherData_Queue_Pop(void);

uint8 WeatherData_Queue_GetSize(void);

uint8 WeatherData_Queue_IsEmpty(void);

uint8 WeatherData_Queue_IsFull(void);

void WeatherData_Queue_Destroy(void);

#endif /* APP_HAL_PATTERNS_SERVER_WEATHERDATA_QUEUE_H_ */
