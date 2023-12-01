///*
// * Testing.c
// *
// *  Created on: May 20, 2023
// *      Author: Abdu
// */
//
//
//
//#include "Testing.h"
//
//
//struct TestingStruct{
//    struct TMDQueue_with_Observable_s *itsTMDQueue_Observable;
//    struct FireDisplay *itsFireDisplay;
//    struct HistogramDisplay *itsHistogramDisplay;
//}myTestingStruct;
//
//struct TestingStruct *Testing_GetHandler(void){
//    return &(myTestingStruct);
//}
//
//
//void Testing_Init_Relations(struct TestingStruct *me){
//
//    me->itsTMDQueue_Observable = TMDQueue_with_Observable_GetHandler();
//    me->itsFireDisplay = FireDisplay_GetHandler();
//    me->itsHistogramDisplay = HistogramDisplay_GetHandler();
//
//    /* initializing the FireDisplay */
//    TMDQueue_with_Observable_Init(me->itsTMDQueue_Observable);
//
//    FireDisplay_Init(me->itsFireDisplay, me->itsTMDQueue_Observable);
//
//   DigitalInterface_Type* fireDisplay_Buzzer;
//   fireDisplay_Buzzer = Digital_Interface_Create(DIO_Channel1_B);
//   FireDisplay_setItsBUZZER( me->itsFireDisplay, fireDisplay_Buzzer);
//
//   DigitalInterface_Type* fireDisplay_Led;
//   fireDisplay_Led = Digital_Interface_Create(DIO_Channel2_B);
//   FireDisplay_setItsLED(me->itsFireDisplay, fireDisplay_Led);
//
//   LCD_Handler_Type *FireDisplay_LCD;
//   FireDisplay_LCD = LCD_Create(LCD_Interface_I2C, 0);
//   FireDisplay_setItsLCD(me->itsFireDisplay, FireDisplay_LCD);
//
//   /* initializing the HistogramDisplay */
//   HistogramDisplay_Init(me->itsHistogramDisplay, me->itsTMDQueue_Observable);
//
//   HistogramDisplay_setItsLCD(me->itsHistogramDisplay, FireDisplay_LCD);
//}
//
//struct TMDQueue_with_Observable_s *Testing_Get_ItsTMDQueue_with_Observable(struct TestingStruct *me){
//    return me->itsTMDQueue_Observable;
//}
//
//
//void PublishData_To_Observers(struct TMDQueue_with_Observable_s *me){
//    WeatherStation_Publish(me);
//}
