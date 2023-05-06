/*
 * FCPeriodicPoller.c
 *
 *  Created on: May 6, 2023
 *      Author: Abdu
 */

#include "FCPeriodicPoller.h"
#include "../FireDisplay/FireDisplay.h"
#include "../FCTimer/FCTimer.h"
#include "../FireCircuitSensor/FireCircuitSensor.h"

#include <stdlib.h>

static FCPeriodicPoller_t *priv_Periodic_Poller;

void FCPeriodicPoller_Init(FCPeriodicPoller_t* const me){
    int i;
    me->pollTime = DEFAULT_POLLING_TIME;
    me->itsFCTimer = Null_Ptr;
    me->itsFireDisplay = Null_Ptr;
    for(i = 0; i < DEFINED_POLL_DEVICES; i++){
        me->iteFireCircuitSensor[i] = Null_Ptr;
    }

}

void FCPeriodicPoller_Cleanup(FCPeriodicPoller_t* const me){

}

/* Operations */
void FCPeriodicPoller_poll(void){
    uint16 Tempstatus, Flamestatus;
    Tempstatus = FireCircuitSensor_getState(priv_Periodic_Poller->iteFireCircuitSensor[0]);
    Flamestatus = FireCircuitSensor_getState(priv_Periodic_Poller->iteFireCircuitSensor[1]);

    FireDisplay_showStatus(priv_Periodic_Poller->itsFireDisplay, Flamestatus, Tempstatus);

}

void FCPeriodicPoller_setPollTime(FCPeriodicPoller_t* const me, uint16 t){
    me->pollTime = t;
}

void FCPeriodicPoller_startPolling(FCPeriodicPoller_t* const me){
    FCTimer_StartTimer(me->itsFCTimer, me->pollTime);
}

void FCPeriodicPoller_stopPolling(FCPeriodicPoller_t* const me){
    FCTimer_StopTimer(me->itsFCTimer);
}


struct FCTimer* FCPeriodicPoller_getItsFCTimer(const FCPeriodicPoller_t* const me){
    return me->itsFCTimer;
}

void FCPeriodicPoller_setItsFCTimer(FCPeriodicPoller_t* const me, struct FCTimer* p_FCTimer){
    me->itsFCTimer = p_FCTimer;
    if(p_FCTimer != Null_Ptr){
        FCTimer_setItsFCPeriodicPoller(p_FCTimer, me);
    }
}

FireCircuitSensor_t* FCPeriodicPoller_getItsFireCircuitSensor(const FCPeriodicPoller_t* const me, uint8 my_SENSOR_ID){
    return me->iteFireCircuitSensor[my_SENSOR_ID];
}

void FCPeriodicPoller_addItsFireCircuitSensor(FCPeriodicPoller_t* const me, struct FireCircuitSensor * p_FireCircuitSensor,  uint8 my_SENSOR_ID){
    if(my_SENSOR_ID < DEFINED_POLL_DEVICES){
        me->iteFireCircuitSensor[my_SENSOR_ID] = p_FireCircuitSensor;
    }
}

void FCPeriodicPoller_removeItsFireCircuitSensor(FCPeriodicPoller_t* const me,struct FireCircuitSensor * p_FireCircuitSensor){
    uint8 i;
    for(i = 0; i < DEFINED_POLL_DEVICES; i++){
        if(me->iteFireCircuitSensor[i] == p_FireCircuitSensor){
            free(me->iteFireCircuitSensor[i]);
            me->iteFireCircuitSensor[i] = Null_Ptr;
        }
    }
}

void FCPeriodicPoller_clearItsFireCircuitSensor(FCPeriodicPoller_t* const me){
    uint8 i;
    for(i = 0; i < DEFINED_POLL_DEVICES; i++){
        free(me->iteFireCircuitSensor[i]);
        me->iteFireCircuitSensor[i] = Null_Ptr;
    }
}

struct FireDisplay* FCPeriodicPoller_getItsFireDisplay(const FCPeriodicPoller_t*const me){
    return me->itsFireDisplay;
}

void FCPeriodicPoller_setItsFireDisplay(FCPeriodicPoller_t* const me, struct FireDisplay* p_FireDisplay){
    me->itsFireDisplay = p_FireDisplay;
}

FCPeriodicPoller_t *FCPeriodicPoller_Create(void){
    FCPeriodicPoller_t* me;
    me = (FCPeriodicPoller_t*)malloc(sizeof(FCPeriodicPoller_t));
    if(me != Null_Ptr){
        FCPeriodicPoller_Init(me);
    }
    priv_Periodic_Poller = me;
    return me;
}

