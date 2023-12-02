

/**
 * main.c
 */
#include "main.h"

#include "HAL_Patterns/Client/Buzzer/Buzzer.h"
#include "HAL_Patterns/Client/LED_1/LED_1.h"
#include "HAL_Patterns/Client/LED_2/LED_2.h"

#include "HAL_Patterns/Server/Server_with_Observable/Server_with_Observable.h"
#include "HAL_Patterns/Server/Publisher_API/Publisher_API.h"

void Board_init(void);

static DigitalInterface_Type *myLED;

void myLED_Response( uint8 status){
    if(status == 1){
        myLED->Write_High(myLED);
    }else if (status == 0){
        myLED->Write_Low(myLED);
    }
}


int main(){
    Board_init();

    myLED = Digital_Interface_Create(DIO_Channel3_F);

    struct Buzzer_s* my_buzzer_Client = Buzzer_GetHandler();
    struct LED_1_s* my_LED_1_Client = LED_1_GetHandler();
    struct LED_2_s* my_LED_2_Client = LED_2_GetHandler();

    struct Server_with_Observable_s* my_Button_Server = get_my_server();
    Server_with_Observable_Init(my_Button_Server);


    my_LED_1_Init(my_LED_1_Client, Server_with_Observable_GetObservable(my_Button_Server));
    my_LED_2_Init(my_LED_2_Client, Server_with_Observable_GetObservable(my_Button_Server));
    my_Buzzer_Init(my_buzzer_Client, Server_with_Observable_GetObservable(my_Button_Server));


    Observer* DynamicObserver = Observer_Create(myLED_Response);
    Observable_Type* TheObservable= Server_with_Observable_GetObservable(my_Button_Server);
    TheObservable->Subscribe(TheObservable, DynamicObserver);

    uint32 k = 0;

    while(1){
        Delay_ms(100);
        ButtonStatus_Publish(my_Button_Server);
        k++;
        if(k == 50){
            TheObservable->unSubscribe(TheObservable, DynamicObserver);
            myLED_Response( 0);
        }else if(k == 100){
            TheObservable->Subscribe(TheObservable, DynamicObserver);
            k = 0;
        }
    }
}

void Board_init(void){
    Port_Init();
}
