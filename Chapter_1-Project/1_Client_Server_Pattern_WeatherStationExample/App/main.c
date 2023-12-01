

/**
 * main.c
 */
#include "main.h"

void Board_init(void);

int main(){
    Board_init();

    TestBuilder * p_TestBuilder;

    p_TestBuilder = TestBuilder_Create();

    /* Histogram client */
    LCD_Handler_Type *my_lcd;
    my_lcd = LCD_Create(LCD_Interface_I2C, HISTOGRAM_LCD_ID);
    HistogramDisplay_setItsLCD(&(p_TestBuilder->itsHistogramDisplay), my_lcd);

    /* FireDisplay client */
    DigitalInterface_Type* my_Buzzer;
    my_Buzzer = Digital_Interface_Create(Buzzer_ID);
    FireDisplay_setItsBUZZER(&(p_TestBuilder->itsFireDisplay), my_Buzzer);

    DigitalInterface_Type* my_Led;
    my_Led = Digital_Interface_Create(Led_ID);
    FireDisplay_setItsLED(&(p_TestBuilder->itsFireDisplay), my_Led);

    // It should be a separate display, but i am poor
    FireDisplay_setItsLCD(&(p_TestBuilder->itsFireDisplay), my_lcd);

    while(1){
        Delay_ms(1000);

        /* Read the tmdQueue values and push it to the server */
        /* Publishing to the server */
        WeatherStation_Module_acquireValue(&(p_TestBuilder->itsWeatherStation_Module));

        /* Client 1 is Reading from the server */
        HistogramDisplay_updateHistogram(&(p_TestBuilder->itsHistogramDisplay));

        /* Client 2 is Reading from the server */
        FireDisplay_updateFireDisplay(&(p_TestBuilder->itsFireDisplay));

    }

}

void Board_init(void){
    Port_Init();
    I2C_init();
    ADC_Init();
    RTC_DS1307_Init();
    TempDriver_WeatherStation_Init();
}
