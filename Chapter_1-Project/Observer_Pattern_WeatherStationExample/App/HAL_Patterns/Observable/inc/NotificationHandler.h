/*
 * NotificationHandler.h
 *
 *  Created on: Mar 4, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_OBSERVABLE_INC_NOTIFICATIONHANDLER_H_
#define APP_HAL_PATTERNS_OBSERVABLE_INC_NOTIFICATIONHANDLER_H_

#include "../../ObserverPattern_Cfg.h"

typedef struct NotificationHandle NotificationHandle;

struct NotificationHandle{
    Update_t FunPtr;
    NotificationHandle *itsNotificationHandle;
};

void NotificationHandle_Init(NotificationHandle*  me);

void NotificationHandle_Cleanup(NotificationHandle* const me);

struct NotificationHandle* NotificationHandle_getItsNotificationHandle(const NotificationHandle* const me);

void NotificationHandle_setItsNotificationHandle(NotificationHandle* const me, struct NotificationHandle* p_NotificationHandle);

NotificationHandle * NotificationHandle_Create(void);

void NotificationHandle_Destroy(NotificationHandle* const me);

#endif /* APP_HAL_PATTERNS_OBSERVABLE_INC_NOTIFICATIONHANDLER_H_ */
