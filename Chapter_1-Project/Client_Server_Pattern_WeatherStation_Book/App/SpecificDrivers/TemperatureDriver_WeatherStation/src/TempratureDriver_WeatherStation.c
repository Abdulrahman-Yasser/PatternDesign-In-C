/*
 * TempratureDriver_WeatherStation.c
 *
 *  Created on: Mar 3, 2023
 *      Author: Abdu
 */

#include "../inc/TempratureDriver_WeatherStation.h"




void TempDriver_WeatherStation_Init(void){
    TempHandler = Sensor_Create(TEMPERATURE_ID, Sensor_Interface_Digital);
}


int TempDriver_WeatherStation_Read(void){
    int x;
    x = TempHandler->GetValue(TempHandler);
    return x;
}


void TempDriver_WeatherStation_Delete(void){
    Sensor_Destroy(TempHandler);
}


