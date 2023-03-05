/*
 * Stack.h
 *
 *  Created on: Dec 26, 2022
 *      Author: abduy
 */

#ifndef COMMON_DATASTRUCTURE_STACK_STATIC_INC_STACK_H_
#define COMMON_DATASTRUCTURE_STACK_STATIC_INC_STACK_H_

#include "Stack_Types.h"

/* For Stack_uint32_Type Functions, which operate Stack that contains n slots of (uint32)*/
/**************************************************************************************
 *
 *                                    uint32
 *
 **************************************************************************************/
/* Constructor and Destructor Dynamic Allocation */
Stack_uint32_DYNAMIC_Type *Stack_Create_DYNAMIC_uint32(uint8 DynamicSize);
void Stack_Destroy_DYNAMIC_uint32(Stack_uint32_DYNAMIC_Type* const me);

/* Constructor and Destructor Static Allocation */
Stack_uint32_STATIC_Type *Stack_Create_STATIC_uint32(void);
void Stack_Destroy_STATIC_uint32(Stack_uint32_STATIC_Type* const me);


/* For Stack_uint16_Type Functions, which operate Stack that contains n slots of (uint16)*/
/**************************************************************************************
 *
 *                                    uint16
 *
 **************************************************************************************/
/* Constructor and Destructor*/
Stack_uint16_DYNAMIC_Type *Stack_Create_DYNAMIC_uint16(uint8 DynamicSize);
void Stack_Destroy_DYNAMIC_uint16(Stack_uint16_DYNAMIC_Type* const me);

/* Constructor and Destructor Static Allocation */
Stack_uint16_STATIC_Type *Stack_Create_STATIC_uint16(void);
void Stack_Destroy_STATIC_uint16(Stack_uint16_STATIC_Type* const me);


/* For Stack_uint8_Type Functions, which operate Stack that contains n slots of (uint8)*/
/**************************************************************************************
 *
 *                                    uint8
 *
 **************************************************************************************/
/* Constructor and Destructor*/
Stack_uint8_DYNAMIC_Type *Stack_Create_DYNAMIC_uint8(uint8 DynamicSize);
void Stack_Destroy_DYNAMIC_uint8(Stack_uint8_DYNAMIC_Type* const me);

/* Constructor and Destructor Static Allocation */
Stack_uint8_STATIC_Type *Stack_Create_STATIC_uint8(void);
void Stack_Destroy_STATIC_uint8(Stack_uint8_STATIC_Type* const me);


#endif /* COMMON_DATASTRUCTURE_STACK_STATIC_INC_STACK_H_ */
