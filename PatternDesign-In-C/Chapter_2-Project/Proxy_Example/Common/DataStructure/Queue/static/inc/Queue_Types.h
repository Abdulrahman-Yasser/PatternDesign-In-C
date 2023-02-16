/*
 * Queue_Types.h
 *
 *  Created on: Dec 20, 2022
 *      Author: abduy
 */

#ifndef COMMON_DATASTRUCTURE_QUEUE_STATIC_INC_QUEUE_TYPES_H_
#define COMMON_DATASTRUCTURE_QUEUE_STATIC_INC_QUEUE_TYPES_H_

#include "../../../../Platform_Types.h"
#include "../../dynamic/inc/Queue_Cfg.h"



typedef struct Queue_uint8_s Queue_uint8_STATIC_Type;
typedef struct Queue_uint16_s Queue_uint16_STATIC_Type;
typedef struct Queue_uint32_s Queue_uint32_STATIC_Type;

typedef struct Queue_uint8_d Queue_uint8_DYNAMIC_Type;
typedef struct Queue_uint16_d Queue_uint16_DYNAMIC_Type;
typedef struct Queue_uint32_d Queue_uint32_DYNAMIC_Type;

struct Queue_uint8_s{
    uint8 Buffer[QUEUE_BUFFER_SIZE_STATIC];
    uint8 head;
    uint8 size;
    uint8 tail;
    uint8 (*isFull)(Queue_uint8_STATIC_Type* const me);
    uint8 (*isEmpty)(Queue_uint8_STATIC_Type* const me);
    uint8 (*getSize)(Queue_uint8_STATIC_Type* const me);
    void (*insert)(Queue_uint8_STATIC_Type* const me, uint8 x);
    uint8 (*remove)(Queue_uint8_STATIC_Type* const me);
};

struct Queue_uint16_s{
    uint16 Buffer[QUEUE_BUFFER_SIZE_STATIC];
    uint8 head;
    uint8 size;
    uint8 tail;
    uint8 (*isFull)(Queue_uint16_STATIC_Type* const me);
    uint8 (*isEmpty)(Queue_uint16_STATIC_Type* const me);
    uint8 (*getSize)(Queue_uint16_STATIC_Type* const me);
    void (*insert)(Queue_uint16_STATIC_Type* const me, uint16 x);
    uint16 (*remove)(Queue_uint16_STATIC_Type* const me);
};

struct Queue_uint32_s{
    uint32 Buffer[QUEUE_BUFFER_SIZE_STATIC];
    uint8 head;
    uint8 size;
    uint8 tail;
    uint8 (*isFull)(Queue_uint32_STATIC_Type* const me);
    uint8 (*isEmpty)(Queue_uint32_STATIC_Type* const me);
    uint8 (*getSize)(Queue_uint32_STATIC_Type* const me);
    void (*insert)(Queue_uint32_STATIC_Type* const me, uint32 x);
    uint32 (*remove)(Queue_uint32_STATIC_Type* const me);
};

struct Queue_uint8_d{
    uint8 *Buffer;
    uint8 Dynamic_Size;
    uint8 head;
    uint8 size;
    uint8 tail;
    uint8 (*isFull)(Queue_uint8_DYNAMIC_Type* const me);
    uint8 (*isEmpty)(Queue_uint8_DYNAMIC_Type* const me);
    uint8 (*getSize)(Queue_uint8_DYNAMIC_Type* const me);
    void (*insert)(Queue_uint8_DYNAMIC_Type* const me, uint8 x);
    uint8 (*remove)(Queue_uint8_DYNAMIC_Type* const me);
};

struct Queue_uint16_d{
    uint16 *Buffer;
    uint8 Dynamic_Size;
    uint8 head;
    uint8 size;
    uint8 tail;
    uint8 (*isFull)(Queue_uint16_DYNAMIC_Type* const me);
    uint8 (*isEmpty)(Queue_uint16_DYNAMIC_Type* const me);
    uint8 (*getSize)(Queue_uint16_DYNAMIC_Type* const me);
    void (*insert)(Queue_uint16_DYNAMIC_Type* const me, uint16 x);
    uint16 (*remove)(Queue_uint16_DYNAMIC_Type* const me);
};

struct Queue_uint32_d{
    uint32 *Buffer;
    uint8 Dynamic_Size;
    uint8 head;
    uint8 size;
    uint8 tail;
    uint8 (*isFull)(Queue_uint32_DYNAMIC_Type* const me);
    uint8 (*isEmpty)(Queue_uint32_DYNAMIC_Type* const me);
    uint8 (*getSize)(Queue_uint32_DYNAMIC_Type* const me);
    void (*insert)(Queue_uint32_DYNAMIC_Type* const me, uint32 x);
    uint32 (*remove)(Queue_uint32_DYNAMIC_Type* const me);
};


#endif /* COMMON_DATASTRUCTURE_QUEUE_STATIC_INC_QUEUE_TYPES_H_ */
