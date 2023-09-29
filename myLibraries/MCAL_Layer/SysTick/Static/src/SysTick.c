/**********************************************************************************************************************
  *  FILE DESCRIPTION
  *  -----------------------------------------------------------------------------------------------------------------*/
 /**        \file  FileName.c
  *        \brief  
  *
  *      \details  
  *
  *
  *********************************************************************************************************************/

 /**********************************************************************************************************************
  *  INCLUDES
  *********************************************************************************************************************/
#include "../../Static/inc/SysTick_Types.h"

#include "../../Static/inc/SysTick.h"

#include "Mcu_Hw.h"

#include "CPU_resources.h"
 /**********************************************************************************************************************
 *  LOCAL MACROS CONSTANT\FUNCTION
 *********************************************************************************************************************/
static void (*SysTick_CallBack_PtrToFunc)(void) = ((void*) 0);


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : void SysTick_Init(SysTick_Config *ConfigPtr)
* \Description     : The function initialize the system tick timer
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : ConfigPtr   A container for the system tick
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
void SysTick_Init(void){
    SYSTICK_RELOAD_REG = My_SysTick.ReLoad;
    if(My_SysTick.Interrupt == SysTick_Interrupt_Enable){
        SYSTICK_CTRL_REG |= 1 << 1;
    }else{
        SYSTICK_CTRL_REG &= ~(1 << 1);
    }
    if(My_SysTick.Clock ==SysTick_ClkSrc_SysClk){
        SYSTICK_CTRL_REG |= 1 << 2;
    }else{
        SYSTICK_CTRL_REG &= ~(1 << 2);
    }
}


/******************************************************************************
* \Syntax          : void SysTick_Start(void)
* \Description     : The function Start the system tick timer
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
void SysTick_Start(void){
    SYSTICK_CTRL_REG |= 1 << 0;
}

/******************************************************************************
* \Syntax          : void SysTick_Stop(void)
* \Description     : The function Stop the system tick timer
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
void SysTick_Stop(void){
    SYSTICK_CTRL_REG &= ~(1 << 0);
}

/******************************************************************************
* \Syntax          : void SysTick_Reload(void)
* \Description     : The function reload the system tick timer
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : SysTick_ReLoadType     is a uint32 that contain the reload value
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
void SysTick_Reload_ms(SysTick_ReLoadType ReLoad){
    volatile uint32 i;
    i = SYSTICK_CTRL_REG;
    SYSTICK_CTRL_REG = 0;
    SYSTICK_RELOAD_REG = (ReLoad * 1000) - 1;
    SYSTICK_CTRL_REG = i;
}

/******************************************************************************
* \Syntax          : void SysTick_SetCallBack(void (*PointerToFunction) (void))
* \Description     : The function loads the user function from a high layer into the MCAL_Layer layer
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : (*PointerToFunction)(void)    a pointer to the user function
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
void SysTick_SetCallBack(void (*PointerToFunction) (void)){
    SysTick_CallBack_PtrToFunc = PointerToFunction;
}

/******************************************************************************
* \Syntax          : void SysTick_Handler(void)
* \Description     : The ISR function
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
extern void SysTick_Handler(void)
{
    if(SysTick_CallBack_PtrToFunc != ((void*)0) )
    {
        (*SysTick_CallBack_PtrToFunc)();
    }
}
