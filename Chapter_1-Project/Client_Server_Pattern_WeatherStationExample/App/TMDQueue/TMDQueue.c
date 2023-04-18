/*
 * TMDQueue_Book.c
 *
 *  Created on: Apr 18, 2023
 *      Author: Abdu
 */


#include <App/TMDQueue/TMDQueue.h>

static void initRelations(TMDQueue* const me);
static void cleanUpRelations(TMDQueue* const me);


void TMDQueue_Init(TMDQueue* const me) {
    int i = 0;
    me->head = 0;
    me->size = 0;
    /* Setting the buffer into zeros */
    for(i = 0; i < TMD_QUEUE_SIZE; i++){
        TimeMarkedData_Init(me->Buffer[i]);
    }
    initRelations(me);

}


void TMDQueue_CleanUp(TMDQueue* const me){
    cleanUpRelations(me);
}

/* operations */

uint8 TMDQueue_getNextIndex(TMDQueue* const me, uint8 index){
    /* this operation computes the next index from the first using modulo arithmetic
    */
    return (index+1) % TMD_QUEUE_SIZE;
}

void TMDQueue_Insert(TMDQueue* const me, const struct TimeMarkedData tmd){
    /* note that because we never ’remove’ data from this leaky queue, size only increases to
    the queue size and then stops increasing. Insertion always takes place at the head.
    */

    me->buffer[me->head] = tmd;
    me->head = TMDQueue_getNextIndex(me, me->head);
    if (me->size < QUEUE_SIZE)
        ++me->size;
}

uint8 TMDQueue_IsEmpty(TMDQueue* const me){
    return (me->size == 0);
}

struct TimeMarkedData TMDQueue_remove(TMDQueue* const me, uint8 index){
    struct TimeMarkedData tmd;
    if (!TMDQueue_isEmpty(me) && (index>=0) && (index < QUEUE_SIZE) && (index < me->size)) {
        tmd = me->Buffer[index];
    }
    return tmd;
}

uint8 TMDQueue_getBuffer(TMDQueue* const me){

}

TMDQueue* TMDQueue_Create(void){
    TMDQueue* me = (TMDQueue *) malloc(sizeof(TMDQueue));
    if(me!=NULL)
    {
        TMDQueue_Init(me);
    }
    return me;
}

void TMDQueue_Destroy(TMDQueue* const me){
    if(me!=NULL)
    {
        TMDQueue_Cleanup(me);
    }
    free(me);
}


static void initRelations(TMDQueue* const me) {
{
    int iter = 0;
    while (iter < TMD_QUEUE_SIZE){
        TimeMarkedData_Init(&(me->Buffer[iter]));
        iter++;
    }
}

static void cleanUpRelations(TMDQueue* const me) {
{
    int iter = 0;
    /* doesn't really matter */
}
