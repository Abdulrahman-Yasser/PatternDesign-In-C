/*
 * WeatherStation_Module.h
 * The Server Publisher
 *
 *  Created on: Apr 18, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_SERVER_WEATHERSTATION_MODULE_WEATHERSTATION_MODULE_H_
#define APP_HAL_PATTERNS_SERVER_WEATHERSTATION_MODULE_WEATHERSTATION_MODULE_H_

#include <App/HAL_Patterns/Server/TMDQueue/TMDQueue.h>
#include "../../../ECGPkg.h"

struct TMDQueue;

typedef struct WeatherStation_Module WeatherStation_Module;

struct WeatherStation_Module {
    int dataNum;
    struct TMDQueue* itsTMDQueue;
};


/* Constructors and destructors:*/

void WeatherStation_Module_Init(WeatherStation_Module* const me);

void WeatherStation_Module_Cleanup(WeatherStation_Module* const me);


/* Operations */

void WeatherStation_Module_acquireValue(WeatherStation_Module* const me);

void WeatherStation_Module_setLeadPair(WeatherStation_Module* const me, int l1, int l2);

struct TMDQueue* WeatherStation_Module_getItsTMDQueue(const WeatherStation_Module* const me);

void WeatherStation_Module_setItsTMDQueue(WeatherStation_Module* const me, struct TMDQueue* p_TMDQueue);

WeatherStation_Module * WeatherStation_Module_Create(void);

void WeatherStation_Module_Destroy(WeatherStation_Module* const me);


#endif /* APP_HAL_PATTERNS_SERVER_WEATHERSTATION_MODULE_WEATHERSTATION_MODULE_H_ */
