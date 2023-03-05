/*
 * WeatherStation_Server.h
 *
 *  Created on: Mar 3, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_SERVER_INC_WEATHERSTATION_SERVER_H_
#define APP_HAL_PATTERNS_SERVER_INC_WEATHERSTATION_SERVER_H_

#include "../DataStructure/inc/WeatherData_Queue.h"

#include "../../../SpecificDrivers/TempDriver_WeatherStation/inc/TempDriver_WeatherStation.h"
#include "../../../SpecificDrivers/LightDriver_WeatherStation/inc/LightDriver_WeatherStation.h"

#include "../../../SpecificDrivers/SmokeDriver_WeatherStation/inc/SmokeDriver_WeatherStation.h"



void WeatherStation_Push(void);

uint8 WeatherStation_IsEmpty(void);


#endif /* APP_HAL_PATTERNS_SERVER_INC_WEATHERSTATION_SERVER_H_ */
