/*
 * WaterDriver_WeatherStation.c
 *
 *  Created on: Apr 18, 2023
 *      Author: Abdu
 */


#include "WaterDriver_WeatherStation.h"

void WaterDriver_WeatherStation_Init(void){
    WaterS_Handler = Sensor_Create(WATER_ID, Sensor_Interface_Digital);
}


int WaterDriver_WeatherStation_Read(void){
    int x;
    x = WaterS_Handler->GetValue(WaterS_Handler);
    return x;
}


void WaterDriver_WeatherStation_Delete(void){
    Sensor_Destroy(WaterS_Handler);
}


