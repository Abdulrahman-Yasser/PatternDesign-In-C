/*
 * Normal_Queue_Types.h
 *
 *  Created on: Apr 14, 2023
 *      Author: Abdu
 */

#ifndef DATASTRUCTURE_NORMAL_QUEUE_STATIC_INC_NORMAL_QUEUE_TYPES_H_
#define DATASTRUCTURE_NORMAL_QUEUE_STATIC_INC_NORMAL_QUEUE_TYPES_H_

#include "Std_Types.h"
#include "../../dynamic/inc/Normal_Queue_Cfg.h"




typedef enum {
    Normal_Queue_uint8, Normal_Queue_uint16, Normal_Queue_uint32,
}Normal_Queue_Types;

typedef struct{
    Normal_Queue_Types my_type;
    union {
        uint8* u8_ptr;
        uint16* u16_ptr;
        uint32* u32_ptr;
    }Buffer;
    uint8 Dynamic_Size;
    uint8 head;
    uint8 size;
    uint8 tail;
}Normal_Queue_DynamicUint;

typedef struct{
    Normal_Queue_Types my_type;
    union {
        uint8 u8[NORMAL_QUEUE_BUFFER_SIZE_STATIC];
        uint16 u16[NORMAL_QUEUE_BUFFER_SIZE_STATIC];
        uint32 u32[NORMAL_QUEUE_BUFFER_SIZE_STATIC];
    }Buffer;
    uint8 head;
    uint8 size;
    uint8 tail;
}Normal_Queue_StaticUint;

#endif /* DATASTRUCTURE_NORMAL_QUEUE_STATIC_INC_NORMAL_QUEUE_TYPES_H_ */
