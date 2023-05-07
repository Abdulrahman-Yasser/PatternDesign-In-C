/*
 * FireDisplay.c
 *
 *  Created on: May 6, 2023
 *      Author: Abdu
 */

#include "FireDisplay.h"

#include "../General_HAL/Digital_Intrface/Static/inc/Digital_Interface.h"
#include <stdlib.h>

static void FireDisplay_showFlameStatus(FireDisplay_t* me, uint8 status);

static void FireDisplay_showTempStatus(FireDisplay_t* me, uint8 status);

FireDisplay_t *FireDisplay_Create(void){
    FireDisplay_t* me;
    me = (FireDisplay_t*)malloc(sizeof(FireDisplay_t));
    if(me != Null_Ptr){
        me->Flame_LED = Digital_Interface_Create(DIO_Channel1_F);
        me->Temp_LED = Digital_Interface_Create(DIO_Channel2_F);
        me->FIRE_LED = Digital_Interface_Create(DIO_Channel3_F);
    }
    return me;
}


static void FireDisplay_showFlameStatus(FireDisplay_t* me, uint8 status){
    if(status == 1){
        me->Flame_LED->Write_High(me->Flame_LED);
    }
}

static void FireDisplay_showTempStatus(FireDisplay_t* me, uint8 status){
    if(status == 1){
        me->Temp_LED->Write_High(me->Temp_LED);
    }
}

void FireDisplay_showStatus(FireDisplay_t* me, uint8 Flamestatus, uint8 Tempstatus){
    if(Flamestatus == 1 && Tempstatus == 1){
        me->FIRE_LED->Write_High(me->FIRE_LED);
        me->Flame_LED->Write_High(me->Flame_LED);
        me->Temp_LED->Write_High(me->Temp_LED);
    }else if(Flamestatus != 1 && Tempstatus == 1){
        me->FIRE_LED->Write_Low(me->FIRE_LED);
        me->Flame_LED->Write_Low(me->Flame_LED);
        me->Temp_LED->Write_High(me->Temp_LED);
    }else if(Flamestatus == 1 && Tempstatus != 1){
        me->FIRE_LED->Write_Low(me->FIRE_LED);
        me->Flame_LED->Write_High(me->Flame_LED);
        me->Temp_LED->Write_Low(me->Temp_LED);
    }else if(Flamestatus != 1 && Tempstatus != 1){
        me->FIRE_LED->Write_Low(me->FIRE_LED);
        me->Flame_LED->Write_Low(me->Flame_LED);
        me->Temp_LED->Write_Low(me->Temp_LED);
    }
}

