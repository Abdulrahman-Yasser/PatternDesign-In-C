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


typedef uint8 Queue_Dynamic_SizeType;

typedef struct Queue_uint8 Queue_uint8_Type;
typedef struct Queue_uint16 Queue_uint16_Type;
typedef struct Queue_uint32 Queue_uint32_Type;

struct Queue_uint8{
    uint8 Static_buffer[QUEUE_BUFFER_SIZE_STATIC];
    uint8 *Dynamic_buffer;
    uint8 head;
    uint8 size;
    uint8 tail;
    uint8 (*isFull)(Queue_uint8_Type* const me);
    uint8 (*isEmpty)(Queue_uint8_Type* const me);
    uint8 (*getSize)(Queue_uint8_Type* const me);
    void (*insert)(Queue_uint8_Type* const me, uint8 x);
    uint8 (*remove)(Queue_uint8_Type* const me);
};

struct Queue_uint16{
    uint16 Static_buffer[QUEUE_BUFFER_SIZE_STATIC];
    uint16 *Dynamic_buffer;
    uint8 head;
    uint8 size;
    uint8 tail;
    uint8 (*isFull)(Queue_uint16_Type* const me);
    uint8 (*isEmpty)(Queue_uint16_Type* const me);
    uint8 (*getSize)(Queue_uint16_Type* const me);
    void (*insert)(Queue_uint16_Type* const me, uint16 x);
    uint16 (*remove)(Queue_uint16_Type* const me);
};

struct Queue_uint32{
    uint32 Static_buffer[QUEUE_BUFFER_SIZE_STATIC];
    uint32 *Dynamic_buffer;
    uint8 head;
    uint8 size;
    uint8 tail;
    uint8 (*isFull)(Queue_uint32_Type* const me);
    uint8 (*isEmpty)(Queue_uint32_Type* const me);
    uint8 (*getSize)(Queue_uint32_Type* const me);
    void (*insert)(Queue_uint32_Type* const me, uint32 x);
    uint32 (*remove)(Queue_uint32_Type* const me);
};

#endif /* COMMON_DATASTRUCTURE_QUEUE_STATIC_INC_QUEUE_TYPES_H_ */
