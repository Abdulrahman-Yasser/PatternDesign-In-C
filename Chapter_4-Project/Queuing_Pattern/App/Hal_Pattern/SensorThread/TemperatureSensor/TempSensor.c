/*
 * LightSensor.c
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */


#include "TempSensor.h"
#include "TemperatureDriver_WeatherStation/TempratureDriver_WeatherStation.h"



void TempSensorThread_Init(Temp_sensor_thread* me){
    TempDriver_WeatherStation_Init();
    me->TempValue = 0;
}

uint8 TempSensorThread_Read(Temp_sensor_thread* me){
    me->TempValue = TempDriver_WeatherStation_Read();
    return me->TempValue;
}
