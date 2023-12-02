/*
 * FireDisplay.c
 *
 *  Created on: May 20, 2023
 *      Author: Abdu
 */

#include "FireDisplay.h"
#include <stdlib.h>

#include "../../Observer/Observer.h"
#include "../../Observable/Observable.h"


static struct FireDisplay{
    LCD_Handler_Type* my_lcd;
    DigitalInterface_Type* my_Buzzer;
    DigitalInterface_Type* my_Led;
    uint8 temperature_value;
    Observer *my_Observer;
}my_FireDisplay;

static void FireDisplay_updateFireDisplay(struct TimeMarkedData *tmd);


void FireDisplay_Init(struct FireDisplay* const me){
    me->my_lcd = Null_Ptr;
    me->temperature_value = 0;
    me->my_Buzzer = Null_Ptr;
    me->my_Led = Null_Ptr;

    me->my_Observer = Observer_Create(FireDisplay_updateFireDisplay);
}

Observer* FireDisplay_getObserver(void){
    return my_FireDisplay.my_Observer;
}


/*
 * The update function that will be passed through the observer to the observable.
 * Here in FireDisplay it's responsible of writing "FIRE" on LCD, set LED and Buzzer HIGH
   if there is a fire only. Other wise it will do nothing.
 * It will write it over the display and it will not free the LCD's semaphore, because
   if it set the semaphore free then the HistogramDisplay will easily write over it .
 */
static void FireDisplay_updateFireDisplay(struct TimeMarkedData *tmd){
    /* Put what you need to update */
    if(my_FireDisplay.my_lcd == Null_Ptr){
        return;
    }
    my_FireDisplay.my_lcd->LCD_Write_Cmd(my_FireDisplay.my_lcd, LCD_I2C_SET_DDRAM_ADDRESS(1, 10));
    if(tmd->temperature_value > 60){
        my_FireDisplay.my_lcd->LCD_Write_Data(my_FireDisplay.my_lcd, "FIRE !");
        my_FireDisplay.my_Buzzer->Write_High(my_FireDisplay.my_Buzzer);
        my_FireDisplay.my_Led->Write_High(my_FireDisplay.my_Led);
        /* until i write semaphore in the LCD library */
    }else{
        my_FireDisplay.my_lcd->LCD_Write_Data(my_FireDisplay.my_lcd, "SAFE");
        my_FireDisplay.my_Buzzer->Write_Low(my_FireDisplay.my_Buzzer);
        my_FireDisplay.my_Led->Write_Low(my_FireDisplay.my_Led);
    }
}

void FireDisplay_setItsLCD(struct FireDisplay* const me, LCD_Handler_Type *p_LCD_Handler){
    me->my_lcd = p_LCD_Handler;
}

void FireDisplay_setItsBUZZER(struct FireDisplay* const me, DigitalInterface_Type* p_BUZZER_Handler){
    me->my_Buzzer = p_BUZZER_Handler;
}

void FireDisplay_setItsLED(struct FireDisplay* const me, DigitalInterface_Type* p_LED_Handler){
    me->my_Led = p_LED_Handler;
}

struct FireDisplay * FireDisplay_GetHandler(void){
    return &my_FireDisplay;
}

