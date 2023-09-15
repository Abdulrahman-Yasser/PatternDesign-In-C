/*
 * TokenizeAsyncSinglePkg.h
 *
 *  Created on: Aug 16, 2023
 *      Author: Abdu
 */

#ifndef APP_HAL_PATTERN_TOKENIZEASYNCSINGLEPKG_H_
#define APP_HAL_PATTERN_TOKENIZEASYNCSINGLEPKG_H_


#define QSIZE 100

typedef enum {
    EVDIGIT,
    EVDOT,
    EVWHITESPACE,
    EVENDOFSTRING
} EventType;

typedef struct {
    EventType eType;
    union{
        char c;
    } ed;
}Event;

typedef enum{
    NULL_STATE,
    NONUMBER_STATE,
    GOTNUMBER_STATE
} TSTATETYPE;

typedef enum{
    NULL_SSTATE,
    PROCESSINGWHOLEPART_SSTATE,
    PROCESSINGFRACTIONALPART_SSTATE
} TSUBSTATETYPE;

/* helper function returns the digit */
/* held by a char */

int digit(char c);

/*
OS signal and wait functions for
task synchronization
*/

void postSignal(void);
void waitOnSignal(void);


#endif /* APP_HAL_PATTERN_TOKENIZEASYNCSINGLEPKG_H_ */
