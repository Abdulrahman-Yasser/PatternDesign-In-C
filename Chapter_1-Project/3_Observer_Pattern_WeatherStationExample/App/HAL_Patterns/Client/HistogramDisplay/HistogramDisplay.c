/*
 * HistogramDisplay.c
 *
 *  Created on: May 20, 2023
 *      Author: Abdu
 */




#include "HistogramDisplay.h"
#include "../../Observable/Observable.h"

#include "../../Server/TimeMarkedData/TimeMarkedData.h"
#include "HAL_Layer/LCD/Static/inc/LCD.h"

#include <stdlib.h>

 struct HistogramDisplay{
    struct TimeMarkedData* my_tmd;
    LCD_Handler_Type* my_lcd;
    Observer* my_Observer;
}my_HistogramDisplay;

static void HistogramDisplay_updateHistogram(struct TimeMarkedData *tmd);


void HistogramDisplay_Init(struct HistogramDisplay* me){
    me->my_lcd = Null_Ptr;

    me->my_tmd = (struct TimeMarkedData*)malloc(sizeof(struct TimeMarkedData));
    TimeMarkedData_Init(me->my_tmd);

    me->my_Observer = Observer_Create(HistogramDisplay_updateHistogram);
}

/* Operations */

/* only cares about the temperature and Time */

/*
 * The update function that will be passed through the observer to the observable.
 * Here in HistogramDisplay it's responsible of writing the time, date and temperature.
 * It will write it over the display if the semaphore for the LCD is free.
 * If there is a fire, then the semaphore will not be freed by the FireDisplay, sure that
   because the FireDisplay have a higher priority than the HistogramDisplay.
 */
static void HistogramDisplay_updateHistogram(struct TimeMarkedData *tmd){
    LCD_CHAR_Type* s;

    /* Put what you need to update */

    my_HistogramDisplay.my_lcd->LCD_Write_Cmd(my_HistogramDisplay.my_lcd, LCD_I2C_SET_DDRAM_ADDRESS(0, 0));

    s = int_to_string(tmd->time.hours);
    my_HistogramDisplay.my_lcd->LCD_Write_Data(my_HistogramDisplay.my_lcd, s);
    my_HistogramDisplay.my_lcd->LCD_Write_Data(my_HistogramDisplay.my_lcd, ":");
    free(s);

    s = int_to_string(tmd->time.minutes);
    my_HistogramDisplay.my_lcd->LCD_Write_Data(my_HistogramDisplay.my_lcd, s);
    my_HistogramDisplay.my_lcd->LCD_Write_Data(my_HistogramDisplay.my_lcd, ":");
    free(s);

    s = int_to_string(tmd->time.seconds);
    my_HistogramDisplay.my_lcd->LCD_Write_Data(my_HistogramDisplay.my_lcd, s);
    my_HistogramDisplay.my_lcd->LCD_Write_Data(my_HistogramDisplay.my_lcd, ":");
    free(s);

    s = int_to_string(tmd->date.date);
    my_HistogramDisplay.my_lcd->LCD_Write_Data(my_HistogramDisplay.my_lcd, s);
    my_HistogramDisplay.my_lcd->LCD_Write_Data(my_HistogramDisplay.my_lcd, "/");
    free(s);

    s = int_to_string(tmd->date.month);
    my_HistogramDisplay.my_lcd->LCD_Write_Data(my_HistogramDisplay.my_lcd, s);
    my_HistogramDisplay.my_lcd->LCD_Write_Data(my_HistogramDisplay.my_lcd, "/");
    free(s);

    s = int_to_string(tmd->date.year);
    my_HistogramDisplay.my_lcd->LCD_Write_Data(my_HistogramDisplay.my_lcd, s);
    free(s);

    my_HistogramDisplay.my_lcd->LCD_Write_Cmd(my_HistogramDisplay.my_lcd, LCD_I2C_INST_CURSOR_GO_2ND_LINE);

    my_HistogramDisplay.my_lcd->LCD_Write_Data(my_HistogramDisplay.my_lcd, "Temp : ");

    s = int_to_string(tmd->temperature_value);
    my_HistogramDisplay.my_lcd->LCD_Write_Data(my_HistogramDisplay.my_lcd, s);
    free(s);

}

Observer* HistogramDisplay_getObserver(void){
    return my_HistogramDisplay.my_Observer;
}

void HistogramDisplay_setItsLCD(struct HistogramDisplay* const me, LCD_Handler_Type *p_LCD_Handler){
    me->my_lcd = p_LCD_Handler;
}

struct HistogramDisplay* HistogramDisplay_GetHandler(void){
    return &my_HistogramDisplay;
}
