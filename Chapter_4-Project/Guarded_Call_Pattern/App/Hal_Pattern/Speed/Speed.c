/*
 * Speed.c
 *
 *  Created on: Jun 2, 2023
 *      Author: Abdu
 */

#include "Speed.h"
#include <stdlib.h>



struct speed* Speed_Create(void){
    struct speed* me;
    me = (struct speed* )malloc(sizeof(struct speed));
    me->my_speed = 0;
    return me;
}


uint8 getSpeed(struct speed* me){
    return me->my_speed;
}

void setSpeed(struct speed* me, uint8 s){
    me->my_speed = s;

}


