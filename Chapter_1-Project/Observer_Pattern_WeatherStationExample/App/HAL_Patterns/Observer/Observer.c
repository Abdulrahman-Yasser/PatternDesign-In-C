/*
 * Observer.c
 *
 *  Created on: May 20, 2023
 *      Author: Abdu
 */

#include "Observer.h"
#include <stdlib.h>

Observer* Observer_Create(Update_t fun){
    Observer* me;
    me = (Observer*)malloc(sizeof(Observer));
    me->UpdateFuncPtr = fun;
}

void Observer_Destroy(Observer* me){
    free(me);
}

void Observer_SetFunction(Observer* me, Update_t func){
    me->UpdateFuncPtr = func;
}

