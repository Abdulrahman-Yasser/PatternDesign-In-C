
#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

#define REG_ORING_WITH_VALUE(REG, VAL) (REG |= VAL)
#define REG_ORING_VALUE_NO_CASTING(REG, VAL) (REG |= VAL)
#define REG_ORING_ONE_BIT_NO_CASTING(REG, CNT) (REG |= 1<<CNT)
#define REG_CLEAR_ONE_BIT_NO_CASTING(REG, CNT) (REG &= (~ (1<<CNT)))

#define REG_ORING_POINTED_REG(REG, VAL)     ((*REG) |= VAL)

#define REG_CLEAR_CASTING_POINTED(REG)       ( (*((volatile uint32 *)(REG))) &= 0x00000000)
#define REG_CLEAR_THOSE_BITS_CASTING_POINTED(REG, VAL)  ( (*((volatile uint32 *)(REG))) &= ~(VAL))
#define REG_ORING_CASTING_POINTED(REG, VAL)  ( (*((volatile uint32 *)(REG))) |= VAL)
#define REG_WRITE_CASTING_POINTED(REG, VAL)  ( (*((volatile uint32 *)(REG))) = VAL)
#define REG_ORING_ONE_BIT_CASTING_POINTED(REG, CNT)     ( (*((volatile uint32 *)(REG))) |= 1<<CNT)
#define REG_CLEAR_ONE_BIT_CASTING_POINTED(REG, CNT)     ( (*((volatile uint32 *)(REG))) &= ~(1<<CNT))

#define REG_READ_CASTING_POINTED(x, REG)              (x = ( (*((volatile uint32 *)(REG))) ) )



typedef unsigned char         uint8;
typedef signed char           sint8;
typedef unsigned short int    uint16;
typedef signed short int      sint16;
typedef unsigned long         uint32;
typedef signed long           sint32;
typedef unsigned long long    uint64;
typedef signed long long      sint64;

#define REG_SET_PEIPTH_BB_PTR(REG,BIT_NUM)      ( *(volatile uint32*)((uint8*)0x42000000 + ( (((uint8*)(REG)-(uint8*)0x40000000) * 32) + ((BIT_NUM) * 4))) = 1)
#define REG_CLR_PERIPH_BB_PTR(REG,BIT_NUM)      ( *(volatile uint32*)((uint8*)0x42000000 + ( (((uint8*)(REG)-(uint8*)0x40000000) * 32) + ((BIT_NUM) * 4))) = 0)

typedef enum{
    E_NOK, E_OK
}Std_ReturnType;

typedef enum{
    E_FALSE, E_TRUE
}Std_BoolReturnType;

/* For using the bit-band region */
void WriteUsingBB(uint32* Ptr, uint32 Value);

/* For delays in ms */
void Delay_ms(unsigned long long n);

char* int_to_string(uint32 var);


#endif
