/*
 * LightDriver_WeatherStation.h
 *
 *  Created on: Mar 3, 2023
 *      Author: Abdu
 */

#ifndef APP_SPECIFICDRIVERS_LIGHTDRIVER_WEATHERSTATION_INC_LIGHTDRIVER_WEATHERSTATION_H_
#define APP_SPECIFICDRIVERS_LIGHTDRIVER_WEATHERSTATION_INC_LIGHTDRIVER_WEATHERSTATION_H_


#include "HAL_Layer/Sensor/Static/inc/Senosr.h"
#include "HAL_Layer/Sensor/Dynamic/inc/Sensor_Cfg.h"

#define LIGHT_ID 1

static Sensor_Type *LightHandler = Null_Ptr;

void LightDriver_WeatherStation_Init(void);

int LightDriver_WeatherStation_Read(void);

void LightDriver_WeatherStation_Delete(void);




#endif /* APP_SPECIFICDRIVERS_LIGHTDRIVER_WEATHERSTATION_INC_LIGHTDRIVER_WEATHERSTATION_H_ */
