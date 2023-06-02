/*
 * CRDisplay.c
 *
 *  Created on: Jun 2, 2023
 *      Author: Abdu
 */

#include "CRDisplay.h"
#include "../../General_HAL/LCD/Static/inc/LCD_Types.h"
#include "../../General_HAL/LCD/Static/inc/LCD.h"


struct CRDisplay{
    LCD_Handler_Type *my_lcd;
};

struct CRDisplay* CRDisplay_Create(void){
    struct CRDisplay* me;
    me = (struct CRDisplay* )malloc(sizeof(struct CRDisplay));
    me->my_lcd = LCD_Create(LCD_Interface_I2C, 0);
}


void CRDisplay_printMsg(struct CRDisplay* me, char* str){
    me->my_lcd->LCD_Write_Data(me->my_lcd, str);
}


