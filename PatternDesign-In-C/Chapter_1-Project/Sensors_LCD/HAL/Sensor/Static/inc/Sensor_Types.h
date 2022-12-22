/*
 * Sendor_Types.h
 *
 *  Created on: Nov 25, 2022
 *      Author: abduy
 */

#ifndef HAL_SENSOR_STATIC_INC_SENSOR_TYPES_H_
#define HAL_SENSOR_STATIC_INC_SENSOR_TYPES_H_
#include "../../../../Common/Platform_Types.h"

typedef uint8 SENSOR_READ_TYPE;

typedef struct Sensor_struct Sensor_Type;
struct Sensor_struct{
    SENSOR_READ_TYPE value;
    SENSOR_READ_TYPE (*GetValue)(Sensor_Type* const me);
};

#endif /* HAL_SENSOR_STATIC_INC_SENSOR_TYPES_H_ */
