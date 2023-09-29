/*
 * Testing_I2C.h
 *
 *  Created on: Mar 29, 2023
 *      Author: Abdu
 */

#ifndef APP_TESTING_I2C_TESTING_I2C_H_
#define APP_TESTING_I2C_TESTING_I2C_H_


#include "MCAL_Layer/I2C/Dynamic/inc/I2C_Cfg.h"
#include "MCAL_Layer/PORT/Dynamic/inc/PORT_Cfg.h"
#include "MCAL_Layer/IntCtrl/Dynamic/inc/IntCtrl_Cfg.h"


#include "MCAL_Layer/I2C/Static/inc/I2C.h"
#include "MCAL_Layer/PORT/Static/inc/PORT.h"
#include "MCAL_Layer/IntCtrl/Static/inc/IntCtrl.h"

#define TESTING_I2C_USED                (I2C_ChannelType)I2C_NUM_3
#define TESTING_I2C_SLAVE_ADDRESS       0x27


void Testing_I2C_Initialization(void);
void Testing_I2C_Loop(void);

#endif /* APP_TESTING_I2C_TESTING_I2C_H_ */
