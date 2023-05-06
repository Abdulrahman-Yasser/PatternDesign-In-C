///*
// * TemperatureCircuitSensor.c
// *
// *  Created on: May 6, 2023
// *      Author: Abdu
// */
//
//#include "TemperatureCircuitSensor.h"
//#include "../General_SpecificDrivers/TemperatureDriver_WeatherStation/TempratureDriver_WeatherStation.h"
//
//typedef struct TempCircuitSensor TempCircuitSensor_t;
//
//struct TempCircuitSensor{
//    uint8 dummy_var;
//};
//
//TempCircuitSensor_t* TempCircuitSensor_Create(void){
//    TempCircuitSensor_t* me;
//    me = (TempCircuitSensor_t*)malloc(sizeof(TempCircuitSensor_t) );
//    if(me != Null_Ptr){
//        return me;
//    }
//}
//
//uint16 Temp_getData(TempCircuitSensor_t* me){
//    return(TempDriver_WeatherStation_Read() );
//}
//
//uint16 Temp_getState(TempCircuitSensor_t* me){
//    if( TempDriver_WeatherStation_Read() > 35){
//        return 2;
//    }else if( TempDriver_WeatherStation_Read() > 30){
//        return 1;
//    }else if( TempDriver_WeatherStation_Read() < 30){
//        return 0;
//    }
//}
//
//
