/*
 * Normal_Queue.c
 *
 *  Created on: Apr 14, 2023
 *      Author: Abdu
 */

#include "../inc/Normal_Queue.h"
#include "../../../../Compiler.h"
#include <stdlib.h>

Normal_Queue_DynamicUint *Queue_Create_DYNAMIC_uint(uint8 Dynamic_Size, Normal_Queue_Types queue_type){
    Normal_Queue_DynamicUint* me;
    me = (Normal_Queue_DynamicUint*)malloc(sizeof(Normal_Queue_DynamicUint));

    if(me != Null_Ptr){
        switch(queue_type){
        case Normal_Queue_uint8:
            me->Buffer.u8_ptr = (uint8*)malloc(sizeof(uint8) * Dynamic_Size);
            break;
        case Normal_Queue_uint16:
            me->Buffer.u16_ptr = (uint16*)malloc(sizeof(uint16) * Dynamic_Size);
            break;
        case Normal_Queue_uint32:
            me->Buffer.u32_ptr = (uint32*)malloc(sizeof(uint16) * Dynamic_Size);
            break;
        }

        me->Dynamic_Size = Dynamic_Size;
        me->head = 0;
        me->my_type = queue_type;
        me->size = 0;
        me->tail = 0;
    }
    return me;
}

void Queue_Destroy_DYNAMIC_uint(Normal_Queue_DynamicUint* const me){
}

/* Constructor and Destructor Static Allocation */

Normal_Queue_StaticUint *Queue_Create_STATIC_uint(Normal_Queue_Types queue_type){
    Normal_Queue_StaticUint* me;
    me = (Normal_Queue_StaticUint*)malloc( sizeof(Normal_Queue_StaticUint) );

    if(me != Null_Ptr){
        me->my_type = queue_type;
        me->head = 0;
        me->size = 0;
        me->tail = 0;
    }
    return me;
}
void Queue_Destroy_STATIC_uint(Normal_Queue_StaticUint* const me){
}


uint8 NormalQueue_Static_isFull(Normal_Queue_StaticUint* const my_queue){
    return ((my_queue->head + 1) % NORMAL_QUEUE_BUFFER_SIZE_STATIC == my_queue->tail);
}
uint8 NormalQueue_Static_isEmpty(Normal_Queue_StaticUint* const my_queue){
    return (my_queue->head == my_queue->tail);
}
uint8 NormalQueue_Static_getSize(Normal_Queue_StaticUint* const my_queue){
    return my_queue->size;
}
void NormalQueue_Static_insert(Normal_Queue_StaticUint* const my_queue, uint32 data){
    if(!NormalQueue_Static_isFull(my_queue)){
        switch(my_queue->my_type){
        case Normal_Queue_uint8:
            my_queue->Buffer.u8[my_queue->head] = data;
            break;
        case Normal_Queue_uint16:
            my_queue->Buffer.u16[my_queue->head] = data;
            break;
        case Normal_Queue_uint32:
            my_queue->Buffer.u32[my_queue->head] = data;
            break;
        }
        my_queue->head = (my_queue->head + 1) % NORMAL_QUEUE_BUFFER_SIZE_STATIC;
        ++my_queue->size;
    }
}
uint32 NormalQueue_Static_remove(Normal_Queue_StaticUint* const my_queue){
    uint32 result = 0;
    if(!NormalQueue_Static_isEmpty(my_queue)){
        switch(my_queue->my_type){
        case Normal_Queue_uint8:
            result = my_queue->Buffer.u8[my_queue->tail];
            break;
        case Normal_Queue_uint16:
            result = my_queue->Buffer.u16[my_queue->tail];
            break;
        case Normal_Queue_uint32:
            result = my_queue->Buffer.u32[my_queue->tail];
            break;
        }
        my_queue->tail = (my_queue->tail + 1) % NORMAL_QUEUE_BUFFER_SIZE_STATIC;
        --my_queue->size;
    }
    return result;
}


uint8 NormalQueue_Dynamic_isFull(Normal_Queue_DynamicUint* const my_queue){
    return(my_queue->head + 1) % my_queue->Dynamic_Size == my_queue->tail;
}
uint8 NormalQueue_Dynamic_isEmpty(Normal_Queue_DynamicUint* const my_queue){
    return (my_queue->head == my_queue->tail);
}
uint8 NormalQueue_Dynamic_getSize(Normal_Queue_DynamicUint* const my_queue){
    return my_queue->size;
}
void NormalQueue_Dynamic_insert(Normal_Queue_DynamicUint* const my_queue, uint32 data){
    if(!NormalQueue_Dynamic_isFull(my_queue)){
        switch(my_queue->my_type){
        case Normal_Queue_uint8:
            my_queue->Buffer.u8_ptr[my_queue->head] = data;
            break;
        case Normal_Queue_uint16:
            my_queue->Buffer.u16_ptr[my_queue->head] = data;
            break;
        case Normal_Queue_uint32:
            my_queue->Buffer.u32_ptr[my_queue->head] = data;
            break;
        }
        my_queue->head = (my_queue->head + 1) % my_queue->Dynamic_Size;
        ++my_queue->size;
    }
}
uint32 NormalQueue_Dynamic_remove(Normal_Queue_DynamicUint* const my_queue){
    uint32 result = 0;
    if(!NormalQueue_Dynamic_isEmpty(my_queue)){
        switch(my_queue->my_type){
        case Normal_Queue_uint8:
            result = my_queue->Buffer.u8_ptr[my_queue->tail];
            break;
        case Normal_Queue_uint16:
            result = my_queue->Buffer.u16_ptr[my_queue->tail];
            break;
        case Normal_Queue_uint32:
            result = my_queue->Buffer.u32_ptr[my_queue->tail];
            break;
        }
        my_queue->tail = (my_queue->tail + 1) % my_queue->Dynamic_Size;
        --my_queue->size;
    }
    return result;
}



