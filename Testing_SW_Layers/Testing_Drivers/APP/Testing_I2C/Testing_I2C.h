/*
 * Testing_I2C.h
 *
 *  Created on: Mar 29, 2023
 *      Author: Abdu
 */

#ifndef APP_TESTING_I2C_TESTING_I2C_H_
#define APP_TESTING_I2C_TESTING_I2C_H_


#include "../../General_Mcal/I2C/Dynamic/Inc/I2C_Cfg.h"
#include "../../General_Mcal/PORT/Dynamic/inc/PORT_Cfg.h"
#include "../../General_Mcal/IntCtrl/Dynamic/inc/IntCtrl_Cfg.h"


#include "../../General_Mcal/I2C/Static/Inc/I2C.h"
#include "../../General_Mcal/PORT/Static/inc/PORT.h"
#include "../../General_Mcal/IntCtrl/Static/inc/IntCtrl.h"

#define TESTING_I2C_USED                (I2C_ChannelType)I2C_NUM_3
#define TESTING_I2C_SLAVE_ADDRESS       0x27


void Testing_I2C_Initialization(void);
void Testing_I2C_Loop(void);

#endif /* APP_TESTING_I2C_TESTING_I2C_H_ */
