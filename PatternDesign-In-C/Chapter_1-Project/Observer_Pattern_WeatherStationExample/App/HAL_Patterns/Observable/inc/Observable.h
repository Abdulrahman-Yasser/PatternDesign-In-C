/*
 * Observable.h
 *
 *  Created on: Mar 4, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_OBSERVABLE_INC_OBSERVABLE_H_
#define APP_HAL_PATTERNS_OBSERVABLE_INC_OBSERVABLE_H_

#include "NotificationHandler.h"

typedef struct{
    int nSubscribers;
    NotificationHandle *itsNotificationHandler;
    void (*Subscribe)(void(*Fun)(void));
    void (*unSubscribe)(void(*Fun)(void));
    void (*Notify)(void(*Fun)(void));
}Observable_Type;

Observable_Type* Observable_Create(void);

void Observable_Destroy(Observable_Type* me);

#endif /* APP_HAL_PATTERNS_OBSERVABLE_INC_OBSERVABLE_H_ */
