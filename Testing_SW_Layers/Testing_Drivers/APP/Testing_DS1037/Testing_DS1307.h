/*
 * Testing_DS1307.h
 *
 *  Created on: Mar 18, 2023
 *      Author: Abdu
 */

#ifndef APP_TESTING_DS1037_TESTING_DS1307_H_
#define APP_TESTING_DS1037_TESTING_DS1307_H_

/*
 * do not forget to edit PORT_Cfg, I2c_Cfg and DIO_Cfg to your own configuration
 * also you need to change DS1307_Cfg to your own intial time
 * Make sure to change the CFG files for your own connection based on what SHIT you are doing
 */

#include "../../General_Mcal/DIO/Static/inc/DIO.h"
#include "../../General_Mcal/I2C/Static/inc/I2C.h"
#include "../../General_Mcal/PORT/Static/inc/PORT.h"
#include "../../General_Mcal/IntCtrl/Static/inc/IntCtrl.h"

#include "../../General_HAL/RTC_I2C_DS1307/Static/inc/RTC_I2C_DS1307.h"

void Testing_DS1307(void);

#endif /* APP_TESTING_DS1037_TESTING_DS1307_H_ */
