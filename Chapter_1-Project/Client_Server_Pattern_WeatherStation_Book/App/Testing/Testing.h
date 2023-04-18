/*
 * Testing.h
 *
 *  Created on: Apr 18, 2023
 *      Author: Abdu
 */

#ifndef APP_TESTING_TESTING_H_
#define APP_TESTING_TESTING_H_

#include "../WeatherStation_Module/WeatherStation_Module.h"
#include "../HistogramDisplay/HistogramDisplay.h"
#include "../TMDQueue/TMDQueue.h"

/* class TestBuilder */
typedef struct TestBuilder TestBuilder;

struct TestBuilder {
    struct WeatherStation_Module itsWeatherStation_Module;
    struct HistogramDisplay itsHistogramDisplay;
    struct TMDQueue itsTMDQueue;
};

/* Constructors and destructors:*/
void TestBuilder_Init(TestBuilder* const me);
void TestBuilder_Cleanup(TestBuilder* const me);

struct WeatherStation_Module* TestBuilder_getItsWeatherStation_Module(const TestBuilder* const me);

struct HistogramDisplay* TestBuilder_getItsHistogramDisplay(const TestBuilder* const me);

struct TMDQueue* TestBuilder_getItsTMDQueue(const TestBuilder* const me);

TestBuilder * TestBuilder_Create(void);

void TestBuilder_Destroy(TestBuilder* const me);

#endif /* APP_TESTING_TESTING_H_ */
