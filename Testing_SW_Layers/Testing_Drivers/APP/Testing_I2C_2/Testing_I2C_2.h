/*
 * Testing_I2C_2.h
 *
 *  Created on: Mar 29, 2023
 *      Author: Abdu
 */

#ifndef APP_Testing_I2C_2_Testing_I2C_2_H_
#define APP_Testing_I2C_2_Testing_I2C_2_H_


#include "MCAL_Layer/I2C/Dynamic/inc/I2C_Cfg.h"
#include "MCAL_Layer/PORT/Dynamic/inc/PORT_Cfg.h"
#include "MCAL_Layer/IntCtrl/Dynamic/inc/IntCtrl_Cfg.h"


#include "MCAL_Layer/I2C/Static/inc/I2C.h"
#include "MCAL_Layer/PORT/Static/inc/PORT.h"
#include "MCAL_Layer/IntCtrl/Static/inc/IntCtrl.h"

#define Testing_I2C_2_USED                (I2C_ChannelType)I2C_NUM_3
#define Testing_I2C_2_SLAVE_ADDRESS       0x27


void Testing_I2C_2_Initialization(void);
void Testing_I2C_2_Loop(void);

#endif /* APP_Testing_I2C_2_Testing_I2C_2_H_ */
