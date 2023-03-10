/*
 * TempratureDriver_WeatherStation.h
 *
 *  Created on: Mar 3, 2023
 *      Author: Abdu
 */

#ifndef APP_SPECIFICDRIVERS_TEMPERATUREDRIVER_WEATHERSTATION_INC_TEMPRATUREDRIVER_WEATHERSTATION_H_
#define APP_SPECIFICDRIVERS_TEMPERATUREDRIVER_WEATHERSTATION_INC_TEMPRATUREDRIVER_WEATHERSTATION_H_



#include "../../General_HAL/Sensor/Static/inc/Senosr.h"
#include "../../General_HAL/Sensor/Dynamic/inc/Sensor_Cfg.h"

#define TEMPERATURE_ID 1

static Sensor_Type *TempHandler = Null_Ptr;

void TempDriver_WeatherStation_Init(void);

int TempDriver_WeatherStation_Read(void);

void TempDriver_WeatherStation_Delete(void);




#endif /* APP_SPECIFICDRIVERS_TEMPERATUREDRIVER_WEATHERSTATION_INC_TEMPRATUREDRIVER_WEATHERSTATION_H_ */
