

/**
 * main.c
 */
#include "main.h"

void Board_init(void);

int main(){
    Board_init();

    struct TestingStruct *mine = Testing_GetHandler();
    Testing_Init_Relations(mine);
    /* Histogram client */


    while(1){
        Delay_ms(1000);

        /* Publishing to the server */
        WeatherStation_Publish(Testing_Get_ItsTMDQueue_with_Observable(mine));
    }

}

void Board_init(void){
    Port_Init();
    I2C_init();
    ADC_Init();
    TempDriver_WeatherStation_Init();
}
