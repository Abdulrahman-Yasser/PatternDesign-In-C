/*
 * WaterDriver_WeatherStation.h
 *
 *  Created on: Apr 18, 2023
 *      Author: Abdu
 */

#ifndef APP_SPECIFICDRIVERS_WATERDRIVER_WEATHERSTATION_INC_WATERDRIVER_WEATHERSTATION_H_
#define APP_SPECIFICDRIVERS_WATERDRIVER_WEATHERSTATION_INC_WATERDRIVER_WEATHERSTATION_H_


#include "HAL_Layer/Sensor/Static/inc/Senosr.h"
#include "HAL_Layer/Sensor/Dynamic/inc/Sensor_Cfg.h"


static Sensor_Type *WaterS_Handler = Null_Ptr;

void WaterDriver_WeatherStation_Init(void);

int WaterDriver_WeatherStation_Read(void);

void WaterDriver_WeatherStation_Delete(void);




#endif /* APP_SPECIFICDRIVERS_TEMPERATUREDRIVER_WEATHERSTATION_INC_TEMPRATUREDRIVER_WEATHERSTATION_H_ */

