/*
 * Stack_Types.h
 *
 *  Created on: Dec 26, 2022
 *      Author: abduy
 */

#ifndef COMMON_DATASTRUCTURE_STACK_STATIC_INC_STACK_TYPES_H_
#define COMMON_DATASTRUCTURE_STACK_STATIC_INC_STACK_TYPES_H_


#include "../../../../Platform_Types.h"
#include "../../../../Std_Types.h"
#include "../../Dynamic/inc/Stack_Cfg.h"

typedef struct Stack_uint8_s Stack_uint8_STATIC_Type;
typedef struct Stack_uint16_s Stack_uint16_STATIC_Type;
typedef struct Stack_uint32_s Stack_uint32_STATIC_Type;

typedef struct Stack_uint8_d Stack_uint8_DYNAMIC_Type;
typedef struct Stack_uint16_d Stack_uint16_DYNAMIC_Type;
typedef struct Stack_uint32_d Stack_uint32_DYNAMIC_Type;

struct Stack_uint8_s{
    uint8 Buffer[STACK_BUFFER_SIZE_STATIC];
    uint8 top;
    uint8 (*isFull)(Stack_uint8_STATIC_Type* const me);
    uint8 (*isEmpty)(Stack_uint8_STATIC_Type* const me);
    uint8 (*getCount)(Stack_uint8_STATIC_Type* const me);
    void (*push)(Stack_uint8_STATIC_Type* const me, uint8 x);
    uint8 (*pop)(Stack_uint8_STATIC_Type* const me);
};

struct Stack_uint16_s{
    uint16 Buffer[STACK_BUFFER_SIZE_STATIC];
    uint8 top;
    uint8 (*isFull)(Stack_uint16_STATIC_Type* const me);
    uint8 (*isEmpty)(Stack_uint16_STATIC_Type* const me);
    uint8 (*getCount)(Stack_uint16_STATIC_Type* const me);
    void (*push)(Stack_uint16_STATIC_Type* const me, uint16 x);
    uint16 (*pop)(Stack_uint16_STATIC_Type* const me);
};

struct Stack_uint32_s{
    uint32 Buffer[STACK_BUFFER_SIZE_STATIC];
    uint8 top;
    uint8 (*isFull)(Stack_uint32_STATIC_Type* const me);
    uint8 (*isEmpty)(Stack_uint32_STATIC_Type* const me);
    uint8 (*getCount)(Stack_uint32_STATIC_Type* const me);
    void (*push)(Stack_uint32_STATIC_Type* const me, uint32 x);
    uint32 (*pop)(Stack_uint32_STATIC_Type* const me);
};


struct Stack_uint8_d{
    uint8 *Buffer;
    uint8 Dynamic_Size;
    uint8 top;
    uint8 (*isFull)(Stack_uint8_DYNAMIC_Type* const me);
    uint8 (*isEmpty)(Stack_uint8_DYNAMIC_Type* const me);
    uint8 (*getCount)(Stack_uint8_DYNAMIC_Type* const me);
    void (*push)(Stack_uint8_DYNAMIC_Type* const me, uint8 x);
    uint8 (*pop)(Stack_uint8_DYNAMIC_Type* const me);
};


struct Stack_uint16_d{
    uint16 *Buffer;
    uint8 Dynamic_Size;
    uint8 top;
    uint8 (*isFull)(Stack_uint16_DYNAMIC_Type* const me);
    uint8 (*isEmpty)(Stack_uint16_DYNAMIC_Type* const me);
    uint8 (*getCount)(Stack_uint16_DYNAMIC_Type* const me);
    void (*push)(Stack_uint16_DYNAMIC_Type* const me, uint16 x);
    uint16 (*pop)(Stack_uint16_DYNAMIC_Type* const me);
};


struct Stack_uint32_d{
    uint32 *Buffer;
    uint8 Dynamic_Size;
    uint8 top;
    uint8 (*isFull)(Stack_uint32_DYNAMIC_Type* const me);
    uint8 (*isEmpty)(Stack_uint32_DYNAMIC_Type* const me);
    uint8 (*getCount)(Stack_uint32_DYNAMIC_Type* const me);
    void (*push)(Stack_uint32_DYNAMIC_Type* const me, uint32 x);
    uint32 (*pop)(Stack_uint32_DYNAMIC_Type* const me);
};

#endif /* COMMON_DATASTRUCTURE_STACK_STATIC_INC_STACK_TYPES_H_ */
