/*
 * Std_Types_Helper.c
 *
 *  Created on: Aug 29, 2022
 *      Author: Abdu
 */


#include "Std_Types.h"

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
    volatile unsigned long long  count = 0;
    while(count++ < (762 * n) );
}
