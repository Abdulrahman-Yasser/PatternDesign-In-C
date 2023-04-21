/*
 * SmokeDriver_WeatherStation.c
 *
 *  Created on: Mar 3, 2023
 *      Author: Abdu
 */


#include <App/SpecificDrivers/SmokeDriver_WeatherStation/SmokeDriver_WeatherStation.h>


void SmokeDriver_WeatherStation_Init(void){
    SmokeHandler = Sensor_Create(SMOKE_ID, Sensor_Interface_Digital);
}


int SmokeDriver_WeatherStation_Read(void){
    int x;
    x = SmokeHandler->GetValue(SmokeHandler);
    return x;
}

void SmokeDriver_WeatherStation_Delete(void){
    Sensor_Destroy(SmokeHandler);
}

