/*
 * Observable.h
 *
 *  Created on: Mar 4, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_OBSERVABLE_OBSERVABLE_H_
#define APP_HAL_PATTERNS_OBSERVABLE_OBSERVABLE_H_

#include <App/HAL_Patterns/Observable/NotificationHandler/NotificationHandler.h>
#include "../ObserverPattern_Cfg.h"
#include "../Observer/Observer.h"

typedef struct Observable_struct Observable_Type;

struct Observable_struct{
    int nSubscribers;
    NotificationHandle *itsNotificationHandler;
    void (*Subscribe)(Observable_Type* me, Observer* o);
    void (*unSubscribe)(Observable_Type* me, Observer* o);
    void (*Notify)(Observable_Type* me, struct TimeMarkedData* data);
};

Observable_Type* Observable_Create(void);

void Observable_Destroy(Observable_Type* me);

#endif /* APP_HAL_PATTERNS_OBSERVABLE_OBSERVABLE_H_ */
