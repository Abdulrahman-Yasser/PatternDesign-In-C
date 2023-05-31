/*
 * Observable.h
 *
 *  Created on: Mar 4, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_OBSERVABLE_OBSERVABLE_H_
#define APP_HAL_PATTERNS_OBSERVABLE_OBSERVABLE_H_

#include "NotificationHandler/NotificationHandler.h"
#include "../ObserverPattern_Cfg.h"
#include "../Observer/Observer.h"

typedef struct observable_struct Observable_Type;

struct observable_struct{
    int nSubscribers;
    NotificationHandle *itsNotificationHandler;
    void (*Subscribe)(Observable_Type*, Observer*);
    void (*unSubscribe)(Observable_Type*, Observer*);
    void (*Notify)(Observable_Type*, uint8);
};

Observable_Type* Observable_Create(void);



void Observable_Destroy(Observable_Type* me);

#endif /* APP_HAL_PATTERNS_OBSERVABLE_OBSERVABLE_H_ */
