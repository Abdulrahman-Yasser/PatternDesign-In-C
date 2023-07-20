/*
 * WeatherStationData.h
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_WEATHERSTATIONDATA_WEATHERSTATIONDATA_H_
#define APP_HAL_PATTERN_WEATHERSTATIONDATA_WEATHERSTATIONDATA_H_

#include "../General_Common/Std_Types.h"

enum weather_station_sensor_type {temperature_type, light_type, smoke_type, Unknown_type};

typedef struct {
    enum weather_station_sensor_type Sensor_type;
    uint8 value;
}WeatherStationData;

void WeatherStationData_Init(WeatherStationData* const me);
void WeatherStationData_CleanUp(WeatherStationData* const me);
WeatherStationData* WeatherStationData_Create(void);
void WeatherStationData_Destroy(WeatherStationData* const me);

#endif /* APP_HAL_PATTERN_WEATHERSTATIONDATA_WEATHERSTATIONDATA_H_ */
