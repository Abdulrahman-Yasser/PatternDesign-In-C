/*
 * TMDQueue_Book.h
 *
 *  Created on: Apr 18, 2023
 *      Author: Abdu
 */

#ifndef APP_TMDQUEUE_TMDQUEUE_H_
#define APP_TMDQUEUE_TMDQUEUE_H_

#include <App/servers/TimeMarkedData/TimeMarkedData.h>
#include "../../ECGPkg.h"

#define TMD_QUEUE_SIZE 5

typedef struct TMDQueue TMDQueue;

struct TMDQueue{
    uint8 head;
    uint8 size;
    struct TimeMarkedData Buffer[TMD_QUEUE_SIZE];
};

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

#endif /* APP_TMDQUEUE_TMDQUEUE_H_ */
