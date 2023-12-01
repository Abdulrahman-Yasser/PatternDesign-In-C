/*
 * TimeMarkedData.c
 *
 *  Created on: Apr 18, 2023
 *      Author: Abdu
 */

#include <App/servers/TimeMarkedData/TimeMarkedData.h>

void TimeMarkedData_Init(struct TimeMarkedData* me){
    me->date.date = 0;
    me->date.day = 0;
    me->date.month = 0;
    me->date.year = 0;

    me->time.AM_PM = 0;
    me->time.hours = 0;
    me->time.minutes = 0;
    me->time.seconds = 0;

    me->temperature_value = 0;

}


