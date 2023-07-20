/*
 * WeatherStationDisplay.c
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */

#include "WeatherStationDisplay.h"
#include "../General_HAL/LCD/Static/inc/LCD.h"
#include <stdlib.h>
/* Constructors and destructors:*/


void WeatherStationDisplay_Init(WeatherStationDisplay* const me){
    me->my_lcd = Null_Ptr;
}

void WeatherStationDisplay_Cleanup(WeatherStationDisplay* const me){

}

/* Operations */

void WeatherStationDisplay_SetItsLCD(WeatherStationDisplay* me, LCD_Handler_Type* the_lcd){
    me->my_lcd = the_lcd;
}


void WeatherStationDisplay_printWeatherStationData(WeatherStationDisplay* const me, enum weather_station_sensor_type sensor_type, uint8 value){
    switch(sensor_type){
    case temperature_type:
        me->my_lcd->LCD_Read_Cmd(me->my_lcd, LCD_I2C_SET_DDRAM_ADDRESS(0, 0));
        me->my_lcd->LCD_Read_Data(me->my_lcd, "T : ");
        break;
    case light_type:
        me->my_lcd->LCD_Read_Cmd(me->my_lcd, LCD_I2C_SET_DDRAM_ADDRESS(0, 8));
        me->my_lcd->LCD_Read_Data(me->my_lcd, "L : ");
        break;
    case smoke_type:
        me->my_lcd->LCD_Read_Cmd(me->my_lcd, LCD_I2C_SET_DDRAM_ADDRESS(1, 0));
        me->my_lcd->LCD_Read_Data(me->my_lcd, "S : ");
        break;
    case Unknown_type:
        me->my_lcd->LCD_Read_Cmd(me->my_lcd, LCD_I2C_SET_DDRAM_ADDRESS(1, 8));
        me->my_lcd->LCD_Read_Data(me->my_lcd, "Un");
        break;
    }
    me->my_lcd->LCD_Read_Data(me->my_lcd, value);
}

WeatherStationDisplay* WeatherStationDisplay_Create(void){
    WeatherStationDisplay* me = (WeatherStationDisplay*)malloc(sizeof(WeatherStationDisplay));
    if(me != Null_Ptr){
        WeatherStationDisplay_Init(me);
    }
    return me;
}

void WeatherStationDisplay_Destroy(WeatherStationDisplay* const me){
    if(me != Null_Ptr){
        WeatherStationDisplay_Cleanup(me);
    }
    free(me);
}

