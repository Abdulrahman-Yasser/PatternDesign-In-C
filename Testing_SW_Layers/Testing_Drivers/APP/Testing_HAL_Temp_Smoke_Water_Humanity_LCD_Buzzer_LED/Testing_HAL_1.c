/*
 * Testing_HAL_1.c
 *
 *  Created on: Aug 4, 2023
 *      Author: Abdu
 */



#include "Testing_HAL_1.h"

#define SMOKE_SENSOR_ID     0
#define TEMPERATURE_SENSOR_ID     1
#define WATER_SENSOR_ID     2
#define HUMANITY_SENSOR_ID     3

void Testing_HAL1_Init(void){
    Port_Init();
    ADC_Init();
    I2C_init();
    Dio_Init();
    PLL_Init();
}

void Testing_HAL1_Loop(void){
    uint32 smokeValue = 0, tempValue = 0, waterValue = 0, humanityValue = 0;

    DigitalInterface_Type* myBuzzer, *myLed;
    LCD_Handler_Type* myLCD;
    Sensor_Type* mySmoke, *myHumanity, *myWater, *myTemperature;

    myBuzzer = Digital_Interface_Create(DIO_Channel2_A);
    myLed = Digital_Interface_Create(DIO_Channel3_A);

    myLCD = LCD_Create(LCD_Interface_I2C, 0);

    mySmoke = Sensor_Create(0, Sensor_Interface_Analog);
    myTemperature = Sensor_Create(1, Sensor_Interface_Analog);
    myWater = Sensor_Create(2, Sensor_Interface_Digital);
    myHumanity = Sensor_Create(3, Sensor_Interface_Analog);


    while(1){
        smokeValue = mySmoke->GetValue(mySmoke);
        tempValue = myTemperature->GetValue(myTemperature);
        waterValue = myWater->GetValue(myWater);
        humanityValue = myHumanity->GetValue(myHumanity);

        myLCD->LCD_Write_Cmd(myLCD, LCD_I2C_SET_DDRAM_ADDRESS(0, 0));
        myLCD->LCD_Write_Data(myLCD, "T : ");
        myLCD->LCD_Write_Data(myLCD, int_to_string(smokeValue));

        myLCD->LCD_Write_Cmd(myLCD, LCD_I2C_SET_DDRAM_ADDRESS(0, 8));
        myLCD->LCD_Write_Data(myLCD, "W : ");
        myLCD->LCD_Write_Data(myLCD, int_to_string(waterValue));

        myLCD->LCD_Write_Cmd(myLCD, LCD_I2C_SET_DDRAM_ADDRESS(1, 0));
        myLCD->LCD_Write_Data(myLCD, "S : ");
        myLCD->LCD_Write_Data(myLCD, int_to_string(smokeValue));

        myLCD->LCD_Write_Cmd(myLCD, LCD_I2C_SET_DDRAM_ADDRESS(1, 8));
        myLCD->LCD_Write_Data(myLCD, "H : ");
        myLCD->LCD_Write_Data(myLCD, int_to_string(humanityValue));

        myBuzzer->Write_Toggle(myBuzzer);
        myLed->Write_Toggle(myLed);

        Delay_ms(3000);
    }
}
