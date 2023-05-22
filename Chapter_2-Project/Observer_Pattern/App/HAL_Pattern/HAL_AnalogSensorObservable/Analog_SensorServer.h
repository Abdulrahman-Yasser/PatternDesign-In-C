/*
 * Analog_SensorServer.h
 *
 *  Created on: May 22, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_HAL_ANALOGSENSOROBSERVABLE_ANALOG_SENSORSERVER_H_
#define APP_HAL_PATTERN_HAL_ANALOGSENSOROBSERVABLE_ANALOG_SENSORSERVER_H_


#include "../../General_Common/Platform_Types.h"

#include "../../General_Mcal/DIO/Dynamic/inc/DIO_Cfg.h"
#include "../../General_Mcal/ADC/Dynamic/inc/ADC_Cfg.h"

typedef uint32 SENSOR_READ_TYPE;


typedef struct Sensor_struct Sensor_Type;

struct Sensor_struct{
    uint8 Sensor_ID;
    SENSOR_READ_TYPE (*GetValue)(Sensor_Type* const me);
};



/*
 * ==================================================== ANALOG SENSOR ====================================================
 */

/* the data that i will need while reading the sensor */
typedef struct Sensor_Analog_Container Sensor_Analog_Container_Type;

struct Sensor_Analog_Container{
    ADC_Module_Num_Type ADC_Num;
    ADC_SS_NumType      sampleSequencer_Num;
};




#endif /* APP_HAL_PATTERN_HAL_ANALOGSENSOROBSERVABLE_ANALOG_SENSORSERVER_H_ */
