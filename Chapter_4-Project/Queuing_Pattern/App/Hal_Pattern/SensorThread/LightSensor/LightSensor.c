/*
 * LightSensor.c
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */


#include "LightSensor.h"
#include "../General_SpecificDrivers/LightDriver_WeatherStation/LightDriver_WeatherStation.h"


void LightSensorThread_Init(Light_sensor_thread* me){
    LightDriver_WeatherStation_Init();
    me->LightValue = 0;
}
uint8 LightSensorThread_Read(Light_sensor_thread* me){
    me->LightValue = LightDriver_WeatherStation_Read();
    return me->LightValue;
}
