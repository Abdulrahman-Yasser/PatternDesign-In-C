/**********************************************************************************************************************
 *  FILE DESCRIPTION
  *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  UART.c
  *        \brief  UART Driver
  *
  *      \details  This file contains the static implementation of the driver
  *                  it contains all the function implementation logic
  *
  *
  *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "../inc/UART.h"
#include "../../Dynamic/inc/UART_Cfg.h"
#include "Std_Types.h"


#include "Mcu_Hw.h"
#include "CPU_resources.h"
#include "DataStructure/Queue/static/inc/Queue.h"

/**********************************************************************************************************************
 *  LOCAL VARIABLES
 *********************************************************************************************************************/
Queue_uint8_DYNAMIC_Type* UART_Queue_Buffer[8 * 2];

#define UART_Transmit_Buffer_Mask   1
#define UART_Receive_Buffer_Mask    0


/**********************************************************************************************************************
 *  LOCAL Functions Definition
 *********************************************************************************************************************/

static uint32 get_address(UART_ChannelType uart_n);

void uart_transmit_one_char(UART_ChannelType my_uart);
void uart_transmit_all_of_it(UART_ChannelType my_uart);
void uart_transmit_some_of_it(UART_ChannelType my_uart, uint8 num);

void uart_receive_one_char(UART_ChannelType my_uart);
void uart_receive_all_of_it(UART_ChannelType my_uart);
void uart_receive_some_of_it(UART_ChannelType my_uart, uint8 num);



void __attribute__((weak)) App_Uart0_Tx_CallBack(void);
void __attribute__((weak)) App_Uart0_Rx_CallBack(void);
void __attribute__((weak)) App_Uart1_Tx_CallBack(void);
void __attribute__((weak)) App_Uart1_Rx_CallBack(void);
void __attribute__((weak)) App_Uart2_Tx_CallBack(void);
void __attribute__((weak)) App_Uart2_Rx_CallBack(void);
void __attribute__((weak)) App_Uart3_Tx_CallBack(void);
void __attribute__((weak)) App_Uart3_Rx_CallBack(void);
void __attribute__((weak)) App_Uart4_Tx_CallBack(void);
void __attribute__((weak)) App_Uart4_Rx_CallBack(void);
void __attribute__((weak)) App_Uart5_Tx_CallBack(void);
void __attribute__((weak)) App_Uart5_Rx_CallBack(void);
void __attribute__((weak)) App_Uart6_Tx_CallBack(void);
void __attribute__((weak)) App_Uart6_Rx_CallBack(void);
void __attribute__((weak)) App_Uart7_Tx_CallBack(void);
void __attribute__((weak)) App_Uart7_Rx_CallBack(void);

/**********************************************************************************************************************
 *  LOCAL Functions Implementation
 *********************************************************************************************************************/

void uart_transmit_one_char(UART_ChannelType my_uart){
    uint32 base, Register_Check;
    uint8 data;
    base = get_address(my_uart);

    if(!(UART_Queue_Buffer[(2 * my_uart) + UART_Transmit_Buffer_Mask]->isEmpty(UART_Queue_Buffer[(2 * my_uart) + UART_Transmit_Buffer_Mask]))){

        do{
            Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        }while((Register_Check & (1 << UART_FR_TXFF_MASK) ));

        data = UART_Queue_Buffer[(2 * my_uart) + UART_Transmit_Buffer_Mask]->remove(UART_Queue_Buffer[(2 * my_uart) + UART_Transmit_Buffer_Mask]);
        REG_ORING_CASTING_POINTED((base + UART_DATA_REG_OFFSET),data);
    }
}

void uart_transmit_all_of_it(UART_ChannelType my_uart){
    uint32 base, Register_Check;
    uint8 data;
    base = get_address(my_uart);

    while(!(UART_Queue_Buffer[(2 * my_uart) + UART_Transmit_Buffer_Mask]->isEmpty(UART_Queue_Buffer[(2 * my_uart) + UART_Transmit_Buffer_Mask]))){
        do{
            Register_Check = (uint32)(*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        }while((Register_Check & (1 << UART_FR_TXFF_MASK) ));

        data = UART_Queue_Buffer[(2 * my_uart) + UART_Transmit_Buffer_Mask]->remove(UART_Queue_Buffer[(2 * my_uart) + UART_Transmit_Buffer_Mask]);
        REG_ORING_CASTING_POINTED((base + UART_DATA_REG_OFFSET),data);
    }
}

void uart_transmit_some_of_it(UART_ChannelType my_uart, uint8 num){
    uint32 base, Register_Check;
    uint8 data, i;
    base = get_address(my_uart);
    for(i = 0; i < num; i++){
        if(!(UART_Queue_Buffer[(2 * my_uart) + UART_Transmit_Buffer_Mask]->isEmpty(UART_Queue_Buffer[(2 * my_uart) + UART_Transmit_Buffer_Mask]))){
            do{
                Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
            }while((Register_Check & (1 << UART_FR_TXFF_MASK) ));

            data = UART_Queue_Buffer[(2 * my_uart) + UART_Transmit_Buffer_Mask]->remove(UART_Queue_Buffer[(2 * my_uart) + UART_Transmit_Buffer_Mask]);
            REG_ORING_CASTING_POINTED((base + UART_DATA_REG_OFFSET),data);
        }
    }
}


void uart_receive_one_char(UART_ChannelType my_uart){
    uint32 base, Register_Check;
    uint8 data;
    base = get_address(my_uart);

    /* it will FREEZ when it has an Empty FIFO */
    do{
        Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
    }while((Register_Check & (1 << UART_FR_RXFE_MASK) ));

    if(!UART_Queue_Buffer[(2 * my_uart) + UART_Receive_Buffer_Mask]->isFull(UART_Queue_Buffer[(2 * my_uart) + UART_Receive_Buffer_Mask])){
    }else{
        UART_Queue_Buffer[(2 * my_uart) + UART_Receive_Buffer_Mask]->remove(UART_Queue_Buffer[(2 * my_uart) + UART_Receive_Buffer_Mask]);
    }
    data = (*(volatile uint32 *)(base + UART_DATA_REG_OFFSET));
    UART_Queue_Buffer[(2 * my_uart) + UART_Receive_Buffer_Mask]->insert(UART_Queue_Buffer[(2 * my_uart) + UART_Receive_Buffer_Mask], data);
}

void uart_receive_all_of_it(UART_ChannelType my_uart){
    uint32 base, Register_Check;
    uint8 data;
    base = get_address(my_uart);

    /* it will stop when it has an Empty FIFO */
    Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
    while(!(Register_Check & (1 << UART_FR_RXFE_MASK) )){
        if(!UART_Queue_Buffer[(2 * my_uart) + UART_Receive_Buffer_Mask]->isFull(UART_Queue_Buffer[(2 * my_uart) + UART_Receive_Buffer_Mask])){
        }else{
            UART_Queue_Buffer[(2 * my_uart) + UART_Receive_Buffer_Mask]->remove(UART_Queue_Buffer[(2 * my_uart) + UART_Receive_Buffer_Mask]);
        }
        data = (*(volatile uint32 *)(base + UART_DATA_REG_OFFSET));
        UART_Queue_Buffer[(2 * my_uart) + UART_Receive_Buffer_Mask]->insert(UART_Queue_Buffer[(2 * my_uart) + UART_Receive_Buffer_Mask], data);
        Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
    }
}

void uart_receive_some_of_it(UART_ChannelType my_uart, uint8 num){
    uint32 base, Register_Check;
    uint8 data, i;
    base = get_address(my_uart);
    /* it will stop when it has an Empty FIFO */
    Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));

    for(i = 0; i < num; i++){
        if(!(UART_Queue_Buffer[(2 * my_uart) + UART_Receive_Buffer_Mask]->isFull(UART_Queue_Buffer[(2 * my_uart) + UART_Receive_Buffer_Mask]))){
            do{
                Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
            }while((Register_Check & (1 << UART_FR_RXFE_MASK) ));
            data = (*(volatile uint32 *)(base + UART_DATA_REG_OFFSET));
            UART_Queue_Buffer[(2 * my_uart) + UART_Receive_Buffer_Mask]->insert(UART_Queue_Buffer[(2 * my_uart) + UART_Receive_Buffer_Mask], data);
        }
    }
}

static uint32 get_address(UART_ChannelType uart_n){
    uint32 ptr ;
    switch(uart_n){
    case UART_NUM_0 :
        ptr = UART0_BASE_ADDRESS;
        break;
    case UART_NUM_1 :
        ptr = UART1_BASE_ADDRESS;
        break;
    case UART_NUM_2 :
        ptr = UART2_BASE_ADDRESS;
        break;
    case UART_NUM_3 :
        ptr = UART3_BASE_ADDRESS;
        break;
    case UART_NUM_4:
        ptr = UART4_BASE_ADDRESS;
        break;
    case UART_NUM_5 :
        ptr = UART5_BASE_ADDRESS;
        break;
    case UART_NUM_6 :
        ptr = UART6_BASE_ADDRESS;
        break;
    case UART_NUM_7 :
        ptr = UART7_BASE_ADDRESS;
        break;
    default:
        ptr = 0;
    }
    return ptr;
}


void __attribute__((weak)) App_Uart0_Tx_CallBack(void){ }
void __attribute__((weak)) App_Uart0_Rx_CallBack(void){ }
void __attribute__((weak)) App_Uart1_Tx_CallBack(void){ }
void __attribute__((weak)) App_Uart1_Rx_CallBack(void){ }
void __attribute__((weak)) App_Uart2_Tx_CallBack(void){ }
void __attribute__((weak)) App_Uart2_Rx_CallBack(void){ }
void __attribute__((weak)) App_Uart3_Tx_CallBack(void){ }
void __attribute__((weak)) App_Uart3_Rx_CallBack(void){ }
void __attribute__((weak)) App_Uart4_Tx_CallBack(void){ }
void __attribute__((weak)) App_Uart4_Rx_CallBack(void){ }
void __attribute__((weak)) App_Uart5_Tx_CallBack(void){ }
void __attribute__((weak)) App_Uart5_Rx_CallBack(void){ }
void __attribute__((weak)) App_Uart6_Tx_CallBack(void){ }
void __attribute__((weak)) App_Uart6_Rx_CallBack(void){ }
void __attribute__((weak)) App_Uart7_Tx_CallBack(void){ }
void __attribute__((weak)) App_Uart7_Rx_CallBack(void){ }

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void uart_init(void){
    uint8 i, j;
    uint32 ptr;
    uint32 k;
    float temp2;
    /*********************************
    *1)   Enable Clock to UART
    *       Registers : SYSCTL_RCGCUART
    *********************************/
    for(j = 0; j < UART_CONFIGURED_NUMBER; j++){
        ptr = get_address(UART_Container[j].uart_n);
        REG_ORING_ONE_BIT_NO_CASTING(SYSCTL_RCGCUART, (uint8)UART_Container[j].uart_n);
        /* For delay */
        k = (uint32)(*(volatile uint32 *)(SYSCTL_RCGCUART));


        /*********************************
        *2)   Disable the UART Before any initialization, not necessary but it's more safe
        *********************************/
        REG_CLEAR_CASTING_POINTED((ptr + UART_CTL_REG_OFFSET));


        /*********************************
        *3)   Initialize the Control Register that will contain most of the UART's Features
        *      Registers : UARTCTL  (UART CONTROL REGISTER)
        *********************************/

        // UART Works as Tx or Rx or both, with configuring HSE(High speed Enable) Flag
        switch(UART_Container[j].Uart_Mode){
        case UARTMode_Transmit:
            REG_CLEAR_ONE_BIT_CASTING_POINTED(ptr + UART_CTL_REG_OFFSET, 9);
            REG_ORING_ONE_BIT_CASTING_POINTED(ptr + UART_CTL_REG_OFFSET, 8);
            REG_CLEAR_ONE_BIT_CASTING_POINTED(ptr + UART_CTL_REG_OFFSET, 5);
            /* Initialize the Buffers for the UART */
            UART_Queue_Buffer[(2 * UART_Container[j].uart_n) + 1] = Queue_Create_DYNAMIC_uint8(30);   // Transmitting Buffer
            break;
        case UARTMode_Receive:
            REG_CLEAR_ONE_BIT_CASTING_POINTED(ptr + UART_CTL_REG_OFFSET, 8);
            REG_ORING_ONE_BIT_CASTING_POINTED(ptr + UART_CTL_REG_OFFSET, 9);
            REG_CLEAR_ONE_BIT_CASTING_POINTED(ptr + UART_CTL_REG_OFFSET, 5);
            /* Initialize the Buffers for the UART */
            UART_Queue_Buffer[2 * UART_Container[j].uart_n] = Queue_Create_DYNAMIC_uint8(30);       // Receiving Buffer
            break;
        case UARTMode_Transmit_Receive:
            REG_ORING_ONE_BIT_CASTING_POINTED(ptr + UART_CTL_REG_OFFSET, 8);
            REG_ORING_ONE_BIT_CASTING_POINTED(ptr + UART_CTL_REG_OFFSET, 9);
            REG_CLEAR_ONE_BIT_CASTING_POINTED(ptr + UART_CTL_REG_OFFSET, 5);
            /* Initialize the Buffers for the UART */
            UART_Queue_Buffer[(2 * UART_Container[j].uart_n) + 1] = Queue_Create_DYNAMIC_uint8(30);   // Transmitting Buffer
            UART_Queue_Buffer[2 * UART_Container[j].uart_n] = Queue_Create_DYNAMIC_uint8(30);       // Receiving Buffer
            break;
        case UARTMode_Transmit_HSE:
            REG_CLEAR_ONE_BIT_CASTING_POINTED(ptr + UART_CTL_REG_OFFSET, 9);
            REG_ORING_ONE_BIT_CASTING_POINTED(ptr + UART_CTL_REG_OFFSET, 8);
            REG_ORING_ONE_BIT_CASTING_POINTED(ptr + UART_CTL_REG_OFFSET, 5);
            /* Initialize the Buffers for the UART */
            UART_Queue_Buffer[(2 * UART_Container[j].uart_n) + 1] = Queue_Create_DYNAMIC_uint8(30);   // Transmitting Buffer
            break;
        case UARTMode_Receive_HSE:
            REG_CLEAR_ONE_BIT_CASTING_POINTED(ptr + UART_CTL_REG_OFFSET, 8);
            REG_ORING_ONE_BIT_CASTING_POINTED(ptr + UART_CTL_REG_OFFSET, 9);
            REG_ORING_ONE_BIT_CASTING_POINTED(ptr + UART_CTL_REG_OFFSET, 5);
            /* Initialize the Buffers for the UART */
            UART_Queue_Buffer[2 * UART_Container[j].uart_n] = Queue_Create_DYNAMIC_uint8(30);       // Receiving Buffer
            break;
        case UARTMode_Transmit_Receive_HSE:
            REG_ORING_ONE_BIT_CASTING_POINTED(ptr + UART_CTL_REG_OFFSET, 8);
            REG_ORING_ONE_BIT_CASTING_POINTED(ptr + UART_CTL_REG_OFFSET, 9);
            REG_ORING_ONE_BIT_CASTING_POINTED(ptr + UART_CTL_REG_OFFSET, 5);
            /* Initialize the Buffers for the UART */
            UART_Queue_Buffer[2 * UART_Container[j].uart_n] = Queue_Create_DYNAMIC_uint8(30);       // Receiving Buffer
            UART_Queue_Buffer[(2 * UART_Container[j].uart_n) + 1] = Queue_Create_DYNAMIC_uint8(30);   // Transmitting Buffer
            break;
        default :
            break;
        }

        // End of transmission Flag
        if(UART_Container[j].endOfTransmission == 0){
            REG_CLEAR_ONE_BIT_CASTING_POINTED(ptr + UART_CTL_REG_OFFSET, 4);
        }else if(UART_Container[j].endOfTransmission == 1){
            REG_ORING_ONE_BIT_CASTING_POINTED(ptr + UART_CTL_REG_OFFSET, 4);
        }

        /*********************************
         *4)    Writing the Baud-Rate for the register
         *      Integer Baud-Rate then the Fractional Baud-Rate
         *      Registers : UARTIBRD (UART Integer Baud-Rate Divisor)
         *                  UARTFBRD (UART Fractional Baud-Rate Divisor)
         *********************************/
        temp2 = ( (float)(CPU_CLOCK*1000000) / (float)(16 * UART_Container[j].BaudRate) );
        REG_CLEAR_CASTING_POINTED((ptr + UART_IBRD_REG_OFFSET));
        REG_ORING_CASTING_POINTED((ptr + UART_IBRD_REG_OFFSET), (uint32)temp2);
        temp2 = (float)temp2 - (uint32)temp2;
        temp2 = (float)(temp2 * 64 + 0.5);
        REG_CLEAR_CASTING_POINTED((ptr + UART_FBRD_REG_OFFSET));
        REG_ORING_CASTING_POINTED((ptr + UART_FBRD_REG_OFFSET), (uint32)temp2);

        /*********************************
         *5)   Dealing with Data-Length, Parity, StopBits and FIFO Enable
         *   Registers : UARTLCRH (UART Line Control)
         *********************************/
        switch(UART_Container[j].Data_Size){
        /* in case we will deal with 8-bit data, we write only in WLEN Bits */
        case UARTSize_EIGHT_BITS:
            REG_ORING_ONE_BIT_CASTING_POINTED(ptr + UART_LCRH_REG_OFFSET, 6);
            REG_ORING_ONE_BIT_CASTING_POINTED(ptr + UART_LCRH_REG_OFFSET, 5);
            break;
            /* in case we will deal with 7-bit data, we write only in WLEN Bits */
        case UARTSize_SEVEN_BITS:
            REG_ORING_ONE_BIT_CASTING_POINTED(ptr + UART_LCRH_REG_OFFSET, 6);
            REG_CLEAR_ONE_BIT_CASTING_POINTED(ptr + UART_LCRH_REG_OFFSET, 5);
            break;
            /* in case we will deal with 6-bit data, we write only in WLEN Bits */
        case UARTSize_SIX_BITS:
            REG_ORING_ONE_BIT_CASTING_POINTED(ptr + UART_LCRH_REG_OFFSET, 5);
            REG_CLEAR_ONE_BIT_CASTING_POINTED(ptr + UART_LCRH_REG_OFFSET, 6);
            break;
            /* in case we will deal with 5-bit data, we write only in WLEN Bits */
        case UARTSize_FIVE_BITS:
            REG_CLEAR_ONE_BIT_CASTING_POINTED(ptr + UART_LCRH_REG_OFFSET, 5);
            REG_CLEAR_ONE_BIT_CASTING_POINTED(ptr + UART_LCRH_REG_OFFSET, 6);
            break;
        default :
            break;
        }

        /*********************************
         *   Dealing with Parity Selection
         *********************************/
        if(UART_Container[j].parity == UARTParity_NO_PARITY){
            REG_CLEAR_ONE_BIT_CASTING_POINTED(ptr + UART_LCRH_REG_OFFSET, 1);
        }else if(UART_Container[j].parity == UARTParity_ODD){
            REG_ORING_ONE_BIT_CASTING_POINTED(ptr + UART_LCRH_REG_OFFSET, 1);
            REG_CLEAR_ONE_BIT_CASTING_POINTED(ptr + UART_LCRH_REG_OFFSET, 2);
        }else if(UART_Container[j].parity == UARTParity_EVEN){
            REG_ORING_ONE_BIT_CASTING_POINTED(ptr + UART_LCRH_REG_OFFSET, 1);
            REG_ORING_ONE_BIT_CASTING_POINTED(ptr + UART_LCRH_REG_OFFSET, 2);
        }

        /*********************************
         *   Dealing with Stop Bits
         *********************************/
        if(UART_Container[j].StopBits_Num == UARTSTOPBIT_ONE){
            REG_CLEAR_ONE_BIT_CASTING_POINTED(ptr + UART_LCRH_REG_OFFSET, 3);
        }else if(UART_Container[j].StopBits_Num == UARTSTOPBIT_TWO){
            REG_ORING_ONE_BIT_CASTING_POINTED(ptr + UART_LCRH_REG_OFFSET, 3);
        }

        /*********************************
         *   Dealing with the FIFO buffers
         *********************************/
        if(UART_Container[j].fifo_size_rx == UART_FIFO_NOTUSED && UART_Container[j].fifo_size_tx == UART_FIFO_NOTUSED){
            REG_CLEAR_ONE_BIT_CASTING_POINTED(ptr + UART_LCRH_REG_OFFSET, 4);
        }else{
            REG_ORING_ONE_BIT_CASTING_POINTED(ptr + UART_LCRH_REG_OFFSET, 4);
        }

        /*********************************
         *6)   Choose the FIFO buffers length
         *      Registers : UARTIFLS (UART Interrupt FIFO Level Select)
         *********************************/
        REG_CLEAR_CASTING_POINTED((ptr + UART_IFLS_REG_OFFSET));
        switch(UART_Container[j].fifo_size_tx){
        case UART_FIFO_NOTUSED:
        case UART_FIFO_7_8:
            break;
        case UART_FIFO_6_8:
            REG_ORING_CASTING_POINTED((ptr + UART_IFLS_REG_OFFSET),0x1);
            break;
        case UART_FIFO_4_8:
            REG_ORING_CASTING_POINTED((ptr + UART_IFLS_REG_OFFSET),0x2);
            break;
        case UART_FIFO_2_8:
            REG_ORING_CASTING_POINTED((ptr + UART_IFLS_REG_OFFSET),0x3);
            break;
        case UART_FIFO_1_8:
            REG_ORING_CASTING_POINTED((ptr + UART_IFLS_REG_OFFSET),0x4);
            break;
        default:
            break;
        }
        switch(UART_Container[j].fifo_size_rx){
        case UART_FIFO_NOTUSED:
        case UART_FIFO_1_8:
            break;
        case UART_FIFO_2_8:
            REG_ORING_CASTING_POINTED((ptr + UART_IFLS_REG_OFFSET),0x1 << 3);
            break;
        case UART_FIFO_4_8:
            REG_ORING_CASTING_POINTED((ptr + UART_IFLS_REG_OFFSET),0x2 << 3);
            break;
        case UART_FIFO_6_8:
            REG_ORING_CASTING_POINTED((ptr + UART_IFLS_REG_OFFSET),0x3 << 3);
            break;
        case UART_FIFO_7_8:
            REG_ORING_CASTING_POINTED((ptr + UART_IFLS_REG_OFFSET),0x4 << 3);
            break;
        default:
            break;
        }

        /*********************************
         *7)   Choose the Interrupt Mask
         *      Registers : UARTIM (UART Interrupt Mask)
         *********************************/
        for(i = 0; i < UART_ALLOWED_INTERRUPTS_NUMBER; i++){
            if(UART_Container[j].Uart_ISRMode[i] != UARTISRMode_None){
                REG_ORING_ONE_BIT_CASTING_POINTED(ptr + UART_IM_REG_OFFSET, UART_Container[j].Uart_ISRMode[i]);
            }
        }

        REG_ORING_ONE_BIT_CASTING_POINTED((ptr + UART_CTL_REG_OFFSET), 0);           //Enable UART

    }
    /*******************************************************
     * Pre-Defined UART
     *******************************************************/
#if UART0_PREDEF_MACRO == Enable
    /*  Enable the clock to it */
    ptr = (uint32)(*(volatile uint32 *)SYSCTL_RCGCUART);
    if(ptr & (1 << 0)){
        /* that could not be possible, we should use it either with predefined UART or a user-defined UART
         * so we going to shut it down to make a  . */
        REG_CLEAR_ONE_BIT_NO_CASTING(SYSCTL_RCGCUART, 0);
    }else{
        REG_ORING_ONE_BIT_NO_CASTING(SYSCTL_RCGCUART, 0);
        /* just for delay purpose */
        ptr = (uint32)(*(volatile uint32 *)SYSCTL_RCGCUART);
    }

    /*  Clear most of Registers from any value it may got from the previous initialization */
    REG_CLEAR_CASTING_POINTED((UART0_BASE_ADDRESS + UART_CTL_REG_OFFSET));
    REG_CLEAR_CASTING_POINTED((UART0_BASE_ADDRESS + UART_IFLS_REG_OFFSET));
    REG_CLEAR_CASTING_POINTED((UART0_BASE_ADDRESS + UART_IM_REG_OFFSET));
    REG_CLEAR_CASTING_POINTED((UART0_BASE_ADDRESS + UART_LCRH_REG_OFFSET));

    UART_Queue_Buffer[0] = Queue_Create_uint8(16);
    UART_Queue_Buffer[1] = Queue_Create_uint8(16);

    /* Rx Enable, Tx Enable, End-Of-Transmission Flag Enable,  */
    REG_ORING_CASTING_POINTED((UART0_BASE_ADDRESS + UART_CTL_REG_OFFSET), 0x310);

    /* 9600 Baud-Rate */
    REG_CLEAR_CASTING_POINTED((UART0_BASE_ADDRESS + UART_IBRD_REG_OFFSET));
    REG_ORING_CASTING_POINTED((UART0_BASE_ADDRESS + UART_IBRD_REG_OFFSET),104);
    REG_CLEAR_CASTING_POINTED((UART0_BASE_ADDRESS + UART_FBRD_REG_OFFSET));
    REG_ORING_CASTING_POINTED((UART0_BASE_ADDRESS + UART_FBRD_REG_OFFSET),11);

    /* 8-Bit Data-width, one stop bit, no parity check, Disable FIFO */
    REG_ORING_CASTING_POINTED((UART0_BASE_ADDRESS + UART_LCRH_REG_OFFSET), 0x60);

    REG_ORING_ONE_BIT_CASTING_POINTED((UART0_BASE_ADDRESS + UART_CTL_REG_OFFSET), 0);
#endif

#if UART1_PREDEF_MACRO == Enable
    /*  Enable the clock to it */
    ptr = (uint32)(*(volatile uint32 *)SYSCTL_RCGCUART);
    if(ptr & (1 << 1)){
        /* that could not be possible, we should use it either with predefined UART or a user-defined UART
         * so we going to shut it down to make a  . */
        REG_CLEAR_ONE_BIT_NO_CASTING(SYSCTL_RCGCUART, 1);
    }else{
        REG_ORING_ONE_BIT_NO_CASTING(SYSCTL_RCGCUART, 1);
        /* just for delay purpose */
        ptr = (uint32)(*(volatile uint32 *)SYSCTL_RCGCUART);
    }

    /*  Clear most of Registers from any value it may got from the previous initialization */
    REG_CLEAR_CASTING_POINTED((UART1_BASE_ADDRESS + UART_CTL_REG_OFFSET));
    REG_CLEAR_CASTING_POINTED((UART1_BASE_ADDRESS + UART_IFLS_REG_OFFSET));
    REG_CLEAR_CASTING_POINTED((UART1_BASE_ADDRESS + UART_IM_REG_OFFSET));
    REG_CLEAR_CASTING_POINTED((UART1_BASE_ADDRESS + UART_LCRH_REG_OFFSET));

    UART_Queue_Buffer[2] = Queue_Create_uint8(16);
    UART_Queue_Buffer[3] = Queue_Create_uint8(16);

    /* 8-Bit Data-width, one stop bit, no parity check, Enable FIFO */
    REG_ORING_CASTING_POINTED((UART1_BASE_ADDRESS + UART_LCRH_REG_OFFSET), 0x70);

    /* Rx Enable, Tx Enable, End-Of-Transmission Flag Disable,  */
    REG_ORING_CASTING_POINTED((UART1_BASE_ADDRESS + UART_CTL_REG_OFFSET), 0x300);

    /* FIFO Tx <= 14/16 empty,  Rx >= 14/16 empty*/
    REG_ORING_CASTING_POINTED((UART1_BASE_ADDRESS + UART_IFLS_REG_OFFSET), 0x4);
    REG_ORING_CASTING_POINTED((UART1_BASE_ADDRESS + UART_IFLS_REG_OFFSET), 0x0);

    /* 9600 Baud-Rate */
    REG_CLEAR_CASTING_POINTED((UART1_BASE_ADDRESS + UART_IBRD_REG_OFFSET));
    REG_ORING_CASTING_POINTED((UART1_BASE_ADDRESS + UART_IBRD_REG_OFFSET),104);
    REG_CLEAR_CASTING_POINTED((UART1_BASE_ADDRESS + UART_FBRD_REG_OFFSET));
    REG_ORING_CASTING_POINTED((UART1_BASE_ADDRESS + UART_FBRD_REG_OFFSET),11);

    /* Enable the UART to be ACTIVE */
    REG_ORING_ONE_BIT_CASTING_POINTED((UART1_BASE_ADDRESS + UART_CTL_REG_OFFSET), 0);
#endif

#if UART5_PREDEF_MACRO == Enable
    /*  Enable the clock to it */
    ptr = (uint32)(*(volatile uint32 *)SYSCTL_RCGCUART);
    if(ptr & (1 << 5)){
        /* that could not be possible, we should use it either with predefined UART or a user-defined UART
         * so we going to shut it down to make a  . */
        REG_CLEAR_ONE_BIT_NO_CASTING(SYSCTL_RCGCUART, 5);
    }else{
        REG_ORING_ONE_BIT_NO_CASTING(SYSCTL_RCGCUART, 5);
        /* just for delay purpose */
        ptr = (uint32)(*(volatile uint32 *)SYSCTL_RCGCUART);
    }

    /*  Clear most of Registers from any value it may got from the previous initialization */
    REG_CLEAR_CASTING_POINTED((UART5_BASE_ADDRESS + UART_CTL_REG_OFFSET));
    REG_CLEAR_CASTING_POINTED((UART5_BASE_ADDRESS + UART_IFLS_REG_OFFSET));
    REG_CLEAR_CASTING_POINTED((UART5_BASE_ADDRESS + UART_IM_REG_OFFSET));
    REG_CLEAR_CASTING_POINTED((UART5_BASE_ADDRESS + UART_LCRH_REG_OFFSET));

    UART_Queue_Buffer[10] = Queue_Create_uint8(50);
    UART_Queue_Buffer[11] = Queue_Create_uint8(50);

    /* Rx Enable, Tx Enable, End-Of-Transmission Flag Disable,  */
    REG_ORING_CASTING_POINTED((UART5_BASE_ADDRESS + UART_CTL_REG_OFFSET), 0x300);

    /* 9600 Baud-Rate */
    REG_CLEAR_CASTING_POINTED((UART5_BASE_ADDRESS + UART_IBRD_REG_OFFSET));
    REG_ORING_CASTING_POINTED((UART5_BASE_ADDRESS + UART_IBRD_REG_OFFSET),104);
    REG_CLEAR_CASTING_POINTED((UART5_BASE_ADDRESS + UART_FBRD_REG_OFFSET));
    REG_ORING_CASTING_POINTED((UART5_BASE_ADDRESS + UART_FBRD_REG_OFFSET),11);

    /* 8-Bit Data-width, one stop bit, no parity check, Enable FIFO */
    REG_ORING_CASTING_POINTED((UART5_BASE_ADDRESS + UART_LCRH_REG_OFFSET), 0x70);

    /* Rx Interrupt Disable, Tx Interrupt Disable */
    REG_ORING_CASTING_POINTED((UART5_BASE_ADDRESS + UART_IM_REG_OFFSET), 0x00);

    /* FIFO Disable */
    REG_ORING_CASTING_POINTED((UART5_BASE_ADDRESS + UART_IFLS_REG_OFFSET), 0x00);

    /* Enable UART */
    REG_ORING_ONE_BIT_CASTING_POINTED((UART5_BASE_ADDRESS + UART_CTL_REG_OFFSET), 0);
#endif
}


void UART_Poke_to_transmit(UART_ChannelType my_uart, uint8 Bytes_Cnt){
    if(Bytes_Cnt == 0){
        uart_transmit_all_of_it(my_uart);
    }else if(Bytes_Cnt == 1){
        uart_transmit_one_char(my_uart);
    }else{
        uart_transmit_some_of_it(my_uart, Bytes_Cnt);
    }
}

void UART_Poke_to_receive(UART_ChannelType my_uart, uint8 Bytes_Cnt){
    if(Bytes_Cnt == 0){
        uart_receive_all_of_it(my_uart);
    }else if(Bytes_Cnt == 1){
        uart_receive_one_char(my_uart);
    }else{
        uart_receive_some_of_it(my_uart, Bytes_Cnt);
    }
}

void UART_Push_to_Transmit(UART_ChannelType my_uart, uint8 x, uint8 must_be_pushed){
    if(must_be_pushed){
        /* it will be stuck here until the any ISR function remove an element to push it */
        while((UART_Queue_Buffer[(2 * my_uart) + UART_Transmit_Buffer_Mask]->isFull(UART_Queue_Buffer[(2 * my_uart) + UART_Transmit_Buffer_Mask]))){
//            UART_Poke_to_transmit(my_uart, UART_TRANSMIT_RECEIVE_ONE_CHAR);
        }
    }else{
        /* it will not push the element if the QUEUE is full, as simple as that */
        if(UART_Queue_Buffer[(2 * my_uart) + UART_Transmit_Buffer_Mask]->isFull(UART_Queue_Buffer[(2 * my_uart) + UART_Transmit_Buffer_Mask])){
            return;
        }
    }
    UART_Queue_Buffer[(2 * my_uart) + UART_Transmit_Buffer_Mask]->insert(UART_Queue_Buffer[(2 * my_uart) + UART_Transmit_Buffer_Mask], x);
}


void UART_Pop_the_Received(UART_ChannelType my_uart, uint8* data){
    uint8 i;
    for( i = 0; i < 100; i++){
        if(!UART_Queue_Buffer[(2 * my_uart) + UART_Receive_Buffer_Mask]->isEmpty(UART_Queue_Buffer[(2 * my_uart) + UART_Receive_Buffer_Mask])){
            data[i] = (uint8)(UART_Queue_Buffer[(2 * my_uart) + UART_Receive_Buffer_Mask]->remove(UART_Queue_Buffer[(2 * my_uart) + UART_Receive_Buffer_Mask]));
        }else{
            break;
        }
    }
}



extern void uart0_handler(void){
    uint32 base, Register_Check;
    base = UART0_BASE_ADDRESS;
    Register_Check = (*(volatile uint32 *)(base + UART_MIS_REG_OFFSET));

    if(Register_Check & (1 << UART_MIS_TX_MASK)){
        uart_transmit_one_char(UART_NUM_0);
        /* Clear the MIS Flag */
        UART0_TX_ISR_CALLBACK();
        REG_ORING_ONE_BIT_CASTING_POINTED((base + UART_ICR_REG_OFFSET), UART_MIS_TX_MASK);
    }else if(Register_Check & (1 << UART_MIS_RX_MASK)){
        uart_receive_one_char(UART_NUM_0);
        /* Clear the MIS Flag */
        UART0_RX_ISR_CALLBACK();
        REG_ORING_ONE_BIT_CASTING_POINTED((base + UART_ICR_REG_OFFSET), UART_MIS_RX_MASK);
    }
}

extern void uart1_handler(void){
    uint32 base, Register_Check;
    base = UART1_BASE_ADDRESS;
    Register_Check = (*(volatile uint32 *)(base + UART_MIS_REG_OFFSET));

    if(Register_Check & (1 << UART_MIS_TX_MASK)){
        uart_transmit_one_char(UART_NUM_1);
        /* Clear the MIS Flag */
        UART1_TX_ISR_CALLBACK();
        REG_ORING_ONE_BIT_CASTING_POINTED((base + UART_ICR_REG_OFFSET), UART_MIS_TX_MASK);
    }else if(Register_Check & (1 << UART_MIS_RX_MASK)){
        uart_receive_one_char(UART_NUM_1);
        /* Clear the MIS Flag */
        UART1_RX_ISR_CALLBACK();
        REG_ORING_ONE_BIT_CASTING_POINTED((base + UART_ICR_REG_OFFSET), UART_MIS_RX_MASK);
    }
}

extern void uart2_handler(void){
    uint32 base, Register_Check;
    base = UART2_BASE_ADDRESS;
    Register_Check = (*(volatile uint32 *)(base + UART_MIS_REG_OFFSET));

    if(Register_Check & (1 << UART_MIS_TX_MASK)){
        uart_transmit_one_char(UART_NUM_2);
        /* Clear the MIS Flag */
        UART2_TX_ISR_CALLBACK();
        REG_ORING_ONE_BIT_CASTING_POINTED((base + UART_ICR_REG_OFFSET), UART_MIS_TX_MASK);
    }else if(Register_Check & (1 << UART_MIS_RX_MASK)){
        uart_receive_one_char(UART_NUM_2);
        /* Clear the MIS Flag */
        UART2_RX_ISR_CALLBACK();
        REG_ORING_ONE_BIT_CASTING_POINTED((base + UART_ICR_REG_OFFSET), UART_MIS_RX_MASK);
    }
}

extern void uart3_handler(void){
    uint32 base, Register_Check;
    base = UART3_BASE_ADDRESS;
    Register_Check = (*(volatile uint32 *)(base + UART_MIS_REG_OFFSET));

    if(Register_Check & (1 << UART_MIS_TX_MASK)){
        uart_transmit_one_char(UART_NUM_3);
        /* Clear the MIS Flag */
        UART3_TX_ISR_CALLBACK();
        REG_ORING_ONE_BIT_CASTING_POINTED((base + UART_ICR_REG_OFFSET), UART_MIS_TX_MASK);
    }else if(Register_Check & (1 << UART_MIS_RX_MASK)){
        uart_receive_one_char(UART_NUM_3);
        /* Clear the MIS Flag */
        UART3_RX_ISR_CALLBACK();
        REG_ORING_ONE_BIT_CASTING_POINTED((base + UART_ICR_REG_OFFSET), UART_MIS_RX_MASK);
    }
}

extern void uart4_handler(void){
    uint32 base, Register_Check;
    base = UART4_BASE_ADDRESS;
    Register_Check = (*(volatile uint32 *)(base + UART_MIS_REG_OFFSET));

    if(Register_Check & (1 << UART_MIS_TX_MASK)){
        uart_transmit_one_char(UART_NUM_4);
        /* Clear the MIS Flag */
        UART4_TX_ISR_CALLBACK();
        REG_ORING_ONE_BIT_CASTING_POINTED((base + UART_ICR_REG_OFFSET), UART_MIS_TX_MASK);
    }else if(Register_Check & (1 << UART_MIS_RX_MASK)){
        uart_receive_one_char(UART_NUM_4);
        /* Clear the MIS Flag */
        UART4_RX_ISR_CALLBACK();
        REG_ORING_ONE_BIT_CASTING_POINTED((base + UART_ICR_REG_OFFSET), UART_MIS_RX_MASK);
    }
}

extern void uart5_handler(void){
    uint32 base, Register_Check;
    base = UART5_BASE_ADDRESS;
    Register_Check = (*(volatile uint32 *)(base + UART_MIS_REG_OFFSET));

    if(Register_Check & (1 << UART_MIS_TX_MASK)){
        uart_transmit_one_char(UART_NUM_5);
        /* Clear the MIS Flag */
        UART5_TX_ISR_CALLBACK();
        REG_ORING_ONE_BIT_CASTING_POINTED((base + UART_ICR_REG_OFFSET), UART_MIS_TX_MASK);
    }else if(Register_Check & (1 << UART_MIS_RX_MASK)){
        uart_transmit_one_char(UART_NUM_5);
        /* Clear the MIS Flag */
        UART5_RX_ISR_CALLBACK();
        REG_ORING_ONE_BIT_CASTING_POINTED((base + UART_ICR_REG_OFFSET), UART_MIS_RX_MASK);
    }
}

extern void uart6_handler(void){
    uint32 base, Register_Check;
    base = UART6_BASE_ADDRESS;
    Register_Check = (*(volatile uint32 *)(base + UART_MIS_REG_OFFSET));

    if(Register_Check & (1 << UART_MIS_TX_MASK)){
        uart_transmit_one_char(UART_NUM_6);
        /* Clear the MIS Flag */
        UART6_TX_ISR_CALLBACK();
        REG_ORING_ONE_BIT_CASTING_POINTED((base + UART_ICR_REG_OFFSET), UART_MIS_TX_MASK);
    }else if(Register_Check & (1 << UART_MIS_RX_MASK)){
        uart_receive_one_char(UART_NUM_6);
        /* Clear the MIS Flag */
        UART6_RX_ISR_CALLBACK();
        REG_ORING_ONE_BIT_CASTING_POINTED((base + UART_ICR_REG_OFFSET), UART_MIS_RX_MASK);
    }
}

extern void uart7_handler(void){
    uint32 base, Register_Check, FLAGS_Check;
    base = UART7_BASE_ADDRESS;
    Register_Check = (*(volatile uint32 *)(base + UART_MIS_REG_OFFSET));

    FLAGS_Check = (uint32)(*(volatile uint32 *)(base + UART_CTL_REG_OFFSET));

    if( (Register_Check & (1 << UART_MIS_TX_MASK ))){
        REG_ORING_ONE_BIT_CASTING_POINTED((base + UART_ICR_REG_OFFSET), UART_MIS_TX_MASK);
        UART7_TX_ISR_CALLBACK();
        if( (FLAGS_Check & (1 << 4)) ){
            uart_transmit_one_char(UART_NUM_7);
        }else{
            FLAGS_Check = (uint32)((*(volatile uint32 *)(base + UART_IFLS_REG_OFFSET)) & 0x07);
            switch(FLAGS_Check){
            case 0x4:
                /* Tx <= 1/8 */
                uart_transmit_some_of_it(UART_NUM_7, 2);
                break;
            case 0x3:
                /* Tx <= 1/4 */
                uart_transmit_some_of_it(UART_NUM_7, 4);
                break;
            case 0x2:
                /* Tx <= 1/2 */
                uart_transmit_some_of_it(UART_NUM_7, 8);
                break;
            case 0x1:
                /* Tx <= 3/4 */
                uart_transmit_some_of_it(UART_NUM_7, 12);
                break;
            case 0x0:
                /* Tx <= 7/8 */
                uart_transmit_some_of_it(UART_NUM_7, 14);
                break;
            }
        }
        UART7_TX_ISR_CALLBACK();
        /* Clear the MIS Flag */
    }else if(Register_Check & (1 << UART_MIS_RX_MASK)){
        uart_receive_one_char(UART_NUM_7);
        /* Clear the MIS Flag */
        UART7_RX_ISR_CALLBACK();
        REG_ORING_ONE_BIT_CASTING_POINTED((base + UART_ICR_REG_OFFSET), UART_MIS_RX_MASK);
    }
}



/**********************************************************************************************************************
 *  END OF FILE: UART.c
 *********************************************************************************************************************/



