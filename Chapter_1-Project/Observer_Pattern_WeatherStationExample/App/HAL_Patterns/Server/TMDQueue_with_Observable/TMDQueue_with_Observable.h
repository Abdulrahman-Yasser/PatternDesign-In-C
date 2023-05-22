/*
 * WeatherData_Queue.h
 *
 *  Created on: Mar 4, 2023
 *      Author: Abdu
 */

/* The Sever */

#ifndef APP_HAL_PATTERNS_SERVER_WEATHERDATA_QUEUE_H_
#define APP_HAL_PATTERNS_SERVER_WEATHERDATA_QUEUE_H_

#include "../../General_Common/Std_Types.h"
#include "../../Observer/Observer.h"

struct TimeMarkedData;
struct TMDQueue_with_Observable_s;

struct TMDQueue_with_Observable_s* TMDQueue_with_Observable_GetHandler(void);
void TMDQueue_with_Observable_Init(struct TMDQueue_with_Observable_s* me);

struct TimeMarkedData TMDQueue_with_Observable_Pop(struct TMDQueue_with_Observable_s* me);

void TMDQueue_with_Observable_Push(struct TMDQueue_with_Observable_s* me, struct TimeMarkedData* tmd);


uint8 TMDQueue_with_Observable_IsEmpty(struct TMDQueue_with_Observable_s* me);

uint8 TMDQueue_with_Observable_IsFull(struct TMDQueue_with_Observable_s* me);

void TMDQueue_with_Observable_Destroy(struct TMDQueue_with_Observable_s* me);

void TMDQueue_with_Observable_UnSubscribe(struct TMDQueue_with_Observable_s* me, Observer *o);
void TMDQueue_with_Observable_Subscribe(struct TMDQueue_with_Observable_s* me, Observer *o);


#endif /* APP_HAL_PATTERNS_SERVER_WEATHERDATA_QUEUE_H_ */
