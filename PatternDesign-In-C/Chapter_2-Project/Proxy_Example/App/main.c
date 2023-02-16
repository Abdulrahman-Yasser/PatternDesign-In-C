

/**
 * main.c
 */
#include "main.h"

/*================================================ UART TEST ================================================*/

void Test_I2C_LCD(void);
void Test_I2C_LCD(void){

    Port_Init();
    Gpt_Init();
    IntCtrl_Init();
    I2C_init();

    LCD_Handler_Type* LCD_1;
    LCD_1 = LCD_Create(LCD_Interface_I2C, 0);

    while(1){
        LCD_1->LCD_Write_Data(LCD_1, "HELLO");
        Delay_ms(1000);
        LCD_1->LCD_Write_Cmd(LCD_1, LCD_I2C_INST_CLEAR);
        Delay_ms(1000);
    }
}

/*================================================ UART TEST ================================================*/
/* UART5 -> PE5 TX, PE4 RX   */
/* UART7 -> PE1 TX, PE0 RX   */
void Send_Msg_UART5(char* msg);
void Send_Msg_UART7(char* msg);

void Test_UART_AlwaysFullBuffer_ISR_Configs(void);

/*================================================ I2C TEST ================================================*/
/* I2C0 -> PB2 SCL, PB3 SDA */
/* I2C1 -> PA6 SCL, PA7 SDA */
void Send_Msg_I2C0(char* msg);
void Send_Msg_I2C1(char* msg);

void Test_I2C_AlwaysFullBuffer_NoISR_Configs(void);

/*================================================ PWM TEST ================================================*/
void Test_PWM_Generation_NoISR_Configs(void);


int main(void){
    Test_I2C_LCD();
}

/*================================================ I2C TEST ================================================*/
void Test_PWM_Generation_NoISR_Configs(void){
    int i = 0;

    Port_Init();
    Gpt_Init();
    IntCtrl_Init();
    pwm_init();
    pwm_enable(PWM_NUM_0_1, (PWM_SubChannelType)0x3);
    while(1){
        Delay_ms(50);
        pwm_AutomaticDutyCycle(PWM_NUM_0_1, i, PWM_SUB_CHANNEL_BOTH);
        i++;
        if(i > 100){
            i = 0;
        }
    }
}
    /*================================================ I2C TEST ================================================*/
void Test_I2C_AlwaysFullBuffer_NoISR_Configs(void){

    Port_Init();
    Gpt_Init();
    IntCtrl_Init();
    I2C_init();
    int i;

    while(1){
        Send_Msg_I2C0("Hello !! ");
        i = I2C_MasterPoke_to_transmit(I2C_NUM_1, I2c_test_Slave_Address, 0X72, 1);
        i = I2C_MasterPoke_to_transmit(I2C_NUM_1, I2c_test_Slave_Address, 0X72, 1);
        i = I2C_MasterPoke_to_transmit(I2C_NUM_1, I2c_test_Slave_Address, 0X72, 1);
        i = I2C_MasterPoke_to_transmit(I2C_NUM_1, I2c_test_Slave_Address, 0X72, 1);
        i = I2C_MasterPoke_to_transmit(I2C_NUM_1, I2c_test_Slave_Address, 0X72, 1);
        i = I2C_MasterPoke_to_transmit(I2C_NUM_1, I2c_test_Slave_Address, 0X72, 1);
        i = I2C_MasterPoke_to_transmit(I2C_NUM_1, I2c_test_Slave_Address, 0X72, 1);
        i = I2C_MasterPoke_to_transmit(I2C_NUM_1, I2c_test_Slave_Address, 0X72, 1);
        Send_Msg_I2C0("my name is abdulrahman yasser");
        i = I2C_MasterPoke_to_transmit(I2C_NUM_1, I2c_test_Slave_Address, 0X72, 1);
        i = I2C_MasterPoke_to_transmit(I2C_NUM_1, I2c_test_Slave_Address, 0X72, 1);
        i = I2C_MasterPoke_to_transmit(I2C_NUM_1, I2c_test_Slave_Address, 0X72, 1);
        i = I2C_MasterPoke_to_transmit(I2C_NUM_1, I2c_test_Slave_Address, 0X72, 1);
        i = I2C_MasterPoke_to_transmit(I2C_NUM_1, I2c_test_Slave_Address, 0X72, 1);
        i = I2C_MasterPoke_to_transmit(I2C_NUM_1, I2c_test_Slave_Address, 0X72, 1);
        i = I2C_MasterPoke_to_transmit(I2C_NUM_1, I2c_test_Slave_Address, 0X72, 1);
        i = I2C_MasterPoke_to_transmit(I2C_NUM_1, I2c_test_Slave_Address, 0X72, 1);
        i = I2C_MasterPoke_to_transmit(I2C_NUM_1, I2c_test_Slave_Address, 0X72, 1);
        i = I2C_MasterPoke_to_transmit(I2C_NUM_1, I2c_test_Slave_Address, 0X72, 1);
        i = I2C_MasterPoke_to_transmit(I2C_NUM_1, I2c_test_Slave_Address, 0X72, 1);
        i = I2C_MasterPoke_to_transmit(I2C_NUM_1, I2c_test_Slave_Address, 0X72, 1);
        i = I2C_MasterPoke_to_transmit(I2C_NUM_1, I2c_test_Slave_Address, 0X72, 1);
        i = I2C_MasterPoke_to_transmit(I2C_NUM_1, I2c_test_Slave_Address, 0X72, 1);
        i = I2C_MasterPoke_to_transmit(I2C_NUM_1, I2c_test_Slave_Address, 0X72, 1);
    }
}



void Send_Msg_I2C0(char* msg){
    while(*msg != '\0'){
        I2C_Push_to_Transmit(I2C_NUM_1, *msg, 0);
        msg++;
    }
}

void Send_Msg_I2C1(char* msg){
    while(*msg != '\0'){
        I2C_Push_to_Transmit(I2C_NUM_1, *msg, 1);
        msg++;
    }
}

/*================================================ UART TEST ================================================*/
void Test_UART_AlwaysFullBuffer_ISR_Configs(void)
{
    int i, j;

    Port_Init();
    uart_init();
    Gpt_Init();
    IntCtrl_Init();

    while(1){
        Send_Msg_UART5("Hello !! ");
        UART_Poke_to_transmit(UART_NUM_5, UART_TRANSMIT_RECEIVE_ONE_CHAR);
        Send_Msg_UART5("my name is abdulrahman yasser");
        UART_Poke_to_transmit(UART_NUM_5, UART_TRANSMIT_RECEIVE_ONE_CHAR);
        for(i = 0; i < 5; i++){
            Send_Msg_UART5("Hello !! ");
            Send_Msg_UART5("my name is abdulrahman yasser");
            UART_Poke_to_transmit(UART_NUM_5, UART_TRANSMIT_RECEIVE_ONE_CHAR);
        }
        for(i = 0; i < 100; i++){
            for(j = 0; j < 1000; j++){

            }
        }
        while(1){
            Send_Msg_UART7("HELP MEE !!!!!!!!!!!!!!!!!!!");
            UART_Poke_to_transmit(UART_NUM_7, 4);
            Send_Msg_UART7("THEY'RE COMING TO TAKE ME AWAY .");
            Send_Msg_UART7("THEY'RE COMING TO TAKE ME AWAY .");
            for(i = 0; i < 5; i++){
                Send_Msg_UART7("PLEASE !! ");
                Send_Msg_UART7("THEY'RE COMING TO TAKE ME !!!!!!");
            }
        }
    }
}


void App_Function(void){
}
void App_Uart5_Tx_CallBack(void){
    Dio_FlipChannel(GPIO_UART5_CHECK_PIN);
}

void App_Uart7_Tx_CallBack(void){
    Dio_FlipChannel(GPIO_UART7_CHECK_PIN);
}
void Send_Msg_UART5(char* msg){
    while(*msg != '\0'){
        UART_Push_to_Transmit(UART_NUM_5, *msg, 1);
        msg++;
    }
}
void Send_Msg_UART7(char* msg){
    while(*msg != '\0'){
        UART_Push_to_Transmit(UART_NUM_7, *msg, 1);
        msg++;
    }
}

uint8* Rcv_Msg(UART_ChannelType my_uart){
    uint8* msg;
    msg = (uint8*)malloc(sizeof(uint8)*16);
    UART_Pop_the_Received(my_uart, msg);
    return msg;
}
