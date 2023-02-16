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
/* Constructor and Destructor Dynamic Allocation */
Queue_uint32_DYNAMIC_Type *Queue_Create_DYNAMIC_uint32(uint8 DynamicSize);
void Queue_Destroy_DYNAMIC_uint32(Queue_uint32_DYNAMIC_Type* const me);

/* Constructor and Destructor Static Allocation */
Queue_uint32_STATIC_Type *Queue_Create_STATIC_uint32(void);
void Queue_Destroy_STATIC_uint32(Queue_uint32_STATIC_Type* const me);


/* For Queue_uint16_Type Functions, which operate Queue that contains n slots of (uint16)*/
/**************************************************************************************
 *
 *                                    uint16
 *
 **************************************************************************************/
/* Constructor and Destructor*/
Queue_uint16_DYNAMIC_Type *Queue_Create_DYNAMIC_uint16(uint8 DynamicSize);
void Queue_Destroy_DYNAMIC_uint16(Queue_uint16_DYNAMIC_Type* const me);

/* Constructor and Destructor Static Allocation */
Queue_uint16_STATIC_Type *Queue_Create_STATIC_uint16(void);
void Queue_Destroy_STATIC_uint16(Queue_uint16_STATIC_Type* const me);


/* For Queue_uint8_Type Functions, which operate Queue that contains n slots of (uint8)*/
/**************************************************************************************
 *
 *                                    uint8
 *
 **************************************************************************************/
/* Constructor and Destructor*/
Queue_uint8_DYNAMIC_Type *Queue_Create_DYNAMIC_uint8(uint8 DynamicSize);
void Queue_Destroy_DYNAMIC_uint8(Queue_uint8_DYNAMIC_Type* const me);

/* Constructor and Destructor Static Allocation */
Queue_uint8_STATIC_Type *Queue_Create_STATIC_uint8(void);
void Queue_Destroy_STATIC_uint8(Queue_uint8_STATIC_Type* const me);

#endif /* COMMON_DATASTRUCTURE_QUEUE_QUEUE_H_ */
