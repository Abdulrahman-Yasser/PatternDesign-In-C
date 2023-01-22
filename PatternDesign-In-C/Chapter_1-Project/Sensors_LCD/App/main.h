/*
 * main.h
 *
 *  Created on: Dec 22, 2022
 *      Author: abduy
 */

#ifndef APP_MAIN_H_
#define APP_MAIN_H_

#include "../Mcal/I2C/Static/inc/I2C.h"
#include "../Mcal/UART/Static/inc/UART.h"
#include "../Mcal/DIO/Static/inc/DIO.h"
#include "../Mcal/PORT/Static/inc/PORT.h"
#include "../Mcal/IntCtrl/Static/inc/IntCtrl.h"
#include "../Mcal/GPT/Static/inc/GPT.h"
#include "../Mcal/SysTick/Static/inc/SysTick.h"
#include "../Mcal/PWM/Static/inc/PWM.h"

#include "../Mcal/I2C/Dynamic/inc/I2C_Cfg.h"
#include "../Mcal/UART/Dynamic/inc/UART_Cfg.h"
#include "../Mcal/DIO/Dynamic/inc/DIO_Cfg.h"
#include "../Mcal/PORT/Dynamic/inc/PORT_Cfg.h"
#include "../Mcal/IntCtrl/Dynamic/inc/IntCtrl_Cfg.h"
#include "../Mcal/GPT/Dynamic/inc/GPT_Cfg.h"
#include "../Mcal/SysTick/Dynamic/inc/SysTick_CFG.h"
#include "../Mcal/PWM/Dynamic/inc/PWM_Cfg.h"


void App_Init(void);
void transmit(void);
void Send_Msg(char* msg);
uint8* Rcv_Msg(UART_ChannelType my_uart);

/*
 * ================================== I2C TEST =========================================
 */
#define I2c_test_Slave_Address 0x02


#endif /* APP_MAIN_H_ */
