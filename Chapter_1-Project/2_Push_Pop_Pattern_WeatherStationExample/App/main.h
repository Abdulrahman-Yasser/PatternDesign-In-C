/*
 * main.h
 *
 *  Created on: Dec 22, 2022
 *      Author: abduy
 */

#ifndef APP_MAIN_H_
#define APP_MAIN_H_


#include "../MCAL_Layer/I2C/Static/inc/I2C.h"
#include "../MCAL_Layer/UART/Static/inc/UART.h"
#include "../MCAL_Layer/DIO/Static/inc/DIO.h"
#include "../MCAL_Layer/PORT/Static/inc/PORT.h"
#include "../MCAL_Layer/IntCtrl/Static/inc/IntCtrl.h"
#include "../MCAL_Layer/GPT/Static/inc/GPT.h"
#include "../MCAL_Layer/SysTick/Static/inc/SysTick.h"
#include "../MCAL_Layer/PWM/Static/inc/PWM.h"

#include "../MCAL_Layer/I2C/Dynamic/inc/I2C_Cfg.h"
#include "../MCAL_Layer/UART/Dynamic/inc/UART_Cfg.h"
#include "../MCAL_Layer/DIO/Dynamic/inc/DIO_Cfg.h"
#include "../MCAL_Layer/PORT/Dynamic/inc/PORT_Cfg.h"
#include "../MCAL_Layer/IntCtrl/Dynamic/inc/IntCtrl_Cfg.h"
#include "../MCAL_Layer/GPT/Dynamic/inc/GPT_Cfg.h"
#include "../MCAL_Layer/SysTick/Dynamic/inc/SysTick_CFG.h"
#include "../MCAL_Layer/PWM/Dynamic/inc/PWM_Cfg.h"

#include "HAL_Layer/LCD/Static/inc/LCD.h"
#include "HAL_Layer/LCD/Dynamic/inc/LCD_Cfg.h"

#include "HAL_Patterns/System_App/inc/System_App.h"

void App_Init(void);
void transmit(void);
void Send_Msg(char* msg);
uint8* Rcv_Msg(UART_ChannelType my_uart);

/*
 * ================================== I2C TEST =========================================
 */
#define I2c_test_Slave_Address 0x02


#endif /* APP_MAIN_H_ */
