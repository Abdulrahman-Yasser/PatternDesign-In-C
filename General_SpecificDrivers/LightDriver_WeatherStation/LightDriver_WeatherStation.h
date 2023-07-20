/*
 * LightDriver_WeatherStation.h
 *
 *  Created on: Mar 3, 2023
 *      Author: Abdu
 */

#ifndef APP_SPECIFICDRIVERS_LIGHTDRIVER_WEATHERSTATION_INC_LIGHTDRIVER_WEATHERSTATION_H_
#define APP_SPECIFICDRIVERS_LIGHTDRIVER_WEATHERSTATION_INC_LIGHTDRIVER_WEATHERSTATION_H_


#include "../General_HAL/Sensor/Static/inc/Senosr.h"
#include "../General_HAL/Sensor/Dynamic/inc/Sensor_Cfg.h"


static Sensor_Type *LightHandler = Null_Ptr;

void LightDriver_WeatherStation_Init(void);

int LightDriver_WeatherStation_Read(void);

void LightDriver_WeatherStation_Delete(void);




#endif /* APP_SPECIFICDRIVERS_LIGHTDRIVER_WEATHERSTATION_INC_LIGHTDRIVER_WEATHERSTATION_H_ */
