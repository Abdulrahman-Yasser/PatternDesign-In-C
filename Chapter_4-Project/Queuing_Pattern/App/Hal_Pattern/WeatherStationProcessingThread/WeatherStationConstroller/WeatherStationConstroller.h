/*
 * WeatherStationConstroller.h
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_WEATHERSTATIONPROCESSINGTHREAD_WEATHERSTATIONCONSTROLLER_WEATHERSTATIONCONSTROLLER_H_
#define APP_HAL_PATTERN_WEATHERSTATIONPROCESSINGTHREAD_WEATHERSTATIONCONSTROLLER_WEATHERSTATIONCONSTROLLER_H_


#include "../../WeatherStationData/WeatherStationData.h"
#include "../WeatherStationDisplay/WeatherStationDisplay.h"

struct WeatherStationDisplay;

typedef struct WeatherStationController WeatherStationController;

struct WeatherStationController {
    struct WeatherStationDisplay* itsWeatherStationDisplay;
};

/* Constructors and destructors:*/

void WeatherStationController_Init(WeatherStationController* const me);

void WeatherStationController_Cleanup(WeatherStationController* const me);

/* Operations */

void WeatherStationController_handleWeatherStationData(WeatherStationController* const me, WeatherStationData* gPtr);

struct WeatherStationDisplay* WeatherStationController_getItsWeatherStationDisplay(const WeatherStationController* const me);

void WeatherStationController_setItsWeatherStationDisplay(WeatherStationController* const me,struct WeatherStationDisplay* p_WeatherStationDisplay);

WeatherStationController * WeatherStationController_Create(void);

void WeatherStationController_Destroy(WeatherStationController* const me);



#endif /* APP_HAL_PATTERN_WEATHERSTATIONPROCESSINGTHREAD_WEATHERSTATIONCONSTROLLER_WEATHERSTATIONCONSTROLLER_H_ */
