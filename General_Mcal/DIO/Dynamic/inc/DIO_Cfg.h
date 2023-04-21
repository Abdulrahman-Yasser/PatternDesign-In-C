/**********************************************************************************************************************

 *  FILE DESCRIPTIO
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  DIO_Cfg.h
 *       Module:  DIO
 *
 *  Description:  The file got all the USER configurations and all the constant values
 *
 *********************************************************************************************************************/
#ifndef DIO_CFG_H
#define DIO_CFG_H

#include "../../Static/inc/DIO_Types.h"

 /**********************************************************************************************************************
  *  GLOBAL CONSTANT MACROS
  *********************************************************************************************************************/
#define DIO_CONFIGURED_NUMBER       2

extern const struct  DIO_ContainerType DIO_Container[DIO_CONFIGURED_NUMBER];

#define DIO_BUZZER_ID           0
#define DIO_BUTTON_ID           1
#define DIO_LED_ID              2


#define GPIO_UART5_CHECK_PIN         (DIO_ChannelType)DIO_Channel0_B
#define GPIO_UART7_CHECK_PIN         (DIO_ChannelType)DIO_Channel1_B

#define GPIO_UART5_CHECK_PIN         (DIO_ChannelType)DIO_Channel0_B
#define GPIO_UART7_CHECK_PIN         (DIO_ChannelType)DIO_Channel1_B



#endif  /* DIO_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: DIO_Cfg.h
 *********************************************************************************************************************/

