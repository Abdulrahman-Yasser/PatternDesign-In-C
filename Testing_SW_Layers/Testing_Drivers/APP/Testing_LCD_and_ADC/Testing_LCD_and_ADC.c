/*
 * Testing_LCD_and_ADC.c
 *
 *  Created on: Aug 5, 2023
 *      Author: Abdu
 */

#include "Testing_LCD_and_ADC.h"

#include <stdlib.h>

void Testing_LCD_and_ADC_init(void){
    Port_Init();
    PLL_Init();
    I2C_init();
    ADC_Init();
}

void Testing_LCD_and_ADC_loop(void){
    Sensor_Type *my_temp = Sensor_Create(0, Sensor_Interface_Analog);
    LCD_Handler_Type* myLcd = LCD_Create(LCD_Interface_I2C, 0);
    uint32 val = 0;
    char* q;
    while(1){
        val = my_temp->GetValue(my_temp);
        myLcd->LCD_Write_Cmd(myLcd, LCD_I2C_SET_DDRAM_ADDRESS(0, 0));
        myLcd->LCD_Write_Data(myLcd, "T : ");
        q = int_to_string(val);
        myLcd->LCD_Write_Data(myLcd, q);
        free(q);
        Delay_ms(1000);
    }

}



