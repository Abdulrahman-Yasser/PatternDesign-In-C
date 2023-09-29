/*
 * Testing_ADC.h
 *
 *  Created on: Apr 14, 2023
 *      Author: Abdu
 */

#ifndef APP_TESTING_ADC_TESTING_ADC_H_
#define APP_TESTING_ADC_TESTING_ADC_H_

#include "MCAL_Layer/ADC/Dynamic/inc/ADC_Cfg.h"
#include "MCAL_Layer/PORT/Dynamic/inc/PORT_Cfg.h"
#include "MCAL_Layer/IntCtrl/Dynamic/inc/IntCtrl_Cfg.h"


#include "MCAL_Layer/ADC/Static/inc/ADC.h"
#include "MCAL_Layer/PORT/Static/inc/PORT.h"
#include "MCAL_Layer/IntCtrl/Static/inc/IntCtrl.h"

#include <stdio.h>
#include <stdlib.h>

#define TESTING_ADC_Channel                 (ADC_Module_Num_Type)ADC_Module_0
#define TESTING_ADC_SS_NUM                  (ADC_SS_NumType)ADC_SS_3
#define TESTING_ADC_Pin                     (ADC_Channel_Num_Type)ADC_Channel_AIN0


void Testing_ADC_Test(void);



#endif /* APP_TESTING_ADC_TESTING_ADC_H_ */
