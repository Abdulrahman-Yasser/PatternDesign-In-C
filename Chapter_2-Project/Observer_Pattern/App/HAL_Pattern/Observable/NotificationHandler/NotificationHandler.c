/*
 * NotificationHandler.c
 *
 *  Created on: Mar 4, 2023
 *      Author: Abdu
 */

#include <App/HAL_Patterns/Observable/NotificationHandler/NotificationHandler.h>

#include "../../General_Common/Compiler.h"

void NotificationHandle_Init(NotificationHandle*  me){
    me->itsNotificationHandle = Null_Ptr;
}

void NotificationHandle_Cleanup(NotificationHandle* const me){
    me->itsNotificationHandle = Null_Ptr;
}

struct NotificationHandle* NotificationHandle_getItsNotificationHandle(const NotificationHandle* const me){
    return me->itsNotificationHandle;
}

void NotificationHandle_setItsNotificationHandle(NotificationHandle* const me, struct NotificationHandle* p_NotificationHandle){
    me->itsNotificationHandle = p_NotificationHandle;
}

NotificationHandle * NotificationHandle_Create(void){
    NotificationHandle* me = (NotificationHandle*)malloc(sizeof(NotificationHandle));
    if(me != Null_Ptr){
        NotificationHandle_Init(me);
    }
}

void NotificationHandle_Destroy(NotificationHandle* const me){
    if(me != Null_Ptr){
        NotificationHandle_Cleanup(me);
    }
    free(me);
}

