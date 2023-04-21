/*
 * Observable.c
 *
 *  Created on: Mar 4, 2023
 *      Author: Abdu
 */

#include <App/HAL_Patterns/Observable/Observable.h>

#include "../../General_Common/Compiler.h"
#include "../../ObserverPattern_Cfg.h"

Observable_Type* Observable_Create(void){
    Observable_Type *me;
    me = (Observable_Type*)malloc(sizeof(Observable_Type));
    if(me != Null_Ptr){
        me->itsNotificationHandler = Null_Ptr;
        me->nSubscribers = 0;
    }
    return me;
}

void Observable_Destroy(Observable_Type* me){
    free(me);
}


