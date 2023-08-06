/*
 * Testing_LCD_and_SpecificDriverTemp.c
 *
 *  Created on: Aug 5, 2023
 *      Author: Abdu
 */


#include "Testing_LCD_and_SpecificDriverTemp.h"


#include <stdlib.h>


//    Port_Init();
//    Gpt_Init();
//    I2C_init();
//    IntCtrl_Init();

void Testing_LCD_and_SpecificDriverTempInit(void){
    Port_Init();
    ADC_Init();
    I2C_init();
}

void Testing_LCD_and_SpecificDriverTemp_loop(void){
    LCD_Handler_Type* myLcd = LCD_Create(LCD_Interface_I2C, 0);
    myLcd->LCD_Write_Cmd(myLcd, LCD_I2C_INST_CLEAR);
    myLcd->LCD_Write_Data(myLcd, "I AM READY ");
    TempDriver_WeatherStation_Init();
    SmokeDriver_WeatherStation_Init();
    WaterDriver_WeatherStation_Init();

    Delay_ms(1000);
    uint32 val = 0;
    char* q;
    while(1){
        val = TempDriver_WeatherStation_Read();
        myLcd->LCD_Write_Cmd(myLcd, LCD_I2C_SET_DDRAM_ADDRESS(0, 0));
        myLcd->LCD_Write_Data(myLcd, "T : ");
        q = int_to_string(val);
        myLcd->LCD_Write_Data(myLcd, q);
        myLcd->LCD_Write_Data(myLcd, "  ");
        free(q);
        Delay_ms(1000);


        val = SmokeDriver_WeatherStation_Read();
        myLcd->LCD_Write_Cmd(myLcd, LCD_I2C_SET_DDRAM_ADDRESS(0, 8));
        myLcd->LCD_Write_Data(myLcd, "S : ");
        q = int_to_string(val);
        myLcd->LCD_Write_Data(myLcd, q);
        myLcd->LCD_Write_Data(myLcd, "  ");
        free(q);
        Delay_ms(1000);

        val = WaterDriver_WeatherStation_Read();
        myLcd->LCD_Write_Cmd(myLcd, LCD_I2C_SET_DDRAM_ADDRESS(1, 0));
        myLcd->LCD_Write_Data(myLcd, "W : ");
        q = int_to_string(val);
        myLcd->LCD_Write_Data(myLcd, q);
        myLcd->LCD_Write_Data(myLcd, "  ");
        free(q);
        Delay_ms(1000);
    }
}




