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

/* For Queue_uint32_Dynamic_Type Functions, which operate Queue that contains n slots of (uint32)*/

/* Constructor and Destructor*/
void Queue_Init_uint32_Dynamic(Queue_uint32_Dynamic_Type* const me  ,int (*isFullFunction)(Queue_uint32_Dynamic_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint32_Dynamic_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint32_Dynamic_Type* const me),
                void (*insertFunction)(Queue_uint32_Dynamic_Type* const me, uint32 x) ,uint8 (*removeFunction)(Queue_uint32_Dynamic_Type* const me) );

void Queue_CleanUp_uint32_Dynamic(Queue_uint32_Dynamic_Type* const me);

/* Operations */
uint8 Queue_isFull_uint32_Dynamic(Queue_uint32_Dynamic_Type* const me);
uint8 Queue_isEmpty_uint32_Dynamic(Queue_uint32_Dynamic_Type *const me);
uint8 Queue_getSize_uint32_Dynamic(Queue_uint32_Dynamic_Type* const me);
void Queue_insert_uint32_Dynamic(Queue_uint32_Dynamic_Type* const me, uint32 x);
uint8 Queue_remove_uint32_Dynamic(Queue_uint32_Dynamic_Type* const me);

Queue_uint32_Dynamic_Type *Queue_Create_uint32_Dynamic(void);
void Queue_Destroy_uint32_Dynamic(Queue_uint32_Dynamic_Type* const me);

/* For Queue_uint16_Dynamic_Type Functions, which operate Queue that contains n slots of (uint16)*/

/* Constructor and Destructor*/
void Queue_Init_uint16_Dynamic(Queue_uint16_Dynamic_Type* const me  ,int (*isFullFunction)(Queue_uint16_Dynamic_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint16_Dynamic_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint16_Dynamic_Type* const me),
                void (*insertFunction)(Queue_uint16_Dynamic_Type* const me, uint32 x) ,uint8 (*removeFunction)(Queue_uint16_Dynamic_Type* const me) );

void Queue_CleanUp_uint16_Dynamic(Queue_uint16_Dynamic_Type* const me);

/* Operations */
uint8 Queue_isFull_uint16_Dynamic(Queue_uint16_Dynamic_Type* const me);
uint8 Queue_isEmpty_uint16_Dynamic(Queue_uint16_Dynamic_Type *const me);
uint8 Queue_getSize_uint16_Dynamic(Queue_uint16_Dynamic_Type* const me);
void Queue_insert_uint16_Dynamic(Queue_uint16_Dynamic_Type* const me, uint32 x);
uint8 Queue_remove_uint16_Dynamic(Queue_uint16_Dynamic_Type* const me);

Queue_uint16_Dynamic_Type *Queue_Create_uint16_Dynamic(void);
void Queue_Destroy_uint16_Dynamic(Queue_uint16_Dynamic_Type* const me);

/* For Queue_uint8_Dynamic_Type Functions, which operate Queue that contains n slots of (uint8)*/

/* Constructor and Destructor*/
void Queue_Init_uint8_Dynamic(Queue_uint8_Dynamic_Type* const me  ,int (*isFullFunction)(Queue_uint8_Dynamic_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint8_Dynamic_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint8_Dynamic_Type* const me),
                void (*insertFunction)(Queue_uint8_Dynamic_Type* const me, uint32 x) ,uint8 (*removeFunction)(Queue_uint8_Dynamic_Type* const me) );

void Queue_CleanUp_uint8_Dynamic(Queue_uint8_Dynamic_Type* const me);

/* Operations */
uint8 Queue_isFull_uint8_Dynamic(Queue_uint8_Dynamic_Type* const me);
uint8 Queue_isEmpty_uint8_Dynamic(Queue_uint8_Dynamic_Type *const me);
uint8 Queue_getSize_uint8_Dynamic(Queue_uint8_Dynamic_Type* const me);
void Queue_insert_uint8_Dynamic(Queue_uint8_Dynamic_Type* const me, uint32 x);
uint8 Queue_remove_uint8_Dynamic(Queue_uint8_Dynamic_Type* const me);

Queue_uint8_Dynamic_Type *Queue_Create_uint8_Dynamic(void);
void Queue_Destroy_uint8_Dynamic(Queue_uint8_Dynamic_Type* const me);

/* For Queue_uint32_8_Type Functions, which operate Queue that contains 32 bytes, 8 slots of (uint32)*/

/* Constructor and Destructor*/
void Queue_Init_uint32_8(Queue_uint32_8_Type* const me  ,int (*isFullFunction)(Queue_uint32_8_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint32_8_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint32_8_Type* const me),
                void (*insertFunction)(Queue_uint32_8_Type* const me, uint32 x) ,uint8 (*removeFunction)(Queue_uint32_8_Type* const me) );

void Queue_CleanUp_uint32_8(Queue_uint32_8_Type* const me);

/* Operations */
uint8 Queue_isFull_uint32_8(Queue_uint32_8_Type* const me);
uint8 Queue_isEmpty_uint32_8(Queue_uint32_8_Type *const me);
uint8 Queue_getSize_uint32_8(Queue_uint32_8_Type* const me);
void Queue_insert_uint32_8(Queue_uint32_8_Type* const me, uint32 x);
uint8 Queue_remove_uint32_8(Queue_uint32_8_Type* const me);

Queue_uint32_8_Type *Queue_Create_uint32_8(void);
void Queue_Destroy_uint32_8(Queue_uint32_8_Type* const me);

/* For Queue_uint32_16_Type Functions, which operate Queue that contains 64 bytes, 16 slots of (uint32)*/

/* Constructor and Destructor*/
void Queue_Init_uint32_16(Queue_uint32_16_Type* const me  ,int (*isFullFunction)(Queue_uint32_16_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint32_16_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint32_16_Type* const me),
                void (*insertFunction)(Queue_uint32_16_Type* const me, uint32 x) ,uint8 (*removeFunction)(Queue_uint32_16_Type* const me) );

void Queue_CleanUp_uint32_16(Queue_uint32_16_Type* const me);

/* Operations */
uint8 Queue_isFull_uint32_16(Queue_uint32_16_Type* const me);
uint8 Queue_isEmpty_uint32_16(Queue_uint32_16_Type *const me);
uint8 Queue_getSize_uint32_16(Queue_uint32_16_Type* const me);
void Queue_insert_uint32_16(Queue_uint32_16_Type* const me, uint32 x);
uint8 Queue_remove_uint32_16(Queue_uint32_16_Type* const me);

Queue_uint32_16_Type *Queue_Create_uint32_16(void);
void Queue_Destroy_uint32_16(Queue_uint32_16_Type* const me);

/* For Queue_uint32_32_Type Functions, which operate Queue that contains 128 bytes, 32 slots of (uint32)*/

/* Constructor and Destructor*/
void Queue_Init_uint32_32(Queue_uint32_32_Type* const me  ,int (*isFullFunction)(Queue_uint32_32_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint32_32_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint32_32_Type* const me),
                void (*insertFunction)(Queue_uint32_32_Type* const me, uint32 x) ,uint8 (*removeFunction)(Queue_uint32_32_Type* const me) );

void Queue_CleanUp_uint32_32(Queue_uint32_32_Type* const me);

/* Operations */
uint8 Queue_isFull_uint32_32(Queue_uint32_32_Type* const me);
uint8 Queue_isEmpty_uint32_32(Queue_uint32_32_Type *const me);
uint8 Queue_getSize_uint32_32(Queue_uint32_32_Type* const me);
void Queue_insert_uint32_32(Queue_uint32_32_Type* const me, uint32 x);
uint8 Queue_remove_uint32_32(Queue_uint32_32_Type* const me);

Queue_uint32_32_Type *Queue_Create_uint32_32(void);
void Queue_Destroy_uint32_32(Queue_uint32_32_Type* const me);


/* For Queue_uint16_8_Type Functions, which operate Queue that contains 16 bytes, 8 slots of (uint16)*/

/* Constructor and Destructor*/
void Queue_Init_uint16_8(Queue_uint16_8_Type* const me  ,int (*isFullFunction)(Queue_uint16_8_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint16_8_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint16_8_Type* const me),
                void (*insertFunction)(Queue_uint16_8_Type* const me, uint16 x) ,uint8 (*removeFunction)(Queue_uint16_8_Type* const me) );

void Queue_CleanUp_uint16_8(Queue_uint16_8_Type* const me);

/* Operations */
uint8 Queue_isFull_uint16_8(Queue_uint16_8_Type* const me);
uint8 Queue_isEmpty_uint16_8(Queue_uint16_8_Type *const me);
uint8 Queue_getSize_uint16_8(Queue_uint16_8_Type* const me);
void Queue_insert_uint16_8(Queue_uint16_8_Type* const me, uint16 x);
uint8 Queue_remove_uint16_8(Queue_uint16_8_Type* const me);

Queue_uint16_8_Type *Queue_Create_uint16_8(void);
void Queue_Destroy_uint16_8(Queue_uint16_8_Type* const me);


/* For Queue_uint16_16_Type Functions, which operate Queue that contains 32 bytes, 16 slots of (uint16)*/

/* Constructor and Destructor*/
void Queue_Init_uint16_16(Queue_uint16_16_Type* const me  ,int (*isFullFunction)(Queue_uint16_16_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint16_16_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint16_16_Type* const me),
                void (*insertFunction)(Queue_uint16_16_Type* const me, uint16 x) ,uint8 (*removeFunction)(Queue_uint16_16_Type* const me) );

void Queue_CleanUp_uint16_16(Queue_uint16_16_Type* const me);

/* Operations */
uint8 Queue_isFull_uint16_16(Queue_uint16_16_Type* const me);
uint8 Queue_isEmpty_uint16_16(Queue_uint16_16_Type *const me);
uint8 Queue_getSize_uint16_16(Queue_uint16_16_Type* const me);
void Queue_insert_uint16_16(Queue_uint16_16_Type* const me, uint16 x);
uint8 Queue_remove_uint16_16(Queue_uint16_16_Type* const me);

Queue_uint16_16_Type *Queue_Create_uint16_16(void);
void Queue_Destroy_uint16_16(Queue_uint16_16_Type* const me);


/* For Queue_uint16_32_Type Functions, which operate Queue that contains 64 bytes, 32 slots of (uint16)*/

/* Constructor and Destructor*/
void Queue_Init_uint16_32(Queue_uint16_32_Type* const me  ,int (*isFullFunction)(Queue_uint16_32_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint16_32_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint16_32_Type* const me),
                void (*insertFunction)(Queue_uint16_32_Type* const me, uint16 x) ,uint8 (*removeFunction)(Queue_uint16_32_Type* const me) );

void Queue_CleanUp_uint16_32(Queue_uint16_32_Type* const me);

/* Operations */
uint8 Queue_isFull_uint16_32(Queue_uint16_32_Type* const me);
uint8 Queue_isEmpty_uint16_32(Queue_uint16_32_Type *const me);
uint8 Queue_getSize_uint16_32(Queue_uint16_32_Type* const me);
void Queue_insert_uint16_32(Queue_uint16_32_Type* const me, uint16 x);
uint8 Queue_remove_uint16_32(Queue_uint16_32_Type* const me);

Queue_uint16_32_Type *Queue_Create_uint16_32(void);
void Queue_Destroy_uint16_32(Queue_uint16_32_Type* const me);

/* For Queue_uint8_8_Type Functions, which operate Queue that contains 8 bytes, 8 slots of (uint8)*/

/* Constructor and Destructor*/
void Queue_Init_uint8_8(Queue_uint8_8_Type* const me  ,int (*isFullFunction)(Queue_uint8_8_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint8_8_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint8_8_Type* const me),
                void (*insertFunction)(Queue_uint8_8_Type* const me, uint8 x) ,uint8 (*removeFunction)(Queue_uint8_8_Type* const me) );

void Queue_CleanUp_uint8_8(Queue_uint8_8_Type* const me);

/* Operations */
uint8 Queue_isFull_uint8_8(Queue_uint8_8_Type* const me);
uint8 Queue_isEmpty_uint8_8(Queue_uint8_8_Type *const me);
uint8 Queue_getSize_uint8_8(Queue_uint8_8_Type* const me);
void Queue_insert_uint8_8(Queue_uint8_8_Type* const me, uint8 x);
uint8 Queue_remove_uint8_8(Queue_uint8_8_Type* const me);

Queue_uint8_8_Type *Queue_Create_uint8_8(void);
void Queue_Destroy_uint8_8(Queue_uint8_8_Type* const me);

/* For Queue_uint8_16_Type Functions, which operate Queue that contains 16 bytes, 16 slots of (uint8)*/

/* Constructor and Destructor*/
void Queue_Init_uint8_16(Queue_uint8_16_Type* const me  ,int (*isFullFunction)(Queue_uint8_16_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint8_16_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint8_16_Type* const me),
                void (*insertFunction)(Queue_uint8_16_Type* const me, uint8 x) ,uint8 (*removeFunction)(Queue_uint8_16_Type* const me) );

void Queue_CleanUp_uint8_16(Queue_uint8_16_Type* const me);

/* Operations */
uint8 Queue_isFull_uint8_16(Queue_uint8_16_Type* const me);
uint8 Queue_isEmpty_uint8_16(Queue_uint8_16_Type *const me);
uint8 Queue_getSize_uint8_16(Queue_uint8_16_Type* const me);
void Queue_insert_uint8_16(Queue_uint8_16_Type* const me, uint8 x);
uint8 Queue_remove_uint8_16(Queue_uint8_16_Type* const me);

Queue_uint8_16_Type *Queue_Create_uint8_16(void);
void Queue_Destroy_uint8_16(Queue_uint8_16_Type* const me);

/* For Queue_uint8_32_Type Functions, which operate Queue that contains 32 bytes, 32 slots of (uint8)*/

/* Constructor and Destructor*/
void Queue_Init_uint8_32(Queue_uint8_32_Type* const me  ,int (*isFullFunction)(Queue_uint8_32_Type* const me),
                uint8 (*isEmptyFunction)(Queue_uint8_32_Type* const me) ,uint8 (*getSizeFunction)(Queue_uint8_32_Type* const me),
                void (*insertFunction)(Queue_uint8_32_Type* const me, uint8 x) ,uint8 (*removeFunction)(Queue_uint8_32_Type* const me) );

void Queue_CleanUp_uint8_32(Queue_uint8_32_Type* const me);

/* Operations */
uint8 Queue_isFull_uint8_32(Queue_uint8_32_Type* const me);
uint8 Queue_isEmpty_uint8_32(Queue_uint8_32_Type *const me);
uint8 Queue_getSize_uint8_32(Queue_uint8_32_Type* const me);
void Queue_insert_uint8_32(Queue_uint8_32_Type* const me, uint8 x);
uint8 Queue_remove_uint8_32(Queue_uint8_32_Type* const me);

Queue_uint8_32_Type *Queue_Create_uint8_32(void);
void Queue_Destroy_uint8_32(Queue_uint8_32_Type* const me);

#endif /* COMMON_DATASTRUCTURE_QUEUE_QUEUE_H_ */
