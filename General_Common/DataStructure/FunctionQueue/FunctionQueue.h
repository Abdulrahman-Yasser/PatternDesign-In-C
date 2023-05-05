/*
 * FunctionQueue.h
 *
 *  Created on: May 5, 2023
 *      Author: Abdu
 */

#ifndef DATASTRUCTURE_FUNCTIONQUEUE_FUNCTIONQUEUE_H_
#define DATASTRUCTURE_FUNCTIONQUEUE_FUNCTIONQUEUE_H_

#include "../General_Common/Std_Types.h"

typedef struct FunctionQueue FunctionQueue_t;

struct FunctionQueue{
    void (*funPtr)(void);
    FunctionQueue_t* next;
};


FunctionQueue_t* FunctionQueue_Create(void);

void FunctionQueue_Destroy(FunctionQueue_t* me);

void FunctionQueue_AddFunction(FunctionQueue_t* me, void(*my_FunPtr)(void) );

Std_ReturnType FunctionQueue_RemoveFunction(FunctionQueue_t* me, void(*my_FunPtr)(void) );

void FunctionQueue_Calling(FunctionQueue_t* me);



#endif /* DATASTRUCTURE_FUNCTIONQUEUE_FUNCTIONQUEUE_H_ */
