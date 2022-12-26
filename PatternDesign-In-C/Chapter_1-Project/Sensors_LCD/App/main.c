

/**
 * main.c
 */
#include "main.h"

void Send_Msg_UART5(char* msg);
void Send_Msg_UART7(char* msg);

void Test_UART_AlwaysFullBuffer_ISR_Configs(void);

int main(void){
    Test_UART_AlwaysFullBuffer_ISR_Configs();
}


void Test_UART_AlwaysFullBuffer_ISR_Configs(void)
{
    int i, j, l;
    App_Init();
    while(1){
        Send_Msg_UART5("Hello !! ");
        Poke_to_transmit(UART_NUM_5, UART_TRANSMIT_RECEIVE_ONE_CHAR);
        Send_Msg_UART5("my name is abdulrahman yasser");
        Poke_to_transmit(UART_NUM_5, UART_TRANSMIT_RECEIVE_ONE_CHAR);
        for(i = 0; i < 5; i++){
            Send_Msg_UART5("Hello !! ");
            Send_Msg_UART5("my name is abdulrahman yasser");
            Poke_to_transmit(UART_NUM_5, UART_TRANSMIT_RECEIVE_ONE_CHAR);
        }
        for(i = 0; i < 100; i++){
            for(j = 0; j < 1000; j++){

            }
        }
        while(1){
            Send_Msg_UART7("HELP MEE !!!!!!!!!!!!!!!!!!!");
            Poke_to_transmit(UART_NUM_7, 4);
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

void App_Init(void){
    Port_Init();
    uart_init();
    Gpt_Init();
    IntCtrl_Init();
}


void Send_Msg_UART5(char* msg){
    while(*msg != '\0'){
        Push_to_Transmit(UART_NUM_5, *msg, 1);
        msg++;
    }
}

void Send_Msg_UART7(char* msg){
    while(*msg != '\0'){
        Push_to_Transmit(UART_NUM_7, *msg, 1);
        msg++;
    }
}

uint8* Rcv_Msg(UART_ChannelType my_uart){
    uint8* msg;
    msg = (uint8*)malloc(sizeof(uint8)*16);
    Pop_the_Received(my_uart, msg);
    return msg;
}
