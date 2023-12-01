/*
 * WeatherStation_Server.c
 *
 *  Created on: Mar 3, 2023
 *      Author: Abdu
 */


#include "../TMDQueue_with_Observable/TMDQueue_with_Observable.h"
#include "../TimeMarkedData/TimeMarkedData_DataType.h"

#include <App/HAL_Patterns/Server/WeatherStation_Api/WeatherStation_Server.h>
#include "HAL_Layer/RTC_I2C_DS1307/Static/inc/RTC_I2C_DS1307.h"
#include "APP_WS_Layer/TemperatureDriver_WeatherStation/TempratureDriver_WeatherStation.h"

void WeatherStation_Publish(struct TMDQueue_with_Observable_s* me){
    struct TimeMarkedData tmd;
    tmd.temperature_value = TempDriver_WeatherStation_Read();
    tmd.date = RTC_DS1307_getDate();
    tmd.time = RTC_DS1307_getTime();
    /*maybe an error here that iam passing a local variable.
     *it shouldn't be an error because it's return by value.
     *it  but just in case i faced one  */
    TMDQueue_with_Observable_Push(me, &tmd);
}

uint8 WeatherStation_IsEmpty(struct TMDQueue_with_Observable_s* me){
    uint8 x = TMDQueue_with_Observable_IsEmpty(me);
    return x;
}

