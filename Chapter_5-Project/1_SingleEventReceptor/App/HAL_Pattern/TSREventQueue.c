/*
 * TSREventQueue.c
 *
 *  Created on: Aug 16, 2023
 *      Author: Abdu
 */

#include "TSREventQueue.h"
#include <stdlib.h>
#include "../General_Common/Std_Types.h"

/* Constructors and destructors:*/

void TSREventQueue_Init(TSREventQueue* const me){
    me->head = 0;
    me->size = 0;
    me->tail = 0;
    me->itsMutex = Null_Ptr;
}

void TSREventQueue_Cleanup(TSREventQueue* const me){

}

/* Operations */

int TSREventQueue_isEmpty(TSREventQueue* const me){
    return me->size <= 0;
}

int TSREventQueue_isFull(TSREventQueue* const me){
    return me->size >= QSIZE-1;
}


/* post enqueues an event and signals that fact */

int TSREventQueue_post(TSREventQueue* const me, Event e){
    xSemaphoreTake(me->itsMutex, 0);
    if(!TSREventQueue_isFull(me)){
        me->q[me->head] = e;
        me->head = (me->head + 1) % QSIZE;
        me->size++;
        xSemaphoreGive(me->itsMutex);
        postSignal();
        return 1;
    }else{
        xSemaphoreGive(me->itsMutex);
        return 0;
    }
}

/* pulls removes the oldest event from the queue */
/* pull should only be called when there is an event waiting */

Event TSREventQueue_pull(TSREventQueue* const me){
    Event e;
    xSemaphoreTake(me->itsMutex, 0);
    if(!TSREventQueue_isEmpty(me)){
        e = me->q[me->tail];
        me->tail = (me->tail + 1) % QSIZE;
        me->size--;
    }
    xSemaphoreGive(me->itsMutex);
    return e;
}

SemaphoreHandle_t TSREventQueue_getItsMutex(const TSREventQueue* const me){
    return me->itsMutex;
}

void TSREventQueue_setItsMutex(TSREventQueue* const me, SemaphoreHandle_t p_Mutex){
    me->itsMutex = p_Mutex;
}

TSREventQueue *TSREventQueue_Create(void){
    TSREventQueue* me = (TSREventQueue *) malloc(sizeof(TSREventQueue));
    if(me!=Null_Ptr){
        TSREventQueue_Init(me);
    }
    return me;
}

void TSREventQueue_Destroy(TSREventQueue* const me){
    if(me!=Null_Ptr){
        TSREventQueue_Cleanup(me);
    }
    free(me);
}
