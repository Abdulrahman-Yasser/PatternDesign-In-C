/*
 * Motor_Cfg.c
 *
 *  Created on: Feb 16, 2023
 *      Author: abduy
 */

#include "../inc/Motor_Cfg.h"

extern const Motor_Container_Type Motor_Container[MOTOR_CONFIGURED_NUMBER] = {
                                                                           {.Direction_Pins = {DIO_Channel0_A,DIO_Channel1_A },
                                                                           .Motor_ID = 0,
                                                                           .Speed_Pins = PWM_NUM_0_0}
};


