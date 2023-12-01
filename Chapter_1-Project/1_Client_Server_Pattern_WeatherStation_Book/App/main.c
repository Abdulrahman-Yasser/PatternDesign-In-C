

/**
 * main.c
 */
#include "main.h"

void Board_init(void);

int main(){
    Board_init();

    TestBuilder * p_TestBuilder;

    p_TestBuilder = TestBuilder_Create();

    LCD_Handler_Type *my_lcd;
    my_lcd = LCD_Create(LCD_Interface_I2C, HISTOGRAM_LCD_ID);
    HistogramDisplay_setItsLCD(&(p_TestBuilder->itsHistogramDisplay), my_lcd);

    while(1){
        Delay_ms(1000);

        /* Read the tmdQueue values and push it to the server */
        /* Publishing to the server */
        WeatherStation_Module_acquireValue(&(p_TestBuilder->itsWeatherStation_Module));

        /* Subscribing to the server */
        HistogramDisplay_updateHistogram(&(p_TestBuilder->itsHistogramDisplay));

    }

}

void Board_init(void){
    Port_Init();
    I2C_init();
    ADC_Init();

    TempDriver_WeatherStation_Init();
    RTC_DS1307_Init();
}
