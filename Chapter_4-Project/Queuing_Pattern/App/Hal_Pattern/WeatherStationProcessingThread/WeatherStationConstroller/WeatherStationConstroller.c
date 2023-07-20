/*
 * WeatherStationConstroller.c
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */

#include "WeatherStationConstroller.h"

void WeatherStationController_Init(WeatherStationController* const me){
    me->itsWeatherStationDisplay = Null_Ptr;
}

void WeatherStationController_Cleanup(WeatherStationController* const me){

}

/* Operations */

void WeatherStationController_handleWeatherStationData(WeatherStationController* const me, WeatherStationData* gPtr){
    WeatherStationDisplay_printWeatherStationData(me->itsWeatherStationDisplay, gPtr->Sensor_type, gPtr->value);
}

struct WeatherStationDisplay* WeatherStationController_getItsWeatherStationDisplay(const WeatherStationController* const me){
    return me->itsWeatherStationDisplay;
}

void WeatherStationController_setItsWeatherStationDisplay(WeatherStationController* const me,struct WeatherStationDisplay* p_WeatherStationDisplay){
    me->itsWeatherStationDisplay = p_WeatherStationDisplay;
}

WeatherStationController* WeatherStationController_Create(void){
    WeatherStationController* me;
    me = (WeatherStationController*)malloc(sizeof(WeatherStationController));
    if(me != Null_Ptr){
        WeatherStationController_Init(me);
    }
    return me;
}

void WeatherStationController_Destroy(WeatherStationController* const me){
    if(me != Null_Ptr){
        WeatherStationController_Cleanup(me);
    }
    free(me);
}
