/*
 * Std_Types_Helper.c
 *
 *  Created on: Aug 29, 2022
 *      Author: Abdu
 */


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

void Delay_ms(unsigned long long n){
    volatile unsigned long long  count = 0, i;
    n = n * 762 ;
    while(count++ < n );
}

char* int_to_string(uint32 var){
    char* s;
    uint8 i = 1, j = 0;
    uint32 temp = var;

    do{
        i++;
        temp /= 10;
    }while(temp > 0);

    s = (char*)malloc(sizeof(char) * (i + 1));

    while(i > j){
        s[j] = (var % 10) + '0';
        var = var / 10;
        j++;
    }
    s[j] = '\0';
    return s;
}
