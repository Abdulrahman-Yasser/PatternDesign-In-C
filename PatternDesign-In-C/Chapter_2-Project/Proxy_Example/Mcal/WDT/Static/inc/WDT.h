#ifndef WDT_H
#define WDT_H

#include "WDT_Types.h"
#include "../../Dynamic/inc/WDT_Cfg.h"

#define INTTYPE_BIT  2

void WDT_Init(const WDT_ConfigType *ConfigPtr);

void WDT_SetTriggerCondition(uint16 timeout);

#endif
