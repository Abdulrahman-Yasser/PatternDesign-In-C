/*
 * FunctionQueue.c
 *
 *  Created on: May 5, 2023
 *      Author: Abdu
 */


#include "FunctionQueue.h"

FunctionQueue_t* FunctionQueue_Create(void){
    FunctionQueue_t *me;
    me = (FunctionQueue_t*)malloc(sizeof(FunctionQueue_t));
    me->next = Null_Ptr;
    me->funPtr = Null_Ptr;
}

void FunctionQueue_Destroy(FunctionQueue_t* me){
    FunctionQueue_t* temp_funPtr = me;
    if(me != Null_Ptr){
        while(me->next != Null_Ptr){
            temp_funPtr = me;
            me = temp_funPtr->next;
            temp_funPtr->funPtr = Null_Ptr;
            temp_funPtr->next = Null_Ptr;
            free(temp_funPtr);
        }
        me->funPtr = Null_Ptr;
        free(me);
    }
}

void FunctionQueue_AddFunction(FunctionQueue_t* me, void(*my_FunPtr)(void) ){
    FunctionQueue_t* temp_funPtr;
    if(me != Null_Ptr){
        if(me->funPtr == Null_Ptr){
            /* the first function is being pushed */
            me->funPtr = my_FunPtr;
        }else{
            /*  is being pushed */
            temp_funPtr = me;
            while(temp_funPtr->next != Null_Ptr){
                temp_funPtr = temp_funPtr->next;
            }
            temp_funPtr->next = (FunctionQueue_t*)malloc(sizeof(FunctionQueue_t));
            temp_funPtr = temp_funPtr->next;
            temp_funPtr->funPtr = my_FunPtr;
            temp_funPtr->next = Null_Ptr;
        }
    }
}

Std_ReturnType FunctionQueue_RemoveFunction(FunctionQueue_t* me, void(*my_FunPtr)(void) ){
    FunctionQueue_t* temp_funPtr = me, *temp_funPtr_2;
    while(temp_funPtr->next != Null_Ptr){
        if(temp_funPtr->funPtr == my_FunPtr){
            temp_funPtr_2->next = temp_funPtr->next;
            temp_funPtr->funPtr = Null_Ptr;
            temp_funPtr->next = Null_Ptr;
            return E_OK;
        }else{
            temp_funPtr_2 = temp_funPtr;
            temp_funPtr = temp_funPtr->next;
        }
    }
    return E_NOK;
}

void FunctionQueue_Calling(FunctionQueue_t* me){
    FunctionQueue_t* temp_funPtr;
    temp_funPtr = me;
    while(temp_funPtr->next != Null_Ptr){
        temp_funPtr->funPtr();
        temp_funPtr = temp_funPtr->next;
    }
    temp_funPtr->funPtr();
}

