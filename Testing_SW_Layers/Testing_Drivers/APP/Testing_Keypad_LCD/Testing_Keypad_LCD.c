/*
 * Testing_Keypad_LCD.c
 *
 *  Created on: Sep 3, 2023
 *      Author: Abdu
 */

#include "Testing_Keypad_LCD.h"


void Testing_Keypad_LCD_Init(void){
    PLL_Init();
    Port_Init();
    I2C_init();
}

void Testing_Keypad_LCD_Loop(void){
    sint8 data[3] = {'0', '0', '\0'};
    LCD_Handler_Type* my_Testing_Keypad_Lcd_lcd;
    my_Testing_Keypad_Lcd_lcd = LCD_Create(LCD_Interface_I2C, 0);
    keypad_Init();
    while(1){
        if(keypad_ScanSpecificKeypad(0, &data[0], &data[1])){
            my_Testing_Keypad_Lcd_lcd->LCD_Write_Data(my_Testing_Keypad_Lcd_lcd, data);
        }
        Delay_ms(500);
    }

}



