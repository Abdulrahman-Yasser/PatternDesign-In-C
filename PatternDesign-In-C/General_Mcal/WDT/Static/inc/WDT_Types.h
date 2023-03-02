#ifndef WDT_TYPES_H
#define WDT_TYPES_H

#include "../../General_Common/Std_Types.h"



typedef enum{
    WDT_Interrupt_NMI, WDT_Interrupt_Standard
}WDT_InterruptType;

typedef uint32 WDT_InitialTimeoutType;

typedef uint32 WDT_MaxTimeoutType;

typedef struct{
    void (*PtrToFun_Notification_CallBack)(void);
    WDT_InterruptType WDT_Interrupt;
    WDT_InitialTimeoutType WDT_InitialTimeOut;
    WDT_MaxTimeoutType WDT_MaxTimeOut;
}WDT_ConfigType;

#endif
