/**********************************************************************************************************************

 *  FILE DESCRIPTIO
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  DIO.h
 *       Module:  DIO
 *
 *  Description:  The file got all the global function we will use in the driver
 *
 *********************************************************************************************************************/
#ifndef DIO_H
#define DIO_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "../../Dynamic/inc/DIO_Cfg.h"
#include "../../General_Common/Std_Types.h"
#include "DIO_Types.h"



/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

void Dio_Init(void);

DIO_ChannelType Dio_GetChannelId(uint8 Dio_cfg_Array_ID);

DIO_LevelType Dio_ReadChannel(DIO_ChannelType ChannelId);

void Dio_WriteChannel(DIO_ChannelType ChannelId, DIO_LevelType Level);

DIO_PortLevelType Dio_ReadPort(DIO_PortType PortId);

void Dio_WritePort(DIO_PortType PortId, DIO_PortLevelType Level);

DIO_LevelType Dio_FlipChannel(DIO_ChannelType ChannelId);

uint8 Dio_Check_Isr(DIO_ChannelType ChannelId);

uint8 Dio_Remove_Isr(DIO_ChannelType ChannelId);

void Dio_Init_ISR(DIO_ChannelType ChannelId, DIO_ChannelISR_Type ISR_Event);

void Dio_Set_CallBackFun(DIO_ChannelType ChannelId, void (*DioCallBackFun)(void));

#endif    /* DIO_H */

/**********************************************************************************************************************
 *  END OF FILE: DIO.h
 *********************************************************************************************************************/

