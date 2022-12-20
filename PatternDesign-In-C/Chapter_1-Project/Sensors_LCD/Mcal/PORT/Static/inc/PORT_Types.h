#ifndef PORT_TYPES_H
#define PORT_TYPES_H

#include "../../../../Common/Std_Types.h"

typedef enum{
    Port_Pin_A0, Port_Pin_A1, Port_Pin_A2, Port_Pin_A3, Port_Pin_A4, Port_Pin_A5, Port_Pin_A6, Port_Pin_A7,
    Port_Pin_B0, Port_Pin_B1, Port_Pin_B2, Port_Pin_B3, Port_Pin_B4, Port_Pin_B5, Port_Pin_B6, Port_Pin_B7,
    Port_Pin_C0, Port_Pin_C1, Port_Pin_C2, Port_Pin_C3, Port_Pin_C4, Port_Pin_C5, Port_Pin_C6, Port_Pin_C7,
    Port_Pin_D0, Port_Pin_D1, Port_Pin_D2, Port_Pin_D3, Port_Pin_D4, Port_Pin_D5, Port_Pin_D6, Port_Pin_D7,
    Port_Pin_E0, Port_Pin_E1, Port_Pin_E2, Port_Pin_E3, Port_Pin_E4, Port_Pin_E5,
    Port_Pin_F0=40, Port_Pin_F1, Port_Pin_F2, Port_Pin_F3, Port_Pin_F4
}Port_PinType;

typedef enum {
    Port_PinDir_IN, Port_PinDir_OUT
}Port_PinDirection;

typedef enum {
    Port_PinMode_DIO, Port_PinMode_ADC, Port_PinMode_UARTn, Port_PinMode_SSIn, Port_PinMode_SSI3, Port_PinMode_I2Cn, Port_PinMode_M0PWMn,
    Port_PinMode_M1PWMn, Port_PinMode_IDXn_Phpn, Port_PinMode_TnCCPn_WTnCCPn, Port_PinMode_CANn, Port_PinMode_CAN0_Pin_F, Port_PinMode_USBn, Port_PinMode_NMI,
    Port_PinMode_ANALOG_COMPARATOR, Port_PinMode_TRD, Port_PinMode_USB0_DM_DP, Port_PinMode_UART1_RTS_CTS, Port_PinMode_NONE
}Port_PinModeType;

typedef enum{
    Port_PinInternal_PullUp, Port_PinInternal_PullDown, Port_PinInternal_OpenDrain
}Port_PinInternalAttatchType;

typedef enum{
    Port_PinOutputCurrent_2ma, Port_PinOutputCurrent_4ma, Port_PinOutputCurrent_8ma
}Port_PinOutputCurrentType;

typedef enum{
    Port_PinLevel_LOW, Port_PinLevel_HIGH
}Port_PinLevelValueType;

typedef struct{
    Port_PinType PinNum;
    Port_PinLevelValueType PinInitialLevel;
    Port_PinDirection PinInitialDirection;
    Port_PinModeType PinMode;
    Port_PinInternalAttatchType PinInternalAttach;
    Port_PinOutputCurrentType PinCurrent;
}Port_ConfigType;



#endif
