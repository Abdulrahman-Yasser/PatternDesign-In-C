

/**
 * main.c
 */

#include "main.h"

int main(void)
{
    main_init();
    main_loop();
}


void main_init(void){
    Port_Init();
    Dio_Init();
}

void main_loop(void){
    DigitalObservableSensor_Type* my_sensor;
    my_sensor = DigitalObservableSensor_Create(DIO_Channel2_B);
    Motor_Observer_Init(my_sensor);
    Led_Observer_Init(my_sensor);
    Buzzer_Observer_Init(my_sensor);
    while(1){
        Delay_ms(500);
        /* it notify all clients */
        my_sensor->GetValue(my_sensor);
    }
}
