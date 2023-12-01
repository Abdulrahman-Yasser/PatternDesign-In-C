/*
 * Testing.c
 *
 *  Created on: Apr 18, 2023
 *      Author: Abdu
 */

#include "Testing.h"
#include <stdlib.h>

/* Constructors and destructors:*/
static void TestBuilder_Init(TestBuilder* const me);
static void TestBuilder_Cleanup(TestBuilder* const me);

static void initRelations(TestBuilder* const me);

static void cleanUpRelations(TestBuilder* const me);

void TestBuilder_Init(TestBuilder* const me) {
    initRelations(me);
}

void TestBuilder_Cleanup(TestBuilder* const me) {
    cleanUpRelations(me);
}

struct WeatherStation_Module* TestBuilder_getItsWeatherStation_Module(const TestBuilder* const me) {
    return (struct WeatherStation_Module*)&(me->itsWeatherStation_Module);
}

struct HistogramDisplay* TestBuilder_getItsHistogramDisplay(const TestBuilder* const me) {
    return (struct HistogramDisplay*)&(me->itsHistogramDisplay);
}

struct FireDisplay* TestBuilder_getItsFireDisplay(const TestBuilder* const me) {
    return (struct FireDisplay*)&(me->itsFireDisplay);
}

struct TMDQueue* TestBuilder_getItsTMDQueue(const TestBuilder* const me) {
    return (struct TMDQueue*)&(me->itsTMDQueue);
}

TestBuilder * TestBuilder_Create(void) {
    TestBuilder* me;
    me = (TestBuilder *)malloc(sizeof(TestBuilder));
    if(me!=Null_Ptr)
    {
            TestBuilder_Init(me);
    }
    return me;
}

void TestBuilder_Destroy(TestBuilder* const me) {
    if(me!=Null_Ptr)
    {
        TestBuilder_Cleanup(me);
    }
}

static void initRelations(TestBuilder* const me) {
    WeatherStation_Module_Init(&(me->itsWeatherStation_Module));
    HistogramDisplay_Init(&(me->itsHistogramDisplay));
    TMDQueue_Init(&(me->itsTMDQueue));

    WeatherStation_Module_setItsTMDQueue(&(me->itsWeatherStation_Module), &(me->itsTMDQueue));
    HistogramDisplay_setItsTMDQueue(&(me->itsHistogramDisplay), &(me->itsTMDQueue));
    FireDisplay_setItsTMDQueue(&(me->itsFireDisplay), &(me->itsTMDQueue));
}

static void cleanUpRelations(TestBuilder* const me) {
    TMDQueue_CleanUp(&(me->itsTMDQueue));
    HistogramDisplay_Cleanup(&(me->itsHistogramDisplay));
    FireDisplay_Cleanup(&(me->itsFireDisplay));
    WeatherStation_Module_Cleanup(&(me->itsWeatherStation_Module));
}
