/*
 * Motor.c
 *
 *  Created on: Feb 16, 2023
 *      Author: abduy
 */

#include "../inc/Motor.h"
#include "../inc/Motor_Types.h"
#include "../../Dynamic/inc/Motor_Cfg.h"
#include <stdlib.h>

static void Motor_Init(Motor_HandlerType* me, uint8 Motor_ID);

static void Motor_CleanUp(Motor_HandlerType* me);

static void Motor_Init(Motor_HandlerType* me, uint8 Motor_ID){
    me->Motor_ID = Motor_ID;
}

static void Motor_CleanUp(Motor_HandlerType* me){
    me->Motor_ID = 0;
}


Motor_HandlerType* Motor_HandlerCreate(uint8 Motor_ID){
    Motor_HandlerType* me = (Motor_HandlerType*)malloc(sizeof(Motor_HandlerType));
    if(me != Null_Ptr){
        Motor_Init(me, Motor_ID);
    }
    return me;
}

void Motor_Move(Motor_HandlerType* me, Motor_Direction_Type Direction, Motor_Speed_Type Speed){

    pwm_AutomaticDutyCycle(Motor_Container[me->Motor_ID].Speed_Pins, Speed);

}

void Motor_ChangeSpeed(Motor_HandlerType* me, Motor_Speed_Type Speed);

void Motor_ChangeDirection(Motor_HandlerType* me,Motor_Direction_Type Direction);

void Motor_Stop(Motor_HandlerType* me);


