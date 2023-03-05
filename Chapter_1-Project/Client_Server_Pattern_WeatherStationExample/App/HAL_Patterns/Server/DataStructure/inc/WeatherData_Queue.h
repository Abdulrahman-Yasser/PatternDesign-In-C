/*
 * WeatherData_Queue.h
 *
 *  Created on: Mar 4, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_SERVER_WEATHERDATA_QUEUE_H_
#define APP_HAL_PATTERNS_SERVER_WEATHERDATA_QUEUE_H_

#include "../../General_Common/DataStructure/Queue/static/inc/Queue.h"

struct {
    Queue_uint8_DYNAMIC_Type* temp;
    Queue_uint8_DYNAMIC_Type* smoke;
    Queue_uint8_DYNAMIC_Type* light;
}WeatherData_Queue;

typedef struct {
    uint8 temp;
    uint8 smoke;
    uint8 light;
}WeatherData_Queue_Element_Type;


void WeatherData_Queue_Create(void);

void WeatherData_Queue_Push(WeatherData_Queue_Element_Type* element);

WeatherData_Queue_Element_Type* WeatherData_Queue_Pop(void);

uint8 WeatherData_Queue_GetSize(void);

uint8 WeatherData_Queue_IsEmpty(void);

uint8 WeatherData_Queue_IsFull(void);

void WeatherData_Queue_Destroy(void);

#endif /* APP_HAL_PATTERNS_SERVER_WEATHERDATA_QUEUE_H_ */
