
#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H



#define REG_WRITE_ALL(REG, VAL) (REG |= VAL)
#define REG_WRITE_32_BIT(REG, VAL) (REG |= VAL)
#define REG_WRITE_BIT(REG, CNT) (REG |= 1<<CNT)
#define REG_CLEAR_BIT(REG, CNT) (REG &= (~ (1<<CNT)))

#define REG_WRITE_ALL_PTR(REG, VAL)     ((*REG) |= VAL)

#define REG_CLEAR_32_BIT_PTR(REG)       ( (*((volatile uint32 *)REG)) &= 0x00000000)
#define REG_WRITE_32_BIT_PTR(REG, VAL)  ( (*((volatile uint32 *)REG)) |= VAL)
#define REG_WRITE_BIT_PTR(REG, CNT)     ( (*((volatile uint32 *)(REG))) |= 1<<CNT)
#define REG_CLEAR_BIT_PTR(REG, CNT)     ( (*((volatile uint32 *)(REG))) &= ~(1<<CNT))



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
    E_OK, E_NOK
}Std_ReturnType;

typedef enum{
    E_FALSE, E_TRUE
}Std_BoolReturnType;

/* For using the bit-band region */
void WriteUsingBB(uint32* Ptr, uint32 Value);

#endif
