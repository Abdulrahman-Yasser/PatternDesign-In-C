/*
 * keypad_Types.h
 *
 *  Created on: Aug 19, 2023
 *      Author: Abdu
 */

#ifndef KEYPAD_STATIC_INC_KEYPAD_TYPES_H_
#define KEYPAD_STATIC_INC_KEYPAD_TYPES_H_

#include "../General_Mcal/DIO/Static/inc/DIO_Types.h"



typedef struct {
    DIO_ChannelType rows_inputs[4];
    DIO_ChannelType cols_outputs[3];
}keypad_4inX3out_Type;


#endif /* KEYPAD_STATIC_INC_KEYPAD_TYPES_H_ */
