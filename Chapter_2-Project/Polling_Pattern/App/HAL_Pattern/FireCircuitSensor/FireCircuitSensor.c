/*
 * FireCircuitSensor.c
 *
 *  Created on: May 6, 2023
 *      Author: Abdu
 */


#include "FireCircuitSensor.h"
#include "../General_HAL/Sensor/Static/inc/Senosr.h"
#include <stdlib.h>


FireCircuitSensor_t* FireCircuitSensor_Create(uint8 Sensor_ID, Sensor_IntrfaceType SensorInterface){
    FireCircuitSensor_t* me;
    me = (FireCircuitSensor_t*)malloc(sizeof(FireCircuitSensor_t));
    if(me != Null_Ptr){
        me->its_Threshold = 0;
        me->theSensor = Sensor_Create(Sensor_ID, SensorInterface);
    }
    return me;
}

void FireCircuitSensor_setItsSensor(FireCircuitSensor_t* me, Sensor_Type* p_Sensor){
    me->theSensor = p_Sensor;
}

void FireCircuitSensor_setThreshold(FireCircuitSensor_t* me, uint8 threshold){
    me->its_Threshold = threshold;
}

uint16 FireCircuitSensor_getData(FireCircuitSensor_t* me){
    return( me->theSensor->GetValue(me->theSensor) );
}

uint16 FireCircuitSensor_getState(FireCircuitSensor_t* me){
    uint16 data;
    data = FireCircuitSensor_getData(me);
    if(data > me->its_Threshold){
        return 1;
    }else{
        return 0;
    }
}
