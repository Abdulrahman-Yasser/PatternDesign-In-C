/*
 * Testing_DIO.h
 *
 *  Created on: May 4, 2023
 *      Author: Abdu
 */

#ifndef APP_TESTING_DIO_ISR_TESTING_DIO_H_
#define APP_TESTING_DIO_ISR_TESTING_DIO_H_



#include "../../General_Mcal/DIO/Dynamic/Inc/DIO_Cfg.h"
#include "../../General_Mcal/PORT/Dynamic/inc/PORT_Cfg.h"
#include "../../General_Mcal/IntCtrl/Dynamic/inc/IntCtrl_Cfg.h"


#include "../../General_Mcal/DIO/Static/Inc/DIO.h"
#include "../../General_Mcal/PORT/Static/inc/PORT.h"
#include "../../General_Mcal/IntCtrl/Static/inc/IntCtrl.h"


#define TESTING_DIO_Button_1_Channel                (DIO_ChannelType)DIO_Channel0_F
#define TESTING_DIO_Button_2_Channel                (DIO_ChannelType)DIO_Channel4_F
#define TESTING_DIO_LED_1_Channel                   (DIO_ChannelType)DIO_Channel1_F
#define TESTING_DIO_LED_2_Channel                   (DIO_ChannelType)DIO_Channel2_F


#endif /* APP_TESTING_DIO_ISR_TESTING_DIO_H_ */
