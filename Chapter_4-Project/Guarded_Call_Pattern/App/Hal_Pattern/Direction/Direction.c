/*
 * Direction.c
 *
 *  Created on: Jun 2, 2023
 *      Author: Abdu
 */

#include "Direction.h"
#include <stdlib.h>




struct Direction* Direction_Create(void){
    struct Direction* me;
    me = (struct Direction*)malloc(sizeof(struct Direction));
    me->my_direction = 0;
    return me;
}

uint8 getDirection(struct Direction* me){
    return me->my_direction;
}

void setDirection(struct Direction* me, uint8 d){
    me->my_direction = d;
}
