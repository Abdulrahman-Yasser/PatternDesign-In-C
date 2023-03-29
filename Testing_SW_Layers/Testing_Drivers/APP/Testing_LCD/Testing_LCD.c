/*
 * Testing_LCD.c
 *
 *  Created on: Mar 14, 2023
 *      Author: Abdu
 */

#ifndef APP_TESTING_LCD_TESTING_LCD_C_
#define APP_TESTING_LCD_TESTING_LCD_C_

#include "Testing_LCD.h"


void App_Initializations(void){
    Port_Init();
    Gpt_Init();
    I2C_init();
    IntCtrl_Init();
}

void Loop(void){
    LCD_Handler_Type* me;
    me = LCD_Create(LCD_Interface_I2C, 0);
    while(1){
    }
}




#endif /* APP_TESTING_LCD_TESTING_LCD_C_ */
