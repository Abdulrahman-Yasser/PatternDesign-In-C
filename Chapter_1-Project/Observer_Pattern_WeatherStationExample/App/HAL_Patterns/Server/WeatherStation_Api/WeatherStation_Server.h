/*
 * WeatherStation_Server.h
 *
 *  Created on: Mar 3, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_SERVER_WEATHERSTATION_WEATHERSTATION_SERVER_H_
#define APP_HAL_PATTERNS_SERVER_WEATHERSTATION_WEATHERSTATION_SERVER_H_

#include "../TMDQueue_with_Observable/TMDQueue_with_Observable.h"

#include "../General_SpecificDrivers/TemperatureDriver_WeatherStation/TempratureDriver_WeatherStation.h"

void WeatherStation_Publish(void);

uint8 WeatherStation_IsEmpty(void);


#endif /* APP_HAL_PATTERNS_SERVER_WEATHERSTATION_WEATHERSTATION_SERVER_H_ */
