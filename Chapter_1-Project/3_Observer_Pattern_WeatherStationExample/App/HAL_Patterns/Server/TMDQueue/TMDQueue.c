/*
 * TMDQueue.c
 *
 *  Created on: May 4, 2023
 *      Author: Abdu
 */

#include "TMDQueue.h"
#include "../../Observable/Observable.h"
#include "../../Observer/Observer.h"
#include <stdlib.h>
#include "../TimeMarkedData/TimeMarkedData.h"


static void initRelations(TMDQueue* const me);
static void cleanUpRelations(TMDQueue* const me);



void TMDQueue_Init(TMDQueue* const me) {
    me->head = 0;
    me->size = 0;
    initRelations(me);
}


void TMDQueue_CleanUp(TMDQueue* const me){
    cleanUpRelations(me);
}

/* operations */

uint8 TMDQueue_getLastIndex(TMDQueue* const me){
    return me->head;
}

uint8 TMDQueue_getNextIndex(TMDQueue* const me, uint8 index){
    /*
     * this operation computes the next index from the first using modulo arithmetic
    */
    return (index+1) % TMD_QUEUE_SIZE;
}

void TMDQueue_Insert(TMDQueue* const me, const struct TimeMarkedData tmd){
    /* note that because we never ’remove’ data from this leaky queue, size only increases to
    the queue size and then stops increasing. Insertion always takes place at the head.
    and we don't have to remove as long as the Head pointer is changed at every insertion
    */

    me->head = TMDQueue_getNextIndex(me, me->head);
    me->Buffer[me->head] = tmd;
    if (me->size < TMD_QUEUE_SIZE-1)
        ++me->size;
}

/* it will never be empty by the way !!
 * because we never delete data or decrease the head, which make sense as long there is multiple
 * clients poping from the Queue, so if a client popped a data the other client won't read it !! */
uint8 TMDQueue_IsEmpty(TMDQueue* const me){
    return (me->size == 0);
}

uint8 TMDQueue_isFull(TMDQueue* const me){
    return (me->size == TMD_QUEUE_SIZE);
}

// we don't decrease the size !!!!
struct TimeMarkedData TMDQueue_remove(TMDQueue* const me, uint8 index){
    struct TimeMarkedData tmd;
    if(me->size == 0){
        return tmd;
    }
    if (!TMDQueue_IsEmpty(me) && (index < TMD_QUEUE_SIZE) && (index < me->size)) {
        tmd = me->Buffer[index];
    }
    if(me->size > 0){
        me->size--;
    }
    return tmd;
}


TMDQueue* TMDQueue_Create(void){
    TMDQueue* me = (TMDQueue *) malloc(sizeof(TMDQueue));
    if(me!=Null_Ptr)
    {
        TMDQueue_Init(me);
    }
    return me;
}

void TMDQueue_Destroy(TMDQueue* const me){
    if(me!=Null_Ptr)
    {
        TMDQueue_CleanUp(me);
    }
    free(me);
}


static void initRelations(TMDQueue* const me)
{
    int iter = 0;
    while (iter < TMD_QUEUE_SIZE){
        TimeMarkedData_Init(&(me->Buffer[iter]));
        iter++;
    }
}

static void cleanUpRelations(TMDQueue* const me){
    int iter = 0;
    /* doesn't really matter */
}


//void weatherData_Queue_Push(TMDQueue *me, struct TimeMarkedData tmd){
//    TMDQueue_Insert(me, tmd);
//    PrivaateNotify();
//}
//
//struct TimeMarkedData weatherData_Queue_Pop(TMDQueue *me){
//    struct TimeMarkedData result;
//    result = (TMDQueue*)malloc(sizeof(TMDQueue));
//    if( TMDQueue_IsEmpty(me) ){
//        return 0;
//    }
//    result = TMDQueue_remove(me, index);
//    return result;
//}
//
///**
// *  Observable Function
// **/
//
//void PrivateSubscribe(TMDQueue *me, Observer *o){
//    /* add the function in the notification handler */
//    NotificationHandle *pNH;
//    pNH = me->my_Observable->itsNotificationHandler;
//    if(pNH == Null_Ptr){
//        me->my_Observable->itsNotificationHandler = NotificationHandle_Create();
//        pNH = me->my_Observable->itsNotificationHandler;
//    }else{
//        while(pNH->itsNotificationHandle != Null_Ptr){
//            pNH = pNH->itsNotificationHandle;
//        }
//        pNH->itsNotificationHandle = NotificationHandle_Create();
//        pNH = pNH->itsNotificationHandle;
//    }
//    pNH->FunPtr = o->UpdateFuncPtr;
//    ++me->my_Observable->nSubscribers;
//}
//
//void PrivateUnSubscribe(TMDQueue *me, Observer *o){
//    NotificationHandle *pNH, *pBack;
//    pNH = pBack = me->my_Observable->itsNotificationHandler;
//
//    if(pNH == Null_Ptr){
//        return ;
//    }else{
//        if(pNH->FunPtr == o->UpdateFuncPtr){
//            me->my_Observable->itsNotificationHandler = pNH->itsNotificationHandle;
//            free(pNH);
//            --me->my_Observable->nSubscribers;
//        }else{
//            while(pNH != Null_Ptr){
//                pBack = pNH;
//                pNH = pNH->itsNotificationHandle;
//                if(pNH->FunPtr == o->UpdateFuncPtr){
//                    pBack->itsNotificationHandle = pNH->itsNotificationHandle;
//                    free(pNH);
//                    --me->my_Observable->nSubscribers;
//                    return;
//                }
//            }
//        }
//    }
//}
//
//void PrivaateNotify(TMDQueue *me){
//    int i;
//    struct TimeMarkedData tmd;
//    if( TMDQueue_IsEmpty(me) ){
//        return;
//    }
//    i = TMDQueue_getLastIndex(me);
//    tmd = TMDQueue_remove(me, i);
//    for(i = 0; i < me.my_Observable->nSubscribers; i++){
//        me->my_Observable->itsNotificationHandler->FunPtr(&tmd);
//    }
//}
//
//
