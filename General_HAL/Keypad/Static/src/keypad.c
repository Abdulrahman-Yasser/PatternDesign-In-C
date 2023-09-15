/*
 * keypad.c
 *
 *  Created on: Aug 19, 2023
 *      Author: Abdu
 */

#include "../inc/keypad.h"
#include "../../Dynamic/inc/Keypad_Cfg.h"

#include "../General_Common/Std_Types.h"

#define KEYPAD_NO_NEW_DATA 0

static sint8 Last_valid_key_g[KEYPAD_CONFIGURED_NUMBER];
static sint8 result_FnKey_g[KEYPAD_CONFIGURED_NUMBER];
static sint8 result_Key_g[KEYPAD_CONFIGURED_NUMBER];

void keypad_Init(void){
    int i;
    for(i = 0; i < KEYPAD_CONFIGURED_NUMBER; i++){
        Dio_WriteChannel(KeypadContainer[i].cols_outputs[0], DIO_Level_LOW);
        Dio_WriteChannel(KeypadContainer[i].cols_outputs[1], DIO_Level_LOW);
        Dio_WriteChannel(KeypadContainer[i].cols_outputs[2], DIO_Level_LOW);
    }
}


void keypad_scanAllKeypads(sint8* myKeys, sint8* myFunKeys){
    int i;
    for(i = 0; i < KEYPAD_CONFIGURED_NUMBER; i++){
        if(keypad_ScanSpecificKeypad(i, &result_Key_g[i], &result_FnKey_g[i])){

        }else{
            result_FnKey_g[i] = 0;
            result_Key_g[i] = 0;
        }
    }
}


uint8 keypad_ScanSpecificKeypad(uint8 keypadID, sint8* myKeys, sint8* my_FnKey){
    static uint8 old_key[KEYPAD_CONFIGURED_NUMBER];

    sint8 key = KEYPAD_NO_NEW_DATA;
    sint8 Fn_Key = 0x00;

    /* Checking first column */
    Dio_WriteChannel(KeypadContainer[keypadID].cols_outputs[0], DIO_Level_HIGH);
        if(Dio_ReadChannel(KeypadContainer[keypadID].rows_inputs[0]) == DIO_Level_HIGH){
            key = '1';
        }else if(Dio_ReadChannel(KeypadContainer[keypadID].rows_inputs[1]) == DIO_Level_HIGH){
            key = '4';
        }else if(Dio_ReadChannel(KeypadContainer[keypadID].rows_inputs[2]) == DIO_Level_HIGH){
            key = '7';
        }else if(Dio_ReadChannel(KeypadContainer[keypadID].rows_inputs[3]) == DIO_Level_HIGH){
            Fn_Key = '*';
        }
    Dio_WriteChannel(KeypadContainer[keypadID].cols_outputs[0], DIO_Level_LOW);

    /* Checking second column */
    Dio_WriteChannel(KeypadContainer[keypadID].cols_outputs[1], DIO_Level_HIGH);
        if(Dio_ReadChannel(KeypadContainer[keypadID].rows_inputs[0]) == DIO_Level_HIGH){
            key = '2';
        }else if(Dio_ReadChannel(KeypadContainer[keypadID].rows_inputs[1]) == DIO_Level_HIGH){
            key = '5';
        }else if(Dio_ReadChannel(KeypadContainer[keypadID].rows_inputs[2]) == DIO_Level_HIGH){
            key = '8';
        }else if(Dio_ReadChannel(KeypadContainer[keypadID].rows_inputs[3]) == DIO_Level_HIGH){
            Fn_Key = '0';
        }
    Dio_WriteChannel(KeypadContainer[keypadID].cols_outputs[1], DIO_Level_LOW);

    /* Checking Third column */
    Dio_WriteChannel(KeypadContainer[keypadID].cols_outputs[2], DIO_Level_HIGH);
        if(Dio_ReadChannel(KeypadContainer[keypadID].rows_inputs[0]) == DIO_Level_HIGH){
            key = '3';
        }else if(Dio_ReadChannel(KeypadContainer[keypadID].rows_inputs[1]) == DIO_Level_HIGH){
            key = '6';
        }else if(Dio_ReadChannel(KeypadContainer[keypadID].rows_inputs[2]) == DIO_Level_HIGH){
            key = '9';
        }else if(Dio_ReadChannel(KeypadContainer[keypadID].rows_inputs[3]) == DIO_Level_HIGH){
            Fn_Key = '#';
        }
    Dio_WriteChannel(KeypadContainer[keypadID].cols_outputs[2], DIO_Level_LOW);

    if(key == KEYPAD_NO_NEW_DATA){
        old_key[keypadID] = KEYPAD_NO_NEW_DATA;
        Last_valid_key_g[keypadID] = KEYPAD_NO_NEW_DATA;
        return 0;
    }

    if(key == old_key[keypadID]){
        if(key != Last_valid_key_g[keypadID]){
            *myKeys = key;
            Last_valid_key_g[keypadID] = key;
            if(Fn_Key){
                *my_FnKey = Fn_Key;
            }else{
                *my_FnKey = 0;
            }
            return 1;
        }
    }
    old_key[keypadID] = key;
    return 0;
}
