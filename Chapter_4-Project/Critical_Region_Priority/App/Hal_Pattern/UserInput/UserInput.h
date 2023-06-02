/*
 * UserInput.h
 *
 *  Created on: Jun 2, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_USERINPUT_USERINPUT_H_
#define APP_HAL_PATTERN_USERINPUT_USERINPUT_H_

#include "../../General_Common/Std_Types.h"

struct UserInput;

uint8 UserInput_getX ( struct UserInput* me);
uint8 UserInput_getY ( struct UserInput* me);
uint8 UserInput_getZ ( struct UserInput* me);

void UserInput_Set_xyz(void* p_pvparameter);

struct UserInput* UserInput_Create(void);


#endif /* APP_HAL_PATTERN_USERINPUT_USERINPUT_H_ */
