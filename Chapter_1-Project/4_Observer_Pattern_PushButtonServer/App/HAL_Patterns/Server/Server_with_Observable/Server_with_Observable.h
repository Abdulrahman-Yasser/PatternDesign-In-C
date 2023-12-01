/*
 * WeatherData_Queue.h
 *
 *  Created on: Mar 4, 2023
 *      Author: Abdu
 */

/* The Sever */

#ifndef APP_HAL_PATTERNS_SERVER_WEATHERDATA_QUEUE_H_
#define APP_HAL_PATTERNS_SERVER_WEATHERDATA_QUEUE_H_

#include "Common/Std_Types.h"
#include "../../Observer/Observer.h"
#include "../../Observable/Observable.h"

struct Server_with_Observable_s;

void Server_with_Observable_Init(struct Server_with_Observable_s* me);
struct Server_with_Observable_s* get_my_server(void);

uint8 Server_with_Observable_Pop(struct Server_with_Observable_s* me);

void Server_with_Observable_Push(struct Server_with_Observable_s* me);

Observable_Type* Server_with_Observable_GetObservable(struct Server_with_Observable_s* me);

uint8 Server_with_Observable_IsEmpty(struct Server_with_Observable_s* me);

uint8 Server_with_Observable_IsFull(struct Server_with_Observable_s* me);

void Server_with_Observable_Destroy(struct Server_with_Observable_s* me);

Observable_Type* Server_with_Observable_GetObservable(struct Server_with_Observable_s* me);

void Server_with_Observable_UnSubscribe(struct Server_with_Observable_s* me, Observer *o);

void Server_with_Observable_Subscribe(struct Server_with_Observable_s* me, Observer *o);


#endif /* APP_HAL_PATTERNS_SERVER_WEATHERDATA_QUEUE_H_ */
