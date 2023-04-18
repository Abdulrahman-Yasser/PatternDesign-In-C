/*
 * FireDisplay.c
 *
 *  Created on: Apr 18, 2023
 *      Author: Abdu
 */


#include "../inc/FireDisplay.h"

void FireDisplay_Init(void){
    FireDisplay_LcdHandler = LCD_Create(LCD_Interface_I2C, FireDisplay_LCD_ID);
}

