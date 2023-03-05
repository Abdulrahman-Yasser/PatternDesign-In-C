
#include "../../General_Common/Mcu_Hw.h"

#include "../inc/WDT.h"
#include "../inc/WDT_Types.h"

#include "../../Dynamic/inc/WDT_Cfg.h"



void WDT_Init(const WDT_ConfigType *ConfigPtr){

    if(ConfigPtr->PtrToFun_Notification_CallBack != '\0'){

    }
    if(ConfigPtr->WDT_Interrupt == WDT_Interrupt_Standard){
        WDT1_CTL_REG &= ~(1 << INTTYPE_BIT);
    }else{
        WDT1_CTL_REG |= (1 << INTTYPE_BIT);
    }
    WDT0_LOAD_REG = ConfigPtr->WDT_InitialTimeOut;

}

void WDT_SetTriggerCondition(uint16 timeout){
    WDT0_LOAD_REG = timeout;
}

//SET_BIT(*(volatile uint32 *)((volatile uint8 *)port + PORT_DIR_REG_OFFSET) , pin);
