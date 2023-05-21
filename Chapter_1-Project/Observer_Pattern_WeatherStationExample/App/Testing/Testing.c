/*
 * Testing.c
 *
 *  Created on: May 20, 2023
 *      Author: Abdu
 */



#include "Testing.h"



struct TestingStruct{
    struct TMDQueue_with_Observable_s *itsTMDQueue;
    struct FireDisplay *itsFireDisplay;
    struct HistogramDisplay *itsHistogramDisplay;
}myTestingStruct;

struct TestingStruct *Testing_Create(void){
    myTestingStruct.itsTMDQueue = weatherData_Queue_Create();
    myTestingStruct.itsFireDisplay = FireDisplay_GetHandler(myTestingStruct.itsTMDQueue);
    myTestingStruct.itsHistogramDisplay = HistogramDisplay_GetHandler();

    if(&myTestingStruct != Null_Ptr){
        Testing_Init_Relations();
    }

    return &myTestingStruct;
}


void Testing_Init_Relations(void){
    /* initializing the FireDisplay */

    FireDisplay_setItsTMDQueue(myTestingStruct.itsFireDisplay, myTestingStruct.itsTMDQueue);

   DigitalInterface_Type* fireDisplay_Buzzer;
   fireDisplay_Buzzer = Digital_Interface_Create(DIO_Channel4_B);
   FireDisplay_setItsBUZZER( myTestingStruct.itsFireDisplay, fireDisplay_Buzzer);

   DigitalInterface_Type* fireDisplay_Led;
   fireDisplay_Buzzer = Digital_Interface_Create(DIO_Channel3_B);
   FireDisplay_setItsBUZZER( myTestingStruct.itsFireDisplay, fireDisplay_Buzzer);

   LCD_Handler_Type *FireDisplay_LCD;
   FireDisplay_LCD = LCD_Create(LCD_Interface_I2C, 0);
   FireDisplay_setItsLCD(myTestingStruct.itsFireDisplay, FireDisplay_LCD);

   /* initializing the HistogramDisplay */
   HistogramDisplay_setItsTMDQueue(myTestingStruct.itsHistogramDisplay, myTestingStruct.itsTMDQueue);

   HistogramDisplay_setItsLCD(myTestingStruct.itsFireDisplay, FireDisplay_LCD);
}



void PublishData_To_Observers(struct TMDQueue_with_Observable_s *me){
    WeatherStation_Push();
}
