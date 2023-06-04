/*
 * KinematicData.c
 *
 *  Created on: Jun 2, 2023
 *      Author: Abdu
 */



#include <stdlib.h>

#include "KinematicData.h"



struct kinematicData* kinematicData_Create(void){
    struct kinematicData* me;
    me = (struct kinematicData* )malloc(sizeof(struct kinematicData));
    me->sema = xSemaphoreCreateBinary();
    return me;
}

struct speed kinematicData_getSpeed(struct kinematicData* me){
    struct speed result;

    xSemaphoreTake(me->sema, (TickType_t)0);
    result = me->my_Speed;
    xSemaphoreGive(me->sema);

    return result;
}

void kinematicData_setSpeed(struct kinematicData* me, struct speed arg_Speed){

    xSemaphoreTake(me->sema, (TickType_t)0);
    me->my_Speed = arg_Speed;
    xSemaphoreGive(me->sema);

}

struct Direction kinematicData_getDirection(struct kinematicData* me){
    struct Direction result;

    xSemaphoreTake(me->sema, (TickType_t)0);
    result = me->my_Direction;
    xSemaphoreGive(me->sema);

    return result;
}
void kinematicData_setDirection(struct kinematicData* me, struct Direction arg_Direction){
    xSemaphoreTake(me->sema, (TickType_t)0);
    me->my_Direction = arg_Direction;
    xSemaphoreGive(me->sema);
}


