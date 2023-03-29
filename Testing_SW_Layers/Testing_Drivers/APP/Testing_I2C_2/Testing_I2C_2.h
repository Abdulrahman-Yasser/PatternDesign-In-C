/*
 * Testing_I2C_2.h
 *
 *  Created on: Mar 29, 2023
 *      Author: Abdu
 */

#ifndef APP_Testing_I2C_2_Testing_I2C_2_H_
#define APP_Testing_I2C_2_Testing_I2C_2_H_


#include "../../General_Mcal/I2C/Dynamic/Inc/I2C_Cfg.h"
#include "../../General_Mcal/PORT/Dynamic/inc/PORT_Cfg.h"
#include "../../General_Mcal/IntCtrl/Dynamic/inc/IntCtrl_Cfg.h"


#include "../../General_Mcal/I2C/Static/Inc/I2C.h"
#include "../../General_Mcal/PORT/Static/inc/PORT.h"
#include "../../General_Mcal/IntCtrl/Static/inc/IntCtrl.h"

#define Testing_I2C_2_USED                (I2C_ChannelType)I2C_NUM_3
#define Testing_I2C_2_SLAVE_ADDRESS       0x27


void Testing_I2C_2_Initialization(void);
void Testing_I2C_2_Loop(void);

#endif /* APP_Testing_I2C_2_Testing_I2C_2_H_ */
