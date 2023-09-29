/*
 * SevenSegment.c
 *
 *  Created on: Aug 19, 2023
 *      Author: Abdu
 */

#include "../inc/SevenSegment.h"
#include "../../Dynamic/inc/SevenSegment_Cfg.h"
#include "MCAL_Layer/DIO/Static/inc/DIO.h"

static uint8 result_g[SEVEN_SEGMENT_CONFIGURED_NUMBER];

static const uint8 SevenSegmentNumbers[10] = {
    0x3F, 0x05, 0b01011011, 0b001001111, 0b01100110, 0b01101101,
    0b01111101, 0b00000111, 0x7f, 0b01101111
};

static uint8 SevenSegmentGetNumber(uint8 result){
    int i;
    for(i = 0; i < 10; i++){
        if(result == SevenSegmentNumbers[i]){
            return i;
        }
    }
    return (uint8)-1;
}

void SeventSegment_WriteSpecificOne(uint8 SevenSegmentID, uint8 num){
    Dio_WriteChannel(SevenSegment_Container[SevenSegmentID].a, SevenSegmentNumbers[num] & 0x01);
    Dio_WriteChannel(SevenSegment_Container[SevenSegmentID].b, SevenSegmentNumbers[num]& 0x02);
    Dio_WriteChannel(SevenSegment_Container[SevenSegmentID].c, SevenSegmentNumbers[num]& 0x04);
    Dio_WriteChannel(SevenSegment_Container[SevenSegmentID].d, SevenSegmentNumbers[num]& 0x08);
    Dio_WriteChannel(SevenSegment_Container[SevenSegmentID].e, SevenSegmentNumbers[num]& 0x10);
    Dio_WriteChannel(SevenSegment_Container[SevenSegmentID].f, SevenSegmentNumbers[num]& 0x20);
    Dio_WriteChannel(SevenSegment_Container[SevenSegmentID].g, SevenSegmentNumbers[num]& 0x40);
    Dio_WriteChannel(SevenSegment_Container[SevenSegmentID].Dot, SevenSegmentNumbers[num]& 0x80);
}

void SeventSegment_WriteAllOfIt(uint8* num){
    int i;
    for(i = 0; i < SEVEN_SEGMENT_CONFIGURED_NUMBER; i++){
        SeventSegment_WriteSpecificOne(i, num[i]);
    }
}

uint8* SeventSegment_ReadAllOfIt(uint8 SevenSegmentID){
    int i;
    for(i = 0; i < SEVEN_SEGMENT_CONFIGURED_NUMBER; i++){
        result_g[i] = SeventSegment_ReadSpecificOne(i);
    }
    return result_g;
}


uint8 SeventSegment_ReadSpecificOne(uint8 SevenSegmentID){
    uint8 result = 0;
    result |= Dio_ReadChannel(SevenSegment_Container[SevenSegmentID].a) << 0;
    result |= Dio_ReadChannel(SevenSegment_Container[SevenSegmentID].b) << 1;
    result |= Dio_ReadChannel(SevenSegment_Container[SevenSegmentID].c) << 2;
    result |= Dio_ReadChannel(SevenSegment_Container[SevenSegmentID].d) << 3;
    result |= Dio_ReadChannel(SevenSegment_Container[SevenSegmentID].e) << 4;
    result |= Dio_ReadChannel(SevenSegment_Container[SevenSegmentID].f) << 5;
    result |= Dio_ReadChannel(SevenSegment_Container[SevenSegmentID].g) << 6;
    result |= Dio_ReadChannel(SevenSegment_Container[SevenSegmentID].Dot) << 7;
    return SevenSegmentGetNumber(result);
}


