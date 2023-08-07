/*
 * Sendor_Types.h
 *
 *  Created on: Nov 25, 2022
 *      Author: abduy
 */

#ifndef HAL_SENSOR_STATIC_INC_SENSOR_TYPES_H_
#define HAL_SENSOR_STATIC_INC_SENSOR_TYPES_H_

#include "../General_Common/Platform_Types.h"

#include "../General_Mcal/DIO/Dynamic/inc/DIO_Cfg.h"
#include "../General_Mcal/ADC/Dynamic/inc/ADC_Cfg.h"

typedef uint32 SENSOR_READ_TYPE;

typedef enum{
    Sensor_Interface_Analog, Sensor_Interface_Digital
}Sensor_IntrfaceType;



typedef struct Sensor_struct Sensor_Type;

struct Sensor_struct{
    uint8 Sensor_ID;
    Sensor_IntrfaceType SensorInterface;
    SENSOR_READ_TYPE (*GetValue)(Sensor_Type* const me);
};


/*
 * ==================================================== DIGITAL SENSOR ====================================================
 */

typedef DIO_ChannelType Sensor_Pins_Type;

typedef struct Sensor_Digital_Container Sensor_Digital_Container_Type;

struct Sensor_Digital_Container{
    Sensor_Pins_Type Sensor_Data_Pins;
};


/*
 * ==================================================== ANALOG SENSOR ====================================================
 */

/* the data that i will need while reading the sensor */
typedef struct Sensor_Analog_Container Sensor_Analog_Container_Type;

struct Sensor_Analog_Container{
    ADC_Module_Num_Type ADC_Num;
    ADC_SS_NumType      sampleSequencer_Num;
    ADC_Channel_Num_Type Sensor_Pin;
};


#endif /* HAL_SENSOR_STATIC_INC_SENSOR_TYPES_H_ */
