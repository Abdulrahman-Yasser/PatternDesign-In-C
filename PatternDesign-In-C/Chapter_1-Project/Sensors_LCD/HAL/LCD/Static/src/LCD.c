/*
 * LCD.c
 *
 *  Created on: Nov 26, 2022
 *      Author: abduy
 */
#include "../inc/LCD.h"
#include "../../../../Common/Platform_Types.h"

#include "../../Dynamic/inc/LCD_Cfg.h"

/* Constructor */
void LCD_Init(LCD_Container_Type* const me, Std_BoolReturnType (*isFull_arg)(LCD_Container_Type* const me),
              Std_BoolReturnType (*isEmpty_arg)(LCD_Container_Type* const me), Std_BoolReturnType (*getSize_arg)(LCD_Container_Type* const me),
              void (*insert_arg)(LCD_Container_Type* const me, LCD_CHAR_Type k), LCD_CHAR_Type (*remove_arg)(LCD_Container_Type* const me, LCD_Position_Type i)){

}

/* Destructor */
void LCD_CleanUp(LCD_Container_Type* const me){

}

/* Operations */


