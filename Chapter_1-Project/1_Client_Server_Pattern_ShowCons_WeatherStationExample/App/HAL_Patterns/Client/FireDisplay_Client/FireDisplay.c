/*
 * FireDisplay.c
 *
 *  Created on: Apr 20, 2023
 *      Author: Abdu
 */

#include "../../Server/TMDQueue/TMDQueue.h"
#include "HAL_Layer/LCD/Static/inc/LCD.h"

#include "FireDisplay.h"

#include <stdlib.h>



static void cleanUpRelations(FireDisplay* const me);

void FireDisplay_Init(FireDisplay* const me){
    me->index = 0;
    me->itsTMDQueue = Null_Ptr;
    me->my_lcd = Null_Ptr;
    me->my_Buzzer = Null_Ptr;
    me->my_Led = Null_Ptr;
}

void FireDisplay_Cleanup(FireDisplay* const me){
    cleanUpRelations(me);
}

/* Operations */

/* only cares about the temperature and Time */

void FireDisplay_getValue(FireDisplay* const me){
    struct TimeMarkedData tmd;
    uint8 t;

    if(me->itsTMDQueue == Null_Ptr || me->my_lcd == Null_Ptr){
        return;
    }

    t = TMDQueue_getLastIndex(me->itsTMDQueue);
    /* that means that FireDisplay did not read that index before*/
    if(t != me->index){
        me->index = t;
        tmd = TMDQueue_remove(me->itsTMDQueue, me->index);
    }else{
    /* i've already read that value */
        return ;
    }

    me->my_lcd->LCD_Write_Cmd(me->my_lcd, LCD_I2C_SET_DDRAM_ADDRESS(1, 8));
    if(tmd.temperature_value > 60){
        me->my_lcd->LCD_Write_Data(me->my_lcd, "FIRE !!");
        me->my_Buzzer->Write_High(me->my_Buzzer);
        me->my_Led->Write_High(me->my_Led);
    }else{
        me->my_lcd->LCD_Write_Data(me->my_lcd, "SAFE   ");
        me->my_Buzzer->Write_Low(me->my_Buzzer);
        me->my_Led->Write_Low(me->my_Led);
    }

}

void FireDisplay_updateFireDisplay(FireDisplay* const me){
    /* Put what you need to update */
    FireDisplay_getValue(me);
}

struct TMDQueue* FireDisplay_getItsTMDQueue(const FireDisplay* const me){
    return (struct TMDQueue*)me->itsTMDQueue;
}

void FireDisplay_setItsTMDQueue(FireDisplay* const me, struct TMDQueue*p_TMDQueue){
    me->itsTMDQueue = p_TMDQueue;
}

void FireDisplay_setItsLCD(FireDisplay* const me, LCD_Handler_Type *p_LCD_Handler){
    me->my_lcd = p_LCD_Handler;
}

void FireDisplay_setItsBUZZER(FireDisplay* const me, DigitalInterface_Type* p_BUZZER_Handler){
    me->my_Buzzer = p_BUZZER_Handler;
}

void FireDisplay_setItsLED(FireDisplay* const me, DigitalInterface_Type* p_LED_Handler){
    me->my_Led = p_LED_Handler;
}

FireDisplay * FireDisplay_Create(void){
    FireDisplay* me = (FireDisplay*)malloc(sizeof(FireDisplay));
    if(me!=Null_Ptr)
    {
        FireDisplay_Init(me);
    }
    return me;
}

void FireDisplay_Destroy(FireDisplay* const me){
    if(me!=Null_Ptr)
    {
        FireDisplay_Cleanup(me);
    }
    free(me);
}

static void cleanUpRelations(FireDisplay* const me) {
    if(me != Null_Ptr){
        free(me->my_Buzzer);
        free(me->my_lcd);
        free(me->my_Led);
    }else{
        return;
    }
    if(me->itsTMDQueue != Null_Ptr)
    {
        /* we will not free it because some other client may be using it */
        me->itsTMDQueue = Null_Ptr;
    }
}
