/*
 * Testing.h
 *
 *  Created on: May 20, 2023
 *      Author: Abdu
 */

#ifndef APP_TESTING_TESTING_H_
#define APP_TESTING_TESTING_H_


/* Server : */
#include "../HAL_Patterns/Server/WeatherStation_Api/WeatherStation_Server.h"

/* Client : */
#include "../HAL_Patterns/Client/FireDisplay/FireDisplay.h"
#include "../HAL_Patterns/Client/HistogramDisplay/HistogramDisplay.h"


struct TestingStruct;


struct TestingStruct *Testing_GetHandler(void);
void Testing_Init_Relations(struct TestingStruct *me);

struct TMDQueue_with_Observable_s *Testing_Get_ItsTMDQueue_with_Observable(struct TestingStruct *me);

void PublishData_To_Observers(struct TMDQueue_with_Observable_s *me);


#endif /* APP_TESTING_TESTING_H_ */