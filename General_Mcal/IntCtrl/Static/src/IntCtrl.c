/**********************************************************************************************************************
 *  FILE DESCRIPTION
  *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file    IntCtrl.c
  *        \brief   Nested Vector Interrupt Controller Driver
  *
  *      \details   The File Contains all the NVIC driver's functions implementation
  *
  *
  *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "../../General_Common/Std_Types.h"


#include "../../General_Common/Mcu_Hw.h"

#include "../inc/IntCtrl.h"


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : void IntCtrl_Init(const IntCtrl_Container_t* IntCtrl_config_var)
* \Description     : Initialize all the used Interrupts that configured by the User
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : IntCtrl_config_var   Variable contains all the configured interrupts by the user
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
void IntCtrl_Init(void)
 {
    uint32 t1, t3;
    volatile uint32* t2;
    uint8 i;
    NVIC_APINT = IntCtrl_Prio_Group_System_Lock_reg | (Initialized_Interrupt_Container.Prio_Group_System << 8);
    for (i = 0; i  < IntCtrl_Interrupt_count_cfg; i++){
        if(Initialized_Interrupt_Container.container_ptr[i].int_state == IntCtrl_Disable){
            continue;
        }
        if(Initialized_Interrupt_Container.container_ptr[i].int_num >= 16){
            switch (((Initialized_Interrupt_Container.container_ptr[i].int_num)-16)/(32))
            {
            case 0:
                REG_WRITE_BIT(NVIC_EN0, ((Initialized_Interrupt_Container.container_ptr[i].int_num - 16) ));
                break;
            case 1:
                REG_WRITE_BIT(NVIC_EN1, ((Initialized_Interrupt_Container.container_ptr[i].int_num - 16) % (32*1)));
                break;
            case 2:
                REG_WRITE_BIT(NVIC_EN2, ((Initialized_Interrupt_Container.container_ptr[i].int_num - 16) % (32*2)));
                break;
            case 3:
                REG_WRITE_BIT(NVIC_EN3, ((Initialized_Interrupt_Container.container_ptr[i].int_num - 16) % (32*3)));
                break;
            case 4:
                REG_WRITE_BIT(NVIC_EN4, ((Initialized_Interrupt_Container.container_ptr[i].int_num - 16) % (32*4)));
                break;
            default:
                break;
            }
            t1 = (((Initialized_Interrupt_Container.container_ptr[i].int_num)-16)/4);
            t2 = ((volatile uint32*)NVIC_PRI0_ADDRESS + t1) ;
            t3 = (Initialized_Interrupt_Container.container_ptr[i].int_priority << ((((Initialized_Interrupt_Container.container_ptr[i].int_num-16)%4)*8)+5));
            (*(volatile uint32 *)t2) |= t3;
        }else if(Initialized_Interrupt_Container.container_ptr[i].int_num < 7){
            if(Initialized_Interrupt_Container.container_ptr[i].int_num == Memory_Management){
                REG_WRITE_BIT(NVIC_SYSHNDCTRL, 16);
                REG_WRITE_32_BIT(NVIC_SYSPRI1, (Initialized_Interrupt_Container.container_ptr[i].int_priority << 5));
            }else if(Initialized_Interrupt_Container.container_ptr[i].int_num == Bus_Fault){
                REG_WRITE_BIT(NVIC_SYSHNDCTRL, 17);
                REG_WRITE_32_BIT(NVIC_SYSPRI1, (Initialized_Interrupt_Container.container_ptr[i].int_priority << 13));
            }else if(Initialized_Interrupt_Container.container_ptr[i].int_num == Usage_Fault){
                REG_WRITE_BIT(NVIC_SYSHNDCTRL, 18);
                REG_WRITE_32_BIT(NVIC_SYSPRI1, (Initialized_Interrupt_Container.container_ptr[i].int_priority << 21));
            }
        }else if(Initialized_Interrupt_Container.container_ptr[i].int_num < 16){
            if(Initialized_Interrupt_Container.container_ptr[i].int_num == SVCall){
                REG_WRITE_32_BIT(NVIC_SYSPRI2, (Initialized_Interrupt_Container.container_ptr[i].int_priority << 29));
            }else if(Initialized_Interrupt_Container.container_ptr[i].int_num == Debug_Monitor){
                REG_WRITE_32_BIT(NVIC_SYSPRI3, (Initialized_Interrupt_Container.container_ptr[i].int_priority << 5));
            }else if(Initialized_Interrupt_Container.container_ptr[i].int_num == PendSV){
                REG_WRITE_32_BIT(NVIC_SYSPRI3, (Initialized_Interrupt_Container.container_ptr[i].int_priority << 21));
            }else if(Initialized_Interrupt_Container.container_ptr[i].int_num == SysTick){
                REG_WRITE_32_BIT(NVIC_SYSPRI3, (Initialized_Interrupt_Container.container_ptr[i].int_priority << 29));
                REG_WRITE_BIT(NVIC_STCTRL, 1);
                REG_WRITE_BIT(NVIC_STCTRL, 0);
            }
        }
    }
 }
void IntCtrl_DisableInterrupt(IntCtrl_InterruptType_t InterruptID){
    if(InterruptID >= 16){
        switch (((InterruptID)-16)/(32))
        {
        case 0:
            REG_CLEAR_BIT(NVIC_EN0, ( (InterruptID - 16) ));
            break;
        case 1:
            REG_CLEAR_BIT(NVIC_EN1, ( (InterruptID - 16) % (32*1)));
            break;
        case 2:
            REG_CLEAR_BIT(NVIC_EN2, ( (InterruptID - 16) % (32*2)));
            break;
        case 3:
            REG_CLEAR_BIT(NVIC_EN3, ( (InterruptID - 16) % (32*3)));
            break;
        case 4:
            REG_CLEAR_BIT(NVIC_EN4, ( (InterruptID - 16) % (32*4)));
            break;
        default:
            break;
        }
    }else if(InterruptID < 7){
        if(InterruptID == Memory_Management){
            REG_CLEAR_BIT(NVIC_SYSHNDCTRL, 16);
        }else if(InterruptID == Bus_Fault){
            REG_CLEAR_BIT(NVIC_SYSHNDCTRL, 17);
        }else if(InterruptID == Usage_Fault){
            REG_CLEAR_BIT(NVIC_SYSHNDCTRL, 18);
        }
    }else if(InterruptID == SysTick){
        REG_CLEAR_BIT(NVIC_STCTRL, 1);
        REG_CLEAR_BIT(NVIC_STCTRL, 0);
    }
}

void IntCtrl_Enable_Interrupt(IntCtrl_InterruptType_t InterruptID){
    if(InterruptID >= 16){
        switch (((InterruptID)-16)/(32))
        {
        case 0:
            REG_WRITE_BIT(NVIC_EN0, ( (InterruptID - 16) ));
            break;
        case 1:
            REG_WRITE_BIT(NVIC_EN1, ( (InterruptID - 16) % (32*1)));
            break;
        case 2:
            REG_WRITE_BIT(NVIC_EN2, ( (InterruptID - 16) % (32*2)));
            break;
        case 3:
            REG_WRITE_BIT(NVIC_EN3, ( (InterruptID - 16) % (32*3)));
            break;
        case 4:
            REG_WRITE_BIT(NVIC_EN4, ( (InterruptID - 16) % (32*4)));
            break;
        default:
            break;
        }
    }else if(InterruptID < 7){
        if(InterruptID == Memory_Management){
            REG_WRITE_BIT(NVIC_SYSHNDCTRL, 16);
        }else if(InterruptID == Bus_Fault){
            REG_WRITE_BIT(NVIC_SYSHNDCTRL, 17);
        }else if(InterruptID == Usage_Fault){
            REG_WRITE_BIT(NVIC_SYSHNDCTRL, 18);
        }
    }else if(InterruptID == SysTick){
        REG_WRITE_BIT(NVIC_STCTRL, 1);
        REG_WRITE_BIT(NVIC_STCTRL, 0);
    }
}

void IntCtrl_ChangePriority(IntCtrl_InterruptType_t InterruptID, IntCtrl_Prio_t Interrupt_Priority){
    uint32 t1, t3;
    volatile uint32* t2;
    if(InterruptID >= 16){
        t1 = (((InterruptID)-16)/4);
        t2 = ((volatile uint32*)NVIC_PRI0 + t1) ;
        t3 = (Interrupt_Priority << ((((InterruptID-16)%4)*8)+5));
        (*(volatile uint32 *)t2) |= t3;
    }else if(InterruptID < 7){
        if(InterruptID == Memory_Management){
            NVIC_SYSPRI1 |= Interrupt_Priority << 5;
        }else if(InterruptID == Bus_Fault){
            NVIC_SYSPRI1 |= Interrupt_Priority << 13;
        }else if(InterruptID == Usage_Fault){
            NVIC_SYSPRI1 |= Interrupt_Priority << 21;
        }
    }else if(InterruptID < 16){
        if(InterruptID == SVCall){
            NVIC_SYSPRI2 |= Interrupt_Priority << 29;
        }else if(InterruptID == Debug_Monitor){
            NVIC_SYSPRI3 |= Interrupt_Priority << 5;
        }else if(InterruptID == PendSV){
            NVIC_SYSPRI3 |= Interrupt_Priority << 21;
        }else if(InterruptID == SysTick){
            NVIC_SYSPRI3 |= Interrupt_Priority << 29;
        }
    }
}

/**********************************************************************************************************************
 *  END OF FILE: IntCtrl.c
 *********************************************************************************************************************/

