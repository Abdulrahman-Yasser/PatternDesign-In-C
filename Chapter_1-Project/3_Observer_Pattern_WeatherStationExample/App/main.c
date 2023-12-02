

/**
 * main.c
 */
#include "main.h"
#include "HAL_Patterns/Server/TMDQueue_with_Observable/TMDQueue_with_Observable.h"
void Board_init(void);


struct TMDQueue_with_Observable_s *myTMDQueue_Observable;

struct FireDisplay *myFireDisplay;

struct HistogramDisplay *myHistogramDisplay;


int main(){
    Board_init();

    /* Initialization */
    myTMDQueue_Observable = TMDQueue_with_Observable_GetHandler();
    TMDQueue_with_Observable_Init(myTMDQueue_Observable);


    myFireDisplay = FireDisplay_GetHandler();
    FireDisplay_Init(myFireDisplay);

    DigitalInterface_Type* myBuzzer = Digital_Interface_Create(DIO_Channel1_B);
    DigitalInterface_Type* myLED = Digital_Interface_Create(DIO_Channel2_B);
    LCD_Handler_Type* myLCD = LCD_Create(LCD_Interface_I2C, 0);

    FireDisplay_setItsBUZZER(myFireDisplay, myBuzzer);
    FireDisplay_setItsLCD(myFireDisplay, myLCD);
    FireDisplay_setItsLED(myFireDisplay, myLED);

    myHistogramDisplay = HistogramDisplay_GetHandler();
    HistogramDisplay_Init(myHistogramDisplay);

    HistogramDisplay_setItsLCD(myHistogramDisplay, myLCD);

    /* Connecting observers with observables */

    TMDQueue_with_Observable_Subscribe(myTMDQueue_Observable, FireDisplay_getObserver());
    TMDQueue_with_Observable_Subscribe(myTMDQueue_Observable, HistogramDisplay_getObserver());

    /* Histogram client */

    while(1){
        Delay_ms(1000);

        /* Publishing to the server */
        WeatherStation_Publish(myTMDQueue_Observable);

    }

}

void Board_init(void){
    Port_Init();
    I2C_init();
    ADC_Init();
    RTC_DS1307_Init();
    TempDriver_WeatherStation_Init();
}
