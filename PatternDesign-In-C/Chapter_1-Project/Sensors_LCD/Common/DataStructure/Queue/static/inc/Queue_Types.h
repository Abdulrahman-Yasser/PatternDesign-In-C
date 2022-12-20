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

// #include <stdlib.h>

typedef struct {
    uint32 *buffer;
    uint8 head;
    uint8 size;
    uint8 tail;
    uint8 (*isFull)(Queue_uint32_8_Type* const me);
    uint8 (*isEmpty)(Queue_uint32_8_Type* const me);
    uint8 (*getSize)(Queue_uint32_8_Type* const me);
    void (*insert)(Queue_uint32_8_Type* const me, uint32 x);
    uint8 (*remove)(Queue_uint32_8_Type* const me);
}Queue_uint32_Dynamic_Type;

typedef struct {
    uint16 *buffer;
    uint8 head;
    uint8 size;
    uint8 tail;
    uint8 (*isFull)(Queue_uint32_8_Type* const me);
    uint8 (*isEmpty)(Queue_uint32_8_Type* const me);
    uint8 (*getSize)(Queue_uint32_8_Type* const me);
    void (*insert)(Queue_uint32_8_Type* const me, uint32 x);
    uint8 (*remove)(Queue_uint32_8_Type* const me);
}Queue_uint16_Dynamic_Type;

typedef struct {
    uint8 *buffer;
    uint8 head;
    uint8 size;
    uint8 tail;
    uint8 (*isFull)(Queue_uint32_8_Type* const me);
    uint8 (*isEmpty)(Queue_uint32_8_Type* const me);
    uint8 (*getSize)(Queue_uint32_8_Type* const me);
    void (*insert)(Queue_uint32_8_Type* const me, uint32 x);
    uint8 (*remove)(Queue_uint32_8_Type* const me);
}Queue_uint8_Dynamic_Type;


typedef struct {
    uint32 buffer[BUFFER_SIZE];
    uint8 head;
    uint8 size;
    uint8 tail;
    uint8 (*isFull)(Queue_uint32_8_Type* const me);
    uint8 (*isEmpty)(Queue_uint32_8_Type* const me);
    uint8 (*getSize)(Queue_uint32_8_Type* const me);
    void (*insert)(Queue_uint32_8_Type* const me, uint32 x);
    uint8 (*remove)(Queue_uint32_8_Type* const me);
}Queue_uint32_8_Type;

typedef struct {
    uint32 buffer[BUFFER_SIZE * 2];
    uint8 head;
    uint8 size;
    uint8 tail;
    uint8 (*isFull)(Queue_uint32_16_Type* const me);
    uint8 (*isEmpty)(Queue_uint32_16_Type* const me);
    uint8 (*getSize)(Queue_uint32_16_Type* const me);
    void (*insert)(Queue_uint32_16_Type* const me, uint32 x);
    uint8 (*remove)(Queue_uint32_16_Type* const me);
}Queue_uint32_16_Type;

typedef struct {
    uint32 buffer[BUFFER_SIZE * 4];
    uint8 head;
    uint8 size;
    uint8 tail;
    uint8 (*isFull)(Queue_uint32_32_Type* const me);
    uint8 (*isEmpty)(Queue_uint32_32_Type* const me);
    uint8 (*getSize)(Queue_uint32_32_Type* const me);
    void (*insert)(Queue_uint32_32_Type* const me, uint32 x);
    uint8 (*remove)(Queue_uint32_32_Type* const me);
}Queue_uint32_32_Type;

typedef struct {
    uint16 buffer[BUFFER_SIZE];
    uint8 head;
    uint8 size;
    uint8 tail;
    uint8 (*isFull)(Queue_uint16_8_Type* const me);
    uint8 (*isEmpty)(Queue_uint16_8_Type* const me);
    uint8 (*getSize)(Queue_uint16_8_Type* const me);
    void (*insert)(Queue_uint16_8_Type* const me, uint16 x);
    uint8 (*remove)(Queue_uint16_8_Type* const me);
}Queue_uint16_8_Type;

typedef struct {
    uint16 buffer[BUFFER_SIZE * 2];
    uint8 head;
    uint8 size;
    uint8 tail;
    uint8 (*isFull)(Queue_uint16_16_Type* const me);
    uint8 (*isEmpty)(Queue_uint16_16_Type* const me);
    uint8 (*getSize)(Queue_uint16_16_Type* const me);
    void (*insert)(Queue_uint16_16_Type* const me, uint16 x);
    uint8 (*remove)(Queue_uint16_16_Type* const me);
}Queue_uint16_16_Type;

typedef struct {
    uint16 buffer[BUFFER_SIZE * 4];
    uint8 head;
    uint8 size;
    uint8 tail;
    uint8 (*isFull)(Queue_uint16_32_Type* const me);
    uint8 (*isEmpty)(Queue_uint16_32_Type* const me);
    uint8 (*getSize)(Queue_uint16_32_Type* const me);
    void (*insert)(Queue_uint16_32_Type* const me, uint16 x);
    uint8 (*remove)(Queue_uint16_32_Type* const me);
}Queue_uint16_32_Type;

typedef struct {
    uint8 buffer[BUFFER_SIZE];
    uint8 head;
    uint8 size;
    uint8 tail;
    uint8 (*isFull)(Queue_uint8_8_Type* const me);
    uint8 (*isEmpty)(Queue_uint8_8_Type* const me);
    uint8 (*getSize)(Queue_uint8_8_Type* const me);
    void (*insert)(Queue_uint8_8_Type* const me, uint8 x);
    uint8 (*remove)(Queue_uint8_8_Type* const me);
}Queue_uint8_8_Type;

typedef struct {
    uint8 buffer[BUFFER_SIZE * 2];
    uint8 head;
    uint8 size;
    uint8 tail;
    uint8 (*isFull)(Queue_uint8_16_Type* const me);
    uint8 (*isEmpty)(Queue_uint8_16_Type* const me);
    uint8 (*getSize)(Queue_uint8_16_Type* const me);
    void (*insert)(Queue_uint8_16_Type* const me, uint8 x);
    uint8 (*remove)(Queue_uint8_16_Type* const me);
}Queue_uint8_16_Type;

typedef struct {
    uint8 buffer[BUFFER_SIZE * 4];
    uint8 head;
    uint8 size;
    uint8 tail;
    uint8 (*isFull)(Queue_uint8_32_Type* const me);
    uint8 (*isEmpty)(Queue_uint8_32_Type* const me);
    uint8 (*getSize)(Queue_uint8_32_Type* const me);
    void (*insert)(Queue_uint8_32_Type* const me, uint8 x);
    uint8 (*remove)(Queue_uint8_32_Type* const me);
}Queue_uint8_32_Type;




#endif /* COMMON_DATASTRUCTURE_QUEUE_STATIC_INC_QUEUE_TYPES_H_ */
