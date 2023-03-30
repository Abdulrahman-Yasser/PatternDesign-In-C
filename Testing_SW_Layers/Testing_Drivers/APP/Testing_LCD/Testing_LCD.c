/*
 * Testing_LCD.c
 *
 *  Created on: Mar 14, 2023
 *      Author: Abdu
 */

#ifndef APP_TESTING_LCD_TESTING_LCD_C_
#define APP_TESTING_LCD_TESTING_LCD_C_

#include "Testing_LCD.h"


void TestingLCD_Initializations(void){
    Port_Init();
    Gpt_Init();
    I2C_init();
    IntCtrl_Init();
}

void TestingLCD_Loop(void){
    LCD_Handler_Type* me;
    me = LCD_Create(LCD_Interface_I2C, 0);
    LCD_CHAR_Type* hello = "Hello !!";
    LCD_CHAR_Type* Goodbye = "GoodBye <3";
    while(1){
        me->LCD_Write_Cmd(me, LCD_I2C_INST_CLEAR);
        me->LCD_Write_Cmd(me, LCD_I2C_INST_CURSOR_GO_1ST_LINE);
        me->LCD_Write_Data(me, hello);
        Delay_ms(1000);
        me->LCD_Write_Cmd(me, LCD_I2C_INST_CLEAR);
        me->LCD_Write_Cmd(me, LCD_I2C_INST_CURSOR_GO_2ND_LINE);
        me->LCD_Write_Data(me, Goodbye);
        Delay_ms(1000);
    }
}




#endif /* APP_TESTING_LCD_TESTING_LCD_C_ */
