/*
 * Testing.h
 *
 *  Created on: May 20, 2023
 *      Author: Abdu
 */

#ifndef APP_TESTING_TESTING_H_
#define APP_TESTING_TESTING_H_


/* Server : */
#include <App/HAL_Patterns/Client/LED_1/LED_1.h>
#include <App/HAL_Patterns/Client/LED_2/LED_2.h>
#include <App/HAL_Patterns/Client/Buzzer/Buzzer.h>


#include "../HAL_Patterns/Server/Publisher_API/Publisher_API.h"

/* Client : */


struct TestingStruct;


struct TestingStruct *Testing_GetHandler(void);
void Testing_Init_Relations(struct TestingStruct *me);

struct TMDQueue_with_Observable_s *Testing_Get_ItsTMDQueue_with_Observable(struct TestingStruct *me);

void PublishData_To_Observers(struct TMDQueue_with_Observable_s *me);


#endif /* APP_TESTING_TESTING_H_ */
