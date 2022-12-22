#include "../inc/Senosr.h"
#include "../inc/Sensor_Types.h"
#include "../../../../Common/Compiler.h"

/* Constructor */
void Sensor_Init(Sensor_Type* const me, SENSOR_READ_TYPE (*GetValueFunction)(Sensor_Type* const me)) {
    me->value = 0;
    me->GetValue = GetValueFunction;
}

/* Destructor */
void Sensor_Cleanup(Sensor_Type* const me) {
    me->value = 0;
    me->GetValue = Null_Ptr;
}

/* Operation GetValue() */
SENSOR_READ_TYPE Sensor_GetValue(const Sensor_Type* const me){
    return me->value;
}

Sensor_Type* Sensor_Create(void){
    Sensor_Type *me = malloc(sizeof(Sensor_Type));
    if(me != Null_Ptr){
        Sensor_Init(me, Sensor_GetValue);
    }
    return me;
}

void Sensor_Destroy( const Sensor_Type* const me){
    if(me != Null_Ptr){
        Sensor_Cleanup(me);
    }
    free(me);
}
