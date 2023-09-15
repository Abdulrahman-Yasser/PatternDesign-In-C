/*
 * TSREventQueue.h
 *
 *  Created on: Aug 16, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_TSREVENTQUEUE_H_
#define APP_HAL_PATTERN_TSREVENTQUEUE_H_

#include "TokenizeAsyncSinglePkg.h"
#include "FreeRTOS.h"
#include "semphr.h"


typedef struct {
    Event q[100];
    int size;
    int head;
    int tail;
    SemaphoreHandle_t itsMutex;
}TSREventQueue;

/* Constructors and destructors:*/

void TSREventQueue_Init(TSREventQueue* const me);
void TSREventQueue_Cleanup(TSREventQueue* const me);

/* Operations */

int TSREventQueue_isEmpty(TSREventQueue* const me);
int TSREventQueue_isFull(TSREventQueue* const me);

/* puts the passed event in */
/* the event queue and then */
/* calls the event receptor of */
/* the state machine. Note */
/* if the queue overflows an */
/* error code (1) is returned. */

int TSREventQueue_post(TSREventQueue* const me, Event e);

/* It is assumed that the caller has */
/* ensured that there is at least one */
/* event in the queue (via the isEmpty() */
/* funtion) prior to calling this function. */
/* Otherwise they get a default event. */

Event TSREventQueue_pull(TSREventQueue* const me);

SemaphoreHandle_t TSREventQueue_getItsMutex(const TSREventQueue* const me);

void TSREventQueue_setItsMutex(TSREventQueue* const me, SemaphoreHandle_t p_Mutex);

TSREventQueue *TSREventQueue_Create(void);

void TSREventQueue_Destroy(TSREventQueue* const me);

#endif /* APP_HAL_PATTERN_TSREVENTQUEUE_H_ */
