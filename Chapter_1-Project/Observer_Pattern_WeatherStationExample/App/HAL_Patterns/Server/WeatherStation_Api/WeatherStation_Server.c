/*
 * WeatherStation_Server.c
 *
 *  Created on: Mar 3, 2023
 *      Author: Abdu
 */


#include "../TMDQueue_with_Observable/TMDQueue_with_Observable.h"
#include "../TimeMarkedData/TimeMarkedData_DataType.h"

#include <App/HAL_Patterns/Server/WeatherStation_Api/WeatherStation_Server.h>
#include "../General_HAL/RTC_I2C_DS1307/Static/inc/RTC_I2C_DS1307.h"
#include "../General_SpecificDrivers/TemperatureDriver_WeatherStation/TempratureDriver_WeatherStation.h"

void WeatherStation_Publish(void){
    struct TimeMarkedData tmd;
    tmd.temperature_value = TempDriver_WeatherStation_Read();
    tmd.date = RTC_DS1307_getDate();
    tmd.time = RTC_DS1307_getTime();
    /*maybe an error here that iam passing a local variable.
     *it shouldn't be an error because it's return by value.
     *it  but just in case i faced one  */
    weatherData_Queue_Push(&tmd);
}

uint8 WeatherStation_IsEmpty(void){
    uint8 x = WeatherData_Queue_IsEmpty();
    return x;
}

