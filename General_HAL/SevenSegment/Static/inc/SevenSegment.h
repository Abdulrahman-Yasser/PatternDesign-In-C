/*
 * SevenSegment.h
 *
 *  Created on: Aug 19, 2023
 *      Author: Abdu
 */

#ifndef SEVENSEGMENT_STATIC_INC_SEVENSEGMENT_H_
#define SEVENSEGMENT_STATIC_INC_SEVENSEGMENT_H_

#include "SevenSegment_Types.h"

void SeventSegment_WriteSpecificOne(uint8 SevenSegmentID, uint8 num);
void SeventSegment_WriteAllOfIt(uint8* num);

uint8* SeventSegment_ReadAllOfIt(uint8 SevenSegmentID);
uint8 SeventSegment_ReadSpecificOne(uint8 SevenSegmentID);


#endif /* SEVENSEGMENT_STATIC_INC_SEVENSEGMENT_H_ */
