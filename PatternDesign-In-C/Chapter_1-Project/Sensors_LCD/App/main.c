

/**
 * main.c
 */
#include "main.h"



int main(void)
{
    int i, j;
    App_Init();
    while(1){
        Send_Msg("Hello");
        transmit();
        for(i = 0; i < 1000; i++){
            for(j = 0; j < 1000; j++){

            }
            Send_Msg("and Welcome");
            transmit();
        }
    }
}


void App_Function(void){

}


void App_Init(void){
    Port_Init();
    IntCtrl_Init();
    uart_init();
    Gpt_Init();
}

void transmit(void){
    Poke_to_transmit(UART_NUM_5);
}

void Send_Msg(char* msg){
    while(*msg != '\0'){
        Push_to_Transmit(UART_NUM_5, *msg);
        msg++;
    }
}

uint8* Rcv_Msg(UART_ChannelType my_uart){
    uint8* msg;
    msg = (uint8*)malloc(sizeof(uint8)*16);
    Pop_the_Received(my_uart, msg);
    return msg;
}
