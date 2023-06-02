/*
 * UserInput.c
 *
 *  Created on: Jun 2, 2023
 *      Author: Abdu
 */

#include "UserInput.h"
#include <stdlib.h>

struct UserInput{
    uint8 x;
    uint8 y;
    uint8 z;
};

void getUserInputs(struct UserInput* me){
    /* 1 or 0 means either forward or backward */
    me->x = rand() % 2;
    /* 0 : 100 by 10 step, which means the fast of the motor
     * 10%, 20%, 30% ... 100%
     * */
    me->y = ((( rand() % 100) / 10) * 10);
}

uint8 UserInput_getX ( struct UserInput* me){
    return me->x;
}

uint8 UserInput_getY ( struct UserInput* me){
    return me->y;
}

uint8 UserInput_getZ ( struct UserInput* me){
    return me->z;
}


