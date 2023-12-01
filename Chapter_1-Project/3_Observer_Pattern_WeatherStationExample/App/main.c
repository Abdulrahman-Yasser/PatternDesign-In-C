

/**
 * main.c
 */
#include "main.h"
#include "HAL_Patterns/Server/TMDQueue_with_Observable/TMDQueue_with_Observable.h"
void Board_init(void);


void myLED_Response( struct TimeMarkedData* tmd){
    static DigitalInterface_Type *myLED;
    myLED = Digital_Interface_Create(DIO_Channel1_F);
    if(tmd->temperature_value > 20){
        myLED->Write_High(myLED);
    }else{
        myLED->Write_Low(myLED);
    }
}


int main(){
    Board_init();

    struct TestingStruct *mine = Testing_GetHandler();
    Testing_Init_Relations(mine);
    /* Histogram client */

    Observer* my_Observer;

    my_Observer = Observer_Create(myLED_Response);
    int i = 0;

    while(1){
        Delay_ms(1000);

        /* Publishing to the server */
        WeatherStation_Publish(Testing_Get_ItsTMDQueue_with_Observable(mine));


        /*
         * Real-time Subscribing and Un-Subscribing for the TMD Queue
         */
        i++;

        TMDQueue_with_Observable_Subscribe(Testing_Get_ItsTMDQueue_with_Observable(mine), my_Observer);

        switch(i){
        case 1:
            TMDQueue_with_Observable_Subscribe(Testing_Get_ItsTMDQueue_with_Observable(mine), my_Observer);
            break;
        case 2:
        case 3:
        case 4:
        case 5:
            break;
        case 6:
            TMDQueue_with_Observable_UnSubscribe(Testing_Get_ItsTMDQueue_with_Observable(mine), my_Observer);
            break;
        case 7:
        case 8:
        case 9:
        case 10:
            break;
        default:
            i = 0;
            break;
        }
    }

}

void Board_init(void){
    Port_Init();
    I2C_init();
    ADC_Init();
    RTC_DS1307_Init();
    TempDriver_WeatherStation_Init();
}
