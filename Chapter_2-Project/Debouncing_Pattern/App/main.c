

/**
 * main.c
 */

#include "main.h"

int main(void)
{
    Debouncing_Pattern_Iint();
    Debouncing_Pattern_Loop();
}


void Debouncing_Pattern_Iint(void){
    Port_Init();
}

void Debouncing_Pattern_Loop(void){
    Button_Type* itsButton;
    ButtonDriver* TheButtonDriver;
    LedEmitter* itsLedEmitter;
    TheButtonDriver = ButtonDriver_Create();
    itsLedEmitter = LedEmitter_Create(DIO_Channel1_F);
    itsButton = Button_Create(DEBOUNCE_BUTTON_DIO_ID);
    ButtonDriver_setItsButton(TheButtonDriver, itsButton);
    ButtonDriver_setItsLedEmitter(TheButtonDriver, itsLedEmitter);
    while(1){
        ButtonDriver_eventReceive(TheButtonDriver);
    }
}

