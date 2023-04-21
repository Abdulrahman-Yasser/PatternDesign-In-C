/*
 * Digital_Interface.h
 *
 *  Created on: Apr 20, 2023
 *      Author: Abdu
 */

#ifndef DIGITAL_INTRFACE_DIGITAL_INTERFACE_H_
#define DIGITAL_INTRFACE_DIGITAL_INTERFACE_H_

#include "../General_Mcal/DIO/Static/inc/DIO_Types.h"

typedef struct DigitalInterface_struct DigitalInterface_Type;

struct DigitalInterface_struct{
    DIO_ChannelType Dio_Ch;
    DIO_LevelType Dio_Level;
    void (*Write_High)(DigitalInterface_Type* const me);
    void (*Write_Low)(DigitalInterface_Type* const me);
    void (*Write_Toggle)(DigitalInterface_Type* const me);
};

DigitalInterface_Type* Digital_Interface_Create(uint8 DIO_ID);
void Digital_Interface_Destroy(DigitalInterface_Type* me);


#endif /* DIGITAL_INTRFACE_DIGITAL_INTERFACE_H_ */
