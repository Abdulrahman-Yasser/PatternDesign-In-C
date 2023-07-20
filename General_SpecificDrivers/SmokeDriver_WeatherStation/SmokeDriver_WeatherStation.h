/*
 * SmokeDriver_WeatherStation.h
 *
 *  Created on: Mar 3, 2023
 *      Author: Abdu
 */

#ifndef APP_SPECIFICDRIVERS_SMOKEDRIVER_WEATHERSTATION_SMOKEDRIVER_WEATHERSTATION_H_
#define APP_SPECIFICDRIVERS_SMOKEDRIVER_WEATHERSTATION_SMOKEDRIVER_WEATHERSTATION_H_

#include "../General_HAL/Sensor/Static/inc/Senosr.h"
#include "../General_HAL/Sensor/Dynamic/inc/Sensor_Cfg.h"

static Sensor_Type *SmokeHandler = Null_Ptr;

void SmokeDriver_WeatherStation_Init(void);

int SmokeDriver_WeatherStation_Read(void);

void SmokeDriver_WeatherStation_Delete(void);



#endif /* APP_SPECIFICDRIVERS_SMOKEDRIVER_WEATHERSTATION_SMOKEDRIVER_WEATHERSTATION_H_ */
