/*
 * WeatherStationDataQueue.c
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */


#include "WeatherStationDataQueue.h"
#include "task.h"
#include <stdlib.h>
#include "../General_HAL/LCD/Static/inc/LCD.h"

/* private (static) methods */
static void cleanUpRelations(WeatherStationDataQueue* const me){
    int i = 0;
    while(i < WEATHER_QUEUE_SIZE){
        WeatherStationData_CleanUp(&(me->itsWeatherStationData[i]));
        i++;
    }
}
static int getNextIndex(WeatherStationDataQueue* const me, int index){
    return ((index+1) % WEATHER_QUEUE_SIZE);
}
static unsigned char isEmpty(WeatherStationDataQueue* const me){
    return(me->size == 0);
}
static unsigned char isFull(WeatherStationDataQueue* const me){
    return(me->size == WEATHER_QUEUE_SIZE);
}
static void initRelations(WeatherStationDataQueue* const me){
    int i = 0;
    while(i < WEATHER_QUEUE_SIZE){
        WeatherStationData_Init(&(me->itsWeatherStationData[i]));
        i++;
    }
}

/* Constructors and destructors:*/

void WeatherStationDataQueue_Init(WeatherStationDataQueue* const me){
    me->head = 0;
    me->size = 0;
    me->tail = 0;
    me->sema = xSemaphoreCreateBinary();
    initRelations(me);
}

void WeatherStationDataQueue_Cleanup(WeatherStationDataQueue* const me){
    vSemaphoreDelete(me->sema);
    cleanUpRelations(me);
}

/* Operations */

int WeatherStationDataQueue_insert(WeatherStationDataQueue* const me, WeatherStationData w){
    xSemaphoreTake(me->sema, 0);
    if(!isFull(me)){
        me->itsWeatherStationData[me->head] = w;
        me->head = getNextIndex(me, me->head);
        ++me->size;
        /* instrumentation */
        /* print stuff out, just to visualize the insertions */
        if(me->WeatherLCD != Null_Ptr){
            switch (w.Sensor_type) {
                case temperature_type:
                    me->WeatherLCD->LCD_Write_Cmd(me->WeatherLCD, LCD_I2C_INST_CURSOR_GO_1ST_LINE);
                    me->WeatherLCD->LCD_Write_Data(me->WeatherLCD, "+++ Temperature ");
                    me->WeatherLCD->LCD_Write_Cmd(me->WeatherLCD, LCD_I2C_INST_CURSOR_GO_2ND_LINE);
                    break;
                case light_type:
                    me->WeatherLCD->LCD_Write_Cmd(me->WeatherLCD, LCD_I2C_INST_CURSOR_GO_1ST_LINE);
                    me->WeatherLCD->LCD_Write_Data(me->WeatherLCD, "+++ Light ");
                    me->WeatherLCD->LCD_Write_Cmd(me->WeatherLCD, LCD_I2C_INST_CURSOR_GO_2ND_LINE);
                    break;
                case smoke_type:
                    me->WeatherLCD->LCD_Write_Cmd(me->WeatherLCD, LCD_I2C_INST_CURSOR_GO_1ST_LINE);
                    me->WeatherLCD->LCD_Write_Data(me->WeatherLCD, "+++ SMOKE ");
                    me->WeatherLCD->LCD_Write_Cmd(me->WeatherLCD, LCD_I2C_INST_CURSOR_GO_2ND_LINE);
                    break;
                default:
                    me->WeatherLCD->LCD_Write_Data(me->WeatherLCD, "UNKNWON ");
                    break;
            };
            me->WeatherLCD->LCD_Write_Data(me->WeatherLCD, int_to_string(w.value));
        }
        /* end instrumentation */
        xSemaphoreGive(me->sema);
        return 1;
    }else{ /* return error indication */
        xSemaphoreGive(me->sema);
        return 0;
    }
}


WeatherStationData* WeatherStationDataQueue_remove(WeatherStationDataQueue* const me){
    WeatherStationData* wPtr;
    xSemaphoreTake(me->sema,0);
    if (!isEmpty(me)) {
        wPtr = (WeatherStationData*)malloc(sizeof(WeatherStationData));
        wPtr->Sensor_type = me->itsWeatherStationData[me->tail].Sensor_type;
        wPtr->value = me->itsWeatherStationData[me->tail].value;
        me->tail = getNextIndex(me, me->tail);
        me->size--;
        /* instrumentation */
        if(me->WeatherLCD != Null_Ptr){
            switch (wPtr->Sensor_type) {
                case temperature_type:
                    me->WeatherLCD->LCD_Write_Cmd(me->WeatherLCD, LCD_I2C_INST_CURSOR_GO_1ST_LINE);
                    me->WeatherLCD->LCD_Write_Data(me->WeatherLCD, "--- Temperature ");
                    me->WeatherLCD->LCD_Write_Cmd(me->WeatherLCD, LCD_I2C_INST_CURSOR_GO_2ND_LINE);
                    break;
                case light_type:
                    me->WeatherLCD->LCD_Write_Cmd(me->WeatherLCD, LCD_I2C_INST_CURSOR_GO_1ST_LINE);
                    me->WeatherLCD->LCD_Write_Data(me->WeatherLCD, "--- Light ");
                    me->WeatherLCD->LCD_Write_Cmd(me->WeatherLCD, LCD_I2C_INST_CURSOR_GO_2ND_LINE);
                    break;
                case smoke_type:
                    me->WeatherLCD->LCD_Write_Cmd(me->WeatherLCD, LCD_I2C_INST_CURSOR_GO_1ST_LINE);
                    me->WeatherLCD->LCD_Write_Data(me->WeatherLCD, "--- SMOKE ");
                    me->WeatherLCD->LCD_Write_Cmd(me->WeatherLCD, LCD_I2C_INST_CURSOR_GO_2ND_LINE);
                    break;
                default:
                    me->WeatherLCD->LCD_Write_Data(me->WeatherLCD, "UNKNWON ");
                    break;
            };
            me->WeatherLCD->LCD_Write_Data(me->WeatherLCD, int_to_string(wPtr->value));
        }
        xSemaphoreGive(me->sema);
        return wPtr;
    }else{ /* if empty return NULL ptr */
        xSemaphoreGive(me->sema);
        return NULL;
    }
}

void WeatherStationDataQueue_setItsLCD(WeatherStationDataQueue* const me, LCD_Handler_Type *the_lcd){
    if(the_lcd != Null_Ptr){
        me->WeatherLCD = the_lcd;
    }
}

WeatherStationDataQueue* WeatherStationDataQueue_Create(void){
    WeatherStationDataQueue* result;
    result = (WeatherStationDataQueue*)malloc(sizeof(WeatherStationDataQueue));
    if(result != Null_Ptr){
        WeatherStationDataQueue_Init(result);
    }
    return result;
}

void WeatherStationDataQueue_Destroy(WeatherStationDataQueue* const me){
    if(me != Null_Ptr){
        WeatherStationDataQueue_Destroy(me);
    }
}




