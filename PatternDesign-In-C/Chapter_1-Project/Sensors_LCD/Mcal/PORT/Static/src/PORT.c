/**********************************************************************************************************************
  *  FILE DESCRIPTION
  *  -----------------------------------------------------------------------------------------------------------------*/
 /**        \file  PORT.c
  *        \brief   PORT driver
  *
  *      \details   This file initialize all the pins on the board
  *
  *
  *********************************************************************************************************************/


 /**********************************************************************************************************************
  *  INCLUDES
  *********************************************************************************************************************/
#include "../../../../Common/Std_Types.h"
#include "../../../../Common/Mcu_Hw.h"

#include "../../Dynamic/inc/PORT_Cfg.h"

#include "../inc/PORT.h"

 /**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/

 /**********************************************************************************************************************
  *  LOCAL DATA 
  *********************************************************************************************************************/

 /**********************************************************************************************************************
  *  GLOBAL DATA
  *********************************************************************************************************************/

 /**********************************************************************************************************************
  *  LOCAL FUNCTION PROTOTYPES
  *********************************************************************************************************************/
volatile uint32 *GetPortAddress(Port_PinType PortNum_Var);
void SetPinDirection(uint32* PortPtr_Var, uint8 PinNum_Var, Port_PinDirection Dir);
void SetInternalAttach(uint32* PortPtr_Var, uint8 PinNum_Var, Port_PinInternalAttatchType Attach);
void SetOutputCurrentValue(uint32* PortPtr_Var, uint8 PinNum_Var, Port_PinOutputCurrentType Current);
void SetPinInitialValue(uint32* PortPtr_Var, uint8 PinNum_Var, Port_PinLevelValueType Level);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
void SetPinInitialValue(uint32* PortPtr_Var, uint8 PinNum_Var, Port_PinLevelValueType Level){
    if(Level == Port_PinLevel_LOW){
        (*(volatile uint32*)((uint32)PortPtr_Var + PORT_DATA_REG_OFFSET)) &= ~(1 << PinNum_Var);
    }else{
        (*(volatile uint32*)((uint32)PortPtr_Var + PORT_DATA_REG_OFFSET)) |= (1 << PinNum_Var);
    }
}

void SetPinDirection(uint32* PortPtr_Var, uint8 PinNum_Var, Port_PinDirection Dir){
    /* Pin Direction */
    if(Dir == Port_PinDir_IN){
        (*(volatile uint32*)((uint32)PortPtr_Var + PORT_DIR_REG_OFFSET)) &= ~(1 << PinNum_Var);
    }else{
        (*(volatile uint32*)((uint32)PortPtr_Var + PORT_DIR_REG_OFFSET)) |= (1 << PinNum_Var);
    }
}

void SetInternalAttach(uint32* PortPtr_Var, uint8 PinNum_Var, Port_PinInternalAttatchType Attach){
    if(Attach == Port_PinInternal_PullUp){
        (*(volatile uint32*)((uint32)PortPtr_Var + PORT_PULL_UP_REG_OFFSET)) |= (1 << PinNum_Var);
    }else if(Attach == Port_PinInternal_PullDown){
        (*(volatile uint32*)((uint32)PortPtr_Var + PORT_PULL_DOWN_REG_OFFSET)) |= (1 << PinNum_Var);
    }else if(Attach == Port_PinInternal_OpenDrain){
        /* For OpenDrain the Direction register must be input */
        (*(volatile uint32*)((uint32)PortPtr_Var + PORT_DIR_REG_OFFSET)) &= ~(1 << PinNum_Var);
        (*(volatile uint32*)((uint32)PortPtr_Var + PORT_OPEN_DRAIN_REG_OFFSET)) |= 1 << PinNum_Var;
    }else{
        (*(volatile uint32*)((uint32)PortPtr_Var + PORT_DIR_REG_OFFSET)) &= ~(1 << PinNum_Var);
    }
}

void SetAlternativeFunction(uint32* PortPtr_Var, uint8 Pin, uint8 Value){
    REG_WRITE_BIT_PTR(((uint32)PortPtr_Var + PORT_COMMIT_REG_OFFSET), Pin);
    REG_WRITE_BIT_PTR(((uint32)PortPtr_Var + PORT_ALT_FUNC_REG_OFFSET), Pin);
    (*(volatile uint32*)((uint32)PortPtr_Var + PORT_CTL_REG_OFFSET)) &= ~(0xf << Pin*4);
    REG_WRITE_32_BIT_PTR(((uint32)PortPtr_Var + PORT_CTL_REG_OFFSET), (Value << Pin*4));
}

void SetOutputCurrentValue(uint32* PortPtr_Var, uint8 PinNum_Var, Port_PinOutputCurrentType Current){
    if(Current == Port_PinOutputCurrent_2ma){
        (*(volatile uint32*)((uint32)PortPtr_Var + PORT_2_MA_DRIVE_REG_OFFSET)) |= (1 << PinNum_Var);
    }else if(Current == Port_PinOutputCurrent_4ma){
        (*(volatile uint32*)((uint32)PortPtr_Var + PORT_4_MA_DRIVE_REG_OFFSET)) |= (1 << PinNum_Var);
    }else{
        (*(volatile uint32*)((uint32)PortPtr_Var + PORT_8_MA_DRIVE_REG_OFFSET)) |= (1 << PinNum_Var);
    }
}

volatile uint32 *GetPortAddress(Port_PinType PortNum_Var){
    volatile uint32* returnPtr = 0;
    switch(PortNum_Var/8){
    case 0:
        returnPtr = (uint32*)GPIO_PORTA_BASE_ADDRESS;
        break;
    case 1:
        returnPtr = (uint32*)GPIO_PORTB_BASE_ADDRESS;
        break;
    case 2:
        returnPtr = (uint32*)GPIO_PORTC_BASE_ADDRESS;
        break;
    case 3:
        returnPtr = (uint32*)GPIO_PORTD_BASE_ADDRESS;
        break;
    case 4:
        returnPtr = (uint32*)GPIO_PORTE_BASE_ADDRESS;
        break;
    case 5:
        returnPtr = (uint32*)GPIO_PORTF_BASE_ADDRESS;
        break;
    default:
        break;
    }
    return returnPtr;
}



/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : void Port_Init(const Port_ConfigType *ConfigPtr)
* \Description     : The Function initialize all the poins on the board
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : ConfigPtr      Container for all the pins configurations                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  None
*******************************************************************************/
void Port_Init(void){
    uint8 i, PinNum;
    volatile uint32* PortPtr;
    static uint8 ClockConfiguredPins = 0;
    for (i = 0; i < configured_pins; i++){
        /* If the PIN is not used */
        if(ConfigPtr[i].PinMode == Port_PinMode_NONE){
            continue;
        }

        /* Check if the ClockGate of the Port is Initialized */
        if( (ClockConfiguredPins & (1 << (ConfigPtr[i].PinNum / 8)) ) == 0){
            SYSCTL_REGCGC2_REG |= 1 <<  (ConfigPtr[i].PinNum / 8);
            ClockConfiguredPins |= 1 << (ConfigPtr[i].PinNum / 8);
        }

        /* Get the Port channel and the Pin Number */
        PortPtr = GetPortAddress(ConfigPtr[i].PinNum);
        PinNum = ConfigPtr[i].PinNum % 8;

        /* If the Pin is DIO Configurations */
        switch(ConfigPtr[i].PinMode){
        case Port_PinMode_DIO:
            SetPinDirection((uint32*)PortPtr, PinNum, ConfigPtr[i].PinInitialDirection);
            SetPinInitialValue((uint32*)PortPtr, PinNum, ConfigPtr[i].PinInitialLevel);
            SetInternalAttach((uint32*)PortPtr, PinNum, ConfigPtr[i].PinInternalAttach);
            SetOutputCurrentValue((uint32*)PortPtr, PinNum, ConfigPtr[i].PinCurrent);
            (*(volatile uint32*)((uint32)PortPtr + PORT_ALT_FUNC_REG_OFFSET)) &= ~(1 << PinNum);
            (*(volatile uint32*)((uint32)PortPtr + PORT_ANALOG_MODE_SEL_REG_OFFSET)) &= ~(1 << PinNum);
            (*(volatile uint32*)((uint32)PortPtr + PORT_ADC_CONTROL_REG_OFFSET)) &= ~(1 << PinNum);
            (*(volatile uint32*)((uint32)PortPtr + PORT_DIGITAL_ENABLE_REG_OFFSET)) |= 1 << PinNum;
            (*(volatile uint32*)((uint32)PortPtr + PORT_LOCK_REG_OFFSET)) = LOCK_VALUE;
            (*(volatile uint32*)((uint32)PortPtr + PORT_COMMIT_REG_OFFSET)) |= 1 << PinNum;
            break;
        case Port_PinMode_ADC:
            REG_CLEAR_BIT_PTR(((volatile uint8 *)PortPtr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PinNum);
            REG_CLEAR_BIT_PTR(((volatile uint8 *)PortPtr + PORT_ALT_FUNC_REG_OFFSET) , PinNum);
            *(volatile uint32 *)((volatile uint8 *)PortPtr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (PinNum * 4));
            break;
        case Port_PinMode_UARTn:
            REG_WRITE_BIT_PTR(((uint32)PortPtr + PORT_DIGITAL_ENABLE_REG_OFFSET), PinNum);
            SetAlternativeFunction((uint32*)PortPtr, PinNum, 1);
            break;
        case Port_PinMode_SSIn:
            REG_WRITE_BIT_PTR(((uint32)PortPtr + PORT_DIGITAL_ENABLE_REG_OFFSET), PinNum);
            SetAlternativeFunction((uint32*)PortPtr, PinNum, 2);
            break;
        case Port_PinMode_SSI3:
            REG_WRITE_BIT_PTR(((uint32)PortPtr + PORT_DIGITAL_ENABLE_REG_OFFSET), PinNum);
            SetAlternativeFunction((uint32*)PortPtr, PinNum, 1);
            break;
        case Port_PinMode_I2Cn:
            REG_WRITE_BIT_PTR(((uint32)PortPtr + PORT_DIGITAL_ENABLE_REG_OFFSET), PinNum);
            SetPinDirection((uint32*)PortPtr, PinNum, Port_PinDir_IN);
            /* SDA Supposed to be in OpenDrain Mode */
            SetInternalAttach((uint32*)PortPtr, PinNum, ConfigPtr[i].PinInternalAttach);
            SetAlternativeFunction((uint32*)PortPtr, PinNum, 3);
            break;
        case Port_PinMode_M0PWMn:
            SetAlternativeFunction((uint32*)PortPtr, PinNum, 4);
            REG_WRITE_BIT_PTR(((uint32)PortPtr + PORT_DIGITAL_ENABLE_REG_OFFSET), PinNum);
            break;
        case Port_PinMode_M1PWMn:
            SetAlternativeFunction((uint32*)PortPtr, PinNum, 5);
            REG_WRITE_BIT_PTR(((uint32)PortPtr + PORT_DIGITAL_ENABLE_REG_OFFSET), PinNum);
            break;
        case Port_PinMode_IDXn_Phpn:
            REG_WRITE_BIT_PTR(((uint32)PortPtr + PORT_DIGITAL_ENABLE_REG_OFFSET), PinNum);
            SetAlternativeFunction((uint32*)PortPtr, PinNum, 6);
            break;
        case Port_PinMode_TnCCPn_WTnCCPn:
            REG_WRITE_BIT_PTR(((uint32)PortPtr + PORT_DIGITAL_ENABLE_REG_OFFSET), PinNum);
            SetAlternativeFunction((uint32*)PortPtr, PinNum, 7);
            break;
        case Port_PinMode_CANn:
            REG_WRITE_BIT_PTR(((uint32)PortPtr + PORT_DIGITAL_ENABLE_REG_OFFSET), PinNum);
            SetAlternativeFunction((uint32*)PortPtr, PinNum, 8);
            break;
        case Port_PinMode_CAN0_Pin_F:
            REG_WRITE_BIT_PTR(((uint32)PortPtr + PORT_DIGITAL_ENABLE_REG_OFFSET), PinNum);
            SetAlternativeFunction((uint32*)PortPtr, PinNum, 3);
            break;
        case Port_PinMode_USBn:
            REG_WRITE_BIT_PTR(((uint32)PortPtr + PORT_DIGITAL_ENABLE_REG_OFFSET), PinNum);
            SetAlternativeFunction((uint32*)PortPtr, PinNum, 8);
            break;
        case Port_PinMode_NMI:
            REG_WRITE_BIT_PTR(((uint32)PortPtr + PORT_DIGITAL_ENABLE_REG_OFFSET), PinNum);
            SetAlternativeFunction((uint32*)PortPtr, PinNum, 8);
            break;
        case Port_PinMode_ANALOG_COMPARATOR:
            REG_CLEAR_BIT_PTR(((volatile uint8 *)PortPtr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PinNum);
            REG_CLEAR_BIT_PTR(((volatile uint8 *)PortPtr + PORT_ALT_FUNC_REG_OFFSET) , PinNum);
            *(volatile uint32 *)((volatile uint8 *)PortPtr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (PinNum * 4));
            break;
        case Port_PinMode_TRD:
            SetAlternativeFunction((uint32*)PortPtr, PinNum, 14);
            break;
        case Port_PinMode_USB0_DM_DP:
            REG_CLEAR_BIT_PTR(((volatile uint8 *)PortPtr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PinNum);
            REG_CLEAR_BIT_PTR(((volatile uint8 *)PortPtr + PORT_ALT_FUNC_REG_OFFSET) , PinNum);
            *(volatile uint32 *)((volatile uint8 *)PortPtr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (PinNum * 4));
            break;
        case Port_PinMode_UART1_RTS_CTS:
            REG_WRITE_BIT_PTR(((uint32)PortPtr + PORT_DIGITAL_ENABLE_REG_OFFSET), PinNum);
            SetAlternativeFunction((uint32*)PortPtr, PinNum, 8);
            break;
        default:
            break;
        }
    }
}
