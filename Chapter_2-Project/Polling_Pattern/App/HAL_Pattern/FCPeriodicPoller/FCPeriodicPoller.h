/*
 * FCPeriodicPoller.h
 *
 *  Created on: May 6, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_FCPERIODICPOLLER_FCPERIODICPOLLER_H_
#define APP_HAL_PATTERN_FCPERIODICPOLLER_FCPERIODICPOLLER_H_

#include "../General_Common/Std_Types.h"

#define DEFAULT_POLLING_TIME        20
#define DEFINED_POLL_DEVICES        3
#define MAX_POLL_DEVICES            10


struct FCTimer;

struct FlameCircuitSensor;

struct FireCircuitSensor;

struct FireDisplay;

typedef struct FCPeriodicPoller FCPeriodicPoller_t;

struct FCPeriodicPoller {
    unsigned long pollTime;
    struct FCTimer* itsFCTimer;
    struct FireCircuitSensor* iteFireCircuitSensor[3];
    struct FireDisplay* itsFireDisplay;
};

void FCPeriodicPoller_Init(FCPeriodicPoller_t* const me);
void FCPeriodicPoller_Cleanup(FCPeriodicPoller_t* const me);
/* Operations */
void FCPeriodicPoller_poll(void);
void FCPeriodicPoller_setPollTime(FCPeriodicPoller_t* const me, uint16 t);
void FCPeriodicPoller_startPolling(FCPeriodicPoller_t* const me);
void FCPeriodicPoller_stopPolling(FCPeriodicPoller_t* const me);

struct FCTimer* FCPeriodicPoller_getItsFCTimer(const FCPeriodicPoller_t* const me);
void FCPeriodicPoller_setItsFCTimer(FCPeriodicPoller_t* const me, struct FCTimer* p_FCTimer);

struct FireCircuitSensor* FCPeriodicPoller_getItsFireCircuitSensor(const FCPeriodicPoller_t* const me, uint8 my_SENSOR_ID);
void FCPeriodicPoller_addItsFireCircuitSensor(FCPeriodicPoller_t* const me, struct FireCircuitSensor* p_FireCircuitSensor,  uint8 my_SENSOR_ID);
void FCPeriodicPoller_removeItsFireCircuitSensor(FCPeriodicPoller_t* const me,struct FireCircuitSensor * p_FireCircuitSensor);
void FCPeriodicPoller_clearItsFireCircuitSensor(FCPeriodicPoller_t* const me);

struct FireDisplay* FCPeriodicPoller_getItsFireDisplay(const FCPeriodicPoller_t*const me);
void FCPeriodicPoller_setItsFireDisplay(FCPeriodicPoller_t* const me, struct FireDisplay* p_FireDisplay);

FCPeriodicPoller_t * FCPeriodicPoller_Create(void);


#endif /* APP_HAL_PATTERN_FCPERIODICPOLLER_FCPERIODICPOLLER_H_ */
