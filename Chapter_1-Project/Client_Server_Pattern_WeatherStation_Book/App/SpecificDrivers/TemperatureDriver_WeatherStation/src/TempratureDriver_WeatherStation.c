/*
 * TempratureDriver_WeatherStation.c
 *
 *  Created on: Mar 3, 2023
 *      Author: Abdu
 */

#include "../inc/TempratureDriver_WeatherStation.h"

#include "../General_Common/CPU_resources.h"


void TempDriver_WeatherStation_Init(void){
    TempHandler = Sensor_Create(TEMPERATURE_ID, Sensor_Interface_Analog);
}


int TempDriver_WeatherStation_Read(void){
    float x;
    x = (float)TempHandler->GetValue(TempHandler);
    x = (float)(100 * INTERNAL_VOLTAGE_SOURCE / 4096) * x;
    return (int)x;
}


void TempDriver_WeatherStation_Delete(void){
    Sensor_Destroy(TempHandler);
}


