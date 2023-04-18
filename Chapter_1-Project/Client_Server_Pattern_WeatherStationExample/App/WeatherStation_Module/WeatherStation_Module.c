/*
 * ECG_Module.c
 *
 *  Created on: Apr 18, 2023
 *      Author: Abdu
 */

#include <App/WeatherStation_Module/WeatherStation_Module.h>
#include <stdlib.h>
static void cleanUpRelations(WeatherStation_Module* const me);

void WeatherStation_Module_Init(WeatherStation_Module* const me) {
    me->dataNum = 0;
    me->itsTMDQueue = NULL;
}

void WeatherStation_Module_Cleanup(WeatherStation_Module* const me) {
    cleanUpRelations(me);
}

/* operation acquireValue() */

void WeatherStation_Module_acquireValue(WeatherStation_Module* const me) {
    // in actual implementation, this would return the
    // measured voltage across the lead pair
    struct TimeMarkedData tmd;
    tmd.dataValue = rand();
    tmd.timeInterval = ++me->dataNum;
    TMDQueue_insert(me->itsTMDQueue, tmd);
}

/* operation setLeadPair(int,int) */

void WeatherStation_Module_setLeadPair(WeatherStation_Module* const me, int l1, int l2)
{
    me->lead1 = l1;
    me->lead2 = l2;
}

struct TMDQueue* WeatherStation_Module_getItsTMDQueue(const WeatherStation_Module* const me) {
    return (struct TMDQueue*)me->itsTMDQueue;
}

void WeatherStation_Module_setItsTMDQueue(WeatherStation_Module* const me, struct TMDQueue* p_TMDQueue) {
    me->itsTMDQueue = p_TMDQueue;
}

WeatherStation_Module * WeatherStation_Module_Create(void) {

    WeatherStation_Module* me = (WeatherStation_Module *) malloc(sizeof(WeatherStation_Module));
    if(me!=NULL)
    {
        WeatherStation_Module_Init(me);
    }
    return me;
}

void WeatherStation_Module_Destroy(WeatherStation_Module* const me) {
    if(me!=NULL)
    {
        WeatherStation_Module_Cleanup(me);
    }
    free(me);
}


static void cleanUpRelations(WeatherStation_Module* const me) {
    if(me->itsTMDQueue != NULL)
    {
        me->itsTMDQueue = NULL;
    }
}

