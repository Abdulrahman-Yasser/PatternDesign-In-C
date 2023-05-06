/*
 * FireCircuitSensor.h
 *
 *  Created on: May 6, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_FIRECIRCUITSENSOR_FIRECIRCUITSENSOR_H_
#define APP_HAL_PATTERN_FIRECIRCUITSENSOR_FIRECIRCUITSENSOR_H_

#include "../General_Common/Std_Types.h"
#include "../General_HAL/Sensor/Static/inc/Senosr.h"
typedef struct FireCircuitSensor FireCircuitSensor_t;

struct FireCircuitSensor{
    Sensor_Type *theSensor;
    uint8 its_Threshold;
};

FireCircuitSensor_t* FireCircuitSensor_Create(uint8 Sensor_ID, Sensor_IntrfaceType SensorInterface);

void FireCircuitSensor_setItsSensor(FireCircuitSensor_t* me, Sensor_Type* p_Sensor);

void FireCircuitSensor_setThreshold(FireCircuitSensor_t* me, uint8 threshold);

uint16 FireCircuitSensor_getData(FireCircuitSensor_t* me);

uint16 FireCircuitSensor_getState(FireCircuitSensor_t* me);

#endif /* APP_HAL_PATTERN_FIRECIRCUITSENSOR_FIRECIRCUITSENSOR_H_ */
