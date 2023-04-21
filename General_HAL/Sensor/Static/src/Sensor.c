

#include "../inc/Senosr.h"
#include "../inc/Sensor_Types.h"
#include "../../Dynamic/inc/Sensor_Cfg.h"

#include "../../General_Common/Compiler.h"
#include "../../General_Mcal/DIO/Static/inc/DIO.h"
#include "../General_Mcal/ADC/Static/inc/ADC.h"

#include <stdlib.h>

void Sensor_Init(Sensor_Type* const me, SENSOR_READ_TYPE (*GetValueFunction)(Sensor_Type* const me));
void Sensor_Cleanup(Sensor_Type* const me) ;

static SENSOR_READ_TYPE GetValueFunction_Digital(Sensor_Type* const me);
static SENSOR_READ_TYPE GetValueFunction_Analog(Sensor_Type* const me);


/* Constructor */
void Sensor_Init(Sensor_Type* const me, SENSOR_READ_TYPE (*GetValueFunction)(Sensor_Type* const me)) {
    me->GetValue = GetValueFunction;
}

/* Destructor */
void Sensor_Cleanup(Sensor_Type* const me) {
    me->GetValue = Null_Ptr;
}

Sensor_Type* Sensor_Create(uint8 Sensor_ID, Sensor_IntrfaceType SensorInterface){
    Sensor_Type* me = (Sensor_Type*)malloc(sizeof(Sensor_Type));
    if(me != Null_Ptr){
        me->SensorInterface = SensorInterface;
        me->Sensor_ID = Sensor_ID;
        if(SensorInterface == Sensor_Interface_Analog){
            Sensor_Init(me, GetValueFunction_Analog);
        }else if(SensorInterface == Sensor_Interface_Digital){
            Sensor_Init(me, GetValueFunction_Digital);
        }
    }
    return me;
}

void Sensor_Destroy( Sensor_Type* const me){
    if(me != Null_Ptr){
        Sensor_Cleanup(me);
    }
    free(me);
}


static SENSOR_READ_TYPE GetValueFunction_Digital(Sensor_Type* const me){
    return Dio_ReadChannel(Sensor_Digital_Config[me->Sensor_ID].Sensor_Data_Pins);
}

static SENSOR_READ_TYPE GetValueFunction_Analog(Sensor_Type* const me){
    return ADC_ReadOneValue( Sensor_Analog_Config[me->Sensor_ID].ADC_Num, Sensor_Analog_Config[me->Sensor_ID].sampleSequencer_Num);
}
