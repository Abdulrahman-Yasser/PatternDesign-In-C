/*
 * keypad.h
 *
 *  Created on: Aug 19, 2023
 *      Author: Abdu
 */

#ifndef KEYPAD_STATIC_INC_KEYPAD_H_
#define KEYPAD_STATIC_INC_KEYPAD_H_

#include "../../Dynamic/inc/Keypad_Cfg.h"

void keypad_Init(void);

void keypad_scanAllKeypads(sint8* myKeys, sint8* myFunKeys);
uint8 keypad_ScanSpecificKeypad(uint8 keypadID, sint8* myKeys, sint8* my_FnKey);

#endif /* KEYPAD_STATIC_INC_KEYPAD_H_ */
