

/**
 * main.c
 */

#include "main.h"

int main(void)
{

}

void main_init(void){
    Port_Init();
    ADC_Init();
    Dio_Init();
}

void main_loop(void){
    WeatherStationData* my_data = WeatherStationData_Create();
    WeatherStationDataQueue* my_dataQueue = WeatherStationDataQueue_Create();
    SensorThread* my_sensorThread = SensorThread_create();
    WeatherStationDisplay* my_Display = WeatherStationDisplay_Create();
    WeatherStationController* my_controller = WeatherStationController_Create();

    LCD_Handler_Type *my_lcd = LCD_Create(LCD_Interface_I2C, 0);

    WeatherStationController_setItsWeatherStationDisplay(my_controller, my_Display);
    WeatherStationDisplay_SetItsLCD(my_Display, my_lcd);
    SensorThread_setItsDataQueue(my_sensorThread, my_dataQueue);

    while(1){
        Delay_ms(500);
        SensorThread_updateData(my_sensorThread);
        Delay_ms(200);
        my_data = WeatherStationDataQueue_remove(my_dataQueue);
        WeatherStationController_handleWeatherStationData(my_controller, my_data);
    }
}
