/*
 * LedEmitter.c
 *
 *  Created on: May 8, 2023
 *      Author: Abdu
 */

#include "LedEmitter.h"

#include <stdlib.h>

LedEmitter *LedEmitter_Create(DIO_ChannelType led_Ch){
    LedEmitter* me;
    me = (LedEmitter*)malloc(sizeof(LedEmitter));
    if(me != Null_Ptr){
        me->Led = Digital_Interface_Create(led_Ch);
    }
    return me;
}

void LedEmitter_Destroy(LedEmitter* me){

}

void LedEmitter_startEmitting(LedEmitter* me){
    me->Led->Write_High(me->Led);
}

void LedEmitter_stopEmitting(LedEmitter* me){
    me->Led->Write_Low(me->Led);
}
