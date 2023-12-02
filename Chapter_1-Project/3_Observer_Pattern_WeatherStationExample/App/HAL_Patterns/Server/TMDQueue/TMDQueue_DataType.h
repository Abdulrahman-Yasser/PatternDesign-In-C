/*
 * TMDQueue_DataType.h
 *
 *  Created on: May 20, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_SERVER_TMDQUEUE_TMDQUEUE_DATATYPE_H_
#define APP_HAL_PATTERNS_SERVER_TMDQUEUE_TMDQUEUE_DATATYPE_H_

#include "../TimeMarkedData/TimeMarkedData_DataType.h"

#define TMD_QUEUE_SIZE 5



typedef struct {
    uint8 head;
    uint8 size;
    struct TimeMarkedData Buffer[TMD_QUEUE_SIZE];
}TMDQueue;


#endif /* APP_HAL_PATTERNS_SERVER_TMDQUEUE_TMDQUEUE_DATATYPE_H_ */
