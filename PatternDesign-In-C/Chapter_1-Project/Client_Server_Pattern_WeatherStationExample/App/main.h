/*
 * main.h
 *
 *  Created on: Dec 22, 2022
 *      Author: abduy
 */

#ifndef APP_MAIN_H_
#define APP_MAIN_H_



#include "../../General_Mcal/I2C/Static/inc/I2C.h"
#include "../../General_Mcal/UART/Static/inc/UART.h"
#include "../../General_Mcal/DIO/Static/inc/DIO.h"
#include "../../General_Mcal/PORT/Static/inc/PORT.h"
#include "../../General_Mcal/IntCtrl/Static/inc/IntCtrl.h"
#include "../../General_Mcal/GPT/Static/inc/GPT.h"
#include "../../General_Mcal/SysTick/Static/inc/SysTick.h"
#include "../../General_Mcal/PWM/Static/inc/PWM.h"

#include "../../General_Mcal/I2C/Dynamic/inc/I2C_Cfg.h"
#include "../../General_Mcal/UART/Dynamic/inc/UART_Cfg.h"
#include "../../General_Mcal/DIO/Dynamic/inc/DIO_Cfg.h"
#include "../../General_Mcal/PORT/Dynamic/inc/PORT_Cfg.h"
#include "../../General_Mcal/IntCtrl/Dynamic/inc/IntCtrl_Cfg.h"
#include "../../General_Mcal/GPT/Dynamic/inc/GPT_Cfg.h"
#include "../../General_Mcal/SysTick/Dynamic/inc/SysTick_CFG.h"
#include "../../General_Mcal/PWM/Dynamic/inc/PWM_Cfg.h"


void App_Init(void);
void transmit(void);
void Send_Msg(char* msg);
uint8* Rcv_Msg(UART_ChannelType my_uart);

/*
 * ================================== I2C TEST =========================================
 */
#define I2c_test_Slave_Address 0x02


#endif /* APP_MAIN_H_ */
