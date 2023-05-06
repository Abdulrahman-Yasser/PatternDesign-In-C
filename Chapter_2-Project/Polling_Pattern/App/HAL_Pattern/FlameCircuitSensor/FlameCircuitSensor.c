///*
// * FlameCircuitSensor.c
// *
// *  Created on: May 6, 2023
// *      Author: Abdu
// */
//
//#include "FlameCircuitSensor.h"
//
//#include "../General_SpecificDrivers/LightDriver_WeatherStation/LightDriver_WeatherStation.h"
//
//typedef struct FlameCircuitSensor FlameCircuitSensor_t;
//struct FlameCircuitSensor{
//    uint8 dumy_var;
//};
//
//
//FlameCircuitSensor_t* FlameCircuitSensor_Create(void){
//    FlameCircuitSensor_t* me;
//    me = (FlameCircuitSensor_t*)malloc(sizeof(FlameCircuitSensor_t));
//    if(me != Null_Ptr){
//        return me;
//    }
//}
//
//uint16 Flame_getData(FlameCircuitSensor_t* me){
//    return(LightDriver_WeatherStation_Read() );
//}
//
//uint16 Flame_getState(FlameCircuitSensor_t* me){
//    if( LightDriver_WeatherStation_Read() > 35){
//        return 2;
//    }else if( LightDriver_WeatherStation_Read() > 30){
//        return 1;
//    }else if( LightDriver_WeatherStation_Read() < 30){
//        return 0;
//    }
//}
//
//
//
//
//
