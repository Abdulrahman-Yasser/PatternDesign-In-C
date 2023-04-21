
/*
 * Digital_Interface.c
 *
 *  Created on: Apr 20, 2023
 *      Author: Abdu
 */


#include <Digital_Intrface/Dynamic/inc/Digital_Interface_Cfg.h>
#include "../inc/Digital_Interface.h"
#include <stdlib.h>
#include "../General_Mcal/DIO/Static/inc/DIO.h"


static void Digital_Interface_WriteHigh(DigitalInterface_Type* const me);
static void Digital_Interface_WriteLow(DigitalInterface_Type* const me);
static void Digital_Interface_Toggle(DigitalInterface_Type* const me);


static void Digital_Interface_WriteHigh(DigitalInterface_Type* const me){
    me->Dio_Level = DIO_Level_HIGH;
    Dio_WriteChannel(me->Dio_Ch, DIO_Level_HIGH);
}

static void Digital_Interface_WriteLow(DigitalInterface_Type* const me){
    me->Dio_Level = DIO_Level_LOW;
    Dio_WriteChannel(me->Dio_Ch, DIO_Level_LOW);
}

static void Digital_Interface_Toggle(DigitalInterface_Type* const me){
    if(me->Dio_Level == DIO_Level_HIGH){
        me->Write_Low(me);
    }else{
        me->Write_High(me);
    }
}

DigitalInterface_Type* Digital_Interface_Create(uint8 DIO_ID){
    DigitalInterface_Type* me;
    me = (DigitalInterface_Type*)malloc(sizeof(DigitalInterface_Type));
    if(me != Null_Ptr){
        me->Write_High = Digital_Interface_WriteHigh;
        me->Write_Low = Digital_Interface_WriteLow;
        me->Write_Toggle = Digital_Interface_Toggle;
        me->Dio_Ch = DIO_Container[DIO_ID].DIO_ch;
        me->Dio_Level = DIO_Container[DIO_ID].DIO_Init_Lvl;
        if(me->Dio_Level == DIO_Level_HIGH){
            me->Write_High(me);
        }else{
            me->Write_Low(me);
        }
    }
    return me;
}

void Digital_Interface_Destroy(DigitalInterface_Type* me){
    if(me != Null_Ptr){
        free(me);
    }
}

