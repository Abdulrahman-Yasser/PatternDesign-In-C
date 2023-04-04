 #ifndef MCU_HW_H
 #define MCU_HW_H

/*****************************************************************************
Nasted Vector Interrupt Controller (NVIC)
*****************************************************************************/
#define       NVIC_STCTRL                             (*((volatile uint32 *)0xE000E010))
#define       NVIC_BASE                               (*((volatile uint32 *)0xE000E000))
#define       NVIC_EN0                                (*((volatile uint32 *)0xE000E100))
#define       NVIC_EN1                                (*((volatile uint32 *)0xE000E104))
#define       NVIC_EN2                                (*((volatile uint32 *)0xE000E108))
#define       NVIC_EN3                                (*((volatile uint32 *)0xE000E10C))
#define       NVIC_EN4                                (*((volatile uint32 *)0xE000E110))
#define       NVIC_DIS0                               (*((volatile uint32 *)0xE000E180))
#define       NVIC_DIS1                               (*((volatile uint32 *)0xE000E184))
#define       NVIC_DIS2                               (*((volatile uint32 *)0xE000E188))
#define       NVIC_DIS3                               (*((volatile uint32 *)0xE000E18C))
#define       NVIC_DIS4                               (*((volatile uint32 *)0xE000E190))
#define       NVIC_PEND0                              (*((volatile uint32 *)0xE000E200))
#define       NVIC_PEND1                              (*((volatile uint32 *)0xE000E204))
#define       NVIC_PEND2                              (*((volatile uint32 *)0xE000E208))
#define       NVIC_PEND3                              (*((volatile uint32 *)0xE000E20C))
#define       NVIC_PEND4                              (*((volatile uint32 *)0xE000E210))
#define       NVIC_UNPEND0                            (*((volatile uint32 *)0xE000E280))
#define       NVIC_UNPEND1                            (*((volatile uint32 *)0xE000E284))
#define       NVIC_UNPEND2                            (*((volatile uint32 *)0xE000E288))
#define       NVIC_UNPEND3                            (*((volatile uint32 *)0xE000E28C))
#define       NVIC_UNPEND4                            (*((volatile uint32 *)0xE000E290))
#define       NVIC_ACTIVE0                            (*((volatile uint32 *)0xE000E300))
#define       NVIC_ACTIVE1                            (*((volatile uint32 *)0xE000E304))
#define       NVIC_ACTIVE2                            (*((volatile uint32 *)0xE000E308))
#define       NVIC_ACTIVE3                            (*((volatile uint32 *)0xE000E30C))
#define       NVIC_ACTIVE4                            (*((volatile uint32 *)0xE000E310))
#define       NVIC_PRI0                               (*((volatile uint32 *)0xE000E400))
#define       NVIC_PRI0_ADDRESS                       0xE000E400
#define       NVIC_SWTRIG                             (*((volatile uint32 *)0xE000EF00))
#define       NVIC_INTCTRL                            (*((volatile uint32 *)0xE000ED04))
#define       NVIC_VTABLE                             (*((volatile uint32 *)0xE000ED08))
#define       NVIC_APINT                              (*((volatile uint32 *)0xE000ED0C))
#define       NVIC_SYSPRI1                            (*((volatile uint32 *)0xE000ED18))
#define       NVIC_SYSPRI2                            (*((volatile uint32 *)0xE000ED1C))
#define       NVIC_SYSPRI3                            (*((volatile uint32 *)0xE000ED20))
#define       NVIC_SYSHNDCTRL                         (*((volatile uint32 *)0xE000ED24))
#define       NVIC_FAULTSTAT                          (*((volatile uint32 *)0xE000ED28))
#define       NVIC_HFAULTSTAT                         (*((volatile uint32 *)0xE000ED2C))




/* Base Addresses For GPIO PORTS */
#define GPIO_PORTA_BASE_ADDRESS           0x40004000
#define GPIO_PORTB_BASE_ADDRESS           0x40005000
#define GPIO_PORTC_BASE_ADDRESS           0x40006000
#define GPIO_PORTD_BASE_ADDRESS           0x40007000
#define GPIO_PORTE_BASE_ADDRESS           0x40024000
#define GPIO_PORTF_BASE_ADDRESS           0x40025000

/* GPIO Registers offset addresses */
#define PORT_DATA_REG_OFFSET              0x3FC
#define PORT_DIR_REG_OFFSET               0x400
#define PORT_ALT_FUNC_REG_OFFSET          0x420
#define PORT_2_MA_DRIVE_REG_OFFSET        0X500
#define PORT_4_MA_DRIVE_REG_OFFSET        0X504
#define PORT_8_MA_DRIVE_REG_OFFSET        0X508
#define PORT_OPEN_DRAIN_REG_OFFSET        0x50C
#define PORT_PULL_UP_REG_OFFSET           0x510
#define PORT_PULL_DOWN_REG_OFFSET         0x514
#define PORT_DIGITAL_ENABLE_REG_OFFSET    0x51C
#define PORT_LOCK_REG_OFFSET              0x520
#define PORT_COMMIT_REG_OFFSET            0x524
#define PORT_ANALOG_MODE_SEL_REG_OFFSET   0x528
#define PORT_CTL_REG_OFFSET               0x52C
#define PORT_ADC_CONTROL_REG_OFFSET       0x530



/*****************************************************************************
GPIO BASES (PORT)
*****************************************************************************/
#define GPIO_PORTA_DATA_ADDRESS       0x40004000
#define GPIO_PORTB_DATA_ADDRESS       0x40005000
#define GPIO_PORTC_DATA_ADDRESS       0x40006000
#define GPIO_PORTD_DATA_ADDRESS       0x40007000
#define GPIO_PORTE_DATA_ADDRESS       0x40024000
#define GPIO_PORTF_DATA_ADDRESS       0x40025000

/*****************************************************************************
GPIO registers (PORTA)
*****************************************************************************/
#define GPIO_PORTA_DATA_REG       (*((volatile uint32 *)0x400043FC))
#define GPIO_PORTA_DIR_REG        (*((volatile uint32 *)0x40004400))
#define GPIO_PORTA_AFSEL_REG      (*((volatile uint32 *)0x40004420))
#define GPIO_PORTA_PUR_REG        (*((volatile uint32 *)0x40004510))
#define GPIO_PORTA_PDR_REG        (*((volatile uint32 *)0x40004514))
#define GPIO_PORTA_DEN_REG        (*((volatile uint32 *)0x4000451C))
#define GPIO_PORTA_LOCK_REG       (*((volatile uint32 *)0x40004520))
#define GPIO_PORTA_CR_REG         (*((volatile uint32 *)0x40004524))
#define GPIO_PORTA_AMSEL_REG      (*((volatile uint32 *)0x40004528))
#define GPIO_PORTA_PCTL_REG       (*((volatile uint32 *)0x4000452C))

/* PORTA External Interrupts Registers */
#define GPIO_PORTA_IS_REG         (*((volatile uint32 *)0x40004404))
#define GPIO_PORTA_IBE_REG        (*((volatile uint32 *)0x40004408))
#define GPIO_PORTA_IEV_REG        (*((volatile uint32 *)0x4000440C))
#define GPIO_PORTA_IM_REG         (*((volatile uint32 *)0x40004410))
#define GPIO_PORTA_RIS_REG        (*((volatile uint32 *)0x40004414))
#define GPIO_PORTA_ICR_REG        (*((volatile uint32 *)0x4000441C))

/*****************************************************************************
GPIO registers (PORTB)
*****************************************************************************/
#define GPIO_PORTB_DATA_REG       (*((volatile uint32 *)0x400053FC))
#define GPIO_PORTB_DIR_REG        (*((volatile uint32 *)0x40005400))
#define GPIO_PORTB_AFSEL_REG      (*((volatile uint32 *)0x40005420))
#define GPIO_PORTB_PUR_REG        (*((volatile uint32 *)0x40005510))
#define GPIO_PORTB_PDR_REG        (*((volatile uint32 *)0x40005514))
#define GPIO_PORTB_DEN_REG        (*((volatile uint32 *)0x4000551C))
#define GPIO_PORTB_LOCK_REG       (*((volatile uint32 *)0x40005520))
#define GPIO_PORTB_CR_REG         (*((volatile uint32 *)0x40005524))
#define GPIO_PORTB_AMSEL_REG      (*((volatile uint32 *)0x40005528))
#define GPIO_PORTB_PCTL_REG       (*((volatile uint32 *)0x4000552C))

/* PORTB External Interrupts Registers */
#define GPIO_PORTB_IS_REG         (*((volatile uint32 *)0x40005404))
#define GPIO_PORTB_IBE_REG        (*((volatile uint32 *)0x40005408))
#define GPIO_PORTB_IEV_REG        (*((volatile uint32 *)0x4000540C))
#define GPIO_PORTB_IM_REG         (*((volatile uint32 *)0x40005410))
#define GPIO_PORTB_RIS_REG        (*((volatile uint32 *)0x40005414))
#define GPIO_PORTB_ICR_REG        (*((volatile uint32 *)0x4000541C))

/*****************************************************************************
GPIO registers (PORTC)
*****************************************************************************/
#define GPIO_PORTC_DATA_REG       (*((volatile uint32 *)0x400063FC))
#define GPIO_PORTC_DIR_REG        (*((volatile uint32 *)0x40006400))
#define GPIO_PORTC_AFSEL_REG      (*((volatile uint32 *)0x40006420))
#define GPIO_PORTC_PUR_REG        (*((volatile uint32 *)0x40006510))
#define GPIO_PORTC_PDR_REG        (*((volatile uint32 *)0x40006514))
#define GPIO_PORTC_DEN_REG        (*((volatile uint32 *)0x4000651C))
#define GPIO_PORTC_LOCK_REG       (*((volatile uint32 *)0x40006520))
#define GPIO_PORTC_CR_REG         (*((volatile uint32 *)0x40006524))
#define GPIO_PORTC_AMSEL_REG      (*((volatile uint32 *)0x40006528))
#define GPIO_PORTC_PCTL_REG       (*((volatile uint32 *)0x4000652C))

/* PORTC External Interrupts Registers */
#define GPIO_PORTC_IS_REG         (*((volatile uint32 *)0x40006404))
#define GPIO_PORTC_IBE_REG        (*((volatile uint32 *)0x40006408))
#define GPIO_PORTC_IEV_REG        (*((volatile uint32 *)0x4000640C))
#define GPIO_PORTC_IM_REG         (*((volatile uint32 *)0x40006410))
#define GPIO_PORTC_RIS_REG        (*((volatile uint32 *)0x40006414))
#define GPIO_PORTC_ICR_REG        (*((volatile uint32 *)0x4000641C))

/*****************************************************************************
GPIO registers (PORTD)
*****************************************************************************/
#define GPIO_PORTD_DATA_REG       (*((volatile uint32 *)0x400073FC))
#define GPIO_PORTD_DIR_REG        (*((volatile uint32 *)0x40007400))
#define GPIO_PORTD_AFSEL_REG      (*((volatile uint32 *)0x40007420))
#define GPIO_PORTD_PUR_REG        (*((volatile uint32 *)0x40007510))
#define GPIO_PORTD_PDR_REG        (*((volatile uint32 *)0x40007514))
#define GPIO_PORTD_DEN_REG        (*((volatile uint32 *)0x4000751C))
#define GPIO_PORTD_LOCK_REG       (*((volatile uint32 *)0x40007520))
#define GPIO_PORTD_CR_REG         (*((volatile uint32 *)0x40007524))
#define GPIO_PORTD_AMSEL_REG      (*((volatile uint32 *)0x40007528))
#define GPIO_PORTD_PCTL_REG       (*((volatile uint32 *)0x4000752C))

/* PORTD External Interrupts Registers */
#define GPIO_PORTD_IS_REG         (*((volatile uint32 *)0x40007404))
#define GPIO_PORTD_IBE_REG        (*((volatile uint32 *)0x40007408))
#define GPIO_PORTD_IEV_REG        (*((volatile uint32 *)0x4000740C))
#define GPIO_PORTD_IM_REG         (*((volatile uint32 *)0x40007410))
#define GPIO_PORTD_RIS_REG        (*((volatile uint32 *)0x40007414))
#define GPIO_PORTD_ICR_REG        (*((volatile uint32 *)0x4000741C))

/*****************************************************************************
GPIO registers (PORTE)
*****************************************************************************/
#define GPIO_PORTE_DATA_REG       (*((volatile uint32 *)0x400243FC))
#define GPIO_PORTE_DIR_REG        (*((volatile uint32 *)0x40024400))
#define GPIO_PORTE_AFSEL_REG      (*((volatile uint32 *)0x40024420))
#define GPIO_PORTE_PUR_REG        (*((volatile uint32 *)0x40024510))
#define GPIO_PORTE_PDR_REG        (*((volatile uint32 *)0x40024514))
#define GPIO_PORTE_DEN_REG        (*((volatile uint32 *)0x4002451C))
#define GPIO_PORTE_LOCK_REG       (*((volatile uint32 *)0x40024520))
#define GPIO_PORTE_CR_REG         (*((volatile uint32 *)0x40024524))
#define GPIO_PORTE_AMSEL_REG      (*((volatile uint32 *)0x40024528))
#define GPIO_PORTE_PCTL_REG       (*((volatile uint32 *)0x4002452C))

/* PORTE External Interrupts Registers */
#define GPIO_PORTE_IS_REG         (*((volatile uint32 *)0x40024404))
#define GPIO_PORTE_IBE_REG        (*((volatile uint32 *)0x40024408))
#define GPIO_PORTE_IEV_REG        (*((volatile uint32 *)0x4002440C))
#define GPIO_PORTE_IM_REG         (*((volatile uint32 *)0x40024410))
#define GPIO_PORTE_RIS_REG        (*((volatile uint32 *)0x40024414))
#define GPIO_PORTE_ICR_REG        (*((volatile uint32 *)0x4002441C))

/*****************************************************************************
GPIO registers (PORTF)
*****************************************************************************/
#define GPIO_PORTF_DATA_REG       (*((volatile uint32 *)0x400253FC))
#define GPIO_PORTF_DIR_REG        (*((volatile uint32 *)0x40025400))
#define GPIO_PORTF_AFSEL_REG      (*((volatile uint32 *)0x40025420))
#define GPIO_PORTF_PUR_REG        (*((volatile uint32 *)0x40025510))
#define GPIO_PORTF_PDR_REG        (*((volatile uint32 *)0x40025514))
#define GPIO_PORTF_DEN_REG        (*((volatile uint32 *)0x4002551C))
#define GPIO_PORTF_LOCK_REG       (*((volatile uint32 *)0x40025520))
#define GPIO_PORTF_CR_REG         (*((volatile uint32 *)0x40025524))
#define GPIO_PORTF_AMSEL_REG      (*((volatile uint32 *)0x40025528))
#define GPIO_PORTF_PCTL_REG       (*((volatile uint32 *)0x4002552C))

/* PORTF External Interrupts Registers */
#define GPIO_PORTF_IS_REG         (*((volatile uint32 *)0x40025404))
#define GPIO_PORTF_IBE_REG        (*((volatile uint32 *)0x40025408))
#define GPIO_PORTF_IEV_REG        (*((volatile uint32 *)0x4002540C))
#define GPIO_PORTF_IM_REG         (*((volatile uint32 *)0x40025410))
#define GPIO_PORTF_RIS_REG        (*((volatile uint32 *)0x40025414))
#define GPIO_PORTF_ICR_REG        (*((volatile uint32 *)0x4002541C))



/*****************************************************************************
SysCtrl Registers
*****************************************************************************/
#define SYSCTL_REGCGC2_REG        (*((volatile uint32 *)0x400FE108))
#define SYSCTL_RCGCTIMER_REG      (*((volatile uint32 *)0x400FE604))


/*****************************************************************************
Systick Timer Registers
*****************************************************************************/
#define SYSTICK_CTRL_REG          (*((volatile uint32 *)0xE000E010))
#define SYSTICK_RELOAD_REG        (*((volatile uint32 *)0xE000E014))
#define SYSTICK_CURRENT_REG       (*((volatile uint32 *)0xE000E018))

/*****************************************************************************
WatchDog Timer Registers
*****************************************************************************/
#define WDT0_LOAD_REG             (*((volatile uint32 *)0x40000000))
#define WDT0_VALUE_REG            (*((volatile uint32 *)0x40000004))
#define WDT0_CTL_REG              (*((volatile uint32 *)0x40000008))
#define WDT0_ICR_REG              (*((volatile uint32 *)0x4000000C))
#define WDT0_RIS_REG              (*((volatile uint32 *)0x40000010))
#define WDT0_MIS_REG              (*((volatile uint32 *)0x40000014))
#define WDT0_TEST_REG             (*((volatile uint32 *)0x40000418))
#define WDT0_LOCK_REG             (*((volatile uint32 *)0x40000C00))

#define WDT1_LOAD_REG             (*((volatile uint32 *)0x40001000))
#define WDT1_VALUE_REG            (*((volatile uint32 *)0x40001004))
#define WDT1_CTL_REG              (*((volatile uint32 *)0x40001008))
#define WDT1_ICR_REG              (*((volatile uint32 *)0x4000100C))
#define WDT1_RIS_REG              (*((volatile uint32 *)0x40001010))
#define WDT1_MIS_REG              (*((volatile uint32 *)0x40001014))
#define WDT1_TEST_REG             (*((volatile uint32 *)0x40001418))
#define WDT1_LOCK_REG             (*((volatile uint32 *)0x40001C00))

#define GPTM_0_16_32_REG          (*((volatile uint32 *)0x40030000))
#define GPTM_1_16_32_REG          (*((volatile uint32 *)0x40031000))
#define GPTM_2_16_32_REG          (*((volatile uint32 *)0x40032000))
#define GPTM_3_16_32_REG          (*((volatile uint32 *)0x40033000))
#define GPTM_4_16_32_REG          (*((volatile uint32 *)0x40034000))
#define GPTM_5_16_32_REG          (*((volatile uint32 *)0x40035000))

#define GPTM_0_32_64_REG          (*((volatile uint32 *)0x40036000))
#define GPTM_1_32_64_REG          (*((volatile uint32 *)0x40037000))
#define GPTM_2_32_64_REG          (*((volatile uint32 *)0x4004C000))
#define GPTM_3_32_64_REG          (*((volatile uint32 *)0x4004D000))
#define GPTM_4_32_64_REG          (*((volatile uint32 *)0x4004E000))
#define GPTM_5_32_64_REG          (*((volatile uint32 *)0x4004F000))


#define GPTM_0_16_32_ADDRESS 0x40030000
#define GPTM_1_16_32_ADDRESS 0x40031000
#define GPTM_2_16_32_ADDRESS 0x40032000
#define GPTM_3_16_32_ADDRESS 0x40033000
#define GPTM_4_16_32_ADDRESS 0x40034000
#define GPTM_5_16_32_ADDRESS 0x40035000

#define GPTM_0_32_64_ADDRESS 0x40036000
#define GPTM_1_32_64_ADDRESS 0x40037000
#define GPTM_2_32_64_ADDRESS 0x4004C000
#define GPTM_3_32_64_ADDRESS 0x4004D000
#define GPTM_4_32_64_ADDRESS 0x4004E000
#define GPTM_5_32_64_ADDRESS 0x4004F000

#define GPTM_CFG_REG_OFFSET     0x000
#define GPTM_TAMR_REG_OFFSET    0x004
#define GPTM_TBMR_REG_OFFSET    0x008
#define GPTM_CTL_REG_OFFSET     0x00C
#define GPTM_SYNC_REG_OFFSET    0x010
#define GPTM_IMR_REG_OFFSET     0x018
#define GPTM_RIS_REG_OFFSET     0x01C
#define GPTM_MIS_REG_OFFSET     0x020
#define GPTM_ICR_REG_OFFSET     0x024
#define GPTM_TAILR_REG_OFFSET   0x028
#define GPTM_TBILR_REG_OFFSET   0x02C
#define GPTM_TAMATCHR_REG_OFFSET 0x030
#define GPTM_TBMATCHR_REG_OFFSET 0x034
#define GPTM_TAPR_REG_OFFSET    0x038
#define GPTM_TBPR_REG_OFFSET    0x03C
#define GPTM_TAPMR_REG_OFFSET   0x040
#define GPTM_TBPMR_REG_OFFSET   0x044
#define GPTM_TAR_REG_OFFSET     0x048
#define GPTM_TBR_REG_OFFSET     0x04C
#define GPTM_TAV_REG_OFFSET     0x050
#define GPTM_TBV_REG_OFFSET     0x054
#define GPTM_RTCPD_REG_OFFSET   0x058
#define GPTM_TAPS_REG_OFFSET    0x05C
#define GPTM_TBPS_REG_OFFSET    0x060
#define GPTM_TAPV_REG_OFFSET    0x064
#define GPTM_TBPV_REG_OFFSET    0x068
#define GPTM_PP_REG_OFFSET      0xFC0


//*****************************************************************************
//
// UART registers (UART0)
//
//*****************************************************************************
#define UART0_DR_R              (*((volatile unsigned long *)0x4000C000))
#define UART0_RSR_R             (*((volatile unsigned long *)0x4000C004))
#define UART0_ECR_R             (*((volatile unsigned long *)0x4000C004))
#define UART0_FR_R              (*((volatile unsigned long *)0x4000C018))
#define UART0_ILPR_R            (*((volatile unsigned long *)0x4000C020))
#define UART0_IBRD_R            (*((volatile unsigned long *)0x4000C024))
#define UART0_FBRD_R            (*((volatile unsigned long *)0x4000C028))
#define UART0_LCRH_R            (*((volatile unsigned long *)0x4000C02C))
#define UART0_CTL_R             (*((volatile unsigned long *)0x4000C030))
#define UART0_IFLS_R            (*((volatile unsigned long *)0x4000C034))
#define UART0_IM_R              (*((volatile unsigned long *)0x4000C038))
#define UART0_RIS_R             (*((volatile unsigned long *)0x4000C03C))
#define UART0_MIS_R             (*((volatile unsigned long *)0x4000C040))
#define UART0_ICR_R             (*((volatile unsigned long *)0x4000C044))
#define UART0_DMACTL_R          (*((volatile unsigned long *)0x4000C048))
#define UART0_9BITADDR_R        (*((volatile unsigned long *)0x4000C0A4))
#define UART0_9BITAMASK_R       (*((volatile unsigned long *)0x4000C0A8))
#define UART0_PP_R              (*((volatile unsigned long *)0x4000CFC0))
#define UART0_CC_R              (*((volatile unsigned long *)0x4000CFC8))

//*****************************************************************************
//
// UART registers (UART1)
//
//*****************************************************************************
#define UART1_DR_R              (*((volatile unsigned long *)0x4000D000))
#define UART1_RSR_R             (*((volatile unsigned long *)0x4000D004))
#define UART1_ECR_R             (*((volatile unsigned long *)0x4000D004))
#define UART1_FR_R              (*((volatile unsigned long *)0x4000D018))
#define UART1_ILPR_R            (*((volatile unsigned long *)0x4000D020))
#define UART1_IBRD_R            (*((volatile unsigned long *)0x4000D024))
#define UART1_FBRD_R            (*((volatile unsigned long *)0x4000D028))
#define UART1_LCRH_R            (*((volatile unsigned long *)0x4000D02C))
#define UART1_CTL_R             (*((volatile unsigned long *)0x4000D030))
#define UART1_IFLS_R            (*((volatile unsigned long *)0x4000D034))
#define UART1_IM_R              (*((volatile unsigned long *)0x4000D038))
#define UART1_RIS_R             (*((volatile unsigned long *)0x4000D03C))
#define UART1_MIS_R             (*((volatile unsigned long *)0x4000D040))
#define UART1_ICR_R             (*((volatile unsigned long *)0x4000D044))
#define UART1_DMACTL_R          (*((volatile unsigned long *)0x4000D048))
#define UART1_9BITADDR_R        (*((volatile unsigned long *)0x4000D0A4))
#define UART1_9BITAMASK_R       (*((volatile unsigned long *)0x4000D0A8))
#define UART1_PP_R              (*((volatile unsigned long *)0x4000DFC0))
#define UART1_CC_R              (*((volatile unsigned long *)0x4000DFC8))

//*****************************************************************************
//
// UART registers (UART2)
//
//*****************************************************************************
#define UART2_DR_R              (*((volatile unsigned long *)0x4000E000))
#define UART2_RSR_R             (*((volatile unsigned long *)0x4000E004))
#define UART2_ECR_R             (*((volatile unsigned long *)0x4000E004))
#define UART2_FR_R              (*((volatile unsigned long *)0x4000E018))
#define UART2_ILPR_R            (*((volatile unsigned long *)0x4000E020))
#define UART2_IBRD_R            (*((volatile unsigned long *)0x4000E024))
#define UART2_FBRD_R            (*((volatile unsigned long *)0x4000E028))
#define UART2_LCRH_R            (*((volatile unsigned long *)0x4000E02C))
#define UART2_CTL_R             (*((volatile unsigned long *)0x4000E030))
#define UART2_IFLS_R            (*((volatile unsigned long *)0x4000E034))
#define UART2_IM_R              (*((volatile unsigned long *)0x4000E038))
#define UART2_RIS_R             (*((volatile unsigned long *)0x4000E03C))
#define UART2_MIS_R             (*((volatile unsigned long *)0x4000E040))
#define UART2_ICR_R             (*((volatile unsigned long *)0x4000E044))
#define UART2_DMACTL_R          (*((volatile unsigned long *)0x4000E048))
#define UART2_9BITADDR_R        (*((volatile unsigned long *)0x4000E0A4))
#define UART2_9BITAMASK_R       (*((volatile unsigned long *)0x4000E0A8))
#define UART2_PP_R              (*((volatile unsigned long *)0x4000EFC0))
#define UART2_CC_R              (*((volatile unsigned long *)0x4000EFC8))

//*****************************************************************************
//
// UART registers (UART3)
//
//*****************************************************************************
#define UART3_DR_R              (*((volatile unsigned long *)0x4000F000))
#define UART3_RSR_R             (*((volatile unsigned long *)0x4000F004))
#define UART3_ECR_R             (*((volatile unsigned long *)0x4000F004))
#define UART3_FR_R              (*((volatile unsigned long *)0x4000F018))
#define UART3_ILPR_R            (*((volatile unsigned long *)0x4000F020))
#define UART3_IBRD_R            (*((volatile unsigned long *)0x4000F024))
#define UART3_FBRD_R            (*((volatile unsigned long *)0x4000F028))
#define UART3_LCRH_R            (*((volatile unsigned long *)0x4000F02C))
#define UART3_CTL_R             (*((volatile unsigned long *)0x4000F030))
#define UART3_IFLS_R            (*((volatile unsigned long *)0x4000F034))
#define UART3_IM_R              (*((volatile unsigned long *)0x4000F038))
#define UART3_RIS_R             (*((volatile unsigned long *)0x4000F03C))
#define UART3_MIS_R             (*((volatile unsigned long *)0x4000F040))
#define UART3_ICR_R             (*((volatile unsigned long *)0x4000F044))
#define UART3_DMACTL_R          (*((volatile unsigned long *)0x4000F048))
#define UART3_9BITADDR_R        (*((volatile unsigned long *)0x4000F0A4))
#define UART3_9BITAMASK_R       (*((volatile unsigned long *)0x4000F0A8))
#define UART3_PP_R              (*((volatile unsigned long *)0x4000FFC0))
#define UART3_CC_R              (*((volatile unsigned long *)0x4000FFC8))

//*****************************************************************************
//
// UART registers (UART4)
//
//*****************************************************************************
#define UART4_DR_R              (*((volatile unsigned long *)0x40010000))
#define UART4_RSR_R             (*((volatile unsigned long *)0x40010004))
#define UART4_ECR_R             (*((volatile unsigned long *)0x40010004))
#define UART4_FR_R              (*((volatile unsigned long *)0x40010018))
#define UART4_ILPR_R            (*((volatile unsigned long *)0x40010020))
#define UART4_IBRD_R            (*((volatile unsigned long *)0x40010024))
#define UART4_FBRD_R            (*((volatile unsigned long *)0x40010028))
#define UART4_LCRH_R            (*((volatile unsigned long *)0x4001002C))
#define UART4_CTL_R             (*((volatile unsigned long *)0x40010030))
#define UART4_IFLS_R            (*((volatile unsigned long *)0x40010034))
#define UART4_IM_R              (*((volatile unsigned long *)0x40010038))
#define UART4_RIS_R             (*((volatile unsigned long *)0x4001003C))
#define UART4_MIS_R             (*((volatile unsigned long *)0x40010040))
#define UART4_ICR_R             (*((volatile unsigned long *)0x40010044))
#define UART4_DMACTL_R          (*((volatile unsigned long *)0x40010048))
#define UART4_9BITADDR_R        (*((volatile unsigned long *)0x400100A4))
#define UART4_9BITAMASK_R       (*((volatile unsigned long *)0x400100A8))
#define UART4_PP_R              (*((volatile unsigned long *)0x40010FC0))
#define UART4_CC_R              (*((volatile unsigned long *)0x40010FC8))

//*****************************************************************************
//
// UART registers (UART5)
//
//*****************************************************************************
#define UART5_DR              (*((volatile unsigned long *)0x40011000))
#define UART5_RSR             (*((volatile unsigned long *)0x40011004))
#define UART5_ECR             (*((volatile unsigned long *)0x40011004))
#define UART5_FR              (*((volatile unsigned long *)0x40011018))
#define UART5_ILPR            (*((volatile unsigned long *)0x40011020))
#define UART5_IBRD            (*((volatile unsigned long *)0x40011024))
#define UART5_FBRD            (*((volatile unsigned long *)0x40011028))
#define UART5_LCRH            (*((volatile unsigned long *)0x4001102C))
#define UART5_CTL             (*((volatile unsigned long *)0x40011030))
#define UART5_IFLS            (*((volatile unsigned long *)0x40011034))
#define UART5_IM              (*((volatile unsigned long *)0x40011038))
#define UART5_RIS             (*((volatile unsigned long *)0x4001103C))
#define UART5_MIS             (*((volatile unsigned long *)0x40011040))
#define UART5_ICR             (*((volatile unsigned long *)0x40011044))
#define UART5_DMACTL          (*((volatile unsigned long *)0x40011048))
#define UART5_9BITADDR        (*((volatile unsigned long *)0x400110A4))
#define UART5_9BITAMASK       (*((volatile unsigned long *)0x400110A8))
#define UART5_PP              (*((volatile unsigned long *)0x40011FC0))
#define UART5_CC              (*((volatile unsigned long *)0x40011FC8))


//*****************************************************************************
//
// UART registers (UART6)
//
//*****************************************************************************
#define UART6_DR_R              (*((volatile unsigned long *)0x40012000))
#define UART6_RSR_R             (*((volatile unsigned long *)0x40012004))
#define UART6_ECR_R             (*((volatile unsigned long *)0x40012004))
#define UART6_FR_R              (*((volatile unsigned long *)0x40012018))
#define UART6_ILPR_R            (*((volatile unsigned long *)0x40012020))
#define UART6_IBRD_R            (*((volatile unsigned long *)0x40012024))
#define UART6_FBRD_R            (*((volatile unsigned long *)0x40012028))
#define UART6_LCRH_R            (*((volatile unsigned long *)0x4001202C))
#define UART6_CTL_R             (*((volatile unsigned long *)0x40012030))
#define UART6_IFLS_R            (*((volatile unsigned long *)0x40012034))
#define UART6_IM_R              (*((volatile unsigned long *)0x40012038))
#define UART6_RIS_R             (*((volatile unsigned long *)0x4001203C))
#define UART6_MIS_R             (*((volatile unsigned long *)0x40012040))
#define UART6_ICR_R             (*((volatile unsigned long *)0x40012044))
#define UART6_DMACTL_R          (*((volatile unsigned long *)0x40012048))
#define UART6_9BITADDR_R        (*((volatile unsigned long *)0x400120A4))
#define UART6_9BITAMASK_R       (*((volatile unsigned long *)0x400120A8))
#define UART6_PP_R              (*((volatile unsigned long *)0x40012FC0))
#define UART6_CC_R              (*((volatile unsigned long *)0x40012FC8))

//*****************************************************************************
//
// UART registers (UART7)
//
//*****************************************************************************
#define UART7_DR_R              (*((volatile unsigned long *)0x40013000))
#define UART7_RSR_R             (*((volatile unsigned long *)0x40013004))
#define UART7_ECR_R             (*((volatile unsigned long *)0x40013004))
#define UART7_FR_R              (*((volatile unsigned long *)0x40013018))
#define UART7_ILPR_R            (*((volatile unsigned long *)0x40013020))
#define UART7_IBRD_R            (*((volatile unsigned long *)0x40013024))
#define UART7_FBRD_R            (*((volatile unsigned long *)0x40013028))
#define UART7_LCRH_R            (*((volatile unsigned long *)0x4001302C))
#define UART7_CTL_R             (*((volatile unsigned long *)0x40013030))
#define UART7_IFLS_R            (*((volatile unsigned long *)0x40013034))
#define UART7_IM_R              (*((volatile unsigned long *)0x40013038))
#define UART7_RIS_R             (*((volatile unsigned long *)0x4001303C))
#define UART7_MIS_R             (*((volatile unsigned long *)0x40013040))
#define UART7_ICR_R             (*((volatile unsigned long *)0x40013044))
#define UART7_DMACTL_R          (*((volatile unsigned long *)0x40013048))
#define UART7_9BITADDR_R        (*((volatile unsigned long *)0x400130A4))
#define UART7_9BITAMASK_R       (*((volatile unsigned long *)0x400130A8))
#define UART7_PP_R              (*((volatile unsigned long *)0x40013FC0))
#define UART7_CC_R              (*((volatile unsigned long *)0x40013FC8))

#define UART0_BASE_ADDRESS           0x4000C000
#define UART1_BASE_ADDRESS           0x4000D000
#define UART2_BASE_ADDRESS           0x4000E000
#define UART3_BASE_ADDRESS           0x4000F000
#define UART4_BASE_ADDRESS           0x40010000
#define UART5_BASE_ADDRESS           0x40011000
#define UART6_BASE_ADDRESS           0x40012000
#define UART7_BASE_ADDRESS           0x40013000

/* UART Registers offset addresses */
#define UART_DATA_REG_OFFSET              0x000
#define UART_FLAG_REG_OFFSET              0x018
#define UART_IBRD_REG_OFFSET              0x024
#define UART_FBRD_REG_OFFSET              0x028
#define UART_LCRH_REG_OFFSET              0x02C
#define UART_CTL_REG_OFFSET               0x030
#define UART_IFLS_REG_OFFSET              0x034
#define UART_IM_REG_OFFSET                0x038
#define UART_RIS_REG_OFFSET               0x03C
#define UART_MIS_REG_OFFSET               0x040
#define UART_ICR_REG_OFFSET               0x044
#define UART_CC_REG_OFFSET                0xFC8
#define UART_UARTRIS_REG_OFFSET           0x03C

#define UART_FR_CTS_MASK            0
#define UART_FR_BUSY_MASK           3
#define UART_FR_RXFE_MASK           4
#define UART_FR_TXFF_MASK           5
#define UART_FR_RXFF_MASK           6
#define UART_FR_TXFE_MASK           7


#define UART_MIS_CTS_MASK           1
#define UART_MIS_RX_MASK            4
#define UART_MIS_TX_MASK            5
#define UART_MIS_RT_MASK            6
#define UART_MIS_FE_MASK            7
#define UART_MIS_PE_MASK            8
#define UART_MIS_BE_MASK            9
#define UART_MIS_OE_MASK            10
#define UART_MIS_9BIT_MASK          12

/* I2C module 0 Master Registers */
#define I2C0_MSA_R          (*((volatile unsigned long *)0x40020000))
#define I2C0_MCS_R          (*((volatile unsigned long *)0x40020004))
#define I2C0_MDR_R          (*((volatile unsigned long *)0x40020008))
#define I2C0_MTPR_R         (*((volatile unsigned long *)0x4002000C))
#define I2C0_MIMR_R         (*((volatile unsigned long *)0x40020010))
#define I2C0_MRIS_R         (*((volatile unsigned long *)0x40020014))
#define I2C0_MMIS_R         (*((volatile unsigned long *)0x40020018))
#define I2C0_MICR_R         (*((volatile unsigned long *)0x4002001C))
#define I2C0_MCR_R          (*((volatile unsigned long *)0x40020020))
#define I2C0_MCLKOCNT_R     (*((volatile unsigned long *)0x40020024))
#define I2C0_MBMON_R        (*((volatile unsigned long *)0x4002002C))
#define I2C0_MCR2_R         (*((volatile unsigned long *)0x40020038))
/* I2C module 0 Slave Registers */
#define I2C0_SOAR_R         (*((volatile unsigned long *)0x40020800))
#define I2C0_SCSR_R         (*((volatile unsigned long *)0x40020804))
#define I2C0_SDR_R          (*((volatile unsigned long *)0x40020808))
#define I2C0_SIMR_R         (*((volatile unsigned long *)0x4002080C))
#define I2C0_SRIS_R         (*((volatile unsigned long *)0x40020810))
#define I2C0_SMIS_R         (*((volatile unsigned long *)0x40020814))
#define I2C0_SICR_R         (*((volatile unsigned long *)0x40020818))
#define I2C0_SOAR2_R        (*((volatile unsigned long *)0x4002081C))
#define I2C0_SACKCTL_R      (*((volatile unsigned long *)0x40020820))
#define I2C0_PP_R           (*((volatile unsigned long *)0x40020FC0))
#define I2C0_PC_R           (*((volatile unsigned long *)0x40020FC4))

/* I2C module 1 Master Registers */
#define I2C1_MSA_R          (*((volatile unsigned long *)0x40021000))
#define I2C1_MCS_R          (*((volatile unsigned long *)0x40021004))
#define I2C1_MDR_R          (*((volatile unsigned long *)0x40021008))
#define I2C1_MTPR_R         (*((volatile unsigned long *)0x4002100C))
#define I2C1_MIMR_R         (*((volatile unsigned long *)0x40021010))
#define I2C1_MRIS_R         (*((volatile unsigned long *)0x40021014))
#define I2C1_MMIS_R         (*((volatile unsigned long *)0x40021018))
#define I2C1_MICR_R         (*((volatile unsigned long *)0x4002101C))
#define I2C1_MCR_R          (*((volatile unsigned long *)0x40021020))
#define I2C1_MCLKOCNT_R     (*((volatile unsigned long *)0x40021024))
#define I2C1_MBMON_R        (*((volatile unsigned long *)0x4002102C))
#define I2C1_MCR2_R         (*((volatile unsigned long *)0x40021038))
/* I2C module 1 Slave Registers */
#define I2C1_SOAR_R         (*((volatile unsigned long *)0x40021800))
#define I2C1_SCSR_R         (*((volatile unsigned long *)0x40021804))
#define I2C1_SDR_R          (*((volatile unsigned long *)0x40021808))
#define I2C1_SIMR_R         (*((volatile unsigned long *)0x4002180C))
#define I2C1_SRIS_R         (*((volatile unsigned long *)0x40021810))
#define I2C1_SMIS_R         (*((volatile unsigned long *)0x40021814))
#define I2C1_SICR_R         (*((volatile unsigned long *)0x40021818))
#define I2C1_SOAR2_R        (*((volatile unsigned long *)0x4002181C))
#define I2C1_SACKCTL_R      (*((volatile unsigned long *)0x40021820))
#define I2C1_PP_R           (*((volatile unsigned long *)0x40021FC0))
#define I2C1_PC_R           (*((volatile unsigned long *)0x40021FC4))

/* I2C module 2 Master Registers */
#define I2C2_MSA_R          (*((volatile unsigned long *)0x40022000))
#define I2C2_MCS_R          (*((volatile unsigned long *)0x40022004))
#define I2C2_MDR_R          (*((volatile unsigned long *)0x40022008))
#define I2C2_MTPR_R         (*((volatile unsigned long *)0x4002200C))
#define I2C2_MIMR_R         (*((volatile unsigned long *)0x40022010))
#define I2C2_MRIS_R         (*((volatile unsigned long *)0x40022014))
#define I2C2_MMIS_R         (*((volatile unsigned long *)0x40022018))
#define I2C2_MICR_R         (*((volatile unsigned long *)0x4002201C))
#define I2C2_MCR_R          (*((volatile unsigned long *)0x40022020))
#define I2C2_MCLKOCNT_R     (*((volatile unsigned long *)0x40022024))
#define I2C2_MBMON_R        (*((volatile unsigned long *)0x4002202C))
#define I2C2_MCR2_R         (*((volatile unsigned long *)0x40022038))
/* I2C module 2 Slave Registers */
#define I2C2_SOAR_R         (*((volatile unsigned long *)0x40022800))
#define I2C2_SCSR_R         (*((volatile unsigned long *)0x40022804))
#define I2C2_SDR_R          (*((volatile unsigned long *)0x40022808))
#define I2C2_SIMR_R         (*((volatile unsigned long *)0x4002280C))
#define I2C2_SRIS_R         (*((volatile unsigned long *)0x40022810))
#define I2C2_SMIS_R         (*((volatile unsigned long *)0x40022814))
#define I2C2_SICR_R         (*((volatile unsigned long *)0x40022818))
#define I2C2_SOAR2_R        (*((volatile unsigned long *)0x4002281C))
#define I2C2_SACKCTL_R      (*((volatile unsigned long *)0x40022820))
#define I2C2_PP_R           (*((volatile unsigned long *)0x40022FC0))
#define I2C2_PC_R           (*((volatile unsigned long *)0x40022FC4))

/* I2C module 3 Master Registers */
#define I2C3_MSA_R          (*((volatile unsigned long *)0x40023000))
#define I2C3_MCS_R          (*((volatile unsigned long *)0x40023004))
#define I2C3_MDR_R          (*((volatile unsigned long *)0x40023008))
#define I2C3_MTPR_R         (*((volatile unsigned long *)0x4002300C))
#define I2C3_MIMR_R         (*((volatile unsigned long *)0x40023010))
#define I2C3_MRIS_R         (*((volatile unsigned long *)0x40023014))
#define I2C3_MMIS_R         (*((volatile unsigned long *)0x40023018))
#define I2C3_MICR_R         (*((volatile unsigned long *)0x4002301C))
#define I2C3_MCR_R          (*((volatile unsigned long *)0x40023020))
#define I2C3_MCLKOCNT_R     (*((volatile unsigned long *)0x40023024))
#define I2C3_MBMON_R        (*((volatile unsigned long *)0x4002302C))
#define I2C3_MCR2_R         (*((volatile unsigned long *)0x40023038))
/* I2C module 3 Slave Registers */
#define I2C3_SOAR_R         (*((volatile unsigned long *)0x40023800))
#define I2C3_SCSR_R         (*((volatile unsigned long *)0x40023804))
#define I2C3_SDR_R          (*((volatile unsigned long *)0x40023808))
#define I2C3_SIMR_R         (*((volatile unsigned long *)0x4002380C))
#define I2C3_SRIS_R         (*((volatile unsigned long *)0x40023810))
#define I2C3_SMIS_R         (*((volatile unsigned long *)0x40023814))
#define I2C3_SICR_R         (*((volatile unsigned long *)0x40023818))
#define I2C3_SOAR2_R        (*((volatile unsigned long *)0x4002381C))
#define I2C3_SACKCTL_R      (*((volatile unsigned long *)0x40023820))
#define I2C3_PP_R           (*((volatile unsigned long *)0x40023FC0))
#define I2C3_PC_R           (*((volatile unsigned long *)0x40023FC4))

/* I2C Base Registers */
#define I2C0_BASE_ADDERSS           0x40020000
#define I2C1_BASE_ADDERSS           0x40021000
#define I2C2_BASE_ADDERSS           0x40022000
#define I2C3_BASE_ADDERSS           0x40023000

/* Master Registers */
#define I2C_MSA_REG_OFFSET          0x000
#define I2C_MCS_REG_OFFSET          0x004
#define I2C_MDR_REG_OFFSET          0x008
#define I2C_MTPR_REG_OFFSET         0x00C
#define I2C_MIMR_REG_OFFSET         0x010
#define I2C_MRIS_REG_OFFSET         0x014
#define I2C_MMIS_REG_OFFSET         0x018
#define I2C_MICR_REG_OFFSET         0x01C
#define I2C_MCR_REG_OFFSET          0x020
#define I2C_MCLKOCNT_REG_OFFSET     0x024
#define I2C_MBMON_REG_OFFSET        0x02C
#define I2C_MCR2_REG_OFFSET         0x038

/* Slave Registers */
#define I2C_SOAR_REG_OFFSET         0x800
#define I2C_SCSR_REG_OFFSET         0x804
#define I2C_SDR_REG_OFFSET          0x808
#define I2C_SIMR_REG_OFFSET         0x80C
#define I2C_SRIS_REG_OFFSET         0x810
#define I2C_SMIS_REG_OFFSET         0x814
#define I2C_SICR_REG_OFFSET         0x818
#define I2C_SOAR2_REG_OFFSET        0x81C
#define I2C_SACKCTL_REG_OFFSET      0x820

#define I2C_MCS_BUSY_MASK           0
#define I2C_MCS_ERROR_MASK          1
#define I2C_MCS_ADRACK_MASK         2
#define I2C_MCS_DATACK_MASK         3
#define I2C_MCS_ARBLST_MASK         4
#define I2C_MCS_IDLE_MASK           5
#define I2C_MCS_BUSBSY_MASK         6
#define I2C_MCS_CLKTO_MASK          7


#define I2C_PP_REG_OFFSET           0xFC0
#define I2C_PC_REG_OFFSET           0xFC4



//*****************************************************************************
//
// UART registers (PWM)
//
//*****************************************************************************

#define PWM0_BASE_ADDERSS       0x40028000
#define PWM1_BASE_ADDERSS       0x40029000

#define PWM_CTL_OFFSET              0x000
#define PWM_SYNC_OFFSET             0x004
#define PWM_ENABLE_OFFSET           0x008
#define PWM_INVERT_OFFSET           0x00C
#define PWM_FAULT_OFFSET            0x010
#define PWM_INTEN_OFFSET            0x014
#define PWM_RIS_OFFSET              0x018
#define PWM_ISC_OFFSET              0x01C
#define PWM_STATUS_OFFSET           0x020
#define PWM_FAULTVAL_OFFSET         0x024
#define PWM_ENUPD_OFFSET            0x028

#define PWM_N_CTL_OFFSET                 0x040
#define PWM_N_INTEN_OFFSET               0x044
#define PWM_N_OFFSETIS_OFFSET            0x048
#define PWM_N_ISC_OFFSET                 0x04C
#define PWM_N_LOAD_OFFSET                0x050
#define PWM_N_COUNT_OFFSET               0x054
#define PWM_N_CMPA_OFFSET                0x058
#define PWM_N_CMPB_OFFSET                0x05C
#define PWM_N_GENA_OFFSET                0x060
#define PWM_N_GENB_OFFSET                0x064
#define PWM_N_DBCTL_OFFSET               0x068
#define PWM_N_DBRISE_OFFSET              0x06C
#define PWM_N_DBFALL_OFFSET              0x070
#define PWM_N_FLTSRC0_OFFSET             0x074
#define PWM_N_FLTSRC1_OFFSET             0x078
#define PWM_N_MINFLTPER_OFFSET           0x07C


//*****************************************************************************
//
// System Control registers (SYSCTL)
//
//*****************************************************************************

#define SYSCTL_RCGCPWM_R        0x400FE640
#define SYSCTL_RCC_REG_PWM      0x400FE060
#define SYSCTL_RCC2_REG_PWM     0x400FE070
#define SYSCTL_RCGCADC_BASE   0x400FE638

#define SYSCTL_RCGCI2C          (*((volatile uint32 *)0x400FE620))
#define SYSCTL_RCGCUART         (*((volatile uint32 *)0x400FE618))

//*****************************************************************************
//
// UART registers (PWM)
//
//*****************************************************************************
#define ADC0_BASE_ADDERSS       0x40038000
#define ADC1_BASE_ADDERSS       0x40039000

#define ADC_ACTSS_OFFSET    0x000
#define ADC_RIS_OFFSET      0x004
#define ADC_IM_OFFSET       0x008
#define ADC_ISC_OFFSET      0x00C
#define ADC_OSTAT_OFFSET    0x010
#define ADC_EMUX_OFFSET     0x014
#define ADC_USTAT_OFFSET    0x018
#define ADC_TSSEL_OFFSET    0x01C
#define ADC_SSPRI_OFFSET    0x020
#define ADC_SPC_OFFSET      0x024
#define ADC_PSSI_OFFSET     0x028
#define ADC_SAC_OFFSET      0x030
#define ADC_DCISC_OFFSET    0x034
#define ADC_CTL_OFFSET      0x038
#define ADC_SSMUXn_OFFSET   0x040
#define ADC_SSCTLn_OFFSET   0x044
#define ADC_SSFIFOn_OFFSET  0x048
#define ADC_SSFSTATn_OFFSET 0x04C
#define ADC_SSOPn_OFFSET    0x050
#define ADC_SSDCn_OFFSET    0x054
#define ADC_DCRIC_OFFSET    0xD00
#define ADC_DCCTL0_OFFSET   0xE00
#define ADC_DCCTL1_OFFSET   0xE04
#define ADC_DCCTL2_OFFSET   0xE08
#define ADC_DCCTL3_OFFSET   0xE0C
#define ADC_DCCTL4_OFFSET   0xE10
#define ADC_DCCTL5_OFFSET   0xE14
#define ADC_DCCTL6_OFFSET   0xE18
#define ADC_DCCTL7_OFFSET   0xE1C
#define ADC_DCCMP0_OFFSET   0xE40
#define ADC_DCCMP1_OFFSET   0xE44
#define ADC_DCCMP2_OFFSET   0xE48
#define ADC_DCCMP3_OFFSET   0xE4C
#define ADC_DCCMP4_OFFSET   0xE50
#define ADC_DCCMP5_OFFSET   0xE54
#define ADC_DCCMP6_OFFSET   0xE58
#define ADC_DCCMP7_OFFSET   0xE5C
#define ADC_PP_OFFSET       0xFC0
#define ADC_PC_OFFSET       0xFC4
#define ADC_CC_OFFSET       0xFC8

 #endif
