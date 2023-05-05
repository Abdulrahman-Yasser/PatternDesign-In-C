/**********************************************************************************************************************
 *  FILE DESCRIPTION
  *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  DIO.c
  *        \brief  Digital Input Output Driver
  *
  *      \details  This file contains the static implementation of the driver
  *                  it contains all the function implementation logic
  *
  *
  *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "../../General_Common/Std_Types.h"

#include "../../Dynamic/inc/DIO_Cfg.h"

#include "../General_Common/DataStructure/FunctionQueue/FunctionQueue.h"

#include "../../General_Common/Mcu_Hw.h"

#include "../inc/DIO.h"


extern void  DIO_A_handler(void);

extern void  DIO_B_handler(void);

extern void  DIO_C_handler(void);

extern void  DIO_D_handler(void);

extern void  DIO_E_handler(void);

extern void  DIO_F_handler(void);

/**********************************************************************************************************************
 *  STATIC VARIABLES
 *********************************************************************************************************************/

static FunctionQueue_t* DIO_handlerFunctionQueue[6];

/**********************************************************************************************************************
 *  STATIC FUNCTIONS
 *********************************************************************************************************************/

inline static uint32 Dio_GetBase_Channel(DIO_ChannelType ChannelId);
inline static uint32 Dio_GetBase_Port(DIO_PortType PortId);




inline static uint32 Dio_GetBase_Channel(DIO_ChannelType ChannelId){
    uint32 temp;
    switch(ChannelId / 8){
    case 0:
        temp = GPIO_PORTA_BASE_ADDRESS;
        break;
    case 1:
        temp = GPIO_PORTB_BASE_ADDRESS;
        break;
    case 2:
        temp = GPIO_PORTC_BASE_ADDRESS;
        break;
    case 3:
        temp = GPIO_PORTD_BASE_ADDRESS;
        break;
    case 4:
        temp = GPIO_PORTE_BASE_ADDRESS ;
        break;
    case 5:
        temp = GPIO_PORTF_BASE_ADDRESS ;
        break;
    default:
        break;
    }
    return temp;
}

inline static uint32 Dio_GetBase_Port(DIO_PortType PortId){
    uint32 temp;
    switch(PortId){
    case DIO_PORTA:
        temp = GPIO_PORTA_BASE_ADDRESS;
        break;
    case DIO_PORTB:
        temp = GPIO_PORTB_BASE_ADDRESS;
        break;
    case DIO_PORTC:
        temp = GPIO_PORTC_BASE_ADDRESS;
        break;
    case DIO_PORTD:
        temp = GPIO_PORTD_BASE_ADDRESS;
        break;
    case DIO_PORTE:
        temp = GPIO_PORTE_BASE_ADDRESS ;
        break;
    case DIO_PORTF:
        temp = GPIO_PORTF_BASE_ADDRESS ;
        break;
    default:
        break;
    }
    return temp;
}
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void Dio_Init(void){
    uint8 i = 0;
    for(i = 0; i < DIO_INPUT_CONFIGURED_NUMBER; i++){
        Dio_Init_ISR(DIO_Input_Container[i].DIO_ch, DIO_Input_Container[i].DIO_Isr);
    }
}


/******************************************************************************
* \Syntax          : DIO_LevelType Dio_ReadChannel(DIO_ChannelType ChannelId)
* \Description     : The Function Reads a specific pin's output
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : ChannelId          The pin Number in the board
* \Parameters (out): None
* \Return value:   : DIO_LevelType      DIO_Level_HIGH
*                                       DIO_Level_LOW
*******************************************************************************/
DIO_LevelType Dio_ReadChannel(DIO_ChannelType ChannelId){
    uint32 base, registerChecker;
    base = Dio_GetBase_Channel(ChannelId);
    REG_READ_CASTING_POINTED(registerChecker, base + (1 << (ChannelId%8) << 2));
    if(registerChecker > 0){
        return DIO_Level_HIGH;
    }else{
        return DIO_Level_LOW;
    }
}

/******************************************************************************
* \Syntax          : void Dio_WriteChannel(DIO_ChannelType ChannelId, DIO_LevelType Level)
* \Description     : It Writes Digital value on a specific pin on the Board
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : ChannelId          The pin Number in the board
*                    Level              The Digital Level we want as an output
* \Parameters (out): None
* \Return value:   : None
* *******************************************************************************/
void Dio_WriteChannel(DIO_ChannelType ChannelId, DIO_LevelType Level){
    uint32 base;
    base = Dio_GetBase_Channel(ChannelId);
    if(Level == DIO_Level_HIGH){
        REG_ORING_CASTING_POINTED(base + (1 << (ChannelId%8) << 2), 0xff);
    }else{
        REG_CLEAR_CASTING_POINTED(base + (1 << (ChannelId%8) << 2));
    }
}

/******************************************************************************
* \Syntax          : DIO_PortLevelType Dio_ReadPort(DIO_PortType PortId)
* \Description     : The Function Reads the output on a whole Port on the Board
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : PortId             The Port Number in the board
* \Parameters (out): None
* \Return value:   : DIO_PortLevelType  The High and Low pins on the Port
*******************************************************************************/
DIO_PortLevelType Dio_ReadPort(DIO_PortType PortId){
    DIO_PortLevelType myLevel;
    uint32 base;
    base = Dio_GetBase_Port(PortId);
    REG_READ_CASTING_POINTED(myLevel, base + PORT_DATA_REG_OFFSET);
    return myLevel;
}

/******************************************************************************
* \Syntax          : void Dio_WritePort(DIO_PortType PortId, DIO_PortLevelType Level)
* \Description     : It Writes Digital value on a specific port on the Board
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : PortId             The Port Number in the board
*                    Level              The Digital Level we want as an output
* \Parameters (out): None
* \Return value:   : None
* *******************************************************************************/
void Dio_WritePort(DIO_PortType PortId, DIO_PortLevelType Level){
    uint32 base;
    base = Dio_GetBase_Port(PortId);
    REG_WRITE_CASTING_POINTED(base + PORT_DATA_REG_OFFSET, PortId);
}

/******************************************************************************
* \Syntax          : DIO_LevelType Dio_FlipChannel(DIO_ChannelType ChannelId)
* \Description     : The Function Flip a specific pin output
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : ChannelId          The Pin Number in the board
* \Parameters (out): None
* \Return value:   : DIO_LevelType      The output level on the Pin
*******************************************************************************/
DIO_LevelType Dio_FlipChannel(DIO_ChannelType ChannelId){
    uint32 base, registerChecker;
    base = Dio_GetBase_Channel(ChannelId);
    REG_READ_CASTING_POINTED(registerChecker, base + (1 << (ChannelId%8) << 2));

    if(registerChecker > 0){
        REG_CLEAR_CASTING_POINTED(base + (1 << (ChannelId%8) << 2));
        return DIO_Level_LOW;
    }else{
        REG_ORING_CASTING_POINTED(base + (1 << (ChannelId%8) << 2), 0xff);
        return DIO_Level_HIGH;
    }
}

void Dio_Init_ISR(DIO_ChannelType ChannelId, DIO_ChannelISR_Type ISR_Event){
    uint32 registerChecker, base;
    if(ISR_Event == DIO_ChannelISR_NotUsed){
        return ;
    }
    if( DIO_handlerFunctionQueue[ChannelId / 8] == Null_Ptr){
        DIO_handlerFunctionQueue[ChannelId / 8] = FunctionQueue_Create();
    }
    base = Dio_GetBase_Channel(ChannelId);
    REG_READ_CASTING_POINTED(registerChecker, base + PORT_DIR_REG_OFFSET);
    registerChecker = registerChecker & (1 << (ChannelId % 8));
    if(registerChecker > 0){
        /* the channel is fucking output !!! */
        return;
    }else{
        /* the channel is input, you good to go */
        REG_ORING_ONE_BIT_CASTING_POINTED(base + PORT_IM_REG_OFFSET, ChannelId % 8);
        if(ISR_Event < 3){
            /* it's Edge Sensitive */
            REG_CLEAR_ONE_BIT_CASTING_POINTED(base + PORT_IS_REG_OFFSET, ChannelId % 8);
            if(ISR_Event == DIO_ChannelISR_edges_both){
                REG_ORING_ONE_BIT_CASTING_POINTED(base + PORT_IBE_REG_OFFSET, ChannelId % 8);
            }else if(ISR_Event == DIO_ChannelISR_edges_falling){
                REG_CLEAR_ONE_BIT_CASTING_POINTED(base + PORT_IBE_REG_OFFSET, ChannelId % 8);
                REG_CLEAR_ONE_BIT_CASTING_POINTED(base + PORT_IEV_REG_OFFSET, ChannelId % 8);
            }else{
                REG_CLEAR_ONE_BIT_CASTING_POINTED(base + PORT_IBE_REG_OFFSET, ChannelId % 8);
                REG_ORING_ONE_BIT_CASTING_POINTED(base + PORT_IEV_REG_OFFSET, ChannelId % 8);
            }
        }else{
            /* It's Level Sensitive */
            REG_ORING_ONE_BIT_CASTING_POINTED(base + PORT_IS_REG_OFFSET, ChannelId % 8);
            if(ISR_Event == DIO_ChannelISR_level_high){
                REG_ORING_ONE_BIT_CASTING_POINTED(base + PORT_IEV_REG_OFFSET, ChannelId % 8);
            }else{
                REG_CLEAR_ONE_BIT_CASTING_POINTED(base + PORT_IEV_REG_OFFSET, ChannelId % 8);
            }
        }
    }
}

uint8 Dio_Check_Isr(DIO_ChannelType ChannelId){
    uint32 registerChecker, base;
    base = Dio_GetBase_Channel(ChannelId);
    REG_READ_CASTING_POINTED(registerChecker, base + PORT_MIS_REG_OFFSETS);
    if(registerChecker & (1 << (ChannelId%8))){
        return 1;
    }else{
        return 0;
    }
}

Std_ReturnType Dio_Remove_Isr(DIO_ChannelType ChannelId){
    uint32 base;
    base = Dio_GetBase_Channel(ChannelId);
    REG_ORING_ONE_BIT_CASTING_POINTED(base + PORT_ICR_REG_OFFSET, ChannelId%8);
    return E_OK;
}

DIO_ChannelType Dio_GetChannelId(uint8 Dio_cfg_Array_ID){
    if(Dio_cfg_Array_ID < DIO_INPUT_CONFIGURED_NUMBER){
        return DIO_Input_Container[Dio_cfg_Array_ID].DIO_ch;
    }else{
        return DIO_Channel_NotUsed;
    }
}

void Dio_Remove_CallBackFun(DIO_ChannelType ChannelId, void (*DioCallBackFun)(void)){
    FunctionQueue_RemoveFunction(DIO_handlerFunctionQueue[ChannelId / 8], DioCallBackFun);
}

void Dio_Set_CallBackFun(DIO_ChannelType ChannelId, void (*DioCallBackFun)(void)){
    FunctionQueue_AddFunction(DIO_handlerFunctionQueue[ChannelId / 8], DioCallBackFun);
}

void __attribute__((weak)) DIO_A_handler(void){
    FunctionQueue_Calling(DIO_handlerFunctionQueue[0]);
}

void __attribute__((weak)) DIO_B_handler(void){
    FunctionQueue_Calling(DIO_handlerFunctionQueue[1]);
}

void __attribute__((weak)) DIO_C_handler(void){
    FunctionQueue_Calling(DIO_handlerFunctionQueue[2]);
}

void __attribute__((weak)) DIO_D_handler(void){
    FunctionQueue_Calling(DIO_handlerFunctionQueue[3]);
}

void __attribute__((weak)) DIO_E_handler(void){
    FunctionQueue_Calling(DIO_handlerFunctionQueue[4]);
}

void __attribute__((weak)) DIO_F_handler(void){
    FunctionQueue_Calling(DIO_handlerFunctionQueue[5]);
}
/**********************************************************************************************************************
 *  END OF FILE: DIO.c
 *********************************************************************************************************************/



