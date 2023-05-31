/*
 * SensorObserver.h
 *
 *  Created on: May 8, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_HAL_DIGITALSENSOROBSERVABLE_DIGITAL_SENSORSERVER_H_
#define APP_HAL_PATTERN_HAL_DIGITALSENSOROBSERVABLE_DIGITAL_SENSORSERVER_H_

#include "../../General_Common/Platform_Types.h"

#include "../../General_Mcal/DIO/Dynamic/inc/DIO_Cfg.h"
#include "../../General_Mcal/DIO/Static/inc/DIO_Types.h"

#include "../Observable/Observable.h"
#include "../Observer/Observer.h"

typedef struct DigitalObservableSensor_struct DigitalObservableSensor_Type;

struct DigitalObservableSensor_struct{
    DIO_ChannelType Sensor_Data_Pins;
    uint8 (*GetValue)(DigitalObservableSensor_Type* const me);
    Observable_Type* my_observable;
};


/*
 * ==================================================== DIGITAL SENSOR ====================================================
 */


DigitalObservableSensor_Type* DigitalObservableSensor_Create(DIO_ChannelType Sensor_Data_Pins);
void DigitalObservableSensor_Destroy( DigitalObservableSensor_Type* const me);






#endif /* APP_HAL_PATTERN_HAL_DIGITALSENSOROBSERVABLE_DIGITAL_SENSORSERVER_H_ */
