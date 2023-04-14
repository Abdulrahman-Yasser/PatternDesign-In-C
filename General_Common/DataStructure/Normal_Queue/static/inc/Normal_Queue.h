/*
 * Normal_Queue.h
 *
 *  Created on: Apr 14, 2023
 *      Author: Abdu
 */

#ifndef DATASTRUCTURE_NORMAL_QUEUE_STATIC_INC_NORMAL_QUEUE_H_
#define DATASTRUCTURE_NORMAL_QUEUE_STATIC_INC_NORMAL_QUEUE_H_

#include "../../../../Platform_Types.h"
#include "Normal_Queue_Types.h"


Normal_Queue_DynamicUint *NormalQueue_Create_DYNAMIC_uint(uint8 Dynamic_Size, Normal_Queue_Types queue_type);
void NormalQueue_Destroy_DYNAMIC_uint(Normal_Queue_DynamicUint* const me);

/* Constructor and Destructor Static Allocation */

Normal_Queue_StaticUint *NormalQueue_Create_STATIC_uint(Normal_Queue_Types queue_type);
void NormalQueue_Destroy_STATIC_uint(Normal_Queue_StaticUint* const me);


uint8 NormalQueue_Static_isFull(Normal_Queue_StaticUint* const my_queue);
uint8 NormalQueue_Static_isEmpty(Normal_Queue_StaticUint* const my_queue);
uint8 NormalQueue_Static_getSize(Normal_Queue_StaticUint* const my_queue);
void NormalQueue_Static_insert(Normal_Queue_StaticUint* const my_queue, uint32 data);
uint32 NormalQueue_Static_remove(Normal_Queue_StaticUint* const my_queue);

uint8 NormalQueue_Dynamic_isFull(Normal_Queue_DynamicUint* const my_queue);
uint8 NormalQueue_Dynamic_isEmpty(Normal_Queue_DynamicUint* const my_queue);
uint8 NormalQueue_Dynamic_getSize(Normal_Queue_DynamicUint* const my_queue);
void NormalQueue_Dynamic_insert(Normal_Queue_DynamicUint* const my_queue, uint32 data);
uint32 NormalQueue_Dynamic_remove(Normal_Queue_DynamicUint* const my_queue);


#endif /* DATASTRUCTURE_NORMAL_QUEUE_STATIC_INC_NORMAL_QUEUE_H_ */
