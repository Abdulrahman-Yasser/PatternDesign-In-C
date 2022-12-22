/*
 * Queue.h
 *
 *  Created on: Dec 20, 2022
 *      Author: abduy
 */

#ifndef COMMON_DATASTRUCTURE_QUEUE_QUEUE_H_
#define COMMON_DATASTRUCTURE_QUEUE_QUEUE_H_

#include "../../../../Platform_Types.h"
#include "Queue_Types.h"

/* For Queue_uint32_Type Functions, which operate Queue that contains n slots of (uint32)*/
/**************************************************************************************
 *
 *                                    uint32
 *
 **************************************************************************************/
/* Constructor and Destructor*/
Queue_uint32_Type *Queue_Create_uint32(Queue_Dynamic_SizeType DynamicSize);
void Queue_Destroy_uint32(Queue_uint32_Type* const me);



/* For Queue_uint16_Type Functions, which operate Queue that contains n slots of (uint16)*/
/**************************************************************************************
 *
 *                                    uint16
 *
 **************************************************************************************/
/* Constructor and Destructor*/
Queue_uint16_Type *Queue_Create_uint16(Queue_Dynamic_SizeType DynamicSize);
void Queue_Destroy_uint16(Queue_uint16_Type* const me);



/* For Queue_uint8_Type Functions, which operate Queue that contains n slots of (uint8)*/
/**************************************************************************************
 *
 *                                    uint8
 *
 **************************************************************************************/
/* Constructor and Destructor*/
Queue_uint8_Type *Queue_Create_uint8(Queue_Dynamic_SizeType DynamicSize);
void Queue_Destroy_uint8(Queue_uint8_Type* const me);


#endif /* COMMON_DATASTRUCTURE_QUEUE_QUEUE_H_ */
