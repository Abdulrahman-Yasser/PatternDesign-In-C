

/**
 * main.c
 */
#include "main.h"

int main(){
    TestBuilder * p_TestBuilder;
    p_TestBuilder = TestBuilder_Create();


    while(1){
        Delay_ms(1000);

        /* Read the tmdQueue values and push it to the server */
        WeatherStation_Module_acquireValue(&(p_TestBuilder->itsWeatherStation_Module));

        HistogramDisplay_updateHistogram(&(p_TestBuilder->itsHistogramDisplay));

    }

    TestBuilder_Destroy(p_TestBuilder);
    return 0;
}
