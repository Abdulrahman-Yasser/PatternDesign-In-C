/*
 * Observer.h
 *
 *  Created on: Mar 4, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERNS_OBSERVER_INC_OBSERVER_H_
#define APP_HAL_PATTERNS_OBSERVER_INC_OBSERVER_H_



typedef struct{
//    void (*update)(void);
    void (*update)(int t, int s, int l);
};
/*
 *    void (*update)(void); will be default in all the clients and then the clients can read the data in update function after
 *    the server pushes it. but it's not the classic observer pattern
 *    void (*update)(int temp, int light, int smoke) is the normal in observer patterns
 */


#endif /* APP_HAL_PATTERNS_OBSERVER_INC_OBSERVER_H_ */
