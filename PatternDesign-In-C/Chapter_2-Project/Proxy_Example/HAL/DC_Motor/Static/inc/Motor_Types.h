/*
 * Motor_Types.h
 *
 *  Created on: Feb 16, 2023
 *      Author: abduy
 */

#ifndef HAL_DC_MOTOR_STATIC_INC_MOTOR_TYPES_H_
#define HAL_DC_MOTOR_STATIC_INC_MOTOR_TYPES_H_

#include "../../../../Mcal/DIO/Dynamic/inc/DIO_Cfg.h"
#include "../../../../Mcal/PWM/Dynamic/inc/PWM_Cfg.h"


typedef enum {
    Motor_Direction_FORWARD, Motor_Direction_BACKWARD, Motor_Direction_RIGHT, Motor_Direction_LEFT
}Motor_Direction_Type;

typedef enum {
    Motor_Speed_10_FROM_100 = 10,
    Motor_Speed_20_FROM_100 = 20,
    Motor_Speed_30_FROM_100 = 30,
    Motor_Speed_40_FROM_100 = 40,
    Motor_Speed_50_FROM_100 = 50,
    Motor_Speed_60_FROM_100 = 60,
    Motor_Speed_70_FROM_100 = 70,
    Motor_Speed_80_FROM_100 = 80,
    Motor_Speed_90_FROM_100 = 90,
    Motor_Speed_100_FROM_100 = 100
}Motor_Speed_Type;

typedef struct{
    uint8 Motor_ID;
}Motor_HandlerType;


typedef struct Motor_Container Motor_Container_Type;

struct Motor_Container{
    uint8 Motor_ID;
    DIO_ChannelType Direction_Pins[2];
    PWM_SubChannelType A_or_B_;
    PWM_ChannelType Speed_Pins;
};

#endif /* HAL_DC_MOTOR_STATIC_INC_MOTOR_TYPES_H_ */
