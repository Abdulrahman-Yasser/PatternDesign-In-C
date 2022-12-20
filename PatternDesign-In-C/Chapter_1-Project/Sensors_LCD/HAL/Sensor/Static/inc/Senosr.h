/*
 * Senosr.h
 *
 *  Created on: Nov 25, 2022
 *      Author: abduy
 */

#ifndef HAL_SENSOR_STATIC_INC_SENOSR_H_
#define HAL_SENSOR_STATIC_INC_SENOSR_H_

#include "../../../../Mcal/DIO/Static/inc/DIO_Types.h"
#include "Sensor_Types.h"


//  Constructor
void Sensor_Init(Sensor_Type* const me, SENSOR_READ_TYPE (*GetValueFunction)(Sensor_Type* const me) );

//  Destructor
void Sensor_Cleanup(Sensor_Type* const me);


SENSOR_READ_TYPE Sensor_GetValue(const Sensor_Type* const me);
Sensor_Type * Sensor_Create(void);
void Sensor_Destroy( const Sensor_Type* const me);

#endif /* HAL_SENSOR_STATIC_INC_SENOSR_H_ */
