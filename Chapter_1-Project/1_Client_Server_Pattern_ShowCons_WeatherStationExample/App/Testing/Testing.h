/*
 * Testing.h
 *
 *  Created on: Apr 18, 2023
 *      Author: Abdu
 */

#ifndef APP_TESTING_TESTING_H_
#define APP_TESTING_TESTING_H_

#include "../HAL_Patterns/Server/WeatherStation_Module/WeatherStation_Module.h"
#include "../HAL_Patterns/Client/HistogramDisplay/HistogramDisplay.h"
#include "../HAL_Patterns/Client/FireDisplay_Client/FireDisplay.h"
#include "../HAL_Patterns/Server/TMDQueue/TMDQueue.h"

/* class TestBuilder */
typedef struct TestBuilder TestBuilder;

struct TestBuilder {
    struct WeatherStation_Module itsWeatherStation_Module;
    struct HistogramDisplay itsHistogramDisplay;
    struct FireDisplay itsFireDisplay;
    struct TMDQueue itsTMDQueue;
};


struct WeatherStation_Module* TestBuilder_getItsWeatherStation_Module(const TestBuilder* const me);

struct HistogramDisplay* TestBuilder_getItsHistogramDisplay(const TestBuilder* const me);

struct FireDisplay* TestBuilder_getItsFireDisplay(const TestBuilder* const me) ;

struct TMDQueue* TestBuilder_getItsTMDQueue(const TestBuilder* const me);

TestBuilder * TestBuilder_Create(void);

void TestBuilder_Destroy(TestBuilder* const me);

#endif /* APP_TESTING_TESTING_H_ */
