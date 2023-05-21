/*
 * HistogramDisplay.c
 *
 *  Created on: May 20, 2023
 *      Author: Abdu
 */




#include "HistogramDisplay.h"
#include "../../Observable/Observable.h"

#include "../../Server/TMDQueue/TMDQueue_DataType.h"
#include "../../Server/TimeMarkedData/TimeMarkedData.h"
#include "../General_HAL/LCD/Static/inc/LCD.h"

#include <stdlib.h>

static struct HistogramDisplay{
    struct TMDQueue_with_Observable_s* itsTMDQueue_observable;
    struct TimeMarkedData* my_tmd;
    LCD_Handler_Type* my_lcd;
    Observer* my_Observer;
}my_HistogramDisplay;

static void HistogramDisplay_updateHistogram(struct TimeMarkedData *tmd);


void HistogramDisplay_Init(struct HistogramDisplay* const me){
    me->itsTMDQueue_observable = Null_Ptr;
    me->my_lcd = Null_Ptr;

    me->my_tmd = (struct TimeMarkedData*)malloc(sizeof(struct TimeMarkedData));
    TimeMarkedData_Init(me->my_tmd);
    me->my_Observer = Observer_Create(HistogramDisplay_updateHistogram);
    me->itsTMDQueue_observable->my_Observable->Subscribe(me->my_Observer);
}

//void HistogramDisplay_Cleanup(struct HistogramDisplay* const me){
//    cleanUpRelations(me);
//}

/* Operations */

/* only cares about the temperature and Time */

void HistogramDisplay_getValue(struct TimeMarkedData *tmd){
    my_HistogramDisplay.my_tmd->date = tmd->date;
    my_HistogramDisplay.my_tmd->time = tmd->time;
    my_HistogramDisplay.my_tmd->temperature_value = tmd->temperature_value;
}


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
    HistogramDisplay_getValue(tmd);

    my_HistogramDisplay.my_lcd->LCD_Write_Cmd(my_HistogramDisplay.my_lcd, LCD_I2C_INST_CURSOR_GO_1ST_LINE);

    s = int_to_string(my_HistogramDisplay.my_tmd->time.hours);
    my_HistogramDisplay.my_lcd->LCD_Write_Data(my_HistogramDisplay.my_lcd, s);
    free(s);

    s = int_to_string(my_HistogramDisplay.my_tmd->time.minutes);
    my_HistogramDisplay.my_lcd->LCD_Write_Data(my_HistogramDisplay.my_lcd, s);
    free(s);

    s = int_to_string(my_HistogramDisplay.my_tmd->time.seconds);
    my_HistogramDisplay.my_lcd->LCD_Write_Data(my_HistogramDisplay.my_lcd, s);

    my_HistogramDisplay.my_lcd->LCD_Write_Cmd(my_HistogramDisplay.my_lcd, LCD_I2C_INST_CURSOR_GO_2ND_LINE);

    my_HistogramDisplay.my_lcd->LCD_Write_Data(my_HistogramDisplay.my_lcd, "Temp : ");

    s = int_to_string(my_HistogramDisplay.my_tmd->temperature_value);
    my_HistogramDisplay.my_lcd->LCD_Write_Data(my_HistogramDisplay.my_lcd, s);
    free(s);

}

struct TMDQueue_with_Observable_s* HistogramDisplay_getItsTMDQueue(const struct HistogramDisplay* const me){
    return (struct TMDQueue_with_Observable_s*)me->itsTMDQueue_observable;
}

void HistogramDisplay_setItsTMDQueue(struct HistogramDisplay* const me, struct TMDQueue_with_Observable_s* p_TMDQueue){
    me->itsTMDQueue_observable = p_TMDQueue;
}

void HistogramDisplay_setItsLCD(struct HistogramDisplay* const me, LCD_Handler_Type *p_LCD_Handler){
    me->my_lcd = p_LCD_Handler;
}

struct HistogramDisplay* HistogramDisplay_GetHandler(void){
    HistogramDisplay_Init(&my_HistogramDisplay);
    return &my_HistogramDisplay;
}

//void HistogramDisplay_Destroy(HistogramDisplay* const me){
//    if(me!=Null_Ptr)
//    {
//        HistogramDisplay_Cleanup(me);
//    }
//    free(me);
//}
//
//static void cleanUpRelations(HistogramDisplay* const me) {
//    if(me->itsTMDQueue != Null_Ptr)
//    {
//        me->itsTMDQueue = Null_Ptr;
//    }
//}
