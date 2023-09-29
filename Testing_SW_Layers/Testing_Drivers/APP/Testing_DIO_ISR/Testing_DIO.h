/*
 * Testing_DIO.h
 *
 *  Created on: May 4, 2023
 *      Author: Abdu
 */

#ifndef APP_TESTING_DIO_ISR_TESTING_DIO_H_
#define APP_TESTING_DIO_ISR_TESTING_DIO_H_



#include "MCAL_Layer/DIO/Dynamic/inc/DIO_Cfg.h"
#include "MCAL_Layer/PORT/Dynamic/inc/PORT_Cfg.h"
#include "MCAL_Layer/IntCtrl/Dynamic/inc/IntCtrl_Cfg.h"


#include "MCAL_Layer/DIO/Static/inc/DIO.h"
#include "MCAL_Layer/PORT/Static/inc/PORT.h"
#include "MCAL_Layer/IntCtrl/Static/inc/IntCtrl.h"


#define TESTING_DIO_Button_1_Channel                (DIO_ChannelType)DIO_Channel0_F
#define TESTING_DIO_Button_2_Channel                (DIO_ChannelType)DIO_Channel4_F
#define TESTING_DIO_LED_1_Channel                   (DIO_ChannelType)DIO_Channel1_F
#define TESTING_DIO_LED_2_Channel                   (DIO_ChannelType)DIO_Channel2_F

void Testing_DIO(void);


#endif /* APP_TESTING_DIO_ISR_TESTING_DIO_H_ */
