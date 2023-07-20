/*
 * WeatherStationDisplay.h
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_WEATHERSTATIONPROCESSINGTHREAD_WEATHERSTATIONDISPLAY_WEATHERSTATIONDISPLAY_H_
#define APP_HAL_PATTERN_WEATHERSTATIONPROCESSINGTHREAD_WEATHERSTATIONDISPLAY_WEATHERSTATIONDISPLAY_H_

#include "../../WeatherStationData/WeatherStationData.h"
#include "../General_Common/Std_Types.h"
#include "../General_HAL/LCD/Static/inc/LCD_Types.h"

typedef struct WeatherStationDisplay WeatherStationDisplay;

struct WeatherStationDisplay {
    LCD_Handler_Type *my_lcd;
};


/* Constructors and destructors:*/

void WeatherStationDisplay_Init(WeatherStationDisplay* const me);

void WeatherStationDisplay_Cleanup(WeatherStationDisplay* const me);

/* Operations */

void WeatherStationDisplay_printWeatherStationData(WeatherStationDisplay* const me, enum weather_station_sensor_type sensor_type, uint8 value);

void WeatherStationDisplay_SetItsLCD(WeatherStationDisplay* me, LCD_Handler_Type* the_lcd);

WeatherStationDisplay* WeatherStationDisplay_Create(void);

void WeatherStationDisplay_Destroy(WeatherStationDisplay* const me);

#endif /* APP_HAL_PATTERN_WEATHERSTATIONPROCESSINGTHREAD_WEATHERSTATIONDISPLAY_WEATHERSTATIONDISPLAY_H_ */
