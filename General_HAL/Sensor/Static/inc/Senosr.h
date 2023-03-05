/*
 * Senosr.h
 *
 *  Created on: Nov 25, 2022
 *      Author: abduy
 */

#ifndef HAL_SENSOR_STATIC_INC_SENOSR_H_
#define HAL_SENSOR_STATIC_INC_SENOSR_H_

#include "../../General_Mcal/DIO/Static/inc/DIO_Types.h"
#include "Sensor_Types.h"


Sensor_Type * Sensor_Create(uint8 Sensor_ID, Sensor_IntrfaceType SensorInterface);
void Sensor_Destroy( Sensor_Type* const me);

#endif /* HAL_SENSOR_STATIC_INC_SENOSR_H_ */
