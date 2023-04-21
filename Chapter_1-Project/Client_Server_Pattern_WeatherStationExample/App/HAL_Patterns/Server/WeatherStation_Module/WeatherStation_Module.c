/*
 * ECG_Module.c
 *
 *  Created on: Apr 18, 2023
 *      Author: Abdu
 */

#include "WeatherStation_Module.h"
#include "../General_SpecificDrivers/SmokeDriver_WeatherStation/SmokeDriver_WeatherStation.h"
#include "../General_SpecificDrivers/TemperatureDriver_WeatherStation/TempratureDriver_WeatherStation.h"
#include <stdlib.h>


#include "../../General_HAL/RTC_I2C_DS1307/Static/inc/RTC_I2C_DS1307.h"

#include "../General_SpecificDrivers/TemperatureDriver_WeatherStation/TempratureDriver_WeatherStation.h"

static void cleanUpRelations(WeatherStation_Module* const me);

void WeatherStation_Module_Init(WeatherStation_Module* const me) {
    me->dataNum = 0;
    me->itsTMDQueue = Null_Ptr;
}

void WeatherStation_Module_Cleanup(WeatherStation_Module* const me) {
    cleanUpRelations(me);
}

/* operation acquireValue()
 * i will read all the server's values in here to publish it into the server
 * the data are : Smoke, Light, Temperature
 *              : RTC date and time
 *              */

void WeatherStation_Module_acquireValue(WeatherStation_Module* const me) {
    // in actual implementation, this would return the
    // measured voltage across the lead pair
    struct TimeMarkedData tmd;

    tmd.temperature_value = TempDriver_WeatherStation_Read();

//    tmd.date = RTC_DS1307_getDate();
//    tmd.time = RTC_DS1307_getTime();

    /* Publishing the data */
    TMDQueue_Insert(me->itsTMDQueue, tmd);
}

/* operation setLeadPair(int,int) */

//void WeatherStation_Module_setLeadPair(WeatherStation_Module* const me, int l1, int l2)
//{
//    me->lead1 = l1;
//    me->lead2 = l2;
//}

struct TMDQueue* WeatherStation_Module_getItsTMDQueue(const WeatherStation_Module* const me) {
    return (struct TMDQueue*)me->itsTMDQueue;
}

void WeatherStation_Module_setItsTMDQueue(WeatherStation_Module* const me, struct TMDQueue* p_TMDQueue) {
    me->itsTMDQueue = p_TMDQueue;
}

WeatherStation_Module * WeatherStation_Module_Create(void) {

    WeatherStation_Module* me = (WeatherStation_Module *) malloc(sizeof(WeatherStation_Module));
    if(me!=Null_Ptr)
    {
        WeatherStation_Module_Init(me);
    }
    return me;
}

void WeatherStation_Module_Destroy(WeatherStation_Module* const me) {
    if(me!=Null_Ptr)
    {
        WeatherStation_Module_Cleanup(me);
    }
    free(me);
}


static void cleanUpRelations(WeatherStation_Module* const me) {
    if(me->itsTMDQueue != Null_Ptr)
    {
        me->itsTMDQueue = Null_Ptr;
    }
}

