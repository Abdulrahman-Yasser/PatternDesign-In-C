/*
 * UserInput.c
 *
 *  Created on: Jun 2, 2023
 *      Author: Abdu
 */

#include "UserInput.h"
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"

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

void UserInput_Set_xyz(void* p_pvparameter){
    struct UserInput* me = p_pvparameter;
    TickType_t UserInputSetting = xTaskGetTickCount();
    while(1){
        vTaskDelayUntil(&UserInputSetting, 1000);
        me->x = rand() % 2;
        me->y = ( ( (rand() % 100) / 10 ) * 10);
    }
}

struct UserInput* UserInput_Create(void){
    struct UserInput* me;
    me = (struct UserInput*)malloc(sizeof(struct UserInput));
    me->x = 0;
    me->y = 0;
    me->z = 0;
    return me;
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


