/*
 * ResourceList.h
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_RESOURCELIST_RESOURCELIST_H_
#define APP_HAL_PATTERN_RESOURCELIST_RESOURCELIST_H_


#include "../General_Common/Std_Types.h"
#include "FreeRTOS.h"
#include "semphr.h"

#define POORLY_ORDERED_ACCESS 1
#define DUPLICATED_IDS 2

typedef struct{
    uint8 nIDLists[20];
    uint8 nIDs;
    SemaphoreHandle_t itsMutex;
}ResourceList;

/* Constructors and destructors:*/

void ResourceList_Init(ResourceList* const me);

void ResourceList_Cleanup(ResourceList* const me);

/* Operations */

int ResourceList_addLock(ResourceList* const me, int rID);

/* The elements are added in order but */
/* can be removed in any order. Therefore, */
/* the stored resoiurceIDs above the current */
/* one in the list must be moved down to */
/* lower in the list. */

void ResourceList_removeLock(ResourceList* const me, uint8 rID);

SemaphoreHandle_t ResourceList_getItsMutex(const ResourceList* const me);

void ResourceList_setItsMutex(ResourceList* const me, SemaphoreHandle_t p_Mutex);

ResourceList * ResourceList_Create(void);

void ResourceList_Destroy(ResourceList* const me);

#endif /* APP_HAL_PATTERN_RESOURCELIST_RESOURCELIST_H_ */
