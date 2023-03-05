/*
 * Queue.c
 *
 *  Created on: Dec 20, 2022
 *      Author: abduy
 */

#include "../inc/Queue.h"
#include "../../../../Platform_Types.h"
#include "../../../../Compiler.h"
#include <stdlib.h>

/**************************************************************************************
 *                                  Definitions
 *                                    STATIC
 *                                    uint32
 **************************************************************************************/

void Queue_Init_uint32_s(Queue_uint32_STATIC_Type* const me, uint8 (*isFullFunction)(Queue_uint32_STATIC_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint32_STATIC_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint32_STATIC_Type* const me),
                void (*insertFunction)(Queue_uint32_STATIC_Type* const me, uint32 x) ,uint32 (*removeFunction)(Queue_uint32_STATIC_Type* const me) );

void Queue_CleanUp_uint32_s(Queue_uint32_STATIC_Type* const me);

uint8 Queue_isFull_uint32_s(Queue_uint32_STATIC_Type* const me);
uint8 Queue_isEmpty_uint32_s(Queue_uint32_STATIC_Type *const me);
uint8 Queue_getSize_uint32_s(Queue_uint32_STATIC_Type* const me);
void Queue_insert_uint32_s(Queue_uint32_STATIC_Type* const me, uint32 x);
uint32 Queue_remove_uint32_s(Queue_uint32_STATIC_Type* const me);


/**************************************************************************************
 *                                  Definitions
 *                                    STATIC
 *                                    uint16
 **************************************************************************************/
void Queue_Init_uint16_s(Queue_uint16_STATIC_Type* const me, uint8 (*isFullFunction)(Queue_uint16_STATIC_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint16_STATIC_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint16_STATIC_Type* const me),
                void (*insertFunction)(Queue_uint16_STATIC_Type* const me, uint16 x) ,uint16 (*removeFunction)(Queue_uint16_STATIC_Type* const me) );

void Queue_CleanUp_uint16_s(Queue_uint16_STATIC_Type* const me);

uint8 Queue_isFull_uint16_s(Queue_uint16_STATIC_Type* const me);
uint8 Queue_isEmpty_uint16_s(Queue_uint16_STATIC_Type *const me);
uint8 Queue_getSize_uint16_s(Queue_uint16_STATIC_Type* const me);
void Queue_insert_uint16_s(Queue_uint16_STATIC_Type* const me, uint16 x);
uint16 Queue_remove_uint16_s(Queue_uint16_STATIC_Type* const me);

/**************************************************************************************
 *                                  Definitions
 *                                    STATIC
 *                                    uint8
 **************************************************************************************/
void Queue_Init_uint8_s(Queue_uint8_STATIC_Type* const me, uint8 (*isFullFunction)(Queue_uint8_STATIC_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint8_STATIC_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint8_STATIC_Type* const me),
                void (*insertFunction)(Queue_uint8_STATIC_Type* const me, uint8 x) ,uint8 (*removeFunction)(Queue_uint8_STATIC_Type* const me) );

void Queue_CleanUp_uint8_s(Queue_uint8_STATIC_Type* const me);

uint8 Queue_isFull_uint8_s(Queue_uint8_STATIC_Type* const me);
uint8 Queue_isEmpty_uint8_s(Queue_uint8_STATIC_Type *const me);
uint8 Queue_getSize_uint8_s(Queue_uint8_STATIC_Type* const me);
void Queue_insert_uint8_s(Queue_uint8_STATIC_Type* const me, uint8 x);
uint8 Queue_remove_uint8_s(Queue_uint8_STATIC_Type* const me);

/**************************************************************************************
 *                                  Definitions
 *                                    DYNAMIC
 *                                    uint32
 **************************************************************************************/
void Queue_Init_uint32_d(Queue_uint32_DYNAMIC_Type* const me ,uint8 Dynamic_Size_P, uint8 (*isFullFunction)(Queue_uint32_DYNAMIC_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint32_DYNAMIC_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint32_DYNAMIC_Type* const me),
                void (*insertFunction)(Queue_uint32_DYNAMIC_Type* const me, uint32 x) ,uint32 (*removeFunction)(Queue_uint32_DYNAMIC_Type* const me) );

void Queue_CleanUp_uint32_d(Queue_uint32_DYNAMIC_Type* const me);

uint8 Queue_isFull_uint32_d(Queue_uint32_DYNAMIC_Type* const me);
uint8 Queue_isEmpty_uint32_d(Queue_uint32_DYNAMIC_Type *const me);
uint8 Queue_getSize_uint32_d(Queue_uint32_DYNAMIC_Type* const me);
void Queue_insert_uint32_d(Queue_uint32_DYNAMIC_Type* const me, uint32 x);
uint32 Queue_remove_uint32_d(Queue_uint32_DYNAMIC_Type* const me);

/**************************************************************************************
 *                                  Definitions
 *                                    DYNAMIC
 *                                    uint16
 **************************************************************************************/
void Queue_Init_uint16_d(Queue_uint16_DYNAMIC_Type* const me ,uint8 Dynamic_Size_P, uint8 (*isFullFunction)(Queue_uint16_DYNAMIC_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint16_DYNAMIC_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint16_DYNAMIC_Type* const me),
                void (*insertFunction)(Queue_uint16_DYNAMIC_Type* const me, uint16 x) ,uint16 (*removeFunction)(Queue_uint16_DYNAMIC_Type* const me) );

void Queue_CleanUp_uint16_d(Queue_uint16_DYNAMIC_Type* const me);

uint8 Queue_isFull_uint16_d(Queue_uint16_DYNAMIC_Type* const me);
uint8 Queue_isEmpty_uint16_d(Queue_uint16_DYNAMIC_Type *const me);
uint8 Queue_getSize_uint16_d(Queue_uint16_DYNAMIC_Type* const me);
void Queue_insert_uint16_d(Queue_uint16_DYNAMIC_Type* const me, uint16 x);
uint16 Queue_remove_uint16_d(Queue_uint16_DYNAMIC_Type* const me);

/**************************************************************************************
 *                                  Definitions
 *                                    DYNAMIC
 *                                    uint8
 **************************************************************************************/
void Queue_Init_uint8_d(Queue_uint8_DYNAMIC_Type* const me ,uint8 Dynamic_Size_P, uint8 (*isFullFunction)(Queue_uint8_DYNAMIC_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint8_DYNAMIC_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint8_DYNAMIC_Type* const me),
                void (*insertFunction)(Queue_uint8_DYNAMIC_Type* const me, uint8 x) ,uint8 (*removeFunction)(Queue_uint8_DYNAMIC_Type* const me) );

void Queue_CleanUp_uint8_d(Queue_uint8_DYNAMIC_Type* const me);

uint8 Queue_isFull_uint8_d(Queue_uint8_DYNAMIC_Type* const me);
uint8 Queue_isEmpty_uint8_d(Queue_uint8_DYNAMIC_Type *const me);
uint8 Queue_getSize_uint8_d(Queue_uint8_DYNAMIC_Type* const me);
void Queue_insert_uint8_d(Queue_uint8_DYNAMIC_Type* const me, uint8 x);
uint8 Queue_remove_uint8_d(Queue_uint8_DYNAMIC_Type* const me);



/**************************************************************************************
 *                                  Implementation
 *                                      STATIC
 *                                      uint32
 **************************************************************************************/

/****************************************************
 *              Creation and Destroying
 ****************************************************/
Queue_uint32_STATIC_Type *Queue_Create_STATIC_uint32(void){
    Queue_uint32_STATIC_Type* me = (Queue_uint32_STATIC_Type*)malloc(sizeof(Queue_uint32_STATIC_Type));
        if(me != Null_Ptr){
                Queue_Init_uint32_s(me, Queue_isFull_uint32_s, Queue_isEmpty_uint32_s, Queue_getSize_uint32_s,
                           Queue_insert_uint32_s, Queue_remove_uint32_s);
        }
        return me;
}

void Queue_Destroy_STATIC_uint32(Queue_uint32_STATIC_Type* const me){
    if(me != Null_Ptr){
        Queue_CleanUp_uint32_s(me);
    }
    free(me);
}

/*********************************************
 *           Constructor and Destructor
 *********************************************/

void Queue_Init_uint32_s(Queue_uint32_STATIC_Type* const me, uint8 (*isFullFunction)(Queue_uint32_STATIC_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint32_STATIC_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint32_STATIC_Type* const me),
                void (*insertFunction)(Queue_uint32_STATIC_Type* const me, uint32 x) ,uint32 (*removeFunction)(Queue_uint32_STATIC_Type* const me) ){
    me->head = 0;
    me->size = 0;
    me->tail = 0;
    /* Initialize function pointers */
    me->isFull = isFullFunction;
    me->isEmpty = isEmptyFunction;
    me->getSize = getSizeFunction;
    me->insert = insertFunction;
    me->remove = removeFunction;
}

/* Operation Clean_up() */
void Queue_CleanUp_uint32_s(Queue_uint32_STATIC_Type* const me){
    free(me->Buffer);
}

/*********************************************
 *           Static Operations
 *********************************************/
/* Operation isFull() */
uint8 Queue_isFull_uint32_s(Queue_uint32_STATIC_Type* const me){
    return(me->head + 1) % QUEUE_BUFFER_SIZE_STATIC == me->tail;
}

/* Operation isEmpty() */
uint8 Queue_isEmpty_uint32_s(Queue_uint32_STATIC_Type *const me){
    return (me->head == me->tail);
}

/* Operation getSize() */
uint8 Queue_getSize_uint32_s(Queue_uint32_STATIC_Type* const me){
    return me->size;
}

/* Operation insert(int) */
void Queue_insert_uint32_s(Queue_uint32_STATIC_Type* const me, uint32 x){
    if(!me->isFull(me)){
        me->Buffer[me->head] = x;
        me->head = (me->head + 1) % QUEUE_BUFFER_SIZE_STATIC;
        ++me->size;
    }
}

/* Operation remove() */
uint32 Queue_remove_uint32_s(Queue_uint32_STATIC_Type* const me){
    uint32 value = 0;
    if(!me->isEmpty(me)){
        value = me->Buffer[me->tail];
        me->tail = (me->tail + 1) % QUEUE_BUFFER_SIZE_STATIC;
        --me->size;
    }
    return value;
}

/**************************************************************************************
 *                                    STATIC
 *                                    uint16
 *
 **************************************************************************************/

/****************************************************
 *              Creation and Destroying
 ****************************************************/
Queue_uint16_STATIC_Type *Queue_Create_STATIC_uint16(void){
    Queue_uint16_STATIC_Type *me = (Queue_uint16_STATIC_Type*)malloc(sizeof(Queue_uint16_STATIC_Type));
    if(me != Null_Ptr){
        Queue_Init_uint16_s(me, Queue_isFull_uint16_s, Queue_isEmpty_uint16_s, Queue_getSize_uint16_s,
                   Queue_insert_uint16_s, Queue_remove_uint16_s);
    }
    return me;
}

void Queue_Destroy_STATIC_uint16(Queue_uint16_STATIC_Type* const me){
    if(me != Null_Ptr){
        Queue_CleanUp_uint16_s(me);

    }
}


/*********************************************
 *           Constructor and Destructor
 *********************************************/
void Queue_Init_uint16_s(Queue_uint16_STATIC_Type* const me, uint8 (*isFullFunction)(Queue_uint16_STATIC_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint16_STATIC_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint16_STATIC_Type* const me),
                void (*insertFunction)(Queue_uint16_STATIC_Type* const me, uint16 x) ,uint16 (*removeFunction)(Queue_uint16_STATIC_Type* const me) ){
    me->head = 0;
    me->size = 0;
    me->tail = 0;
    /* Initialize function pointers */
    me->isFull = isFullFunction;
    me->isEmpty = isEmptyFunction;
    me->getSize = getSizeFunction;
    me->insert = insertFunction;
    me->remove = removeFunction;
}

/* Operation Clean_up() */
void Queue_CleanUp_uint16_s(Queue_uint16_STATIC_Type* const me){
    free(me->Buffer);
}


/*********************************************
 *           Static Operations
 *********************************************/
/* Operation isFull() */
uint8 Queue_isFull_uint16_s(Queue_uint16_STATIC_Type* const me){
    return(me->head + 1) % QUEUE_BUFFER_SIZE_STATIC == me->tail;
}

/* Operation isEmpty() */
uint8 Queue_isEmpty_uint16_s(Queue_uint16_STATIC_Type *const me){
    return (me->head == me->tail);
}

/* Operation getSize() */
uint8 Queue_getSize_uint16_s(Queue_uint16_STATIC_Type* const me){
    return me->size;
}

/* Operation insert(int) */
void Queue_insert_uint16_s(Queue_uint16_STATIC_Type* const me, uint16 x){
    if(!me->isFull(me)){
        me->Buffer[me->head] = x;
        me->head = (me->head + 1) % QUEUE_BUFFER_SIZE_STATIC;
        ++me->size;
    }
}

/* Operation remove() */
uint16 Queue_remove_uint16_s(Queue_uint16_STATIC_Type* const me){
    uint16 value = 0;
    if(!me->isEmpty(me)){
        value = me->Buffer[me->tail];
        me->tail = (me->tail + 1) % QUEUE_BUFFER_SIZE_STATIC;
        --me->size;
    }
    return value;
}


/**************************************************************************************
 *                                    STATIC
 *                                    uint8
 *
 **************************************************************************************/

/****************************************************
 *              Creation and Destroying
 ****************************************************/
Queue_uint8_STATIC_Type *Queue_Create_STATIC_uint8(void){
    Queue_uint8_STATIC_Type *me = (Queue_uint8_STATIC_Type*)malloc(sizeof(Queue_uint8_STATIC_Type));
    if(me != Null_Ptr){
        Queue_Init_uint8_s(me, Queue_isFull_uint8_s, Queue_isEmpty_uint8_s, Queue_getSize_uint8_s,
                   Queue_insert_uint8_s, Queue_remove_uint8_s);
    }
    return me;
}

void Queue_Destroy_STATIC_uint8(Queue_uint8_STATIC_Type* const me){
    if(me != Null_Ptr){
        Queue_CleanUp_uint8_s(me);

    }
}

/*********************************************
 *           Constructor and Destructor
 *********************************************/
void Queue_Init_uint8_s(Queue_uint8_STATIC_Type* const me, uint8 (*isFullFunction)(Queue_uint8_STATIC_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint8_STATIC_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint8_STATIC_Type* const me),
                void (*insertFunction)(Queue_uint8_STATIC_Type* const me, uint8 x) ,uint8 (*removeFunction)(Queue_uint8_STATIC_Type* const me) ){
    me->head = 0;
    me->size = 0;
    me->tail = 0;
    /* Initialize function pointers */
    me->isFull = isFullFunction;
    me->isEmpty = isEmptyFunction;
    me->getSize = getSizeFunction;
    me->insert = insertFunction;
    me->remove = removeFunction;
}

/* Operation Clean_up() */
void Queue_CleanUp_uint8_s(Queue_uint8_STATIC_Type* const me){
    free(me->Buffer);
}

/*********************************************
 *           Static Operations
 *********************************************/

/* Operation isFull() */
uint8 Queue_isFull_uint8_s(Queue_uint8_STATIC_Type* const me){
    return(me->head + 1) % QUEUE_BUFFER_SIZE_STATIC == me->tail;
}

/* Operation isEmpty() */
uint8 Queue_isEmpty_uint8_s(Queue_uint8_STATIC_Type *const me){
    return (me->head == me->tail);
}

/* Operation getSize() */
uint8 Queue_getSize_uint8_s(Queue_uint8_STATIC_Type* const me){
    return me->size;
}

/* Operation insert(int) */
void Queue_insert_uint8_s(Queue_uint8_STATIC_Type* const me, uint8 x){
    if(!me->isFull(me)){
        me->Buffer[me->head] = x;
        me->head = (me->head + 1) % QUEUE_BUFFER_SIZE_STATIC;
        ++me->size;
    }
}

/* Operation remove() */
uint8 Queue_remove_uint8_s(Queue_uint8_STATIC_Type* const me){
    uint8 value = 0;
    if(!me->isEmpty(me)){
        value = me->Buffer[me->tail];
        me->tail = (me->tail + 1) % QUEUE_BUFFER_SIZE_STATIC;
        --me->size;
    }
    return value;
}



/**************************************************************************************
 *                                   DYNAMIC
 *                                   uint32
 *
 **************************************************************************************/

/****************************************************
 *              Creation and cleaning
 ****************************************************/
Queue_uint32_DYNAMIC_Type *Queue_Create_DYNAMIC_uint32(uint8 DynamicSize){
    Queue_uint32_DYNAMIC_Type* me = (Queue_uint32_DYNAMIC_Type*)malloc(sizeof(Queue_uint32_DYNAMIC_Type));
        if(me != Null_Ptr){
            if(DynamicSize > 0){
                me->Dynamic_Size = DynamicSize;
                Queue_Init_uint32_d(me, DynamicSize, Queue_isFull_uint32_d, Queue_isEmpty_uint32_d, Queue_getSize_uint32_d,
                           Queue_insert_uint32_d, Queue_remove_uint32_d);
            }
        }
        return me;
}

void Queue_Destroy_DYNAMIC_uint32(Queue_uint32_DYNAMIC_Type* const me){
    if(me != Null_Ptr){
        Queue_CleanUp_uint32_d(me);
    }
    free(me);
}


/*********************************************
 *           Constructor and Destructor
 *********************************************/
void Queue_Init_uint32_d(Queue_uint32_DYNAMIC_Type* const me ,uint8 Dynamic_Size_P, uint8 (*isFullFunction)(Queue_uint32_DYNAMIC_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint32_DYNAMIC_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint32_DYNAMIC_Type* const me),
                void (*insertFunction)(Queue_uint32_DYNAMIC_Type* const me, uint32 x) ,uint32 (*removeFunction)(Queue_uint32_DYNAMIC_Type* const me) ){
    me->head = 0;
    me->size = 0;
    me->tail = 0;
    me->Dynamic_Size = Dynamic_Size_P;
    /* Initialize function pointers */
    if(me->Dynamic_Size > 0){
        me->Buffer = (uint32*)malloc(sizeof(uint32) * me->Dynamic_Size);
    }
    me->isFull = isFullFunction;
    me->isEmpty = isEmptyFunction;
    me->getSize = getSizeFunction;
    me->insert = insertFunction;
    me->remove = removeFunction;
}

/* Operation Clean_up() */

void Queue_CleanUp_uint32_d(Queue_uint32_DYNAMIC_Type* const me){
    free(me->Buffer);
}


/*********************************************
 *           Dynamic Operations
 *********************************************/

/* Operation isFull() */
uint8 Queue_isFull_uint32_d(Queue_uint32_DYNAMIC_Type* const me){
    return(me->head + 1) % me->Dynamic_Size == me->tail;
}

/* Operation isEmpty() */
uint8 Queue_isEmpty_uint32_d(Queue_uint32_DYNAMIC_Type *const me){
    return (me->head == me->tail);
}

/* Operation getSize() */
uint8 Queue_getSize_uint32_d(Queue_uint32_DYNAMIC_Type* const me){
    return me->size;
}

/* Operation insert(int) */
void Queue_insert_uint32_d(Queue_uint32_DYNAMIC_Type* const me, uint32 x){
    if(!me->isFull(me)){
        me->Buffer[me->head] = x;
        me->head = (me->head + 1) % me->Dynamic_Size;
        ++me->size;
    }
}

/* Operation remove() */
uint32 Queue_remove_uint32_d(Queue_uint32_DYNAMIC_Type* const me){
    uint32 value = 0;
    if(!me->isEmpty(me)){
        value = me->Buffer[me->tail];
        me->tail = (me->tail + 1) % me->Dynamic_Size;
        --me->size;
    }
    return value;
}


/**************************************************************************************
 *                                   DYNAMIC
 *                                   uint16
 *
 **************************************************************************************/

/****************************************************
 *              Creation and cleaning
 ****************************************************/

Queue_uint16_DYNAMIC_Type *Queue_Create_DYNAMIC_uint16(uint8 DynamicSize){
    Queue_uint16_DYNAMIC_Type* me = (Queue_uint16_DYNAMIC_Type*)malloc(sizeof(Queue_uint16_DYNAMIC_Type));
    if(DynamicSize > 0){
        if(me != Null_Ptr){
            Queue_Init_uint16_d(me, DynamicSize, Queue_isFull_uint16_d, Queue_isEmpty_uint16_d, Queue_getSize_uint16_d,
                           Queue_insert_uint16_d, Queue_remove_uint16_d);
            }
        }
        return me;
}

void Queue_Destroy_DYNAMIC_uint16(Queue_uint16_DYNAMIC_Type* const me){
    if(me != Null_Ptr){
        Queue_CleanUp_uint16_d(me);
    }
    free(me);
}

/*********************************************
 *           Constructor and Destructor
 *********************************************/

void Queue_Init_uint16_d(Queue_uint16_DYNAMIC_Type* const me ,uint8 Dynamic_Size_P, uint8 (*isFullFunction)(Queue_uint16_DYNAMIC_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint16_DYNAMIC_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint16_DYNAMIC_Type* const me),
                void (*insertFunction)(Queue_uint16_DYNAMIC_Type* const me, uint16 x) ,uint16 (*removeFunction)(Queue_uint16_DYNAMIC_Type* const me) ){
    me->head = 0;
    me->size = 0;
    me->tail = 0;
    me->Dynamic_Size = Dynamic_Size_P;
    /* Initialize function pointers */
    if(me->Dynamic_Size > 0){
        me->Buffer = (uint16*)malloc(sizeof(uint16) * me->Dynamic_Size);
    }
    me->isFull = isFullFunction;
    me->isEmpty = isEmptyFunction;
    me->getSize = getSizeFunction;
    me->insert = insertFunction;
    me->remove = removeFunction;
}


void Queue_CleanUp_uint16_d(Queue_uint16_DYNAMIC_Type* const me){
    free(me->Buffer);
}

/*********************************************
 *           Dynamic Operations
 *********************************************/
/* Operation isFull() */
uint8 Queue_isFull_uint16_d(Queue_uint16_DYNAMIC_Type* const me){
    return(me->head + 1) % me->Dynamic_Size == me->tail;
}

/* Operation isEmpty() */
uint8 Queue_isEmpty_uint16_d(Queue_uint16_DYNAMIC_Type *const me){
    return (me->head == me->tail);
}

/* Operation getSize() */
uint8 Queue_getSize_uint16_d(Queue_uint16_DYNAMIC_Type* const me){
    return me->size;
}

/* Operation insert(int) */
void Queue_insert_uint16_d(Queue_uint16_DYNAMIC_Type* const me, uint16 x){
    if(!me->isFull(me)){
        me->Buffer[me->head] = x;
        me->head = (me->head + 1) % me->Dynamic_Size;
        ++me->size;
    }
}

/* Operation remove() */
uint16 Queue_remove_uint16_d(Queue_uint16_DYNAMIC_Type* const me){
    uint16 value = 0;
    if(!me->isEmpty(me)){
        value = me->Buffer[me->tail];
        me->tail = (me->tail + 1) % me->Dynamic_Size;
        --me->size;
    }
    return value;
}



/**************************************************************************************
 *                                   DYNAMIC
 *                                   uint8
 *
 **************************************************************************************/
/****************************************************
 *              Creation and cleaning
 ****************************************************/

Queue_uint8_DYNAMIC_Type *Queue_Create_DYNAMIC_uint8(uint8 DynamicSize){
    Queue_uint8_DYNAMIC_Type* me = (Queue_uint8_DYNAMIC_Type*)malloc(sizeof(Queue_uint8_DYNAMIC_Type));
        if(me != Null_Ptr){
            if(DynamicSize > 0){
                Queue_Init_uint8_d(me, DynamicSize, Queue_isFull_uint8_d, Queue_isEmpty_uint8_d, Queue_getSize_uint8_d,
                           Queue_insert_uint8_d, Queue_remove_uint8_d);
            }
        }
        return me;
}

void Queue_Destroy_DYNAMIC_uint8(Queue_uint8_DYNAMIC_Type* const me){
    if(me != Null_Ptr){
        Queue_CleanUp_uint8_d(me);
    }
    free(me);
}
/*********************************************
 *           Constructor and Destructor
 *********************************************/

void Queue_Init_uint8_d(Queue_uint8_DYNAMIC_Type* const me ,uint8 Dynamic_Size_P, uint8 (*isFullFunction)(Queue_uint8_DYNAMIC_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint8_DYNAMIC_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint8_DYNAMIC_Type* const me),
                void (*insertFunction)(Queue_uint8_DYNAMIC_Type* const me, uint8 x) ,uint8 (*removeFunction)(Queue_uint8_DYNAMIC_Type* const me) ){
    me->head = 0;
    me->size = 0;
    me->tail = 0;
    me->Dynamic_Size = Dynamic_Size_P;
    /* Initialize function pointers */
    if(me->Dynamic_Size > 0){
        me->Buffer = (uint8*)malloc(sizeof(uint8) * me->Dynamic_Size);
    }
    me->isFull = isFullFunction;
    me->isEmpty = isEmptyFunction;
    me->getSize = getSizeFunction;
    me->insert = insertFunction;
    me->remove = removeFunction;
}


void Queue_CleanUp_uint8_d(Queue_uint8_DYNAMIC_Type* const me){
    free(me->Buffer);
}

/*********************************************
 *           Dynamic Operations
 *********************************************/


/* Operation isFull() */
uint8 Queue_isFull_uint8_d(Queue_uint8_DYNAMIC_Type* const me){
    return(((me->head + 1) % me->Dynamic_Size) == me->tail);
}

/* Operation isEmpty() */
uint8 Queue_isEmpty_uint8_d(Queue_uint8_DYNAMIC_Type *const me){
    return (me->head == me->tail);
}

/* Operation getSize() */
uint8 Queue_getSize_uint8_d(Queue_uint8_DYNAMIC_Type* const me){
    return me->size;
}

/* Operation insert(int) */
void Queue_insert_uint8_d(Queue_uint8_DYNAMIC_Type* const me, uint8 x){
    if(!(me->isFull(me))){
        me->Buffer[me->head] = x;
        me->head = (me->head + 1) % me->Dynamic_Size;
        ++me->size;
    }
}

/* Operation remove() */
uint8 Queue_remove_uint8_d(Queue_uint8_DYNAMIC_Type* const me){
    uint8 value = 0;
    if(!(me->isEmpty(me))){
        value = me->Buffer[me->tail];
        me->Buffer[me->tail] = '0';
        me->tail = (me->tail + 1) % me->Dynamic_Size;
        --me->size;
    }
    return value;
}

