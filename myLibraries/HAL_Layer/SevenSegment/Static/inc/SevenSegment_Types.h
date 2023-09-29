/*
 * SevenSegment_Types.h
 *
 *  Created on: Aug 19, 2023
 *      Author: Abdu
 */

#ifndef SEVENSEGMENT_STATIC_INC_SEVENSEGMENT_TYPES_H_
#define SEVENSEGMENT_STATIC_INC_SEVENSEGMENT_TYPES_H_

#include "MCAL_Layer/DIO/Static/inc/DIO_Types.h"
#include "Common/Std_Types.h"

typedef struct{
    DIO_ChannelType a;
    DIO_ChannelType b;
    DIO_ChannelType c;
    DIO_ChannelType d;
    DIO_ChannelType e;
    DIO_ChannelType f;
    DIO_ChannelType g;
    DIO_ChannelType Dot;
}SeventSegment_Type;



#endif /* SEVENSEGMENT_STATIC_INC_SEVENSEGMENT_TYPES_H_ */
