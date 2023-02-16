/*
 * Stack.c
 *
 *  Created on: Dec 26, 2022
 *      Author: abduy
 */



#include "../inc/Stack.h"
#include "../../../../Platform_Types.h"
#include "../../../../Compiler.h"
#include <stdlib.h>


/**************************************************************************************
 *                                  Definitions
 *                                    STATIC
 *                                    uint32
 **************************************************************************************/

void Stack_Init_uint32_s(Stack_uint32_STATIC_Type* const me, uint8 (*isFullFunction)(Stack_uint32_STATIC_Type* const me),
                uint8 (*isEmptyFunction)(Stack_uint32_STATIC_Type* const me) ,uint8 (*getCountFunction)(Stack_uint32_STATIC_Type* const me),
                void (*pushFunction)(Stack_uint32_STATIC_Type* const me, uint32 x) ,uint32 (*popFunction)(Stack_uint32_STATIC_Type* const me) );

void Stack_CleanUp_uint32_s(Stack_uint32_STATIC_Type* const me);

uint8 Stack_isFull_uint32_s(Stack_uint32_STATIC_Type* const me);
uint8 Stack_isEmpty_uint32_s(Stack_uint32_STATIC_Type *const me);
uint8 Stack_getCount_uint32_s(Stack_uint32_STATIC_Type* const me);
void Stack_push_uint32_s(Stack_uint32_STATIC_Type* const me, uint32 x);
uint32 Stack_pop_uint32_s(Stack_uint32_STATIC_Type* const me);


/**************************************************************************************
 *                                  Definitions
 *                                    STATIC
 *                                    uint16
 **************************************************************************************/
void Stack_Init_uint16_s(Stack_uint16_STATIC_Type* const me, uint8 (*isFullFunction)(Stack_uint16_STATIC_Type* const me),
                uint8 (*isEmptyFunction)(Stack_uint16_STATIC_Type* const me) ,uint8 (*getCountFunction)(Stack_uint16_STATIC_Type* const me),
                void (*pushFunction)(Stack_uint16_STATIC_Type* const me, uint16 x) ,uint16 (*popFunction)(Stack_uint16_STATIC_Type* const me) );

void Stack_CleanUp_uint16_s(Stack_uint16_STATIC_Type* const me);

uint8 Stack_isFull_uint16_s(Stack_uint16_STATIC_Type* const me);
uint8 Stack_isEmpty_uint16_s(Stack_uint16_STATIC_Type *const me);
uint8 Stack_getCount_uint16_s(Stack_uint16_STATIC_Type* const me);
void Stack_push_uint16_s(Stack_uint16_STATIC_Type* const me, uint16 x);
uint16 Stack_pop_uint16_s(Stack_uint16_STATIC_Type* const me);

/**************************************************************************************
 *                                  Definitions
 *                                    STATIC
 *                                    uint8
 **************************************************************************************/
void Stack_Init_uint8_s(Stack_uint8_STATIC_Type* const me, uint8 (*isFullFunction)(Stack_uint8_STATIC_Type* const me),
                uint8 (*isEmptyFunction)(Stack_uint8_STATIC_Type* const me) ,uint8 (*getCountFunction)(Stack_uint8_STATIC_Type* const me),
                void (*pushFunction)(Stack_uint8_STATIC_Type* const me, uint8 x) ,uint8 (*popFunction)(Stack_uint8_STATIC_Type* const me) );

void Stack_CleanUp_uint8_s(Stack_uint8_STATIC_Type* const me);

uint8 Stack_isFull_uint8_s(Stack_uint8_STATIC_Type* const me);
uint8 Stack_isEmpty_uint8_s(Stack_uint8_STATIC_Type *const me);
uint8 Stack_getCount_uint8_s(Stack_uint8_STATIC_Type* const me);
void Stack_push_uint8_s(Stack_uint8_STATIC_Type* const me, uint8 x);
uint8 Stack_pop_uint8_s(Stack_uint8_STATIC_Type* const me);


/**************************************************************************************
 *                                  Definitions
 *                                    DYNAMIC
 *                                    uint32
 **************************************************************************************/
void Stack_Init_uint32_d(Stack_uint32_DYNAMIC_Type* const me ,uint8 Dynamic_count_P, uint8 (*isFullFunction)(Stack_uint32_DYNAMIC_Type* const me),
                uint8 (*isEmptyFunction)(Stack_uint32_DYNAMIC_Type* const me) ,uint8 (*getCountFunction)(Stack_uint32_DYNAMIC_Type* const me),
                void (*pushFunction)(Stack_uint32_DYNAMIC_Type* const me, uint32 x) ,uint32 (*popFunction)(Stack_uint32_DYNAMIC_Type* const me) );

void Stack_CleanUp_uint32_d(Stack_uint32_DYNAMIC_Type* const me);

uint8 Stack_isFull_uint32_d(Stack_uint32_DYNAMIC_Type* const me);
uint8 Stack_isEmpty_uint32_d(Stack_uint32_DYNAMIC_Type *const me);
uint8 Stack_getCount_uint32_d(Stack_uint32_DYNAMIC_Type* const me);
void Stack_push_uint32_d(Stack_uint32_DYNAMIC_Type* const me, uint32 x);
uint32 Stack_pop_uint32_d(Stack_uint32_DYNAMIC_Type* const me);

/**************************************************************************************
 *                                  Definitions
 *                                    DYNAMIC
 *                                    uint16
 **************************************************************************************/
void Stack_Init_uint16_d(Stack_uint16_DYNAMIC_Type* const me ,uint8 Dynamic_count_P, uint8 (*isFullFunction)(Stack_uint16_DYNAMIC_Type* const me),
                uint8 (*isEmptyFunction)(Stack_uint16_DYNAMIC_Type* const me) ,uint8 (*getCountFunction)(Stack_uint16_DYNAMIC_Type* const me),
                void (*pushFunction)(Stack_uint16_DYNAMIC_Type* const me, uint16 x) ,uint16 (*popFunction)(Stack_uint16_DYNAMIC_Type* const me) );

void Stack_CleanUp_uint16_d(Stack_uint16_DYNAMIC_Type* const me);

uint8 Stack_isFull_uint16_d(Stack_uint16_DYNAMIC_Type* const me);
uint8 Stack_isEmpty_uint16_d(Stack_uint16_DYNAMIC_Type *const me);
uint8 Stack_getCount_uint16_d(Stack_uint16_DYNAMIC_Type* const me);
void Stack_push_uint16_d(Stack_uint16_DYNAMIC_Type* const me, uint16 x);
uint16 Stack_pop_uint16_d(Stack_uint16_DYNAMIC_Type* const me);

/**************************************************************************************
 *                                  Definitions
 *                                    DYNAMIC
 *                                    uint8
 **************************************************************************************/
void Stack_Init_uint8_d(Stack_uint8_DYNAMIC_Type* const me ,uint8 Dynamic_count_P, uint8 (*isFullFunction)(Stack_uint8_DYNAMIC_Type* const me),
                uint8 (*isEmptyFunction)(Stack_uint8_DYNAMIC_Type* const me) ,uint8 (*getCountFunction)(Stack_uint8_DYNAMIC_Type* const me),
                void (*pushFunction)(Stack_uint8_DYNAMIC_Type* const me, uint8 x) ,uint8 (*popFunction)(Stack_uint8_DYNAMIC_Type* const me) );

void Stack_CleanUp_uint8_d(Stack_uint8_DYNAMIC_Type* const me);

uint8 Stack_isFull_uint8_d(Stack_uint8_DYNAMIC_Type* const me);
uint8 Stack_isEmpty_uint8_d(Stack_uint8_DYNAMIC_Type *const me);
uint8 Stack_getCount_uint8_d(Stack_uint8_DYNAMIC_Type* const me);
void Stack_push_uint8_d(Stack_uint8_DYNAMIC_Type* const me, uint8 x);
uint8 Stack_pop_uint8_d(Stack_uint8_DYNAMIC_Type* const me);



/**************************************************************************************
 *                                  Implementation
 *                                      STATIC
 *                                      uint32
 **************************************************************************************/

/****************************************************
 *              Creation and Destroying
 ****************************************************/
Stack_uint32_STATIC_Type *Stack_Create_STATIC_uint32(void){
    Stack_uint32_STATIC_Type* me = (Stack_uint32_STATIC_Type*)malloc(sizeof(Stack_uint32_STATIC_Type));
        if(me != Null_Ptr){
                Stack_Init_uint32_s(me, Stack_isFull_uint32_s, Stack_isEmpty_uint32_s, Stack_getCount_uint32_s,
                           Stack_push_uint32_s, Stack_pop_uint32_s);
        }
        return me;
}

void Stack_Destroy_STATIC_uint32(Stack_uint32_STATIC_Type* const me){
    if(me != Null_Ptr){
        Stack_CleanUp_uint32_s(me);
    }
    free(me);
}

/*********************************************
 *           Constructor and Destructor
 *********************************************/

void Stack_Init_uint32_s(Stack_uint32_STATIC_Type* const me, uint8 (*isFullFunction)(Stack_uint32_STATIC_Type* const me),
                uint8 (*isEmptyFunction)(Stack_uint32_STATIC_Type* const me) ,uint8 (*getCountFunction)(Stack_uint32_STATIC_Type* const me),
                void (*pushFunction)(Stack_uint32_STATIC_Type* const me, uint32 x) ,uint32 (*popFunction)(Stack_uint32_STATIC_Type* const me) ){
    me->top = 0;
    /* Initialize function pointers */
    me->isFull = isFullFunction;
    me->isEmpty = isEmptyFunction;
    me->getCount = getCountFunction;
    me->push = pushFunction;
    me->pop = popFunction;
}

/* Operation Clean_up() */
void Stack_CleanUp_uint32_s(Stack_uint32_STATIC_Type* const me){
    free(me->Buffer);
}

/*********************************************
 *           Static Operations
 *********************************************/
uint8 Stack_isFull_uint32_s(Stack_uint32_STATIC_Type* const me){
    return(me->top == STACK_BUFFER_SIZE_STATIC);
}

uint8 Stack_isEmpty_uint32_s(Stack_uint32_STATIC_Type *const me){
    return(me->top == 0);
}

uint8 Stack_getCount_uint32_s(Stack_uint32_STATIC_Type* const me){
    return (me->top);
}

void Stack_push_uint32_s(Stack_uint32_STATIC_Type* const me, uint32 x){
    if(!(me->isFull(me))){
        me->Buffer[me->top] = x;
        me->top++;
    }
}

uint32 Stack_pop_uint32_s(Stack_uint32_STATIC_Type* const me){
    uint32 x;
    if(!(me->isEmpty(me))){
        me->top--;
        x = me->Buffer[me->top];
    }
    return x;
}


/**************************************************************************************
 *                                    STATIC
 *                                    uint16
 *
 **************************************************************************************/

/****************************************************
 *              Creation and Destroying
 ****************************************************/
Stack_uint16_STATIC_Type *Stack_Create_STATIC_uint16(void){
    Stack_uint16_STATIC_Type *me = (Stack_uint16_STATIC_Type*)malloc(sizeof(Stack_uint16_STATIC_Type));
    if(me != Null_Ptr){
        Stack_Init_uint16_s(me, Stack_isFull_uint16_s, Stack_isEmpty_uint16_s, Stack_getCount_uint16_s,
                   Stack_push_uint16_s, Stack_pop_uint16_s);
    }
    return me;
}

void Stack_Destroy_STATIC_uint16(Stack_uint16_STATIC_Type* const me){
    if(me != Null_Ptr){
        Stack_CleanUp_uint16_s(me);

    }
}


/*********************************************
 *           Constructor and Destructor
 *********************************************/
void Stack_Init_uint16_s(Stack_uint16_STATIC_Type* const me, uint8 (*isFullFunction)(Stack_uint16_STATIC_Type* const me),
                uint8 (*isEmptyFunction)(Stack_uint16_STATIC_Type* const me) ,uint8 (*getCountFunction)(Stack_uint16_STATIC_Type* const me),
                void (*pushFunction)(Stack_uint16_STATIC_Type* const me, uint16 x) ,uint16 (*popFunction)(Stack_uint16_STATIC_Type* const me) ){
    me->top = 0;
    /* Initialize function pointers */
    me->isFull = isFullFunction;
    me->isEmpty = isEmptyFunction;
    me->getCount = getCountFunction;
    me->push = pushFunction;
    me->pop = popFunction;
}

/* Operation Clean_up() */
void Stack_CleanUp_uint16_s(Stack_uint16_STATIC_Type* const me){
    free(me->Buffer);
}


/*********************************************
 *           Static Operations
 *********************************************/
/* Operation isFull() */
uint8 Stack_isFull_uint16_s(Stack_uint16_STATIC_Type* const me){
    return(me->top == STACK_BUFFER_SIZE_STATIC);
}

/* Operation isEmpty() */
uint8 Stack_isEmpty_uint16_s(Stack_uint16_STATIC_Type *const me){
    return(me->top == 0);
}

/* Operation getSize() */
uint8 Stack_getCount_uint16_s(Stack_uint16_STATIC_Type* const me){
    return (me->top);
}

/* Operation push(int) */
void Stack_push_uint16_s(Stack_uint16_STATIC_Type* const me, uint16 x){
    if(!(me->isFull(me))){
        me->Buffer[me->top] = x;
        me->top++;
    }
}

/* Operation pop() */
uint16 Stack_pop_uint16_s(Stack_uint16_STATIC_Type* const me){
    uint32 x;
    if(!(me->isEmpty(me))){
        me->top--;
        x = me->Buffer[me->top];
    }
    return x;
}

/**************************************************************************************
 *                                    STATIC
 *                                    uint8
 *
 **************************************************************************************/

/****************************************************
 *              Creation and Destroying
 ****************************************************/
Stack_uint8_STATIC_Type *Stack_Create_STATIC_uint8(void){
    Stack_uint8_STATIC_Type *me = (Stack_uint8_STATIC_Type*)malloc(sizeof(Stack_uint8_STATIC_Type));
    if(me != Null_Ptr){
        Stack_Init_uint8_s(me, Stack_isFull_uint8_s, Stack_isEmpty_uint8_s, Stack_getCount_uint8_s,
                   Stack_push_uint8_s, Stack_pop_uint8_s);
    }
    return me;
}

void Stack_Destroy_STATIC_uint8(Stack_uint8_STATIC_Type* const me){
    if(me != Null_Ptr){
        Stack_CleanUp_uint8_s(me);

    }
}


/*********************************************
 *           Constructor and Destructor
 *********************************************/
void Stack_Init_uint8_s(Stack_uint8_STATIC_Type* const me, uint8 (*isFullFunction)(Stack_uint8_STATIC_Type* const me),
                uint8 (*isEmptyFunction)(Stack_uint8_STATIC_Type* const me) ,uint8 (*getCountFunction)(Stack_uint8_STATIC_Type* const me),
                void (*pushFunction)(Stack_uint8_STATIC_Type* const me, uint8 x) ,uint8 (*popFunction)(Stack_uint8_STATIC_Type* const me) ){
    me->top = 0;
    /* Initialize function pointers */
    me->isFull = isFullFunction;
    me->isEmpty = isEmptyFunction;
    me->getCount = getCountFunction;
    me->push = pushFunction;
    me->pop = popFunction;
}

/* Operation Clean_up() */
void Stack_CleanUp_uint8_s(Stack_uint8_STATIC_Type* const me){
    free(me->Buffer);
}


/*********************************************
 *           Static Operations
 *********************************************/
/* Operation isFull() */
uint8 Stack_isFull_uint8_s(Stack_uint8_STATIC_Type* const me){
    return(me->top == STACK_BUFFER_SIZE_STATIC);
}

/* Operation isEmpty() */
uint8 Stack_isEmpty_uint8_s(Stack_uint8_STATIC_Type *const me){
    return(me->top == 0);
}

/* Operation getSize() */
uint8 Stack_getCount_uint8_s(Stack_uint8_STATIC_Type* const me){
    return (me->top);
}

/* Operation push(int) */
void Stack_push_uint8_s(Stack_uint8_STATIC_Type* const me, uint8 x){
    if(!(me->isFull(me))){
        me->Buffer[me->top] = x;
        me->top++;
    }
}

/* Operation pop() */
uint8 Stack_pop_uint8_s(Stack_uint8_STATIC_Type* const me){
    uint32 x;
    if(!(me->isEmpty(me))){
        me->top--;
        x = me->Buffer[me->top];
    }
    return x;
}


/**************************************************************************************
 *                                   DYNAMIC
 *                                   uint32
 *
 **************************************************************************************/

/****************************************************
 *              Creation and cleaning
 ****************************************************/
Stack_uint32_DYNAMIC_Type *Stack_Create_DYNAMIC_uint32(uint8 DynamicSize){
    Stack_uint32_DYNAMIC_Type* me = (Stack_uint32_DYNAMIC_Type*)malloc(sizeof(Stack_uint32_DYNAMIC_Type));
        if(me != Null_Ptr){
            if(DynamicSize > 0){
                me->Dynamic_Size = DynamicSize;
                Stack_Init_uint32_d(me, DynamicSize, Stack_isFull_uint32_d, Stack_isEmpty_uint32_d, Stack_getCount_uint32_d,
                           Stack_push_uint32_d, Stack_pop_uint32_d);
            }
        }
        return me;
}

void Stack_Destroy_DYNAMIC_uint32(Stack_uint32_DYNAMIC_Type* const me){
    if(me != Null_Ptr){
        Stack_CleanUp_uint32_d(me);
    }
    free(me);
}


/*********************************************
 *           Constructor and Destructor
 *********************************************/
void Stack_Init_uint32_d(Stack_uint32_DYNAMIC_Type* const me ,uint8 Dynamic_Size_P, uint8 (*isFullFunction)(Stack_uint32_DYNAMIC_Type* const me),
                uint8 (*isEmptyFunction)(Stack_uint32_DYNAMIC_Type* const me) ,uint8 (*getCountFunction)(Stack_uint32_DYNAMIC_Type* const me),
                void (*pushFunction)(Stack_uint32_DYNAMIC_Type* const me, uint32 x) ,uint32 (*popFunction)(Stack_uint32_DYNAMIC_Type* const me) ){
    me->top = 0;
    me->Dynamic_Size = Dynamic_Size_P;
    /* Initialize function pointers */
    if(me->Dynamic_Size > 0){
        me->Buffer = (uint32*)malloc(sizeof(uint32) * me->Dynamic_Size);
    }
    me->isFull = isFullFunction;
    me->isEmpty = isEmptyFunction;
    me->getCount = getCountFunction;
    me->push = pushFunction;
    me->pop = popFunction;
}

/* Operation Clean_up() */

void Stack_CleanUp_uint32_d(Stack_uint32_DYNAMIC_Type* const me){
    free(me->Buffer);
}


/*********************************************
 *           Dynamic Operations
 *********************************************/

/* Operation isFull() */
uint8 Stack_isFull_uint32_d(Stack_uint32_DYNAMIC_Type* const me){
    return(me->top == me->Dynamic_Size);
}

/* Operation isEmpty() */
uint8 Stack_isEmpty_uint32_d(Stack_uint32_DYNAMIC_Type *const me){
    return(me->top == 0);
}

/* Operation getCount() */
uint8 Stack_getCount_uint32_d(Stack_uint32_DYNAMIC_Type* const me){
    return me->top;
}

/* Operation push(int) */
void Stack_push_uint32_d(Stack_uint32_DYNAMIC_Type* const me, uint32 x){
    if(!(me->isFull(me))){
        me->Buffer[me->top] = x;
        me->top++;
    }
}

/* Operation pop() */
uint32 Stack_pop_uint32_d(Stack_uint32_DYNAMIC_Type* const me){
    uint32 value = 0;
    if(!(me->isEmpty(me))){
        me->top--;
        value = me->Buffer[me->top];
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
Stack_uint16_DYNAMIC_Type *Stack_Create_DYNAMIC_uint16(uint8 DynamicSize){
    Stack_uint16_DYNAMIC_Type* me = (Stack_uint16_DYNAMIC_Type*)malloc(sizeof(Stack_uint16_DYNAMIC_Type));
        if(me != Null_Ptr){
            if(DynamicSize > 0){
                me->Dynamic_Size = DynamicSize;
                Stack_Init_uint16_d(me, DynamicSize, Stack_isFull_uint16_d, Stack_isEmpty_uint16_d, Stack_getCount_uint16_d,
                           Stack_push_uint16_d, Stack_pop_uint16_d);
            }
        }
        return me;
}

void Stack_Destroy_DYNAMIC_uint16(Stack_uint16_DYNAMIC_Type* const me){
    if(me != Null_Ptr){
        Stack_CleanUp_uint16_d(me);
    }
    free(me);
}


/*********************************************
 *           Constructor and Destructor
 *********************************************/
void Stack_Init_uint16_d(Stack_uint16_DYNAMIC_Type* const me ,uint8 Dynamic_Size_P, uint8 (*isFullFunction)(Stack_uint16_DYNAMIC_Type* const me),
                uint8 (*isEmptyFunction)(Stack_uint16_DYNAMIC_Type* const me) ,uint8 (*getCountFunction)(Stack_uint16_DYNAMIC_Type* const me),
                void (*pushFunction)(Stack_uint16_DYNAMIC_Type* const me, uint16 x) ,uint16 (*popFunction)(Stack_uint16_DYNAMIC_Type* const me) ){
    me->top = 0;
    me->Dynamic_Size = Dynamic_Size_P;
    /* Initialize function pointers */
    if(me->Dynamic_Size > 0){
        me->Buffer = (uint16*)malloc(sizeof(uint16) * me->Dynamic_Size);
    }
    me->isFull = isFullFunction;
    me->isEmpty = isEmptyFunction;
    me->getCount = getCountFunction;
    me->push = pushFunction;
    me->pop = popFunction;
}

/* Operation Clean_up() */

void Stack_CleanUp_uint16_d(Stack_uint16_DYNAMIC_Type* const me){
    free(me->Buffer);
}


/*********************************************
 *           Dynamic Operations
 *********************************************/

/* Operation isFull() */
uint8 Stack_isFull_uint16_d(Stack_uint16_DYNAMIC_Type* const me){
    return(me->top == me->Dynamic_Size);
}

/* Operation isEmpty() */
uint8 Stack_isEmpty_uint16_d(Stack_uint16_DYNAMIC_Type *const me){
    return(me->top == 0);
}

/* Operation getCount() */
uint8 Stack_getCount_uint16_d(Stack_uint16_DYNAMIC_Type* const me){
    return me->top;
}

/* Operation push(int) */
void Stack_push_uint16_d(Stack_uint16_DYNAMIC_Type* const me, uint16 x){
    if(!(me->isFull(me))){
        me->Buffer[me->top] = x;
        me->top++;
    }
}

/* Operation pop() */
uint16 Stack_pop_uint16_d(Stack_uint16_DYNAMIC_Type* const me){
    uint16 value = 0;
    if(!(me->isEmpty(me))){
        me->top--;
        value = me->Buffer[me->top];
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
Stack_uint8_DYNAMIC_Type *Stack_Create_DYNAMIC_uint8(uint8 DynamicSize){
    Stack_uint8_DYNAMIC_Type* me = (Stack_uint8_DYNAMIC_Type*)malloc(sizeof(Stack_uint8_DYNAMIC_Type));
        if(me != Null_Ptr){
            if(DynamicSize > 0){
                me->Dynamic_Size = DynamicSize;
                Stack_Init_uint8_d(me, DynamicSize, Stack_isFull_uint8_d, Stack_isEmpty_uint8_d, Stack_getCount_uint8_d,
                           Stack_push_uint8_d, Stack_pop_uint8_d);
            }
        }
        return me;
}

void Stack_Destroy_DYNAMIC_uint8(Stack_uint8_DYNAMIC_Type* const me){
    if(me != Null_Ptr){
        Stack_CleanUp_uint8_d(me);
    }
    free(me);
}


/*********************************************
 *           Constructor and Destructor
 *********************************************/
void Stack_Init_uint8_d(Stack_uint8_DYNAMIC_Type* const me ,uint8 Dynamic_Size_P, uint8 (*isFullFunction)(Stack_uint8_DYNAMIC_Type* const me),
                uint8 (*isEmptyFunction)(Stack_uint8_DYNAMIC_Type* const me) ,uint8 (*getCountFunction)(Stack_uint8_DYNAMIC_Type* const me),
                void (*pushFunction)(Stack_uint8_DYNAMIC_Type* const me, uint8 x) ,uint8 (*popFunction)(Stack_uint8_DYNAMIC_Type* const me) ){
    me->top = 0;
    me->Dynamic_Size = Dynamic_Size_P;
    /* Initialize function pointers */
    if(me->Dynamic_Size > 0){
        me->Buffer = (uint8*)malloc(sizeof(uint8) * me->Dynamic_Size);
    }
    me->isFull = isFullFunction;
    me->isEmpty = isEmptyFunction;
    me->getCount = getCountFunction;
    me->push = pushFunction;
    me->pop = popFunction;
}

/* Operation Clean_up() */

void Stack_CleanUp_uint8_d(Stack_uint8_DYNAMIC_Type* const me){
    free(me->Buffer);
}


/*********************************************
 *           Dynamic Operations
 *********************************************/

/* Operation isFull() */
uint8 Stack_isFull_uint8_d(Stack_uint8_DYNAMIC_Type* const me){
    return(me->top == me->Dynamic_Size);
}

/* Operation isEmpty() */
uint8 Stack_isEmpty_uint8_d(Stack_uint8_DYNAMIC_Type *const me){
    return(me->top == 0);
}

/* Operation getCount() */
uint8 Stack_getCount_uint8_d(Stack_uint8_DYNAMIC_Type* const me){
    return me->top;
}

/* Operation push(int) */
void Stack_push_uint8_d(Stack_uint8_DYNAMIC_Type* const me, uint8 x){
    if(!(me->isFull(me))){
        me->Buffer[me->top] = x;
        me->top++;
    }
}

/* Operation pop() */
uint8 Stack_pop_uint8_d(Stack_uint8_DYNAMIC_Type* const me){
    uint8 value = 0;
    if(!(me->isEmpty(me))){
        me->top--;
        value = me->Buffer[me->top];
    }
    return value;
}

