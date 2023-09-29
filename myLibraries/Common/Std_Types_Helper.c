/*
 * Std_Types_Helper.c
 *
 *  Created on: Aug 29, 2022
 *      Author: Abdu
 */

#include "Platform_Types.h"
#include "Std_Types.h"
#include <stdlib.h>
#include "CPU_resources.h"

void WriteUsingBB(uint32* Ptr, uint32 Value){
    uint8 i;
    for(i = 0; i < 32; i++){
        if((Value & (1 << i)) > 0){
            REG_SET_PEIPTH_BB_PTR(((uint8*)Ptr),i);
        }else{
            REG_CLR_PERIPH_BB_PTR(((uint8*)Ptr),i);
        }
    }

}

/*
#ifndef PLL_STATIC_INC_PLL_H_
void Delay_ms(unsigned long long n){
    volatile unsigned long long  count = 0, i;
    n = n * 76 * 1000 ;
    while(count++ < n );
}
#else
*/
void Delay_ms(unsigned long long const n){
    volatile unsigned long long  count = 0;
    int i;
	for(i = 0; i++; i < CPU_CLOCK){
		count = n  * 77;
		while(count--);
	}
}
//#endif

char* int_to_string(uint32 var){
    char* s;
    sint8 i = 0, j = 0;
    uint32 temp = var;

    do{
        i++;
        temp /= 10;
    }while(temp > 0);

    s = (char*)malloc(sizeof(char) * (i + 1));

    s[i] = '\0';
    i--;
    while(i >= j){
        s[i] = (var % 10) + '0';
        var = var / 10;
        i--;
    }
    return s;
}
