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
 *
 *                                    uint32
 *
 **************************************************************************************/
void Queue_Init_uint32(Queue_uint32_Type* const me ,uint8 (*isFullFunction)(Queue_uint32_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint32_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint32_Type* const me),
                void (*insertFunction)(Queue_uint32_Type* const me, uint32 x) ,uint32 (*removeFunction)(Queue_uint32_Type* const me) ){
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
void Queue_CleanUp_uint32(Queue_uint32_Type* const me){
    free(me->Dynamic_buffer);
    free(me->Static_buffer);
}

/*********************************************
 *           Static Operations
 *********************************************/

/* Operation isFull() */
uint8 Queue_isFull_uint32_s(Queue_uint32_Type* const me){
    return(me->head + 1) % QUEUE_BUFFER_SIZE_STATIC == me->tail;
}

/* Operation isEmpty() */
uint8 Queue_isEmpty_uint32_s(Queue_uint32_Type *const me){
    return (me->head = me->tail);
}

/* Operation getSize() */
uint8 Queue_getSize_uint32_s(Queue_uint32_Type* const me){
    return me->size;
}

/* Operation insert(int) */
void Queue_insert_uint32_s(Queue_uint32_Type* const me, uint32 x){
    if(me->isFull(me)){
        me->Static_buffer[me->head] = x;
        me->head = (me->head + 1) % QUEUE_BUFFER_SIZE_STATIC;
        ++me->size;
    }
}

/* Operation remove() */
uint32 Queue_remove_uint32_s(Queue_uint32_Type* const me){
    uint32 value = 0;
    if(!me->isEmpty(me)){
        value = me->Static_buffer[me->tail];
        me->tail = (me->tail + 1) % QUEUE_BUFFER_SIZE_STATIC;
        --me->size;
    }
    return value;
}

/*********************************************
 *           Dynamic Operations
 *********************************************/

/* Operation Clean_up() */
void Queue_CleanUp_uint32_d(Queue_uint32_Type* const me){
    free(me->Dynamic_buffer);
    free(me->Static_buffer);
}

/* Operation isFull() */
uint8 Queue_isFull_uint32_d(Queue_uint32_Type* const me){
    return(me->head + 1) % QUEUE_BUFFER_SIZE_STATIC == me->tail;
}

/* Operation isEmpty() */
uint8 Queue_isEmpty_uint32_d(Queue_uint32_Type *const me){
    return (me->head = me->tail);
}

/* Operation getSize() */
uint8 Queue_getSize_uint32_d(Queue_uint32_Type* const me){
    return me->size;
}

/* Operation insert(int) */
void Queue_insert_uint32_d(Queue_uint32_Type* const me, uint32 x){
    if(me->isFull(me)){
        me->Dynamic_buffer[me->head] = x;
        me->head = (me->head + 1) % QUEUE_BUFFER_SIZE_STATIC;
        ++me->size;
    }
}

/* Operation remove() */
uint32 Queue_remove_uint32_d(Queue_uint32_Type* const me){
    uint32 value = 0;
    if(!me->isEmpty(me)){
        value = me->Dynamic_buffer[me->tail];
        me->tail = (me->tail + 1) % QUEUE_BUFFER_SIZE_STATIC;
        --me->size;
    }
    return value;
}

/****************************************************
 *              Creation and cleaning
 ****************************************************/

Queue_uint32_Type *Queue_Create_uint32(Queue_Dynamic_SizeType DynamicSize){
    Queue_uint32_Type* me = (Queue_uint32_Type*)malloc(sizeof(Queue_uint32_Type));
        if(me != Null_Ptr){
            if(DynamicSize == 0){
                Queue_Init_uint32(me, Queue_isFull_uint32_s, Queue_isEmpty_uint32_s, Queue_getSize_uint32_s,
                           Queue_insert_uint32_s, Queue_remove_uint32_s);
            }else{
                me->Dynamic_buffer = (uint32*)malloc(sizeof(uint32) * DynamicSize);
                Queue_Init_uint32(me, Queue_isFull_uint32_d, Queue_isEmpty_uint32_d, Queue_getSize_uint32_d,
                           Queue_insert_uint32_d, Queue_remove_uint32_d);
            }
        }
        return me;
}

void Queue_Destroy_uint32(Queue_uint32_Type* const me){
    if(me != Null_Ptr){
        Queue_CleanUp_uint32(me);
    }
    free(me);
}


/**************************************************************************************
 *
 *                                    uint16
 *
 **************************************************************************************/
void Queue_Init_uint16(Queue_uint16_Type* const me ,uint8 (*isFullFunction)(Queue_uint16_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint16_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint16_Type* const me),
                void (*insertFunction)(Queue_uint16_Type* const me, uint16 x) ,uint16 (*removeFunction)(Queue_uint16_Type* const me) ){
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
void Queue_CleanUp_uint16(Queue_uint16_Type* const me){
    free(me->Dynamic_buffer);
    free(me->Static_buffer);
}

/*********************************************
 *           Static Operations
 *********************************************/

/* Operation isFull() */
uint8 Queue_isFull_uint16_s(Queue_uint16_Type* const me){
    return(me->head + 1) % QUEUE_BUFFER_SIZE_STATIC == me->tail;
}

/* Operation isEmpty() */
uint8 Queue_isEmpty_uint16_s(Queue_uint16_Type *const me){
    return (me->head = me->tail);
}

/* Operation getSize() */
uint8 Queue_getSize_uint16_s(Queue_uint16_Type* const me){
    return me->size;
}

/* Operation insert(int) */
void Queue_insert_uint16_s(Queue_uint16_Type* const me, uint16 x){
    if(me->isFull(me)){
        me->Static_buffer[me->head] = x;
        me->head = (me->head + 1) % QUEUE_BUFFER_SIZE_STATIC;
        ++me->size;
    }
}

/* Operation remove() */
uint16 Queue_remove_uint16_s(Queue_uint16_Type* const me){
    uint16 value = 0;
    if(!me->isEmpty(me)){
        value = me->Static_buffer[me->tail];
        me->tail = (me->tail + 1) % QUEUE_BUFFER_SIZE_STATIC;
        --me->size;
    }
    return value;
}

/*********************************************
 *           Dynamic Operations
 *********************************************/

/* Operation Clean_up() */
void Queue_CleanUp_uint16_d(Queue_uint16_Type* const me){
    free(me->Dynamic_buffer);
    free(me->Static_buffer);
}

/* Operation isFull() */
uint8 Queue_isFull_uint16_d(Queue_uint16_Type* const me){
    return(me->head + 1) % QUEUE_BUFFER_SIZE_STATIC == me->tail;
}

/* Operation isEmpty() */
uint8 Queue_isEmpty_uint16_d(Queue_uint16_Type *const me){
    return (me->head = me->tail);
}

/* Operation getSize() */
uint8 Queue_getSize_uint16_d(Queue_uint16_Type* const me){
    return me->size;
}

/* Operation insert(int) */
void Queue_insert_uint16_d(Queue_uint16_Type* const me, uint16 x){
    if(me->isFull(me)){
        me->Dynamic_buffer[me->head] = x;
        me->head = (me->head + 1) % QUEUE_BUFFER_SIZE_STATIC;
        ++me->size;
    }
}

/* Operation remove() */
uint16 Queue_remove_uint16_d(Queue_uint16_Type* const me){
    uint16 value = 0;
    if(!me->isEmpty(me)){
        value = me->Dynamic_buffer[me->tail];
        me->tail = (me->tail + 1) % QUEUE_BUFFER_SIZE_STATIC;
        --me->size;
    }
    return value;
}

/****************************************************
 *              Creation and cleaning
 ****************************************************/

Queue_uint16_Type *Queue_Create_uint16(Queue_Dynamic_SizeType DynamicSize){
    Queue_uint16_Type* me = (Queue_uint16_Type*)malloc(sizeof(Queue_uint16_Type));
        if(me != Null_Ptr){
            if(DynamicSize == 0){
                Queue_Init_uint16(me, Queue_isFull_uint16_s, Queue_isEmpty_uint16_s, Queue_getSize_uint16_s,
                           Queue_insert_uint16_s, Queue_remove_uint16_s);
            }else{
                me->Dynamic_buffer = (uint16*)malloc(sizeof(uint16) * DynamicSize);
                Queue_Init_uint16(me, Queue_isFull_uint16_d, Queue_isEmpty_uint16_d, Queue_getSize_uint16_d,
                           Queue_insert_uint16_d, Queue_remove_uint16_d);
            }
        }
        return me;
}

void Queue_Destroy_uint16(Queue_uint16_Type* const me){
    if(me != Null_Ptr){
        Queue_CleanUp_uint16(me);
    }
    free(me);
}


/**************************************************************************************
 *
 *                                    uint8
 *
 **************************************************************************************/
void Queue_Init_uint8(Queue_uint8_Type* const me ,uint8 (*isFullFunction)(Queue_uint8_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint8_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint8_Type* const me),
                void (*insertFunction)(Queue_uint8_Type* const me, uint8 x) ,uint8 (*removeFunction)(Queue_uint8_Type* const me) ){
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
void Queue_CleanUp_uint8(Queue_uint8_Type* const me){
    free(me->Dynamic_buffer);
    free(me->Static_buffer);
}

/*********************************************
 *           Static Operations
 *********************************************/

/* Operation isFull() */
uint8 Queue_isFull_uint8_s(Queue_uint8_Type* const me){
    return(me->head + 1) % QUEUE_BUFFER_SIZE_STATIC == me->tail;
}

/* Operation isEmpty() */
uint8 Queue_isEmpty_uint8_s(Queue_uint8_Type *const me){
    return (me->head = me->tail);
}

/* Operation getSize() */
uint8 Queue_getSize_uint8_s(Queue_uint8_Type* const me){
    return me->size;
}

/* Operation insert(int) */
void Queue_insert_uint8_s(Queue_uint8_Type* const me, uint8 x){
    if(me->isFull(me)){
        me->Static_buffer[me->head] = x;
        me->head = (me->head + 1) % QUEUE_BUFFER_SIZE_STATIC;
        ++me->size;
    }
}

/* Operation remove() */
uint8 Queue_remove_uint8_s(Queue_uint8_Type* const me){
    uint8 value = 0;
    if(!me->isEmpty(me)){
        value = me->Static_buffer[me->tail];
        me->tail = (me->tail + 1) % QUEUE_BUFFER_SIZE_STATIC;
        --me->size;
    }
    return value;
}

/*********************************************
 *           Dynamic Operations
 *********************************************/

/* Operation Clean_up() */
void Queue_CleanUp_uint8_d(Queue_uint8_Type* const me){
    free(me->Dynamic_buffer);
    free(me->Static_buffer);
}

/* Operation isFull() */
uint8 Queue_isFull_uint8_d(Queue_uint8_Type* const me){
    return(me->head + 1) % QUEUE_BUFFER_SIZE_STATIC == me->tail;
}

/* Operation isEmpty() */
uint8 Queue_isEmpty_uint8_d(Queue_uint8_Type *const me){
    return (me->head = me->tail);
}

/* Operation getSize() */
uint8 Queue_getSize_uint8_d(Queue_uint8_Type* const me){
    return me->size;
}

/* Operation insert(int) */
void Queue_insert_uint8_d(Queue_uint8_Type* const me, uint8 x){
    if(me->isFull(me)){
        me->Dynamic_buffer[me->head] = x;
        me->head = (me->head + 1) % QUEUE_BUFFER_SIZE_STATIC;
        ++me->size;
    }
}

/* Operation remove() */
uint8 Queue_remove_uint8_d(Queue_uint8_Type* const me){
    uint8 value = 0;
    if(!me->isEmpty(me)){
        value = me->Dynamic_buffer[me->tail];
        me->tail = (me->tail + 1) % QUEUE_BUFFER_SIZE_STATIC;
        --me->size;
    }
    return value;
}

/****************************************************
 *              Creation and cleaning
 ****************************************************/

Queue_uint8_Type *Queue_Create_uint8(Queue_Dynamic_SizeType DynamicSize){
    Queue_uint8_Type* me = (Queue_uint8_Type*)malloc(sizeof(Queue_uint8_Type));
        if(me != Null_Ptr){
            if(DynamicSize == 0){
                Queue_Init_uint8(me, Queue_isFull_uint8_s, Queue_isEmpty_uint8_s, Queue_getSize_uint8_s,
                           Queue_insert_uint8_s, Queue_remove_uint8_s);
            }else{
                me->Dynamic_buffer = (uint8*)malloc(sizeof(uint8) * DynamicSize);
                Queue_Init_uint8(me, Queue_isFull_uint8_d, Queue_isEmpty_uint8_d, Queue_getSize_uint8_d,
                           Queue_insert_uint8_d, Queue_remove_uint8_d);
            }
        }
        return me;
}

void Queue_Destroy_uint8(Queue_uint8_Type* const me){
    if(me != Null_Ptr){
        Queue_CleanUp_uint8(me);
    }
    free(me);
}

