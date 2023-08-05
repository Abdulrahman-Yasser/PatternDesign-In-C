/*
 * SmokeDriver_WeatherStation.c
 *
 *  Created on: Mar 3, 2023
 *      Author: Abdu
 */


#include "SmokeDriver_WeatherStation.h"
#include "../General_Mcal/ADC/Dynamic/inc/ADC_Cfg.h"

void SmokeDriver_WeatherStation_Init(void){
    SmokeHandler = Sensor_Create(SMOKE_ID, Sensor_Interface_Analog);
}


int SmokeDriver_WeatherStation_Read(void){
    int x;
    x = SmokeHandler->GetValue(SmokeHandler);
    return (x * 500) / 4096;
}

void SmokeDriver_WeatherStation_Delete(void){
    Sensor_Destroy(SmokeHandler);
}

