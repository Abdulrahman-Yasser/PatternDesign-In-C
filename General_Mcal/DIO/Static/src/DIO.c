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


#include "../../General_Common/Mcu_Hw.h"

#include "../inc/DIO.h"


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


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
    uint32 temp;
    switch(ChannelId / 8){
    case 0:
        temp = *(volatile uint32*)((uint8*)GPIO_PORTA_DATA_ADDRESS + ( (1 << ChannelId%8) << 2));
        break;
    case 1:
        temp = *(volatile uint32*)((uint8*)GPIO_PORTB_DATA_ADDRESS + ( (1 << ChannelId%8) << 2));
        break;
    case 2:
        temp = *(volatile uint32*)((uint8*)GPIO_PORTC_DATA_ADDRESS + ( (1 << ChannelId%8) << 2));
        break;
    case 3:
        temp = *(volatile uint32*)((uint8*)GPIO_PORTD_DATA_ADDRESS + ( (1 << ChannelId%8) << 2));
        break;
    case 4:
        temp = *(volatile uint32*)((uint8*)GPIO_PORTE_DATA_ADDRESS + ( (1 << ChannelId%8) << 2));
        break;
    case 5:
        temp = *(volatile uint32*)((uint8*)GPIO_PORTF_DATA_ADDRESS + ( (1 << ChannelId%8) << 2));
        break;
    default:
        break;
    }
    if(temp > 0){
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
    if(Level == DIO_Level_HIGH){
        switch(ChannelId / 8){
        case 0:
            *(volatile uint32*)((uint8*)GPIO_PORTA_DATA_ADDRESS + ( (1 << ChannelId%8) << 2)) |= 0XFF;
            break;
        case 1:
            *(volatile uint32*)((uint8*)GPIO_PORTB_DATA_ADDRESS + ( (1 << ChannelId%8) << 2)) |= 0XFF;
            break;
        case 2:
            *(volatile uint32*)((uint8*)GPIO_PORTC_DATA_ADDRESS + ( (1 << ChannelId%8) << 2)) |= 0XFF;
            break;
        case 3:
            *(volatile uint32*)((uint8*)GPIO_PORTD_DATA_ADDRESS + ( (1 << ChannelId%8) << 2)) |= 0XFF;
            break;
        case 4:
            *(volatile uint32*)((uint8*)GPIO_PORTE_DATA_ADDRESS + ( (1 << ChannelId%8) << 2)) |= 0XFF;
            break;
        case 5:
            *(volatile uint32*)((uint8*)GPIO_PORTF_DATA_ADDRESS + ( (1 << (ChannelId%8)) << 2)) |= 0XFF;
            break;
        default:
            break;
        }
    }else{
        switch(ChannelId / 8){
        case 0:
            *(volatile uint32*)((uint8*)GPIO_PORTA_DATA_ADDRESS + ( (1 << ChannelId%8) << 2)) &= ~(0XFF);
            break;
        case 1:
            *(volatile uint32*)((uint8*)GPIO_PORTB_DATA_ADDRESS + ( (1 << ChannelId%8) << 2)) &= ~(0XFF);
            break;
        case 2:
            *(volatile uint32*)((uint8*)GPIO_PORTC_DATA_ADDRESS + ( (1 << ChannelId%8) << 2)) &= ~(0XFF);
            break;
        case 3:
            *(volatile uint32*)((uint8*)GPIO_PORTD_DATA_ADDRESS + ( (1 << ChannelId%8) << 2)) &= ~(0XFF);
            break;
        case 4:
            *(volatile uint32*)((uint8*)GPIO_PORTE_DATA_ADDRESS + ( (1 << ChannelId%8) << 2)) &= ~(0XFF);
            break;
        case 5:
            *(volatile uint32*)((uint8*)GPIO_PORTF_DATA_ADDRESS + ( (1 << ChannelId%8) << 2)) &= ~(0XFF);
            break;
        default:
            break;
        }
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
    switch(PortId){
    case DIO_PORTA:
        myLevel = GPIO_PORTA_DATA_REG;
        break;
    case DIO_PORTB:
        myLevel = GPIO_PORTB_DATA_REG;
        break;
    case DIO_PORTC:
        myLevel = GPIO_PORTC_DATA_REG;
        break;
    case DIO_PORTD:
        myLevel = GPIO_PORTD_DATA_REG;
        break;
    case DIO_PORTE:
        myLevel = GPIO_PORTE_DATA_REG & 0b111111;
        break;
    case DIO_PORTF:
        myLevel = GPIO_PORTF_DATA_REG & 0b11111;
        break;
    }
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
    switch(PortId / 8){
    case 0:
        GPIO_PORTA_DATA_REG = Level;
        break;
    case 1:
        GPIO_PORTB_DATA_REG = Level;
        break;
    case 2:
        GPIO_PORTC_DATA_REG = Level;
        break;
    case 3:
        GPIO_PORTD_DATA_REG = Level;
        break;
    case 4:
        GPIO_PORTE_DATA_REG = Level;
        break;
    case 5:
        GPIO_PORTF_DATA_REG = Level;
        break;
    default:
        break;
    }
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
    uint8 myLevel;
    switch(ChannelId / 8){
    case 0:
        *(volatile uint32*)((uint8*)GPIO_PORTA_DATA_ADDRESS + ( (1 << ChannelId%8) << 2)) ^= 0XFF;
        myLevel = *(volatile uint32*)((uint8*)GPIO_PORTA_DATA_ADDRESS + ( (1 << ChannelId%8) << 2));
        break;
    case 1:
        *(volatile uint32*)((uint8*)GPIO_PORTB_DATA_ADDRESS + ( (1 << ChannelId%8) << 2)) ^= 0XFF;
        myLevel = *(volatile uint32*)((uint8*)GPIO_PORTB_DATA_ADDRESS + ( (1 << ChannelId%8) << 2));
        break;
    case 2:
        *(volatile uint32*)((uint8*)GPIO_PORTC_DATA_ADDRESS + ( (1 << ChannelId%8) << 2)) ^= 0XFF;
        myLevel = *(volatile uint32*)((uint8*)GPIO_PORTC_DATA_ADDRESS + ( (1 << ChannelId%8) << 2));
        break;
    case 3:
        *(volatile uint32*)((uint8*)GPIO_PORTD_DATA_ADDRESS + ( (1 << ChannelId%8) << 2)) ^= 0XFF;
        myLevel = *(volatile uint32*)((uint8*)GPIO_PORTD_DATA_ADDRESS + ( (1 << ChannelId%8) << 2));
        break;
    case 4:
        *(volatile uint32*)((uint8*)GPIO_PORTE_DATA_ADDRESS + ( (1 << ChannelId%8) << 2)) ^= 0XFF;
        myLevel = *(volatile uint32*)((uint8*)GPIO_PORTE_DATA_ADDRESS + ( (1 << ChannelId%8) << 2));
        break;
    case 5:
        *(volatile uint32*)((uint8*)GPIO_PORTF_DATA_ADDRESS + ( (1 << ChannelId%8) << 2)) ^= 0XFF;
        myLevel = *(volatile uint32*)((uint8*)GPIO_PORTF_DATA_ADDRESS + ( (1 << ChannelId%8) << 2));
        break;
    default:
        break;
    }
    if(myLevel > 0){
        return DIO_Level_HIGH;
    }else{
        return DIO_Level_LOW;
    }
}

/**********************************************************************************************************************
 *  END OF FILE: DIO.c
 *********************************************************************************************************************/



