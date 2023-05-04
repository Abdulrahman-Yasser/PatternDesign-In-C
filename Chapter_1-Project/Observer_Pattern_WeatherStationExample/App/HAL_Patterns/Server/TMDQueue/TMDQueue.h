/*
 * TMDQueue.h
 *
 *  Created on: May 4, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_SERVER_TMDQUEUE_TMDQUEUE_H_
#define APP_HAL_PATTERNS_SERVER_TMDQUEUE_TMDQUEUE_H_


#include "../TimeMarkedData/TimeMarkedData.h"

#define TMD_QUEUE_SIZE 5

typedef struct {
    uint8 head;
    uint8 size;
    struct TimeMarkedData Buffer[TMD_QUEUE_SIZE]
}TMDQueue;

void TMDQueue_Init(TMDQueue* const me);

void TMDQueue_CleanUp(TMDQueue* const me);

/* operations */

uint8 TMDQueue_getLastIndex(TMDQueue* const me);

uint8 TMDQueue_getNextIndex(TMDQueue* const me, uint8 index);

void TMDQueue_Insert(TMDQueue* const me, const struct TimeMarkedData tmd);

uint8 TMDQueue_IsEmpty(TMDQueue* const me);

struct TimeMarkedData TMDQueue_remove(TMDQueue* const me, uint8 index);

TMDQueue* TMDQueue_Create(void);

void TMDQueue_Destroy(TMDQueue* const me);


#endif /* APP_HAL_PATTERNS_SERVER_TMDQUEUE_TMDQUEUE_H_ */
