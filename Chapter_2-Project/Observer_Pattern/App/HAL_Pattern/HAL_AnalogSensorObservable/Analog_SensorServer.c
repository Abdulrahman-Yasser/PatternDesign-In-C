///*
// * Analog_SensorServer.c
// *
// *  Created on: May 22, 2023
// *      Author: Abdu
// */
//
//
//#include "../../General_Common/Std_Types.h"
//#include "../General_Mcal/ADC/Static/inc/ADC.h"
//
//#include "Analog_SensorServer.h"
//
//#include <stdlib.h>
//
//static void Sensor_Init(Sensor_AnalogType* const me, SENSOR_READ_TYPE (*GetValueFunction)(Sensor_AnalogType* const me));
//static void Sensor_Cleanup(Sensor_AnalogType* const me) ;
//
//static SENSOR_READ_TYPE GetValueFunction_Analog(Sensor_AnalogType* const me);
//
//
///* Constructor */
//static void Sensor_Init(Sensor_AnalogType* const me, SENSOR_READ_TYPE (*GetValueFunction)(Sensor_AnalogType* const me)) {
//    me->GetValue = GetValueFunction;
//}
//
///* Destructor */
//static void Sensor_Cleanup(Sensor_AnalogType* const me) {
//    me->GetValue = Null_Ptr;
//}
//
//Sensor_AnalogType* Sensor_Create(uint8 Sensor_ID){
//    Sensor_AnalogType* me = (Sensor_AnalogType*)malloc(sizeof(Sensor_AnalogType));
//    if(me != Null_Ptr){
//        me->Sensor_ID = Sensor_ID;
//        me->my_observable = Observable_Create();
//        Sensor_Init(me, GetValueFunction_Analog);
//    }
//    return me;
//}
//
//void Sensor_Destroy( Sensor_AnalogType* const me){
//    if(me != Null_Ptr){
//        Sensor_Cleanup(me);
//    }
//    free(me);
//}
//
//
//static SENSOR_READ_TYPE GetValueFunction_Analog(Sensor_AnalogType* const me){
//    return ADC_ReadOneValue( Sensor_Analog_Config[me->Sensor_ID].ADC_Num, Sensor_Analog_Config[me->Sensor_ID].sampleSequencer_Num);
//}
