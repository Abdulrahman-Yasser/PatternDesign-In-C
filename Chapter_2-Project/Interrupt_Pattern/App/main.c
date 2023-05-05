

/**
 * main.c
 */

#include "main.h"


int main(void)
{
    InterruptPattern();
}

void InterruptPattern(void){
    Enable_Interrupts();
    Port_Init();
    LED_Init();
    IntCtrl_Init();
    ButtonInit();
    install();
    while(1);
}
