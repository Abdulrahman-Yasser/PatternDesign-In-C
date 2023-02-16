/*
 * Motor.h
 *
 *  Created on: Feb 16, 2023
 *      Author: abduy
 */

#ifndef HAL_DC_MOTOR_STATIC_INC_MOTOR_H_
#define HAL_DC_MOTOR_STATIC_INC_MOTOR_H_

#include "Motor_Types.h"

Motor_HandlerType* Motor_HandlerCreate(uint8 Motor_ID);

void Motor_Move(Motor_HandlerType* me, Motor_Direction_Type Direction, Motor_Speed_Type Speed);

void Motor_ChangeSpeed(Motor_HandlerType* me, Motor_Speed_Type Speed);

void Motor_ChangeDirection(Motor_HandlerType* me,Motor_Direction_Type Direction);

void Motor_Stop(Motor_HandlerType* me);

#endif /* HAL_DC_MOTOR_STATIC_INC_MOTOR_H_ */
