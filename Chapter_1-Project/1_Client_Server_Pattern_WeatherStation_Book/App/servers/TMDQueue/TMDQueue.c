/*
 * TMDQueue_Book.c
 *
 *  Created on: Apr 18, 2023
 *      Author: Abdu
 */


#include <App/servers/TMDQueue/TMDQueue.h>
#include <stdlib.h>


static void initRelations(TMDQueue* const me);
static void cleanUpRelations(TMDQueue* const me);


void TMDQueue_Init(TMDQueue* const me) {
    me->head = 0;
    me->size = 0;
    /* Setting the buffer into zeros */
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
    /* this operation computes the next index from the first using modulo arithmetic
    */
    return (index+1) % TMD_QUEUE_SIZE;
}

void TMDQueue_Insert(TMDQueue* const me, const struct TimeMarkedData tmd){
    /* note that because we never ’remove’ data from this leaky queue, size only increases to
    the queue size and then stops increasing. Insertion always takes place at the head.
    */

    me->head = TMDQueue_getNextIndex(me, me->head);
    me->Buffer[me->head] = tmd;
    if (me->size < TMD_QUEUE_SIZE)
        ++me->size;
}

uint8 TMDQueue_IsEmpty(TMDQueue* const me){
    return (me->size == 0);
}

// we don't decrease the size !!!!
struct TimeMarkedData TMDQueue_remove(TMDQueue* const me, uint8 index){
    struct TimeMarkedData tmd;
    if(me->size > 0){
        tmd = me->Buffer[index];
        --me->size;
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
