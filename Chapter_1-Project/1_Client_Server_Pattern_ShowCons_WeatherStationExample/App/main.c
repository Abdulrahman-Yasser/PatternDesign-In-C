

/**
 * main.c
 */
#include "main.h"

void Board_init(void);

void my_isr_dio(void);

TestBuilder * p_TestBuilder;

Button_Type *my_button;

uint8 Button_flag = 0;

int main(){
    Board_init();

    p_TestBuilder = TestBuilder_Create();

    my_button =Button_Create(DIO_BUTTON_ID);
    if( E_NOK == Button_Set_CallBackFuncISR(my_button, my_isr_dio)){
        while(1);
    }

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



    while(1){

        if(Button_flag){
            Button_flag = 0;
            /* Read the tmdQueue values and push it to the server */
            /* Publishing to the server */

            /* Client 1 is Reading from the server */
            HistogramDisplay_updateHistogram(&(p_TestBuilder->itsHistogramDisplay));

            /* Client 2 is Reading from the server */
            FireDisplay_updateFireDisplay(&(p_TestBuilder->itsFireDisplay));
        }
    }

}

void my_isr_dio(void){
    if( Button_Check_Isr(my_button) ){
        Button_flag = 1;
        WeatherStation_Module_acquireValue(&(p_TestBuilder->itsWeatherStation_Module));
        Button_Remove_Isr(my_button);
    }
}


void Board_init(void){
    Port_Init();
    I2C_init();
    ADC_Init();
    Dio_Init();
    IntCtrl_Init();
    TempDriver_WeatherStation_Init();
}
