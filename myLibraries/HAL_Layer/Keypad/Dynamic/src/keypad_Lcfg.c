/*
 * keypad_Lcfg.c
 *
 *  Created on: Aug 19, 2023
 *      Author: Abdu
 */

#include "../inc/Keypad_Cfg.h"

extern keypad_4inX3out_Type KeypadContainer[KEYPAD_CONFIGURED_NUMBER] = {
                                 DIO_Channel0_B, DIO_Channel1_B, DIO_Channel2_B, DIO_Channel3_B, DIO_Channel4_B,
                                 DIO_Channel5_B, DIO_Channel6_B, DIO_Channel7_B
};



