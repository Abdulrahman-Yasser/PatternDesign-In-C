/*
 * ResourceList.c
 *
 *  Created on: Jul 7, 2023
 *      Author: Abdu
 */



#include "ResourceList.h"
#include <stdlib.h>

static char isInOrder(ResourceList* const me, uint8 rID);

static void cleanUpRelations(ResourceList* const me);

/* Constructors and destructors:*/


void ResourceList_Init(ResourceList* const me){
    me->nIDs = 0;
    me->itsMutex = xSemaphoreCreateMutex();
}

void ResourceList_Cleanup(ResourceList* const me){
    cleanUpRelations(me);
}

/* Operations */

int ResourceList_addLock(ResourceList* const me, int rID){
    uint8 retVal;
    xSemaphoreTake(me->itsMutex, 0);
    if(isInOrder(me, rID)){
        me->nIDLists[me->nIDs++] = rID;
        retVal = 0;
    }else{
        if(rID == me->nIDLists[me->nIDs]){
            retVal = DUPLICATED_IDS;
        }else{
            retVal = POORLY_ORDERED_ACCESS;
        }
    }
    xSemaphoreGive(me->itsMutex);
    return retVal;
}

/* The elements are added in order but */
/* can be removed in any order. Therefore, */
/* the stored resoiurceIDs above the current */
/* one in the list must be moved down to */
/* lower in the list. */

void ResourceList_removeLock(ResourceList* const me, uint8 rID){
    uint8 j, k;
    if(me->nIDs){
        for(j = 0; j < me->nIDs; j++){
            if(rID == me->nIDLists[j]){
                for(k = j; k < me->nIDs-1; k++){
                    me->nIDLists[k] = me->nIDLists[k+1];
                }
                //some instruction here
                break;
            }
        }
    }
}

static char isInOrder(ResourceList* const me, uint8 rID){
    if(me->nIDs){
        return (rID > me->nIDLists[me->nIDs - 1]);
    }else{
        return 1;
    }
}



SemaphoreHandle_t ResourceList_getItsMutex(const ResourceList* const me){
    return me->itsMutex;
}

void ResourceList_setItsMutex(ResourceList* const me, SemaphoreHandle_t p_Mutex){
    me->itsMutex = p_Mutex;
}

ResourceList* ResourceList_Create(void){
    ResourceList* me;
    me = (ResourceList*)malloc(sizeof(ResourceList));
    if(me != Null_Ptr){
        ResourceList_Init(me);
    }
    return me;
}

void ResourceList_Destroy(ResourceList* const me){
    if(me != Null_Ptr){
        ResourceList_Cleanup(me);
    }
    free(me);
}

static void cleanUpRelations(ResourceList* const me){
    if(me->itsMutex != Null_Ptr){
        me->itsMutex = Null_Ptr;
    }
}
