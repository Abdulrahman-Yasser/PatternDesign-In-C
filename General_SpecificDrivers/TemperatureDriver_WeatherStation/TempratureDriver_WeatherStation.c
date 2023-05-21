/*
 * TempratureDriver_WeatherStation.c
 *
 *  Created on: Mar 3, 2023
 *      Author: Abdu
 */

#include "TempratureDriver_WeatherStation.h"

static Sensor_Type *TempHandler = Null_Ptr;


void TempDriver_WeatherStation_Init(void){
    TempHandler = Sensor_Create(TEMPERATURE_ID, Sensor_Interface_Digital);
}


uint32 TempDriver_WeatherStation_Read(void){
    uint32 x;
    x = TempHandler->GetValue(TempHandler);
    x = x * 330 / 4096;
    return x;
}


void TempDriver_WeatherStation_Delete(void){
    Sensor_Destroy(TempHandler);
}


