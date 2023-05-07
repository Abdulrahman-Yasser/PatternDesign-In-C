

/**
 * main.c
 */

#include "main.h"

#define FIRE_CIRCUIT_SENSOR_TEMPERATURE     0
#define FIRE_CIRCUIT_SENSOR_LIGHT     1

int main(void)
{
    main_init();
    Pattern_Creation();
}

void main_init(void){
    Enable_Interrupts();
    Port_Init();
    ADC_Init();
    IntCtrl_Init();
    Gpt_Init();
    Gpt_EnableNotification(Gpt_Channel_Normal_0);
}

void Pattern_Creation(void){
    FCPeriodicPoller_t *my_FCPeriodicPoller;
    FCTimer_t *my_FCTimer;
    FireCircuitSensor_t *my_FireCircuitSensor_1, *my_FireCircuitSensor_2;
    FireDisplay_t *my_FireDisplay;

    my_FCPeriodicPoller = FCPeriodicPoller_Create();
    my_FCTimer = FCTimer_Create();
    FCTimer_setItsTimerChannel(my_FCTimer, Gpt_Channel_Normal_0);
    my_FireCircuitSensor_1 = FireCircuitSensor_Create(TEMPERATURE_ID, Sensor_Interface_Analog);
    FireCircuitSensor_setThreshold(my_FireCircuitSensor_1, 200);
    my_FireCircuitSensor_2 = FireCircuitSensor_Create(LIGHT_ID, Sensor_Interface_Analog);
    FireCircuitSensor_setThreshold(my_FireCircuitSensor_2, 200);
    my_FireDisplay = FireDisplay_Create();

    FCTimer_installTimerInterruptHandler(my_FCPeriodicPoller->itsFCTimer, FCPeriodicPoller_poll);

    FCPeriodicPoller_setItsFCTimer(my_FCPeriodicPoller, my_FCTimer);
    FCPeriodicPoller_setItsFireDisplay(my_FCPeriodicPoller, my_FireDisplay);
    FCPeriodicPoller_setPollTime(my_FCPeriodicPoller, DEFAULT_POLLING_TIME);
    FCPeriodicPoller_addItsFireCircuitSensor(my_FCPeriodicPoller, my_FireCircuitSensor_1, FIRE_CIRCUIT_SENSOR_TEMPERATURE);
    FCPeriodicPoller_addItsFireCircuitSensor(my_FCPeriodicPoller, my_FireCircuitSensor_2, FIRE_CIRCUIT_SENSOR_LIGHT);
    FCPeriodicPoller_startPolling(my_FCPeriodicPoller);
    while(1);
}
