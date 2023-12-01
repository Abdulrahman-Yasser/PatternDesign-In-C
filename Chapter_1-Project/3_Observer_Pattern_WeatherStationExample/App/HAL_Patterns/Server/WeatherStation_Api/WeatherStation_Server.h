/*
 * WeatherStation_Server.h
 *
 *  Created on: Mar 3, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_SERVER_WEATHERSTATION_WEATHERSTATION_SERVER_H_
#define APP_HAL_PATTERNS_SERVER_WEATHERSTATION_WEATHERSTATION_SERVER_H_

#include "../TMDQueue_with_Observable/TMDQueue_with_Observable.h"

#include "APP_WS_Layer/TemperatureDriver_WeatherStation/TempratureDriver_WeatherStation.h"

void WeatherStation_Publish(struct TMDQueue_with_Observable_s* me);

uint8 WeatherStation_IsEmpty(struct TMDQueue_with_Observable_s* me);


#endif /* APP_HAL_PATTERNS_SERVER_WEATHERSTATION_WEATHERSTATION_SERVER_H_ */
