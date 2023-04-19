/*
 * HistogramDisplay.c
 *
 *  Created on: Apr 18, 2023
 *      Author: Abdu
 */

#include <App/TMDQueue/TMDQueue.h>

#include "../General_HAL/LCD/Static/inc/LCD.h"

#include "HistogramDisplay.h"

#include <stdlib.h>

static void cleanUpRelations(HistogramDisplay* const me);

void HistogramDisplay_Init(HistogramDisplay* const me){
    me->index = 0;
    me->itsTMDQueue = Null_Ptr;
    me->my_lcd = Null_Ptr;
}

void HistogramDisplay_Cleanup(HistogramDisplay* const me){
    cleanUpRelations(me);
}

/* Operations */

/* only cares about the temperature and Time */

void HistogramDisplay_getValue(HistogramDisplay* const me){
    struct TimeMarkedData tmd;
    uint8 t;
    LCD_CHAR_Type *s;

    if(me->itsTMDQueue == Null_Ptr || me->my_lcd == Null_Ptr){
        return;
    }

    t = TMDQueue_getLastIndex(me->itsTMDQueue);
    /* that means that HistogramDisplay did not read that index before*/
    if(t != me->index){
        me->index = t;
        tmd = TMDQueue_remove(me->itsTMDQueue, me->index);
    }else{
    /* i've already read that value */
        return ;
    }

    me->my_lcd->LCD_Write_Cmd(me->my_lcd, LCD_I2C_SET_DDRAM_ADDRESS(0, 0));

    s = int_to_string(tmd.time.hours);
    me->my_lcd->LCD_Write_Data(me->my_lcd, s);

    s = int_to_string(tmd.time.minutes);
    me->my_lcd->LCD_Write_Data(me->my_lcd, s);

    s = int_to_string(tmd.time.seconds);
    me->my_lcd->LCD_Write_Data(me->my_lcd, s);

    me->my_lcd->LCD_Write_Cmd(me->my_lcd, LCD_I2C_INST_CURSOR_GO_2ND_LINE);

    me->my_lcd->LCD_Write_Data(me->my_lcd, "Temp : ");

    s = int_to_string(tmd.temperature_value);
    me->my_lcd->LCD_Write_Data(me->my_lcd, s);
}

void HistogramDisplay_updateHistogram(HistogramDisplay* const me){
    /* Put what you need to update */
    HistogramDisplay_getValue(me);
}

struct TMDQueue* HistogramDisplay_getItsTMDQueue(const HistogramDisplay* const me){
    return (struct TMDQueue*)me->itsTMDQueue;
}

void HistogramDisplay_setItsTMDQueue(HistogramDisplay* const me, struct TMDQueue*p_TMDQueue){
    me->itsTMDQueue = p_TMDQueue;
}

void HistogramDisplay_setItsLCD(HistogramDisplay* const me, LCD_Handler_Type *p_LCD_Handler){
    me->my_lcd = p_LCD_Handler;
}

HistogramDisplay * HistogramDisplay_Create(void){
    HistogramDisplay* me = (HistogramDisplay*)malloc(sizeof(HistogramDisplay));
    if(me!=Null_Ptr)
    {
        HistogramDisplay_Init(me);
    }
    return me;
}

void HistogramDisplay_Destroy(HistogramDisplay* const me){
    if(me!=Null_Ptr)
    {
        HistogramDisplay_Cleanup(me);
    }
    free(me);
}

static void cleanUpRelations(HistogramDisplay* const me) {
    if(me->itsTMDQueue != Null_Ptr)
    {
        me->itsTMDQueue = Null_Ptr;
    }
}
