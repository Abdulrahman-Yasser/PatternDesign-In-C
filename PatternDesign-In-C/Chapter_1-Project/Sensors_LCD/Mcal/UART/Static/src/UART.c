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

#include <Mcal/UART/Static/inc/UART.h>
#include <Mcal/UART/Dynamic/inc/UART_Cfg.h>
#include "../../../../Common/Std_Types.h"


#include "../../../../Common/Mcu_Hw.h"
#include "../../../../Common/CPU_resources.h"
#include "../../../../Common/DataStructure/Queue/static/inc/Queue.h"

/**********************************************************************************************************************
 *  LOCAL VARIABLES
 *********************************************************************************************************************/
Queue_uint8_Type* UART_Queue_Buffer[7 * 2];

Queue_uint8_Type* UART_Queue_Buffer_Predef[UART_CONFIGURED_PREDEF_NUMBER * 2];

#define UART_Transmit_Buffer_Mask    1
#define UART_Receive_Buffer_Mask     0

/**********************************************************************************************************************
 *  LOCAL Functions Definition
 *********************************************************************************************************************/

static uint32 get_address(UART_ChannelType uart_n);

void uart_transmit(UART_ChannelType my_uart);
void uart_receive(UART_ChannelType my_uart);


void uart_transmit_predef(UART_PredefUARTType uart_predef_arg);
void uart_receive_predef(UART_PredefUARTType uart_predef_arg);


/**********************************************************************************************************************
 *  LOCAL Functions Implementation
 *********************************************************************************************************************/

void uart_transmit(UART_ChannelType my_uart){
    uint32 base, Register_Check;
    uint8 data;
    base = get_address(my_uart);
    Register_Check = (*(volatile uint32 *)(base + UART_RIS_REG_OFFSET));

    // CAN WE CHECK ONLY USING THIS REGISTER ?

    if(Register_Check  & (1 << UART_MIS_TX_MASK)){
        /* it will stop when it has a Full FIFO */
        Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        while(! Register_Check & (1 << UART_FR_TXFF_MASK) ){
            if(!UART_Queue_Buffer[my_uart + UART_Transmit_Buffer_Mask]->isEmpty(UART_Queue_Buffer[my_uart + UART_Transmit_Buffer_Mask])){
                data = UART_Queue_Buffer[my_uart + UART_Transmit_Buffer_Mask]->remove(UART_Queue_Buffer[my_uart + UART_Transmit_Buffer_Mask]);
                REG_WRITE_32_BIT_PTR((base + UART_DATA_REG_OFFSET),data);
            }else{
                break;
            }
        }
    }
    /* Clear the MIS Flag */
    REG_WRITE_BIT_PTR((base + UART_ICR_REG_OFFSET), UART_MIS_TX_MASK);
}

void uart_receive(UART_ChannelType my_uart){
    uint32 base, Register_Check;
    uint8 data;
    base = get_address(my_uart);
    Register_Check = (*(volatile uint32 *)(base + UART_RIS_REG_OFFSET));

    // CAN WE CHECK ONLY USING THIS REGISTER ?

    if(Register_Check  & (1 << UART_MIS_RX_MASK)){
        /* it will stop when it has an Empty FIFO */
        Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        while(! Register_Check & (1 << UART_FR_RXFE_MASK) ){
            if(!UART_Queue_Buffer[my_uart + UART_Receive_Buffer_Mask]->isFull(UART_Queue_Buffer[my_uart + UART_Receive_Buffer_Mask])){
                data = (*(volatile uint32 *)(base + UART_DATA_REG_OFFSET));
                UART_Queue_Buffer[my_uart + UART_Receive_Buffer_Mask]->insert(UART_Queue_Buffer[my_uart + UART_Receive_Buffer_Mask], data);
            }else{
                break;
            }
        }
    }
    /* Clear the MIS Flag */
    REG_WRITE_BIT_PTR((base + UART_ICR_REG_OFFSET), UART_MIS_RX_MASK);
}

void uart_transmit_predef(UART_PredefUARTType uart_predef_arg){
    uint32 base, Register_Check;
    uint8 data;
    switch(uart_predef_arg){
    case UART0_PREDEF_enum:
        base = UART0_BASE_ADDRESS;
        break;
    case UART1_PREDEF_enum:
        base = UART1_BASE_ADDRESS;
        break;
    case UART5_PREDEF_enum:
        base = UART5_BASE_ADDRESS;
        break;
    }
    Register_Check = (*(volatile uint32 *)(base + UART_RIS_REG_OFFSET));

    // CAN WE CHECK ONLY USING THIS REGISTER ?

    if(Register_Check  & (1 << UART_MIS_TX_MASK)){
        /* it will stop when it has a Full FIFO */
        Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        while(! Register_Check & (1 << UART_FR_TXFF_MASK) ){
            if(!UART_Queue_Buffer_Predef[uart_predef_arg + UART_Transmit_Buffer_Mask]->isEmpty(UART_Queue_Buffer_Predef[uart_predef_arg + UART_Transmit_Buffer_Mask])){
                data = UART_Queue_Buffer_Predef[uart_predef_arg + UART_Transmit_Buffer_Mask]->remove(UART_Queue_Buffer_Predef[uart_predef_arg + UART_Transmit_Buffer_Mask]);
                REG_WRITE_32_BIT_PTR((base + UART_DATA_REG_OFFSET),data);
            }else{
                break;
            }
        }
    }
    /* Clear the MIS Flag */
    REG_WRITE_BIT_PTR((base + UART_ICR_REG_OFFSET), UART_MIS_TX_MASK);
}

void uart_receive_predef(UART_PredefUARTType uart_predef_arg){
    uint32 base, Register_Check;
    uint8 data;
    switch(uart_predef_arg){
    case UART0_PREDEF_enum:
        base = UART0_BASE_ADDRESS;
        break;
    case UART1_PREDEF_enum:
        base = UART1_BASE_ADDRESS;
        break;
    case UART5_PREDEF_enum:
        base = UART5_BASE_ADDRESS;
        break;
    }
    Register_Check = (*(volatile uint32 *)(base + UART_RIS_REG_OFFSET));

    // CAN WE CHECK ONLY USING THIS REGISTER ?

    if(Register_Check  & (1 << UART_MIS_RX_MASK)){
        /* it will stop when it has an Empty FIFO */
        Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        while(! Register_Check & (1 << UART_FR_RXFE_MASK) ){
            if(!UART_Queue_Buffer_Predef[uart_predef_arg + UART_Receive_Buffer_Mask]->isFull(UART_Queue_Buffer_Predef[uart_predef_arg + UART_Receive_Buffer_Mask])){
                data = (*(volatile uint32 *)(base + UART_DATA_REG_OFFSET));
                UART_Queue_Buffer_Predef[uart_predef_arg + UART_Receive_Buffer_Mask]->insert(UART_Queue_Buffer_Predef[uart_predef_arg + UART_Receive_Buffer_Mask], data);
            }else{
                break;
            }
        }
    }
    /* Clear the MIS Flag */
    REG_WRITE_BIT_PTR((base + UART_ICR_REG_OFFSET), UART_MIS_RX_MASK);
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
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void uart_init(void){
    uint8 i, j;
    uint32 ptr;
    float temp2;
    /*********************************
    *1)   Enable Clock to UART
    *       Registers : SYSCTL_RCGCUART
    *********************************/
    for(j = 0; j < UART_CONFIGURED_NUMBER; j++){
        REG_WRITE_BIT(SYSCTL_RCGCUART, (uint8)UART_Container[j].uart_n);


        /*********************************
        *2)   Disable the UART Before any initialization, not necessary but it's more safe
        *********************************/
        REG_CLEAR_32_BIT_PTR((ptr + UART_CTL_REG_OFFSET));


        /*********************************
        *3)   Initialize the Control Register that will contain most of the UART's Features
        *      Registers : UARTCTL  (UART CONTROL REGISTER)
        *********************************/

        // UART Works as Tx or Rx or both, with configuring HSE(High speed Enable) Flag
        switch(UART_Container[j].Uart_Mode){
        case UARTMode_Transmit:
            REG_CLEAR_BIT_PTR(ptr + UART_CTL_REG_OFFSET, 9);
            REG_WRITE_BIT_PTR(ptr + UART_CTL_REG_OFFSET, 8);
            REG_CLEAR_BIT_PTR(ptr + UART_CTL_REG_OFFSET, 5);
            /* Initialize the Buffers for the UART */
            UART_Queue_Buffer[j + 1] = Queue_Create_uint8(8);   // Transmitting Buffer
            break;
        case UARTMode_Receive:
            REG_CLEAR_BIT_PTR(ptr + UART_CTL_REG_OFFSET, 8);
            REG_WRITE_BIT_PTR(ptr + UART_CTL_REG_OFFSET, 9);
            REG_CLEAR_BIT_PTR(ptr + UART_CTL_REG_OFFSET, 5);
            /* Initialize the Buffers for the UART */
            UART_Queue_Buffer[j] = Queue_Create_uint8(8);       // Receiving Buffer
            break;
        case UARTMode_Transmit_Receive:
            REG_WRITE_BIT_PTR(ptr + UART_CTL_REG_OFFSET, 8);
            REG_WRITE_BIT_PTR(ptr + UART_CTL_REG_OFFSET, 9);
            REG_CLEAR_BIT_PTR(ptr + UART_CTL_REG_OFFSET, 5);
            /* Initialize the Buffers for the UART */
            UART_Queue_Buffer[j] = Queue_Create_uint8(8);       // Receiving Buffer
            UART_Queue_Buffer[j + 1] = Queue_Create_uint8(8);   // Transmitting Buffer
            break;
        case UARTMode_Transmit_HSE:
            REG_CLEAR_BIT_PTR(ptr + UART_CTL_REG_OFFSET, 9);
            REG_WRITE_BIT_PTR(ptr + UART_CTL_REG_OFFSET, 8);
            REG_WRITE_BIT_PTR(ptr + UART_CTL_REG_OFFSET, 5);
            /* Initialize the Buffers for the UART */
            UART_Queue_Buffer[j + 1] = Queue_Create_uint8(8);   // Transmitting Buffer
            break;
        case UARTMode_Receive_HSE:
            REG_CLEAR_BIT_PTR(ptr + UART_CTL_REG_OFFSET, 8);
            REG_WRITE_BIT_PTR(ptr + UART_CTL_REG_OFFSET, 9);
            REG_WRITE_BIT_PTR(ptr + UART_CTL_REG_OFFSET, 5);
            /* Initialize the Buffers for the UART */
            UART_Queue_Buffer[j] = Queue_Create_uint8(8);       // Receiving Buffer
            break;
        case UARTMode_Transmit_Receive_HSE:
            REG_WRITE_BIT_PTR(ptr + UART_CTL_REG_OFFSET, 8);
            REG_WRITE_BIT_PTR(ptr + UART_CTL_REG_OFFSET, 9);
            REG_WRITE_BIT_PTR(ptr + UART_CTL_REG_OFFSET, 5);
            /* Initialize the Buffers for the UART */
            UART_Queue_Buffer[j] = Queue_Create_uint8(8);       // Receiving Buffer
            UART_Queue_Buffer[j + 1] = Queue_Create_uint8(8);   // Transmitting Buffer
            break;
        default :
            break;
        }

        // End of transmission Flag
        if(UART_Container[j].endOfTransmission == 0){
            REG_CLEAR_BIT_PTR(ptr + UART_CTL_REG_OFFSET, 4);
        }else if(UART_Container[j].endOfTransmission == 1){
            REG_WRITE_BIT_PTR(ptr + UART_CTL_REG_OFFSET, 4);
        }

        /*********************************
         *4)    Writing the Baud-Rate for the register
         *      Integer Baud-Rate then the Fractional Baud-Rate
         *      Registers : UARTIBRD (UART Integer Baud-Rate Divisor)
         *                  UARTFBRD (UART Fractional Baud-Rate Divisor)
         *********************************/
        temp2 = ( (float)(CPU_CLOCK*1000000) / (float)(16 * UART_Container[j].BaudRate) );
        REG_CLEAR_32_BIT_PTR((ptr + UART_IBRD_REG_OFFSET));
        REG_WRITE_32_BIT_PTR((ptr + UART_IBRD_REG_OFFSET), (uint32)temp2);
        temp2 = (float)temp2 - (uint32)temp2;
        temp2 = (float)(temp2 * 64 + 0.5);
        REG_CLEAR_32_BIT_PTR((ptr + UART_FBRD_REG_OFFSET));
        REG_WRITE_32_BIT_PTR((ptr + UART_FBRD_REG_OFFSET), (uint32)temp2);

        /*********************************
         *5)   Dealing with Data-Length, Parity, StopBits and FIFO Enable
         *   Registers : UARTLCRH (UART Line Control)
         *********************************/
        switch(UART_Container[j].Data_Size){
        /* in case we will deal with 8-bit data, we write only in WLEN Bits */
        case UARTSize_EIGHT_BITS:
            REG_WRITE_BIT_PTR(ptr + UART_LCRH_REG_OFFSET, 6);
            REG_WRITE_BIT_PTR(ptr + UART_LCRH_REG_OFFSET, 5);
            break;
            /* in case we will deal with 7-bit data, we write only in WLEN Bits */
        case UARTSize_SEVEN_BITS:
            REG_WRITE_BIT_PTR(ptr + UART_LCRH_REG_OFFSET, 6);
            REG_CLEAR_BIT_PTR(ptr + UART_LCRH_REG_OFFSET, 5);
            break;
            /* in case we will deal with 6-bit data, we write only in WLEN Bits */
        case UARTSize_SIX_BITS:
            REG_WRITE_BIT_PTR(ptr + UART_LCRH_REG_OFFSET, 5);
            REG_CLEAR_BIT_PTR(ptr + UART_LCRH_REG_OFFSET, 6);
            break;
            /* in case we will deal with 5-bit data, we write only in WLEN Bits */
        case UARTSize_FIVE_BITS:
            REG_CLEAR_BIT_PTR(ptr + UART_LCRH_REG_OFFSET, 5);
            REG_CLEAR_BIT_PTR(ptr + UART_LCRH_REG_OFFSET, 6);
            break;
        default :
            break;
        }

        /*********************************
         *   Dealing with Parity Selection
         *********************************/
        if(UART_Container[j].parity == UARTParity_NO_PARITY){
            REG_CLEAR_BIT_PTR(ptr + UART_LCRH_REG_OFFSET, 1);
        }else if(UART_Container[j].parity == UARTParity_ODD){
            REG_WRITE_BIT_PTR(ptr + UART_LCRH_REG_OFFSET, 1);
            REG_CLEAR_BIT_PTR(ptr + UART_LCRH_REG_OFFSET, 2);
        }else if(UART_Container[j].parity == UARTParity_EVEN){
            REG_WRITE_BIT_PTR(ptr + UART_LCRH_REG_OFFSET, 1);
            REG_WRITE_BIT_PTR(ptr + UART_LCRH_REG_OFFSET, 2);
        }

        /*********************************
         *   Dealing with Stop Bits
         *********************************/
        if(UART_Container[j].StopBits_Num == UARTSTOPBIT_ONE){
            REG_CLEAR_BIT_PTR(ptr + UART_LCRH_REG_OFFSET, 3);
        }else if(UART_Container[j].StopBits_Num == UARTSTOPBIT_TWO){
            REG_WRITE_BIT_PTR(ptr + UART_LCRH_REG_OFFSET, 3);
        }

        /*********************************
         *   Dealing with the FIFO buffers
         *********************************/
        if(UART_Container[j].fifo_size_rx == UART_FIFO_NOTUSED && UART_Container[j].fifo_size_tx == UART_FIFO_NOTUSED){
            REG_CLEAR_BIT_PTR(ptr + UART_LCRH_REG_OFFSET, 4);
        }else{
            REG_WRITE_BIT_PTR(ptr + UART_LCRH_REG_OFFSET, 4);
        }

        /*********************************
         *6)   Choose the FIFO buffers length
         *      Registers : UARTIFLS (UART Interrupt FIFO Level Select)
         *********************************/
        switch(UART_Container[j].fifo_size_tx){
        case UART_FIFO_NOTUSED:
        case UART_FIFO_1_8:
            break;
        case UART_FIFO_2_8:
            REG_WRITE_32_BIT_PTR((ptr + UART_IFLS_REG_OFFSET),0x1);
            break;
        case UART_FIFO_4_8:
            REG_WRITE_32_BIT_PTR((ptr + UART_IFLS_REG_OFFSET),0x2);
            break;
        case UART_FIFO_6_8:
            REG_WRITE_32_BIT_PTR((ptr + UART_IFLS_REG_OFFSET),0x3);
            break;
        case UART_FIFO_7_8:
            REG_WRITE_32_BIT_PTR((ptr + UART_IFLS_REG_OFFSET),0x4);
            break;
        default:
            break;
        }
        switch(UART_Container[j].fifo_size_rx){
        case UART_FIFO_NOTUSED:
        case UART_FIFO_1_8:
            break;
        case UART_FIFO_2_8:
            REG_WRITE_32_BIT_PTR((ptr + UART_IFLS_REG_OFFSET),0x1 << 3);
            break;
        case UART_FIFO_4_8:
            REG_WRITE_32_BIT_PTR((ptr + UART_IFLS_REG_OFFSET),0x2 << 3);
            break;
        case UART_FIFO_6_8:
            REG_WRITE_32_BIT_PTR((ptr + UART_IFLS_REG_OFFSET),0x3 << 3);
            break;
        case UART_FIFO_7_8:
            REG_WRITE_32_BIT_PTR((ptr + UART_IFLS_REG_OFFSET),0x4 << 3);
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
                REG_WRITE_BIT_PTR(ptr + UART_IM_REG_OFFSET, UART_Container[j].Uart_ISRMode[i]);
            }
        }

        REG_WRITE_BIT_PTR((ptr + UART_CTL_REG_OFFSET), 0);           //Enable UART

    }
    /*******************************************************
     * Pre-Defined UART
     *******************************************************/
#if UART0_PREDEF_MACRO == Enable
    /*  Enable the clock to it */
    REG_WRITE_BIT(SYSCTL_RCGCUART, 0);

    /*  Clear most of Registers from any value it may got from the previous initialization */
    REG_CLEAR_32_BIT_PTR((UART0_BASE_ADDRESS + UART_CTL_REG_OFFSET));
    REG_CLEAR_32_BIT_PTR((UART0_BASE_ADDRESS + UART_IFLS_REG_OFFSET));
    REG_CLEAR_32_BIT_PTR((UART0_BASE_ADDRESS + UART_IM_REG_OFFSET));
    REG_CLEAR_32_BIT_PTR((UART0_BASE_ADDRESS + UART_LCRH_REG_OFFSET));

    UART_Queue_Buffer_Predef[0] = Queue_Create_uint8(16);
    UART_Queue_Buffer_Predef[1] = Queue_Create_uint8(16);

    /* 8-Bit Data-width, one stop bit, no parity check, Disable FIFO */
    REG_WRITE_32_BIT_PTR((UART0_BASE_ADDRESS + UART_LCRH_REG_OFFSET), 0x60);

    /* Rx Enable, Tx Enable, End-Of-Transmission Flag Enable,  */
    REG_WRITE_32_BIT_PTR((UART0_BASE_ADDRESS + UART_CTL_REG_OFFSET), 0x310);

    /* 9600 Baud-Rate */
    REG_CLEAR_32_BIT_PTR((UART0_BASE_ADDRESS + UART_IBRD_REG_OFFSET));
    REG_WRITE_32_BIT_PTR((UART0_BASE_ADDRESS + UART_IBRD_REG_OFFSET),104);
    REG_CLEAR_32_BIT_PTR((UART0_BASE_ADDRESS + UART_FBRD_REG_OFFSET));
    REG_WRITE_32_BIT_PTR((UART0_BASE_ADDRESS + UART_FBRD_REG_OFFSET),11);

    REG_WRITE_BIT_PTR((UART0_BASE_ADDRESS + UART_CTL_REG_OFFSET), 0);
#endif

#if UART1_PREDEF_MACRO == Enable
    /*  Enable the clock to it */
    REG_WRITE_BIT(SYSCTL_RCGCUART, 1);

    /*  Clear most of Registers from any value it may got from the previous initialization */
    REG_CLEAR_32_BIT_PTR((UART1_BASE_ADDRESS + UART_CTL_REG_OFFSET));
    REG_CLEAR_32_BIT_PTR((UART1_BASE_ADDRESS + UART_IFLS_REG_OFFSET));
    REG_CLEAR_32_BIT_PTR((UART1_BASE_ADDRESS + UART_IM_REG_OFFSET));
    REG_CLEAR_32_BIT_PTR((UART1_BASE_ADDRESS + UART_LCRH_REG_OFFSET));

    UART_Queue_Buffer_Predef[2] = Queue_Create_uint8(16);
    UART_Queue_Buffer_Predef[3] = Queue_Create_uint8(16);

    /* 8-Bit Data-width, one stop bit, no parity check, Enable FIFO */
    REG_WRITE_32_BIT_PTR((UART1_BASE_ADDRESS + UART_LCRH_REG_OFFSET), 0x70);

    /* Rx Enable, Tx Enable, End-Of-Transmission Flag Disable,  */
    REG_WRITE_32_BIT_PTR((UART1_BASE_ADDRESS + UART_CTL_REG_OFFSET), 0x300);

    /* FIFO Tx <= 14/16 empty,  Rx >= 14/16 empty*/
    REG_WRITE_32_BIT_PTR((UART1_BASE_ADDRESS + UART_IFLS_REG_OFFSET), 0x4);
    REG_WRITE_32_BIT_PTR((UART1_BASE_ADDRESS + UART_IFLS_REG_OFFSET), 0x0);

    /* 9600 Baud-Rate */
    REG_CLEAR_32_BIT_PTR((UART1_BASE_ADDRESS + UART_IBRD_REG_OFFSET));
    REG_WRITE_32_BIT_PTR((UART1_BASE_ADDRESS + UART_IBRD_REG_OFFSET),104);
    REG_CLEAR_32_BIT_PTR((UART1_BASE_ADDRESS + UART_FBRD_REG_OFFSET));
    REG_WRITE_32_BIT_PTR((UART1_BASE_ADDRESS + UART_FBRD_REG_OFFSET),11);

    /* Enable the UART to be ACTIVE */
    REG_WRITE_BIT_PTR((UART1_BASE_ADDRESS + UART_CTL_REG_OFFSET), 0);
#endif

#if UART5_PREDEF_MACRO == Enable
    /*  Enable the clock to it */
    REG_WRITE_BIT(SYSCTL_RCGCUART, 5);

    /*  Clear most of Registers from any value it may got from the previous initialization */
    REG_CLEAR_32_BIT_PTR((UART5_BASE_ADDRESS + UART_CTL_REG_OFFSET));
    REG_CLEAR_32_BIT_PTR((UART5_BASE_ADDRESS + UART_IFLS_REG_OFFSET));
    REG_CLEAR_32_BIT_PTR((UART5_BASE_ADDRESS + UART_IM_REG_OFFSET));
    REG_CLEAR_32_BIT_PTR((UART5_BASE_ADDRESS + UART_LCRH_REG_OFFSET));

    UART_Queue_Buffer_Predef[4] = Queue_Create_uint8(16);
    UART_Queue_Buffer_Predef[5] = Queue_Create_uint8(16);

    /* 8-Bit Data-width, one stop bit, no parity check, Disable FIFO */
    REG_WRITE_32_BIT_PTR((UART5_BASE_ADDRESS + UART_LCRH_REG_OFFSET), 0x60);

    /* Rx Enable, Tx Enable, End-Of-Transmission Flag Enable,  */
    REG_WRITE_32_BIT_PTR((UART5_BASE_ADDRESS + UART_CTL_REG_OFFSET), 0x310);

    /* Rx Interrupt Enable, Tx Interrupt Enable */
    REG_WRITE_32_BIT_PTR((UART5_BASE_ADDRESS + UART_IM_REG_OFFSET), 0x30);

    /* 9600 Baud-Rate */
    REG_CLEAR_32_BIT_PTR((UART5_BASE_ADDRESS + UART_IBRD_REG_OFFSET));
    REG_WRITE_32_BIT_PTR((UART5_BASE_ADDRESS + UART_IBRD_REG_OFFSET),104);
    REG_CLEAR_32_BIT_PTR((UART5_BASE_ADDRESS + UART_FBRD_REG_OFFSET));
    REG_WRITE_32_BIT_PTR((UART5_BASE_ADDRESS + UART_FBRD_REG_OFFSET),11);

    REG_WRITE_BIT_PTR((UART5_BASE_ADDRESS + UART_CTL_REG_OFFSET), 0);
#endif
}


void Poke_to_transmit(UART_ChannelType my_uart){
    uart_transmit(my_uart);
}


void Push_to_Transmit(UART_ChannelType my_uart, uint8 x){
    if(!UART_Queue_Buffer[my_uart + UART_Transmit_Buffer_Mask]->isFull(UART_Queue_Buffer[my_uart + UART_Transmit_Buffer_Mask])){
        UART_Queue_Buffer[my_uart + UART_Transmit_Buffer_Mask]->insert(UART_Queue_Buffer[my_uart + UART_Transmit_Buffer_Mask], x);
    }
}
void Pop_the_Received(UART_ChannelType my_uart, uint8* data){
    uint8 i;
    for( i = 0; i < 100; i++){
        if(!UART_Queue_Buffer[my_uart + UART_Receive_Buffer_Mask]->isEmpty(UART_Queue_Buffer[my_uart + UART_Receive_Buffer_Mask])){
            data[i] = (uint8)(UART_Queue_Buffer[my_uart + UART_Receive_Buffer_Mask]->remove(UART_Queue_Buffer[my_uart + UART_Receive_Buffer_Mask]));
        }else{
            break;
        }
    }
}

void Push_to_Transmit_predef(UART_PredefUARTType uart_predef_arg, uint8 x){
    if(!UART_Queue_Buffer_Predef[uart_predef_arg + UART_Transmit_Buffer_Mask]->isFull(UART_Queue_Buffer_Predef[uart_predef_arg + UART_Transmit_Buffer_Mask])){
        UART_Queue_Buffer_Predef[uart_predef_arg + UART_Transmit_Buffer_Mask]->insert(UART_Queue_Buffer_Predef[uart_predef_arg + UART_Transmit_Buffer_Mask], x);
    }
}
void Pop_the_Received_predef(UART_PredefUARTType uart_predef_arg, uint8* data){
    uint8 i;
    for(i = 0; i < 100; i++){
        if(!UART_Queue_Buffer_Predef[uart_predef_arg + UART_Receive_Buffer_Mask]->isEmpty(UART_Queue_Buffer_Predef[uart_predef_arg + UART_Receive_Buffer_Mask])){
            data[i] = UART_Queue_Buffer_Predef[uart_predef_arg + UART_Receive_Buffer_Mask]->remove(UART_Queue_Buffer_Predef[uart_predef_arg + UART_Receive_Buffer_Mask]);
        }else{
            break;
        }
    }
}

extern void uart0_handler(void){
    uint32 base, Register_Check;
    uint8 data;
    base = UART0_BASE_ADDRESS;
    Register_Check = (*(volatile uint32 *)(base + UART_IM_REG_OFFSET));

    if(Register_Check & (1 << UART_MIS_TX_MASK)){
        /* Transmitting data */
        /* Reading the Flag and check if the FIFO is available to transmit and stop when it's full */
        Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        while( !Register_Check & (1 << UART_FR_TXFF_MASK)){
            if(!UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 0]->isEmpty(UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 0]) ){
                /* there is some data to be send */
                data = UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 0]->remove(UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 0]);
                REG_WRITE_32_BIT_PTR((base + UART_DATA_REG_OFFSET),data);
            }else{
                /* there is no data to be send */
                break;
            }
            /* Reading the Flag and check if the FIFO is available to transmit */
            Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        }
        /* Clear the MIS Flag */
        REG_WRITE_BIT_PTR((base + UART_ICR_REG_OFFSET), UART_MIS_TX_MASK);
    }else if(Register_Check & (1 << UART_MIS_RX_MASK)){
        /* Receiving data */
        /* Reading the Flag and check if the FIFO is available to Receive and stop when it's empty */
        Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        while( !Register_Check & (1 << UART_FR_RXFE_MASK)){
            /* Receive the data in the buffer even if the buffer is full */
            if(!UART_Queue_Buffer[UART_Receive_Buffer_Mask + 0]->isFull(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 0]) ){
                REG_WRITE_32_BIT_PTR((base + UART_DATA_REG_OFFSET),data);
                UART_Queue_Buffer[UART_Receive_Buffer_Mask + 0]->insert(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 0], data);
            }else{
                UART_Queue_Buffer[UART_Receive_Buffer_Mask + 0]->remove(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 0]);
                REG_WRITE_32_BIT_PTR((base + UART_DATA_REG_OFFSET),data);
                UART_Queue_Buffer[UART_Receive_Buffer_Mask + 0]->insert(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 0], data);
            }
            /* Reading the Flag and check if the FIFO is available to receive */
            Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        }

        /* Clear the MIS Flag */
        REG_WRITE_BIT_PTR((base + UART_ICR_REG_OFFSET), UART_MIS_RX_MASK);
    }
}

extern void uart1_handler(void){
    uint32 base, Register_Check;
    uint8 data;
    base = UART1_BASE_ADDRESS;
    Register_Check = (*(volatile uint32 *)(base + UART_IM_REG_OFFSET));

    if(Register_Check & (1 << UART_MIS_TX_MASK)){
        /* Transmitting data */
        /* Reading the Flag and check if the FIFO is available to transmit and stop when it's full */
        Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        while( !Register_Check & (1 << UART_FR_TXFF_MASK)){
            if(!UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 1]->isEmpty(UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 1]) ){
                /* there is some data to be send */
                data = UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 1]->remove(UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 1]);
                REG_WRITE_32_BIT_PTR((base + UART_DATA_REG_OFFSET),data);
            }else{
                /* there is no data to be send */
                break;
            }
            /* Reading the Flag and check if the FIFO is available to transmit */
            Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        }
        /* Clear the MIS Flag */
        REG_WRITE_BIT_PTR((base + UART_ICR_REG_OFFSET), UART_MIS_TX_MASK);
    }else if(Register_Check & (1 << UART_MIS_RX_MASK)){
        /* Receiving data */
        /* Reading the Flag and check if the FIFO is available to Receive and stop when it's empty */
        Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        while( !Register_Check & (1 << UART_FR_RXFE_MASK)){
            /* Receive the data in the buffer even if the buffer is full */
            if(!UART_Queue_Buffer[UART_Receive_Buffer_Mask + 1]->isFull(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 1]) ){
                REG_WRITE_32_BIT_PTR((base + UART_DATA_REG_OFFSET),data);
                UART_Queue_Buffer[UART_Receive_Buffer_Mask + 1]->insert(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 1], data);
            }else{
                UART_Queue_Buffer[UART_Receive_Buffer_Mask + 1]->remove(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 1]);
                REG_WRITE_32_BIT_PTR((base + UART_DATA_REG_OFFSET),data);
                UART_Queue_Buffer[UART_Receive_Buffer_Mask + 1]->insert(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 1], data);
            }
            /* Reading the Flag and check if the FIFO is available to receive */
            Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        }

        /* Clear the MIS Flag */
        REG_WRITE_BIT_PTR((base + UART_ICR_REG_OFFSET), UART_MIS_RX_MASK);
    }
}

extern void uart2_handler(void){
    uint32 base, Register_Check;
    uint8 data;
    base = UART2_BASE_ADDRESS;
    Register_Check = (*(volatile uint32 *)(base + UART_IM_REG_OFFSET));

    if(Register_Check & (1 << UART_MIS_TX_MASK)){
        /* Transmitting data */
        /* Reading the Flag and check if the FIFO is available to transmit and stop when it's full */
        Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        while( !Register_Check & (1 << UART_FR_TXFF_MASK)){
            if(!UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 2]->isEmpty(UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 2]) ){
                /* there is some data to be send */
                data = UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 2]->remove(UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 2]);
                REG_WRITE_32_BIT_PTR((base + UART_DATA_REG_OFFSET),data);
            }else{
                /* there is no data to be send */
                break;
            }
            /* Reading the Flag and check if the FIFO is available to transmit */
            Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        }
        /* Clear the MIS Flag */
        REG_WRITE_BIT_PTR((base + UART_ICR_REG_OFFSET), UART_MIS_TX_MASK);
    }else if(Register_Check & (1 << UART_MIS_RX_MASK)){
        /* Receiving data */
        /* Reading the Flag and check if the FIFO is available to Receive and stop when it's empty */
        Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        while( !Register_Check & (1 << UART_FR_RXFE_MASK)){
            /* Receive the data in the buffer even if the buffer is full */
            if(!UART_Queue_Buffer[UART_Receive_Buffer_Mask + 2]->isFull(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 2]) ){
                REG_WRITE_32_BIT_PTR((base + UART_DATA_REG_OFFSET),data);
                UART_Queue_Buffer[UART_Receive_Buffer_Mask + 2]->insert(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 2], data);
            }else{
                UART_Queue_Buffer[UART_Receive_Buffer_Mask + 2]->remove(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 2]);
                REG_WRITE_32_BIT_PTR((base + UART_DATA_REG_OFFSET),data);
                UART_Queue_Buffer[UART_Receive_Buffer_Mask + 2]->insert(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 2], data);
            }
            /* Reading the Flag and check if the FIFO is available to receive */
            Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        }

        /* Clear the MIS Flag */
        REG_WRITE_BIT_PTR((base + UART_ICR_REG_OFFSET), UART_MIS_RX_MASK);
    }
}

extern void uart3_handler(void){
    uint32 base, Register_Check;
    uint8 data;
    base = UART3_BASE_ADDRESS;
    Register_Check = (*(volatile uint32 *)(base + UART_IM_REG_OFFSET));

    if(Register_Check & (1 << UART_MIS_TX_MASK)){
        /* Transmitting data */
        /* Reading the Flag and check if the FIFO is available to transmit and stop when it's full */
        Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        while( !Register_Check & (1 << UART_FR_TXFF_MASK)){
            if(!UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 3]->isEmpty(UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 3]) ){
                /* there is some data to be send */
                data = UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 3]->remove(UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 3]);
                REG_WRITE_32_BIT_PTR((base + UART_DATA_REG_OFFSET),data);
            }else{
                /* there is no data to be send */
                break;
            }
            /* Reading the Flag and check if the FIFO is available to transmit */
            Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        }
        /* Clear the MIS Flag */
        REG_WRITE_BIT_PTR((base + UART_ICR_REG_OFFSET), UART_MIS_TX_MASK);
    }else if(Register_Check & (1 << UART_MIS_RX_MASK)){
        /* Receiving data */
        /* Reading the Flag and check if the FIFO is available to Receive and stop when it's empty */
        Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        while( !Register_Check & (1 << UART_FR_RXFE_MASK)){
            /* Receive the data in the buffer even if the buffer is full */
            if(!UART_Queue_Buffer[UART_Receive_Buffer_Mask + 3]->isFull(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 3]) ){
                REG_WRITE_32_BIT_PTR((base + UART_DATA_REG_OFFSET),data);
                UART_Queue_Buffer[UART_Receive_Buffer_Mask + 3]->insert(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 3], data);
            }else{
                UART_Queue_Buffer[UART_Receive_Buffer_Mask + 3]->remove(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 3]);
                REG_WRITE_32_BIT_PTR((base + UART_DATA_REG_OFFSET),data);
                UART_Queue_Buffer[UART_Receive_Buffer_Mask + 3]->insert(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 3], data);
            }
            /* Reading the Flag and check if the FIFO is available to receive */
            Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        }

        /* Clear the MIS Flag */
        REG_WRITE_BIT_PTR((base + UART_ICR_REG_OFFSET), UART_MIS_RX_MASK);
    }
}

extern void uart4_handler(void){
    uint32 base, Register_Check;
    uint8 data;
    base = UART4_BASE_ADDRESS;
    Register_Check = (*(volatile uint32 *)(base + UART_IM_REG_OFFSET));

    if(Register_Check & (1 << UART_MIS_TX_MASK)){
        /* Transmitting data */
        /* Reading the Flag and check if the FIFO is available to transmit and stop when it's full */
        Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        while( !Register_Check & (1 << UART_FR_TXFF_MASK)){
            if(!UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 4]->isEmpty(UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 4]) ){
                /* there is some data to be send */
                data = UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 4]->remove(UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 4]);
                REG_WRITE_32_BIT_PTR((base + UART_DATA_REG_OFFSET),data);
            }else{
                /* there is no data to be send */
                break;
            }
            /* Reading the Flag and check if the FIFO is available to transmit */
            Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        }
        /* Clear the MIS Flag */
        REG_WRITE_BIT_PTR((base + UART_ICR_REG_OFFSET), UART_MIS_TX_MASK);
    }else if(Register_Check & (1 << UART_MIS_RX_MASK)){
        /* Receiving data */
        /* Reading the Flag and check if the FIFO is available to Receive and stop when it's empty */
        Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        while( !Register_Check & (1 << UART_FR_RXFE_MASK)){
            /* Receive the data in the buffer even if the buffer is full */
            if(!UART_Queue_Buffer[UART_Receive_Buffer_Mask + 4]->isFull(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 4]) ){
                REG_WRITE_32_BIT_PTR((base + UART_DATA_REG_OFFSET),data);
                UART_Queue_Buffer[UART_Receive_Buffer_Mask + 4]->insert(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 4], data);
            }else{
                UART_Queue_Buffer[UART_Receive_Buffer_Mask + 4]->remove(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 4]);
                REG_WRITE_32_BIT_PTR((base + UART_DATA_REG_OFFSET),data);
                UART_Queue_Buffer[UART_Receive_Buffer_Mask + 4]->insert(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 4], data);
            }
            /* Reading the Flag and check if the FIFO is available to receive */
            Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        }

        /* Clear the MIS Flag */
        REG_WRITE_BIT_PTR((base + UART_ICR_REG_OFFSET), UART_MIS_RX_MASK);
    }
}

extern void uart5_handler(void){
    uint32 base, Register_Check;
    uint8 data;
    base = UART2_BASE_ADDRESS;
    Register_Check = (*(volatile uint32 *)(base + UART_IM_REG_OFFSET));

    if(Register_Check & (1 << UART_MIS_TX_MASK)){
        /* Transmitting data */
        /* Reading the Flag and check if the FIFO is available to transmit and stop when it's full */
        Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        while( !Register_Check & (1 << UART_FR_TXFF_MASK)){
            if(!UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 5]->isEmpty(UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 5]) ){
                /* there is some data to be send */
                data = UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 5]->remove(UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 5]);
                REG_WRITE_32_BIT_PTR((base + UART_DATA_REG_OFFSET),data);
            }else{
                /* there is no data to be send */
                break;
            }
            /* Reading the Flag and check if the FIFO is available to transmit */
            Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        }
        /* Clear the MIS Flag */
        REG_WRITE_BIT_PTR((base + UART_ICR_REG_OFFSET), UART_MIS_TX_MASK);
    }else if(Register_Check & (1 << UART_MIS_RX_MASK)){
        /* Receiving data */
        /* Reading the Flag and check if the FIFO is available to Receive and stop when it's empty */
        Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        while( !Register_Check & (1 << UART_FR_RXFE_MASK)){
            /* Receive the data in the buffer even if the buffer is full */
            if(!UART_Queue_Buffer[UART_Receive_Buffer_Mask + 5]->isFull(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 5]) ){
                REG_WRITE_32_BIT_PTR((base + UART_DATA_REG_OFFSET),data);
                UART_Queue_Buffer[UART_Receive_Buffer_Mask + 5]->insert(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 5], data);
            }else{
                UART_Queue_Buffer[UART_Receive_Buffer_Mask + 5]->remove(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 5]);
                REG_WRITE_32_BIT_PTR((base + UART_DATA_REG_OFFSET),data);
                UART_Queue_Buffer[UART_Receive_Buffer_Mask + 5]->insert(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 5], data);
            }
            /* Reading the Flag and check if the FIFO is available to receive */
            Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        }

        /* Clear the MIS Flag */
        REG_WRITE_BIT_PTR((base + UART_ICR_REG_OFFSET), UART_MIS_RX_MASK);
    }
}

extern void uart6_handler(void){
    uint32 base, Register_Check;
    uint8 data;
    base = UART6_BASE_ADDRESS;
    Register_Check = (*(volatile uint32 *)(base + UART_IM_REG_OFFSET));

    if(Register_Check & (1 << UART_MIS_TX_MASK)){
        /* Transmitting data */
        /* Reading the Flag and check if the FIFO is available to transmit and stop when it's full */
        Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        while( !Register_Check & (1 << UART_FR_TXFF_MASK)){
            if(!UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 6]->isEmpty(UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 6]) ){
                /* there is some data to be send */
                data = UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 6]->remove(UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 6]);
                REG_WRITE_32_BIT_PTR((base + UART_DATA_REG_OFFSET),data);
            }else{
                /* there is no data to be send */
                break;
            }
            /* Reading the Flag and check if the FIFO is available to transmit */
            Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        }
        /* Clear the MIS Flag */
        REG_WRITE_BIT_PTR((base + UART_ICR_REG_OFFSET), UART_MIS_TX_MASK);
    }else if(Register_Check & (1 << UART_MIS_RX_MASK)){
        /* Receiving data */
        /* Reading the Flag and check if the FIFO is available to Receive and stop when it's empty */
        Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        while( !Register_Check & (1 << UART_FR_RXFE_MASK)){
            /* Receive the data in the buffer even if the buffer is full */
            if(!UART_Queue_Buffer[UART_Receive_Buffer_Mask + 6]->isFull(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 6]) ){
                REG_WRITE_32_BIT_PTR((base + UART_DATA_REG_OFFSET),data);
                UART_Queue_Buffer[UART_Receive_Buffer_Mask + 6]->insert(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 6], data);
            }else{
                UART_Queue_Buffer[UART_Receive_Buffer_Mask + 6]->remove(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 6]);
                REG_WRITE_32_BIT_PTR((base + UART_DATA_REG_OFFSET),data);
                UART_Queue_Buffer[UART_Receive_Buffer_Mask + 6]->insert(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 6], data);
            }
            /* Reading the Flag and check if the FIFO is available to receive */
            Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        }

        /* Clear the MIS Flag */
        REG_WRITE_BIT_PTR((base + UART_ICR_REG_OFFSET), UART_MIS_RX_MASK);
    }
}

extern void uart7_handler(void){
    uint32 base, Register_Check;
    uint8 data;
    base = UART7_BASE_ADDRESS;
    Register_Check = (*(volatile uint32 *)(base + UART_IM_REG_OFFSET));

    if(Register_Check & (1 << UART_MIS_TX_MASK)){
        /* Transmitting data */
        /* Reading the Flag and check if the FIFO is available to transmit and stop when it's full */
        Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        while( !Register_Check & (1 << UART_FR_TXFF_MASK)){
            if(!UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 7]->isEmpty(UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 7]) ){
                /* there is some data to be send */
                data = UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 7]->remove(UART_Queue_Buffer[UART_Transmit_Buffer_Mask + 7]);
                REG_WRITE_32_BIT_PTR((base + UART_DATA_REG_OFFSET),data);
            }else{
                /* there is no data to be send */
                break;
            }
            /* Reading the Flag and check if the FIFO is available to transmit */
            Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        }
        /* Clear the MIS Flag */
        REG_WRITE_BIT_PTR((base + UART_ICR_REG_OFFSET), UART_MIS_TX_MASK);
    }else if(Register_Check & (1 << UART_MIS_RX_MASK)){
        /* Receiving data */
        /* Reading the Flag and check if the FIFO is available to Receive and stop when it's empty */
        Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        while( !Register_Check & (1 << UART_FR_RXFE_MASK)){
            /* Receive the data in the buffer even if the buffer is full */
            if(!UART_Queue_Buffer[UART_Receive_Buffer_Mask + 7]->isFull(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 7]) ){
                REG_WRITE_32_BIT_PTR((base + UART_DATA_REG_OFFSET),data);
                UART_Queue_Buffer[UART_Receive_Buffer_Mask + 7]->insert(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 7], data);
            }else{
                UART_Queue_Buffer[UART_Receive_Buffer_Mask + 7]->remove(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 7]);
                REG_WRITE_32_BIT_PTR((base + UART_DATA_REG_OFFSET),data);
                UART_Queue_Buffer[UART_Receive_Buffer_Mask + 7]->insert(UART_Queue_Buffer[UART_Receive_Buffer_Mask + 7], data);
            }
            /* Reading the Flag and check if the FIFO is available to receive */
            Register_Check = (*(volatile uint32 *)(base + UART_FLAG_REG_OFFSET));
        }

        /* Clear the MIS Flag */
        REG_WRITE_BIT_PTR((base + UART_ICR_REG_OFFSET), UART_MIS_RX_MASK);
    }
}


/**********************************************************************************************************************
 *  END OF FILE: UART.c
 *********************************************************************************************************************/



