/*
 * LightDriver_WeatherStation.c
 *
 *  Created on: Mar 3, 2023
 *      Author: Abdu
 */

#include "LightDriver_WeatherStation.h"


void LightDriver_WeatherStation_Init(void){
    LightHandler = Sensor_Create(LIGHT_ID, Sensor_Interface_Digital);
}

int LightDriver_WeatherStation_Read(void){
    int x;
    x = LightHandler->GetValue(LightHandler);
    return x;
}

void LightDriver_WeatherStation_Delete(void){
    Sensor_Destroy(LightHandler);
}
