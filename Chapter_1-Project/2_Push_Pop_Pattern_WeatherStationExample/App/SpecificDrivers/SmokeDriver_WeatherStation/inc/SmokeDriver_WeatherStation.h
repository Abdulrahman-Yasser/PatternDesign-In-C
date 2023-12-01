/*
 * SmokeDriver_WeatherStation.h
 *
 *  Created on: Mar 3, 2023
 *      Author: Abdu
 */

#ifndef APP_SPECIFICDRIVERS_SMOKEDRIVER_WEATHERSTATION_INC_SMOKEDRIVER_WEATHERSTATION_H_
#define APP_SPECIFICDRIVERS_SMOKEDRIVER_WEATHERSTATION_INC_SMOKEDRIVER_WEATHERSTATION_H_

#include "HAL_Layer/Sensor/Static/inc/Senosr.h"
#include "HAL_Layer/Sensor/Dynamic/inc/Sensor_Cfg.h"

#define SMOKE_ID 0

static Sensor_Type *SmokeHandler = Null_Ptr;

void SmokeDriver_WeatherStation_Init(void);

int SmokeDriver_WeatherStation_Read(void);

void SmokeDriver_WeatherStation_Delete(void);



#endif /* APP_SPECIFICDRIVERS_SMOKEDRIVER_WEATHERSTATION_INC_SMOKEDRIVER_WEATHERSTATION_H_ */
