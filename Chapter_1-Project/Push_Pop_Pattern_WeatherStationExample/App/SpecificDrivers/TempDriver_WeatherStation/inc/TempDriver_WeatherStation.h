/*
 * TempDriver_WeatherStation.h
 *
 *  Created on: Mar 4, 2023
 *      Author: Abdu
 */

#ifndef APP_SPECIFICDRIVERS_TEMPDRIVER_WEATHERSTATION_INC_TEMPDRIVER_WEATHERSTATION_H_
#define APP_SPECIFICDRIVERS_TEMPDRIVER_WEATHERSTATION_INC_TEMPDRIVER_WEATHERSTATION_H_



#include "../../General_HAL/Sensor/Static/inc/Senosr.h"
#include "../../General_HAL/Sensor/Dynamic/inc/Sensor_Cfg.h"

#define TEMPERATURE_ID 2

static Sensor_Type *TempHandler = Null_Ptr;

void TempDriver_WeatherStation_Init(void);

int TempDriver_WeatherStation_Read(void);

void TempDriver_WeatherStation_Delete(void);






#endif /* APP_SPECIFICDRIVERS_TEMPDRIVER_WEATHERSTATION_INC_TEMPDRIVER_WEATHERSTATION_H_ */
