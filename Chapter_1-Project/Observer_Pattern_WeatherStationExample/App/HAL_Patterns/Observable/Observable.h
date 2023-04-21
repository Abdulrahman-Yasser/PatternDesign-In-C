/*
 * Observable.h
 *
 *  Created on: Mar 4, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_OBSERVABLE_OBSERVABLE_H_
#define APP_HAL_PATTERNS_OBSERVABLE_OBSERVABLE_H_

#include <App/HAL_Patterns/Observable/NotificationHandler/NotificationHandler.h>
#include "../../ObserverPattern_Cfg.h"
#include "../../Observer/inc/Observer.h"

typedef struct{
    int nSubscribers;
    NotificationHandle *itsNotificationHandler;
    void (*Subscribe)(Observer* o);
    void (*unSubscribe)(Observer* o);
    void (*Notify)(void);
}Observable_Type;

Observable_Type* Observable_Create(void);

void Observable_Destroy(Observable_Type* me);

#endif /* APP_HAL_PATTERNS_OBSERVABLE_OBSERVABLE_H_ */
