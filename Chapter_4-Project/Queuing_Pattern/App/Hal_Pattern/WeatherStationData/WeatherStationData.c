/*
 * WeatherStationData.c
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */


#include "WeatherStationData.h"


void WeatherStationData_Init(WeatherStationData* const me){
    me->value = 0;
    me->Sensor_type = Unknown_type;
}


void WeatherStationData_CleanUp(WeatherStationData* const me){

}

WeatherStationData* WeatherStationData_Create(void){
    WeatherStationData* me = (WeatherStationData*) malloc(sizeof(WeatherStationData));
    if(me != Null_Ptr){
        WeatherStationData_Init(me);
    }
    return me;
}

void WeatherStationData_Destroy(WeatherStationData* const me){
    if(me != Null_Ptr){
        WeatherStationData_CleanUp(me);
    }
    free(me);
}
