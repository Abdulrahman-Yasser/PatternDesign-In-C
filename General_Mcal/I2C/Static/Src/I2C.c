/**********************************************************************************************************************
 *  FILE DESCRIPTION
  *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  I2C.c
  *        \brief  I2C Driver
  *
  *      \details  This file contains the static implementation of the driver
  *                  it contains all the function implementation logic
  *
  *
  *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "../inc/I2C.h"
#include "../../Dynamic/inc/I2C_Cfg.h"
#include "../../General_Common/Std_Types.h"


#include "../../General_Common/Mcu_Hw.h"
#include "../../General_Common/CPU_resources.h"
#include "../../General_Common/DataStructure/Queue/static/inc/Queue.h"

/**********************************************************************************************************************
 *  Variables Definitions
 *********************************************************************************************************************/
#define I2C_RepeatedStart_ON          1
#define I2C_RepeatedStart_OFF      0

/**********************************************************************************************************************
 *  LOCAL VARIABLES
 *********************************************************************************************************************/
static Queue_uint8_DYNAMIC_Type* I2C_Queue_Buffer[4*2];

#define I2C_Transmit_Buffer_Mask   1
#define I2C_Receive_Buffer_Mask    0


static uint8 I2C_MasterModulesUsed = 0;
static uint8 I2C_SlaveModulesUsed = 0;

/**********************************************************************************************************************
 *  LOCAL Functions Definition
 *********************************************************************************************************************/

static uint32 get_address(I2C_ChannelType I2C_n);

static uint16 I2C_Wait_Untill_Its_End(uint32 base);

static void MasterMultibleTransmitLoop(uint32 base,uint8 n, Queue_uint8_DYNAMIC_Type* Data);
static void MasterMultibleReceiveLoop(uint32 base,uint8 n, Queue_uint8_DYNAMIC_Type* Data);

static uint16 I2C_MasterSingleTransmit(I2C_ChannelType my_I2C, uint8 Slave_Address,  uint8 Slave_memory_Address);
static uint16 I2C_MasterTransmitMultibleBytes(I2C_ChannelType my_I2C, uint8 Slave_Address, uint8 Slave_memory_Address, uint8 bytes_Counts);

static uint16 I2C_MasterReceiveMultibleBytes(I2C_ChannelType my_I2C, uint8 Slave_Address, uint8 Slave_memory_Address, uint8 bytes_Counts);

static void I2C_SlaveTransmit_one_Byte(I2C_ChannelType my_I2C);
static void I2C_SlaveReceive_one_Byte(I2C_ChannelType my_I2C);



void __attribute__((weak)) App_I2C0_Tx_CallBack(void);
void __attribute__((weak)) App_I2C0_Rx_CallBack(void);
void __attribute__((weak)) App_I2C1_Tx_CallBack(void);
void __attribute__((weak)) App_I2C1_Rx_CallBack(void);
void __attribute__((weak)) App_I2C2_Tx_CallBack(void);
void __attribute__((weak)) App_I2C2_Rx_CallBack(void);
void __attribute__((weak)) App_I2C3_Tx_CallBack(void);
void __attribute__((weak)) App_I2C3_Rx_CallBack(void);

/**********************************************************************************************************************
 *  LOCAL Functions Implementation
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : static uint32 get_address(I2C_ChannelType I2C_n)
* \Description     : The Function Returns the I2C module Channel's Base Address
*
* \Parameters (in) : I2C_n          The I2C Channel Number
* \Parameters (out): None
* \Return value:   : uint32         The I2C Channel Module base Address
*******************************************************************************/
static uint32 get_address(I2C_ChannelType I2C_n){
    switch(I2C_n){
    case I2C_NUM_0:
        return (uint32)I2C0_BASE_ADDERSS;
    case I2C_NUM_1:
        return (uint32)I2C1_BASE_ADDERSS;
    case I2C_NUM_2:
        return (uint32)I2C2_BASE_ADDERSS;
    case I2C_NUM_3:
        return (uint32)I2C3_BASE_ADDERSS;
    default:
        return 0;
    }
}

static uint16 I2C_Wait_Untill_Its_End(uint32 base){
    uint16 error;
    uint32 RegisterCheck;
    do{
        RegisterCheck = (*(volatile uint32 *)(base + I2C_MCS_REG_OFFSET));
    }while(RegisterCheck & (1 << I2C_MCS_BUSY_MASK));
    /* Error Checking */
    error = (*(volatile uint32 *)(base + I2C_MCS_REG_OFFSET)) & 0x0E;
    return error;
}

/******************************************************************************
* \Syntax          : static void MasterMultibleTransmitLoop(uint32 base,uint8 bytesCount, Queue_uint8_DYNAMIC_Type* Data)
* \Description     : The Function Transmits n Bytes to the Slave
* \Parameters (in) : base          The I2C Channel base Address
*                    bytesCount    The number of bytes i want to send
*                    Data          The Data buffer of the I2C channel
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
static void MasterMultibleTransmitLoop(uint32 base,uint8 bytesCount, Queue_uint8_DYNAMIC_Type* Data){
    uint32 RegisterCheck;
    uint8 i, my_data;
    for(i = 0; i < bytesCount-1; i++){
        /* 1
         * Write the Data */
        /* Write the Data, Freeze if the Queue is Empty
         * */
        while(Data->isEmpty(Data));
        my_data = Data->remove(Data);
        REG_WRITE_ALL_32_BIT_PTR((base + I2C_MDR_REG_OFFSET), my_data);
        /* 2
         * Write the master control signal
         * 0_001
         * RUN Bit is HIGH, STOP and START are LOW
         * That would generate a Transmitting multiple bytes signal
         * */
        REG_WRITE_ALL_32_BIT_PTR((base + I2C_MCS_REG_OFFSET), 1);
        /* 3
         * BUSY Checking "if the I2C module is BUSY (Finished Transmission or not )"
         * Error Checking
         * */
        RegisterCheck = I2C_Wait_Untill_Its_End(base);
        if(RegisterCheck & (1 << I2C_MCS_ERROR_MASK)){
            /* That is going to be a response for error detection */
            if(RegisterCheck & (1 << I2C_MCS_ARBLST_MASK)){
            }else{
                /* 0_100 */
                REG_CLEAR_SPECIFIC_BIT_PTR((base + I2C_MCS_REG_OFFSET), 0X13);
                REG_WRITE_BIT_PTR(base + I2C_MCS_REG_OFFSET, 2);
            }
            return;
        }else{
        }
    }
}


/******************************************************************************
* \Syntax          : static void MasterMultibleReceiveLoop(uint32 base,uint8 n, Queue_uint8_DYNAMIC_Type* Data)
* \Description     : The Function Receives n Bytes of the Slave
* \Parameters (in) : base          The I2C Channel base Address
*                    n             The number of bytes i want to receive
*                    Data          The Data buffer of the I2C channel
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
static void MasterMultibleReceiveLoop(uint32 base,uint8 bytesCount, Queue_uint8_DYNAMIC_Type* Data){
    uint32 RegisterCheck;
    uint8 i;
    for(i = 0; i < bytesCount-1; i++){

        /* 4
         * Write the master control signal
         * 01001
         * RUN  and ACK Bits are HIGH
         * STOP and START Bits are LOW
         * That would generate a Transmitting multiple bytes signal
         * */
        REG_WRITE_ALL_32_BIT_PTR(base + I2C_MCS_REG_OFFSET, 0x9);

        /*BUSY Checking "if the I2C module is BUSY (Finished Transmission or not )" */
        /* 5
         * BUSY Checking "if the I2C module is BUSY (Finished Transmission or not )"
         * Error Checking and handling
         * */
        RegisterCheck = I2C_Wait_Untill_Its_End(base);
        if(RegisterCheck & (1 << I2C_MCS_ERROR_MASK)){
            /* Error Handling, it will return after that */
            if(RegisterCheck & (1 << I2C_MCS_ARBLST_MASK)){
            }else{
                /* 0_100
                 * STOP Bits are HIGH
                 * RUN, START, HS are low *
                 * That would generate a STOP signal */
                REG_CLEAR_SPECIFIC_BIT_PTR((base + I2C_MCS_REG_OFFSET), 0X18);
                REG_WRITE_BIT_PTR(base + I2C_MCS_REG_OFFSET, 2);
            }
            return ;
        }
        /* Read the Data, Freeze if the Queue is Full */
        RegisterCheck = (uint32)(*(volatile uint32 *)(base + I2C_MDR_REG_OFFSET));
        while(Data->isFull(Data));
        Data->insert(Data, RegisterCheck);
    }
}


/******************************************************************************
* \Syntax          : uint16 I2C_MasterSingleTransmit(I2C_ChannelType my_I2C, uint8 address, I2C_RepeatedStartType RepeatedStart)
* \Description     : The Function Transmits a single bytes to the slave
* \Parameters (in) : my_I2C          A struct that contains ( I2C Channel number, Slave Address )
*                    RepeatedStart   Flag that determine whether the transmission is a repeatedStart or not
* \Parameters (out): None
* \Return value:   : uint16     I2C_RETURN_ERROR
*                               I2C_RETURN_FINE
*******************************************************************************/
static uint16 I2C_MasterSingleTransmit(I2C_ChannelType my_I2C, uint8 Slave_Address,  uint8 Slave_memory_Address){
    uint32 base, RegisterCheck, data, error;
    // Check if the I2C is Configured as Master
    if(! (I2C_MasterModulesUsed & (1 << my_I2C)) ){
        /* error, the I2C module is not configured as a Master */
        return I2C_RETURN_ERROR;
    }
    base = get_address(my_I2C);

    /*
     * Get my data from the buffer
     */
    while(I2C_Queue_Buffer[(2*my_I2C)+I2C_Transmit_Buffer_Mask]->isEmpty(I2C_Queue_Buffer[(2*my_I2C)+I2C_Transmit_Buffer_Mask]));
    data = I2C_Queue_Buffer[(2*my_I2C)+I2C_Transmit_Buffer_Mask]->remove(I2C_Queue_Buffer[(2*my_I2C)+I2C_Transmit_Buffer_Mask]);
    /* 1
     * Write the Slave's Address, Bit 0 'R/S' is LOW for transmit
     * */
    REG_WRITE_32_BIT_PTR((base + I2C_MSA_REG_OFFSET), Slave_Address << 1);
    REG_CLEAR_BIT_PTR(base + I2C_MSA_REG_OFFSET, 0);

    /* 2
     * Write the Data
     * */
    (*(volatile uint32*)(base + I2C_MDR_REG_OFFSET)) = Slave_memory_Address;

    /* 3
     * BUSBUSY Checking "Check if the I2C BUS is free or used by another MASTER"
     * if that line does not exist and i wanted to make a repeated start it will stuck here.
     * but because that condition it will check before.
     * */
//    do{
//        RegisterCheck = (*(volatile uint32 *)(base + I2C_MCS_REG_OFFSET));
//    }while(RegisterCheck & (1 << I2C_MCS_BUSBSY_MASK));
    (*(volatile uint32*)(base + I2C_MCS_REG_OFFSET)) = 0X3;

    /* 4
     * Write the master control signal
     * 00011
     *  RUN, START Bits are HIGH
     * STOP, ACK, HS are low
     * That would generate a MasterSingleTransmit signal
     * */
//    REG_CLEAR_SPECIFIC_BIT_PTR((base + I2C_MCS_REG_OFFSET), 0X18);

    /* 5
     * BUSY Checking "if the I2C module is BUSY (Finished Transmission or not )"
     * Error Checking and handling
     * */
    error = I2C_Wait_Untill_Its_End(base);
    if(error & (1 << I2C_MCS_ERROR_MASK)){
        return I2C_RETURN_ERROR;
    }else{
    }

    (*(volatile uint32*)(base + I2C_MDR_REG_OFFSET)) = data;
    (*(volatile uint32*)(base + I2C_MCS_REG_OFFSET)) = 0X5;
    error = I2C_Wait_Untill_Its_End(base);
    do{
        REG_READ_PTR(RegisterCheck, I2C_MCS_REG_OFFSET + base);
    }while(RegisterCheck & (1 << I2C_MCS_BUSBSY_MASK));
    if(RegisterCheck & (1 << I2C_MCS_ERROR_MASK)){
        return I2C_RETURN_ERROR;
    }else{
        return I2C_RETURN_FINE;
    }
}


/******************************************************************************
* \Syntax          : uint16 I2C_MasterTransmitMultibleBytes(I2C_ChannelType my_I2C, uint8 address, uint8 n, I2C_RepeatedStartType RepeatedStart )
* \Description     : The Function Transmits Multiple bytes to the slave
* \Parameters (in) : my_I2C          A struct that contains ( I2C Channel number, Slave Address )
*                    n               Number of the bytes i need to transmit
*                    RepeatedStart   Flag that determine whether the transmission is a repeatedStart or not
* \Parameters (out): None
* \Return value:   : uint16     I2C_RETURN_ERROR
*                               I2C_RETURN_FINE
*******************************************************************************/
static uint16 I2C_MasterTransmitMultibleBytes(I2C_ChannelType my_I2C, uint8 Slave_Address, uint8 Slave_memory_Address, uint8 bytes_Counts){
    uint32 base, RegisterCheck, size, data;
    // Check if the I2C is Configured as Master
    if(! (I2C_MasterModulesUsed & (1 << my_I2C))){
        /* error, the I2C module is not configured as a Master */
        return I2C_RETURN_ERROR;
    }
    base = get_address(my_I2C);

    /* 1
     * Write the Slave's Address, Bit 0 'R/S' is LOW for transmit
     * */
    REG_WRITE_32_BIT_PTR((base + I2C_MSA_REG_OFFSET), Slave_Address << 1);
    REG_CLEAR_BIT_PTR(base + I2C_MSA_REG_OFFSET, 0);
    /* 2
     * Write the Slave_memory_Address the i2c will transmit in
     * */
    REG_WRITE_32_BIT_PTR((base + I2C_MDR_REG_OFFSET), Slave_memory_Address);
    /* 3
     * BUSBUSY Checking "Check if the I2C BUS is free or used by another MASTER"
     * if that line does not exist and i wanted to make a repeated start it will stuck here.
     * but because that condition it will check before.
     * */
//    do{
//        RegisterCheck = (*(volatile uint32 *)(base + I2C_MCS_REG_OFFSET));
//    }while(! RegisterCheck & (1 << I2C_MCS_BUSBSY_MASK));

    /* you will just check if the user wants to send anything in the queue, he will need to write 0 here */
    size = I2C_Queue_Buffer[(2*my_I2C)+I2C_Transmit_Buffer_Mask]->getSize(I2C_Queue_Buffer[(2*my_I2C)+I2C_Transmit_Buffer_Mask]);
    if(bytes_Counts > size){
        bytes_Counts = size;
    }
    /* 4
     * Write the master control signal
     * 0_011
     * RUN, START Bits are HIGH
     * STOP, ACK, HS are low *
     * That would generate a Transmitting Single bytes signal
     * */
    REG_CLEAR_SPECIFIC_BIT_PTR((base + I2C_MCS_REG_OFFSET), 0X14);
    REG_WRITE_32_BIT_PTR((base + I2C_MCS_REG_OFFSET), 0X3);
    /* 5
     * BUSY Checking "if the I2C module is BUSY (Finished Transmission or not )"
     * Error Checking and handling
     * */
    RegisterCheck = I2C_Wait_Untill_Its_End(base);

    if(RegisterCheck & (1 << I2C_MCS_ERROR_MASK)){
        /* Error Handling, it will return after that */
        if(RegisterCheck & (1 << I2C_MCS_ARBLST_MASK)){
        }else{
            /* 0_100
             * STOP Bits are HIGH
             * RUN, START, HS are low *
             * That would generate a STOP signal */
            REG_CLEAR_SPECIFIC_BIT_PTR((base + I2C_MCS_REG_OFFSET), 0X18);
            REG_WRITE_BIT_PTR(base + I2C_MCS_REG_OFFSET, 2);
        }
        return I2C_RETURN_ERROR;
    }
    /* 6
     * Write the Data */
    /* Write the Data, Freeze if the Queue is Empty
     * */
    if(bytes_Counts > 1){
        MasterMultibleTransmitLoop(base, bytes_Counts, I2C_Queue_Buffer[(2*my_I2C)+I2C_Transmit_Buffer_Mask]);
    }
    /* 7
     * Write the Last Byte, Freeze if the Queue is Empty
     * */
    while(I2C_Queue_Buffer[(2*my_I2C)+I2C_Transmit_Buffer_Mask]->isEmpty(I2C_Queue_Buffer[(2*my_I2C)+I2C_Transmit_Buffer_Mask]));

    data = I2C_Queue_Buffer[(2*my_I2C)+I2C_Transmit_Buffer_Mask]->remove(I2C_Queue_Buffer[(2*my_I2C)+I2C_Transmit_Buffer_Mask]);
    REG_WRITE_ALL_32_BIT_PTR((base + I2C_MDR_REG_OFFSET), data);
    /* 8
     * Write the master control signal
     * 0_101
     * RUN, STOP Bits are HIGH
     * START, HS are low *
     * That would generate a Last Transmission signal */
    REG_WRITE_ALL_32_BIT_PTR((base + I2C_MCS_REG_OFFSET), 0X05);
    /* 9
     * BUSY Checking "if the I2C module is BUSY (Finished Transmission or not )"
     * Error Checking
     * */
    RegisterCheck = I2C_Wait_Untill_Its_End(base);
    do{
        REG_READ_PTR(RegisterCheck, I2C_MCS_REG_OFFSET + base);
    }while(RegisterCheck & (1 << I2C_MCS_BUSBSY_MASK));
    if(RegisterCheck & (1 << I2C_MCS_ERROR_MASK)){
        return I2C_RETURN_ERROR;
    }
    return I2C_RETURN_FINE;
}



/******************************************************************************
* \Syntax          : uint16 I2C_MasterReceiveMultibleBytes(I2C_ChannelType my_I2C, uint8 address, uint8 n, I2C_RepeatedStartType RepeatedStart)
* \Description     : The Function Receives Multiple Bytes from the Slave
* \Parameters (in) : my_I2C          A struct that contains ( I2C Channel number, Slave Address )
*                    n               the number of data i need to receive
*                    RepeatedStart   Flag that determine whether the transmission is a repeatedStart or not
* \Parameters (out): None
* \Return value:   : uint16     I2C_RETURN_ERROR
*                               I2C_RETURN_FINE
*******************************************************************************/
static uint16 I2C_MasterReceiveMultibleBytes(I2C_ChannelType my_I2C, uint8 Slave_Address, uint8 Slave_memory_Address, uint8 bytes_Counts){
    uint32 base, RegisterCheck;
    // Check if the I2C is Configured as Master
    if(! (I2C_MasterModulesUsed & (1 << my_I2C))){
        /* error, the I2C module is not configured as a Master */
        return I2C_RETURN_ERROR;
    }
    base = get_address(my_I2C);

    /* 1
     * Write the Slave's Address, Bit 0 'R/S' is LOW for transmit
     * */
    REG_WRITE_32_BIT_PTR((base + I2C_MSA_REG_OFFSET), Slave_Address << 1);
    REG_CLEAR_BIT_PTR(base + I2C_MSA_REG_OFFSET, 0);

    /* 2
     * Write the Slave_memory_Address the i2c will transmit in
     * */
    REG_WRITE_32_BIT_PTR((base + I2C_MDR_REG_OFFSET), Slave_memory_Address);

    /* 3
     * BUSBUSY Checking "Check if the I2C BUS is free or used by another MASTER"
     * if that line does not exist and i wanted to make a repeated start it will stuck here.
     * but because that condition it will check before.
     * */
//    do{
//        RegisterCheck = (*(volatile uint32 *)(base + I2C_MCS_REG_OFFSET));
//    }while(! RegisterCheck & (1 << I2C_MCS_BUSBSY_MASK));


    /* 4
     * Write the master control signal
     * 0_011
     * RUN, START Bits are HIGH
     * STOP is low *
     * That would generate a Transmit signal just to transmit the slave_memory_address
     * */
    REG_WRITE_ALL_32_BIT_PTR(base + I2C_MCS_REG_OFFSET, 0x03);

    /* 5
     * BUSY Checking "if the I2C module is BUSY (Finished Transmission or not )"
     * Error Checking and handling
     * */
    RegisterCheck = I2C_Wait_Untill_Its_End(base);

    if(RegisterCheck & (1 << I2C_MCS_ERROR_MASK)){
        /* Error Handling, it will return after that */
        if(RegisterCheck & (1 << I2C_MCS_ARBLST_MASK)){
        }else{
            /* 0_100
             * STOP Bits are HIGH
             * RUN, START, HS are low *
             * That would generate a STOP signal */
            REG_CLEAR_SPECIFIC_BIT_PTR((base + I2C_MCS_REG_OFFSET), 0X18);
            REG_WRITE_BIT_PTR(base + I2C_MCS_REG_OFFSET, 2);
        }
        return I2C_RETURN_ERROR;
    }
    /*
     * ========================================== Here i will start receiving =======================================
     */

    /* 6
     * Write the Slave's Address, Bit 0 'R/S' is LOW for transmit
     * */
    REG_WRITE_32_BIT_PTR((base + I2C_MSA_REG_OFFSET), Slave_Address << 1);
    REG_WRITE_BIT_PTR(base + I2C_MSA_REG_OFFSET, 0);

    /* 7
     * Write the master control signal Restart Signal
     * */
    if(bytes_Counts == 1){
        /* 0_111
         * RUN, START, STOP Bits are HIGH
         * ACK is low *
         * That would generate a single receive byte then stop receiving
         * */
        REG_WRITE_ALL_32_BIT_PTR(base + I2C_MCS_REG_OFFSET, 0x07);
    }else{
        /* 01011
         * RUN, START, ACK Bits are HIGH
         * STOP is low *
         * That would generate a Multiple receive signal that generates acknowledge
         * */
        REG_WRITE_ALL_32_BIT_PTR(base + I2C_MCS_REG_OFFSET, 0x0B);
    }

    /* 8
     * BUSY Checking "if the I2C module is BUSY (Finished Transmission or not )"
     * Error Checking and handling
     * */
    RegisterCheck = I2C_Wait_Untill_Its_End(base);
    if(RegisterCheck & (1 << I2C_MCS_ERROR_MASK)){
        /* Error Handling, it will return after that */
        if(RegisterCheck & (1 << I2C_MCS_ARBLST_MASK)){
        }else{
            /* 0_100
             * STOP Bits are HIGH
             * RUN, START, HS are low *
             * That would generate a STOP signal */
            REG_CLEAR_SPECIFIC_BIT_PTR((base + I2C_MCS_REG_OFFSET), 0X18);
            REG_WRITE_BIT_PTR(base + I2C_MCS_REG_OFFSET, 2);
        }
        return I2C_RETURN_ERROR;
    }

    /* 9
     * Read the Data, Freeze if the Queue is Full
     * */
    RegisterCheck = (uint32)(*(volatile uint32 *)(base + I2C_MDR_REG_OFFSET));
    while(I2C_Queue_Buffer[(2*my_I2C)+I2C_Receive_Buffer_Mask]->isFull(I2C_Queue_Buffer[(2*my_I2C)+I2C_Receive_Buffer_Mask]));
    I2C_Queue_Buffer[(2*my_I2C)+I2C_Receive_Buffer_Mask]->insert(I2C_Queue_Buffer[(2*my_I2C)+I2C_Receive_Buffer_Mask], RegisterCheck);
    bytes_Counts--;
    if(bytes_Counts == 0){
        do{
            REG_READ_PTR(RegisterCheck, I2C_MCS_REG_OFFSET + base);
        }while(RegisterCheck & (1 << I2C_MCS_BUSBSY_MASK));
        return I2C_RETURN_FINE;
    }

    /* 10
     * Receive byte_Count number of Data
     */
    MasterMultibleReceiveLoop(base, bytes_Counts, I2C_Queue_Buffer[(2*my_I2C)+I2C_Receive_Buffer_Mask]);

    /* 11
     * Write the master control signal for the last byte
     * 00101
     * RUN, STOP is HIGH
     * START is low
     * That would generate a Master Last Receive Signal */
    REG_CLEAR_SPECIFIC_BIT_PTR(base + I2C_MCS_REG_OFFSET, 0x1A);
    REG_WRITE_32_BIT_PTR(base + I2C_MCS_REG_OFFSET, 0x5);

    /* 12
     * BUSY Checking "if the I2C module is BUSY (Finished Transmission or not )"
     * Error Checking and handling
     * */
    RegisterCheck = I2C_Wait_Untill_Its_End(base);
    if(RegisterCheck & (1 << I2C_MCS_ERROR_MASK)){
        /* Error Handling, it will return after that */
        return I2C_RETURN_ERROR;
    }

    /* 13
     * Read the Data, Freeze if the Queue is Full
     * */
    RegisterCheck = (uint32)(*(volatile uint32 *)(base + I2C_MDR_REG_OFFSET));
    while(I2C_Queue_Buffer[(2*my_I2C)+I2C_Receive_Buffer_Mask]->isFull(I2C_Queue_Buffer[(2*my_I2C)+I2C_Receive_Buffer_Mask]));
    I2C_Queue_Buffer[(2*my_I2C)+I2C_Receive_Buffer_Mask]->insert(I2C_Queue_Buffer[(2*my_I2C)+I2C_Receive_Buffer_Mask], RegisterCheck);
    return I2C_RETURN_FINE;
}


static void I2C_SlaveTransmit_one_Byte(I2C_ChannelType my_I2C){

}
static void I2C_SlaveReceive_one_Byte(I2C_ChannelType my_I2C){

}


void __attribute__((weak)) App_I2C0_Tx_CallBack(void){ }
void __attribute__((weak)) App_I2C0_Rx_CallBack(void){ }
void __attribute__((weak)) App_I2C1_Tx_CallBack(void){ }
void __attribute__((weak)) App_I2C1_Rx_CallBack(void){ }
void __attribute__((weak)) App_I2C2_Tx_CallBack(void){ }
void __attribute__((weak)) App_I2C2_Rx_CallBack(void){ }
void __attribute__((weak)) App_I2C3_Tx_CallBack(void){ }
void __attribute__((weak)) App_I2C3_Rx_CallBack(void){ }

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/



/******************************************************************************
* \Syntax          : void I2C_init(void)
* \Description     : The Function Initialize all the I2C we are going to
*                    use in our program
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/

void I2C_init(void){
    sint8 i, j;
    uint32 base;
    volatile sint32 TimeCalculation;
    volatile uint32 RegisterCheck;


    /******************************************************************************
     * Dealing with "I2C_ConfigType" that contains the I2C module Slaves and Masters.
     * So we need to check over everything in the implementation
    *******************************************************************************/

    for(i = 0; i < I2C_CONFIGURED_NUMBER; i++){
        base = get_address(I2C_Container[i].I2C_num);
        /*
         * 1 .. Initialize the I2C clock using RCGCI2C Register
         */
        /* Check if the I2C module is already configured and the RCGCI2C already has a value of 1 */

        RegisterCheck = (uint32)SYSCTL_RCGCI2C;
        if(RegisterCheck & (1 << (uint8)I2C_Container[i].I2C_num)){
            /* the I2C module is already configured !!!! */
            continue;
        }else{
            REG_WRITE_BIT(SYSCTL_RCGCI2C, (uint8)I2C_Container[i].I2C_num);
            // For delay purpose
            RegisterCheck = (uint32)SYSCTL_RCGCI2C;
        }

        // Create a buffer for it
        I2C_Queue_Buffer[(2 * I2C_Container[i].I2C_num) + I2C_Transmit_Buffer_Mask] = Queue_Create_DYNAMIC_uint8(16);
        I2C_Queue_Buffer[(2 * I2C_Container[i].I2C_num) + I2C_Receive_Buffer_Mask] = Queue_Create_DYNAMIC_uint8(16);

        /*
         * 2 .. Initialize the I2C Mode whether it was Master or Slave
         * using the bits MasterEnable and SlaveEnable in MCR (Master Configuration Register)
         * we also will Set the Interrupt Mask as long we are checking it's master or slave
         */
        if(I2C_Container[i].I2C_Mode == I2C_ModeMaster){
/* ================================================ Master I2c ==================================== */

            // Check if the same I2C has been used as Slave
            if( I2C_SlaveModulesUsed & (1 << I2C_Container[i].I2C_num)){
                continue;
            }else{
            // Save it in Transmit Variable
                I2C_MasterModulesUsed |= (1 << I2C_Container[i].I2C_num);
            }

            // I2CMCR For SlaveDisable and MasterEnable
            REG_WRITE_BIT_PTR(base + I2C_MCR_REG_OFFSET, 4);
            REG_CLEAR_BIT_PTR(base + I2C_MCR_REG_OFFSET, 5);

            // I2CMCR For GlitchSupression
            if(I2C_Container[i].I2c_GlitchSupression == I2C_GlitchSuppression_ON){
                REG_WRITE_BIT_PTR(base + I2C_MCR_REG_OFFSET, 6);
                REG_WRITE_32_BIT_PTR((base + I2C_MCR2_REG_OFFSET), I2C_Container[i].I2C_GlitchFilterPulseWidth);
            }else{
                REG_CLEAR_BIT_PTR(base + I2C_MCR_REG_OFFSET, 6);
            }

            // I2CMCR For Loop Back
            if(I2C_Container[i].I2C_LoopBack == I2C_LoopBack_ON){
                REG_WRITE_BIT_PTR(base + I2C_MCR_REG_OFFSET, 0);
            }else{
                REG_CLEAR_BIT_PTR(base + I2C_MCR_REG_OFFSET, 0);
            }

            // Clock Low Time Out
            REG_WRITE_32_BIT_PTR((base + I2C_MCLKOCNT_REG_OFFSET), I2C_Container[i].I2C_Clock_Low_Timeout_Count);

            // I2CIM For Setting the Master Interrupt mask Register
            for(j = 0; j < I2C_ALLOWED_INTERRUPTS_NUMBER; j++){
                switch(I2C_Container[i].I2C_MasterISRMode[j]){
                case I2C_MasterISR_None :
                    break;
                case I2C_MasterISR_BusTimeout:
                    REG_WRITE_BIT_PTR(base + I2C_MIMR_REG_OFFSET, 1);
                    break;
                case I2C_MasterISR_TransactionComplete:
                case I2C_MasterISR_ArbitrationLost:
                case I2C_MasterISR_TransactionError:
                    REG_WRITE_BIT_PTR(base + I2C_MIMR_REG_OFFSET, 0);
                    break;
                default :
                    break;
                }
            }

            /*
             * 3 .. Set the I2C Clock using the formula
             * TPR = (System Clock/(2*(SCL_LP + SCL_HP)*SCL_CLK))-1;
             * TPR = (20MHz/(2*(6+4)*100000))-1;
             * TPR = 9
             * Using the register I2CMTPR
             */

            switch(I2C_Container[i].I2C_Speed){
            case I2cSpeed_SM_100Kbps:
                TimeCalculation = (CPU_CLOCK*1000/((20)*100))-1;
                break;
            case I2cSpeed_FM_400Kbps:
                TimeCalculation = (CPU_CLOCK*1000/((20)*400))-1;
                break;
            case I2cSpeed_FMP_1Mbps:
                TimeCalculation = (CPU_CLOCK*1000/((20)*1000))-1;
                break;
            case I2cSpeed_HS_3Mbps:
                TimeCalculation = (CPU_CLOCK*10000/((6)*33300))-1;
                REG_WRITE_BIT_PTR(base + I2C_MTPR_REG_OFFSET, 7);
                break;
            default :
                break;
            }
            if(TimeCalculation > 0 && TimeCalculation <= 128){
                REG_CLEAR_32_BIT_PTR((base + I2C_MTPR_REG_OFFSET));
                REG_WRITE_32_BIT_PTR((base + I2C_MTPR_REG_OFFSET), (uint32)TimeCalculation);
            }else{
                /* error */
                return ;
            }

        }else if(I2C_Container[i].I2C_Mode == I2C_ModeSlave){
/* ================================================ Slave I2c ==================================== */
            // Check if the same I2C has been used as Transmit
            if( I2C_MasterModulesUsed & (1 << I2C_Container[i].I2C_num)){
                continue;
            }else{
            // Save it in Slave Variable
                I2C_SlaveModulesUsed |= (1 << I2C_Container[i].I2C_num);
            }

            // Create a buffer for it
            I2C_Queue_Buffer[I2C_Container[i].I2C_Mode] = Queue_Create_DYNAMIC_uint8(16);

            // I2CMCR For SlaveEnable and MasterDisable
            REG_WRITE_BIT_PTR(base + I2C_MCR_REG_OFFSET, 5);
            REG_CLEAR_BIT_PTR(base + I2C_MCR_REG_OFFSET, 4);

            // Setting it's Address 0
            REG_WRITE_32_BIT_PTR((base + I2C_SOAR_REG_OFFSET), (0x7F & I2C_Container[i].I2C_SlaveAddress1));

            // Setting it's Second Address "If used"
            if(I2C_Container[i].I2C_SlaveAddress2 > 0){
                REG_WRITE_32_BIT_PTR((base + I2C_SOAR2_REG_OFFSET), (0x7F & I2C_Container[i].I2C_SlaveAddress2));
                REG_WRITE_BIT_PTR(base + I2C_SOAR2_REG_OFFSET, 7);
            }


            // I2CIM For Setting the Master Interrupt mask Register
            for(j = 0; j < I2C_ALLOWED_INTERRUPTS_NUMBER; j++){
                switch(I2C_Container[i].I2C_SlaveISRMode[j]){
                case I2C_SlaveISR_None :
                    break;
                case I2C_SlaveISR_TransactionReceived:
                case I2C_SlaveISR_TransactionRequested:
                    REG_WRITE_BIT_PTR(base + I2C_SIMR_REG_OFFSET, 0);
                    break;
                case I2C_SlaveISR_StartCondition:
                    REG_WRITE_BIT_PTR(base + I2C_SIMR_REG_OFFSET, 1);
                    break;
                case I2C_SlaveISR_StopCondition:
                    REG_WRITE_BIT_PTR(base + I2C_SIMR_REG_OFFSET, 2);
                    break;
                default :
                    break;
                }
            }

            // Activate the Slave Operations
            REG_WRITE_BIT_PTR(base + I2C_SCSR_REG_OFFSET, 0);
        }
    }
}



/******************************************************************************
* \Syntax          : void I2C_MasterPoke_to_transmit(I2C_ChannelType my_I2C, uint8 address, uint8 Bytes_Cnt)
* \Description     : The Function Transmits the number of the Bytes_Cnt of the I2C module's Queue
* \Parameters (in) : my_I2C          The I2C Channel module number
*                    Bytes_Cnt       The number of the bytes i need to transmit
*                       Bytes_Cnt == 0 that's mean that i need to send all the data in the Queue
*                       Bytes_Cnt == 1 that's mean that i need to send Only one Byte
*                       Bytes_Cnt == n that's mean that i need to send n bytes from the Queue
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/

uint16 I2C_MasterPoke_to_transmit(I2C_ChannelType my_I2C, uint8 slave_address, uint8 Slave_memory_Address, uint8 Bytes_Cnt){
    uint16 err;
    if(Bytes_Cnt > 1){
        I2C_MasterTransmitMultibleBytes(my_I2C, slave_address, Slave_memory_Address, Bytes_Cnt);
    }else{
        err = I2C_MasterSingleTransmit(my_I2C, slave_address, Slave_memory_Address);
    }
    return err;
}



/******************************************************************************
* \Syntax          : void I2C_MasterPoke_to_receive(I2C_ChannelType my_I2C, uint8 address, uint8 Bytes_Cnt)
* \Description     : The Function Receives the number of the Bytes_Cnt in the I2C module's Queue
* \Parameters (in) : my_I2C          The I2C Channel module number
*                    Bytes_Cnt       The number of the bytes i need to transmit
*                       Bytes_Cnt == 0 that's mean that i need to receive all the data in the Queue
*                       Bytes_Cnt == 1 that's mean that i need to receive Only one Byte
*                       Bytes_Cnt == n that's mean that i need to receive n bytes from the Queue
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
uint16 I2C_MasterPoke_to_receive(I2C_ChannelType my_I2C, uint8 slave_address, uint8 Slave_memory_Address, uint8 Bytes_Cnt){
    uint16 err;
    if(Bytes_Cnt > 0){
        err = I2C_MasterReceiveMultibleBytes(my_I2C, slave_address, Slave_memory_Address, Bytes_Cnt);
    }
    return err;
}



/******************************************************************************
* \Syntax          : void I2C_Push_to_Transmit(I2C_ChannelType my_I2C, uint8 x, uint8 must_be_pushed)
* \Description     : The Function Push one Byte to the I2C module Queue to transmit it later
* \Parameters (in) : my_I2C             A struct that contains ( I2C Channel number, Slave Address )
*                    x                  The number of the bytes i need to transmit
*                    must_be_pushed     whether it might be lost or not
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
uint16 I2C_Push_to_Transmit(I2C_ChannelType my_I2C, uint8 x, uint8 must_be_pushed){
    uint16 err;
    uint8 chances = 0;
    /* Check if the I2C Channel Queue is Empty or not */
    if(must_be_pushed == 1){
        /* it will stuck here until it get free */
        while((I2C_Queue_Buffer[(2*my_I2C)+I2C_Transmit_Buffer_Mask]->isFull(I2C_Queue_Buffer[(2*my_I2C)+I2C_Transmit_Buffer_Mask]) )){
            chances++;
            if(chances == 60){
                err = I2C_RETURN_ERROR;
                break;
            }
        }
        I2C_Queue_Buffer[(2*my_I2C)+I2C_Transmit_Buffer_Mask]->insert(I2C_Queue_Buffer[(2*my_I2C)+I2C_Transmit_Buffer_Mask], x);
    }else{
        I2C_Queue_Buffer[(2*my_I2C)+I2C_Transmit_Buffer_Mask]->insert(I2C_Queue_Buffer[(2*my_I2C)+I2C_Transmit_Buffer_Mask], x);
    }
    return err;
}

/******************************************************************************
* \Syntax          : void I2C_Pop_the_Received(I2C_ChannelType my_I2C, uint8* data)
* \Description     : The Function Push one Byte to the I2C module Queue to transmit it later
* \Parameters (in) : my_I2C             A struct that contains ( I2C Channel number, Slave Address )
* \Parameters (out): data               The data that have been received and saved in the Queue
* \Return value:   : None
*******************************************************************************/
uint16 I2C_Pop_the_Received(I2C_ChannelType my_I2C, uint8* data, uint8 iterator){
    uint8 i, chances = 0;
    uint16 err = I2C_RETURN_FINE;
    /* Check if the I2C Channel Queue is Empty or not */
    /* it will stuck here until there is some data */
    for(i = 0; i < iterator; i++){
        while((I2C_Queue_Buffer[(2*my_I2C)+I2C_Receive_Buffer_Mask]->isEmpty(I2C_Queue_Buffer[(2*my_I2C)+I2C_Receive_Buffer_Mask]) )){
            chances++;
            if(chances == 60){
                err = I2C_RETURN_ERROR;
                break;
            }
        }
        data[i] = I2C_Queue_Buffer[(2*my_I2C)+I2C_Receive_Buffer_Mask]->remove(I2C_Queue_Buffer[(2*my_I2C)+I2C_Receive_Buffer_Mask]);
    }
    return err;
}



void I2C0_handler(void);

void I2C1_handler(void);

void I2C2_handler(void);

void I2C3_handler(void);






