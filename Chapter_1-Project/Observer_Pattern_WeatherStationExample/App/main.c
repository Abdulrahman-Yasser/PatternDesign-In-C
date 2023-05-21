

/**
 * main.c
 */
#include "main.h"

void Board_init(void);

int main(){
    Board_init();

    struct TestingStruct *mine = Testing_Create();

    /* Histogram client */


    while(1){
        Delay_ms(1000);

        /* Publishing to the server */
        WeatherStation_Publish();
    }

}

void Board_init(void){
    Port_Init();
    I2C_init();
    ADC_Init();
    TempDriver_WeatherStation_Init();
}
