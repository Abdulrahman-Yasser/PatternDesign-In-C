/*
 * ButtonDriver.c
 *
 *  Created on: May 8, 2023
 *      Author: Abdu
 */

#include "ButtonDriver.h"
#include <stdlib.h>

#include "../LedEmitter/LedEmitter.h"

void ButtonDriver_Init(ButtonDriver* const me){
    me->oldState = 0;
    me->toggleOn = 0;
    me->itsButton = Null_Ptr;
    me->itsLedEmitter = Null_Ptr;
}
void ButtonDriver_Cleanup(ButtonDriver* const me){
    free(me->itsButton);
    free(me->itsLedEmitter);

}
/* Operations */
void ButtonDriver_eventReceive(ButtonDriver* const me){
    Delay_ms(DEBOUNCE_TIME);
    if( me->itsButton->Read(me->itsButton) != me->oldState){
        me->oldState = me->itsButton->Last_State;
        if(me->toggleOn){
            me->toggleOn = 0;
            LedEmitter_stopEmitting(me->itsLedEmitter);
        }else{
            me->toggleOn = 1;
            LedEmitter_startEmitting(me->itsLedEmitter);
        }
    }
}

Button_Type* ButtonDriver_getItsButton(const ButtonDriver* const me){
    return me->itsButton;
}
void ButtonDriver_setItsButton(ButtonDriver* const me, Button_Type* p_Button){
    me->itsButton = p_Button;
}
struct LedEmitter* ButtonDriver_getItsLedEmitter(const ButtonDriver* const me){
    return me->itsLedEmitter;
}
void ButtonDriver_setItsLedEmitter(ButtonDriver* const me, struct LedEmitter* p_LedEmitter){
    me->itsLedEmitter = p_LedEmitter;
}
ButtonDriver *ButtonDriver_Create(void){
    ButtonDriver* me;
    me = (ButtonDriver*)malloc(sizeof(ButtonDriver));
    if(me != Null_Ptr){
        ButtonDriver_Init(me);
    }
    return me;
}
void ButtonDriver_Destroy(ButtonDriver* const me){

}



