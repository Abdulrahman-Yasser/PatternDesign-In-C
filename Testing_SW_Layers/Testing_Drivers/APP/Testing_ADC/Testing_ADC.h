/*
 * Testing_ADC.h
 *
 *  Created on: Apr 14, 2023
 *      Author: Abdu
 */

#ifndef APP_TESTING_ADC_TESTING_ADC_H_
#define APP_TESTING_ADC_TESTING_ADC_H_

#include "../../General_Mcal/ADC/Dynamic/Inc/ADC_Cfg.h"
#include "../../General_Mcal/PORT/Dynamic/inc/PORT_Cfg.h"
#include "../../General_Mcal/IntCtrl/Dynamic/inc/IntCtrl_Cfg.h"


#include "../../General_Mcal/ADC/Static/Inc/ADC.h"
#include "../../General_Mcal/PORT/Static/inc/PORT.h"
#include "../../General_Mcal/IntCtrl/Static/inc/IntCtrl.h"

#define TESTING_ADC_Channel                 (ADC_Module_Num_Type)ADC_Module_0
#define TESTING_ADC_SS_NUM                  (ADC_SS_NumType)ADC_SS_3


void Testing_ADC_Test(void);



#endif /* APP_TESTING_ADC_TESTING_ADC_H_ */
