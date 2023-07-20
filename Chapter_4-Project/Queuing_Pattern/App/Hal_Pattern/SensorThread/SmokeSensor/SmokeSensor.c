/*
 * LightSensor.c
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */

#include "SmokeDriver_WeatherStation/SmokeDriver_WeatherStation.h"
#include "SmokeSensor.h"


void SmokeSensorThread_Init(Smoke_sensor_thread* me){
    me->SmokeValue = 0;
    SmokeDriver_WeatherStation_Init();
}

uint8 SmokeSensorThread_Read(Smoke_sensor_thread* me){
    me->SmokeValue = SmokeDriver_WeatherStation_Read();
    return me->SmokeValue;
}

