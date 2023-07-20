/*
 * SensorThread.c
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */


#include "SensorThread.h"
#include "../WeatherStationDataQueue/WeatherStationDataQueue.h"
#include <stdlib.h>
#include <stdio.h>

SensorThread* SensorThread_create(void){
    SensorThread* me = (SensorThread*)malloc(sizeof(SensorThread));
    if(me != Null_Ptr){
        SensorThread_init(me);
    }
    return me;
}


void SensorThread_init(SensorThread* const me){
    LightSensorThread_Init(&me->my_light);
    SmokeSensorThread_Init(&me->my_smoke);
    TempSensorThread_Init(&me->my_temp);
}


void SensorThread_setItsDataQueue(SensorThread* me, WeatherStationDataQueue* const dataQueuePtr){
    if(dataQueuePtr != Null_Ptr){
        me->my_data_queue = dataQueuePtr;
    }
}


void SensorThread_updateData(SensorThread* const me){
    WeatherStationData my_data;

    LightSensorThread_Read(&me->my_light);
    SmokeSensorThread_Read(&me->my_smoke);
    TempSensorThread_Read(&me->my_temp);

    if(rand() % 3){
        my_data.Sensor_type = light_type;
        my_data.value = me->my_light.LightValue;
        WeatherStationDataQueue_insert(me->my_data_queue, my_data);
    }

    if(rand() % 3){
        my_data.Sensor_type = smoke_type;
        my_data.value = me->my_smoke.SmokeValue;
        WeatherStationDataQueue_insert(me->my_data_queue, my_data);
    }
    if(rand() % 3){
        my_data.Sensor_type = temperature_type;
        my_data.value = me->my_temp.TempValue;
        WeatherStationDataQueue_insert(me->my_data_queue, my_data);
    }
}
