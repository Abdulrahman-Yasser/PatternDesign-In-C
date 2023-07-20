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

#include "../General_Mcal/DIO/Static/inc/DIO.h"
#include "../General_Mcal/PWM/Static/inc/PWM.h"

static void Motor_Init(Motor_HandlerType* me, uint8 Motor_ID);
static void Motor_CleanUp(Motor_HandlerType* me);
static void Motor_Move_Direction(Motor_HandlerType* me);
static void Motor_Move_Speed(Motor_HandlerType* me);

Motor_HandlerType* Motor_HandlerCreate(uint8 Motor_ID){
    Motor_HandlerType* me = (Motor_HandlerType*)malloc(sizeof(Motor_HandlerType));
    if(me != Null_Ptr){
        Motor_Init(me, Motor_ID);
    }
    return me;
}

void Motor_Move(Motor_HandlerType* me, Motor_Direction_Type Direction, Motor_Speed_Type Speed){
    Motor_ChangeSpeed(me, Speed);
    Motor_ChangeDirection(me, Direction);
}

void Motor_ChangeSpeed(Motor_HandlerType* me, Motor_Speed_Type Speed){
    me->Motor_Speed = Speed;
    Motor_Move_Speed(me);
}

void Motor_ChangeDirection(Motor_HandlerType* me,Motor_Direction_Type Direction){
    me->Motor_Direction = Direction;
    Motor_Move_Direction(me);
}

void Motor_Stop(Motor_HandlerType* me){
    Dio_WriteChannel(Motor_Container[me->Motor_ID].Direction_Pins[0], DIO_Level_LOW);
    Dio_WriteChannel(Motor_Container[me->Motor_ID].Direction_Pins[1], DIO_Level_LOW);
    pwm_stop(Motor_Container[me->Motor_ID].Speed_Pins);
}





static void Motor_Move_Speed(Motor_HandlerType* me){
    pwm_AutomaticDutyCycle(Motor_Container[me->Motor_ID].Speed_Pins, me->Motor_Speed);
    pwm_enable(Motor_Container[me->Motor_ID].Speed_Pins);
}

static void Motor_Move_Direction(Motor_HandlerType* me){
    switch(me->Motor_Direction){
    case Motor_Direction_CLOCKWISE:
        Dio_WriteChannel(Motor_Container[me->Motor_ID].Direction_Pins[0], DIO_Level_HIGH);
        Dio_WriteChannel(Motor_Container[me->Motor_ID].Direction_Pins[1], DIO_Level_LOW);
        break;
    case Motor_Direction_ANTICLOCKWISE:
        Dio_WriteChannel(Motor_Container[me->Motor_ID].Direction_Pins[0], DIO_Level_LOW);
        Dio_WriteChannel(Motor_Container[me->Motor_ID].Direction_Pins[1], DIO_Level_HIGH);
        break;
    default:
        break;
    }
}

static void Motor_Init(Motor_HandlerType* me, uint8 Motor_ID){
    me->Motor_ID = Motor_ID;
    me->Motor_Direction = Motor_Direction_CLOCKWISE;
    me->Motor_Speed = Motor_Speed_50_FROM_100;
}

static void Motor_CleanUp(Motor_HandlerType* me){
    me->Motor_ID = 0;
}
