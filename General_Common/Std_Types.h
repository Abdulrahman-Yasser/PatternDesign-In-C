 #ifndef STD_TYPES_H
 #define STD_TYPES_H
  

#include "Platform_Types.h"
#include "Compiler.h"  

#define Enable          1
#define Disable         0

typedef enum{
    Disable_EnumType, Enable_EnumType
}Enable_vs_DisableType;

#define STD_ON          0x01U       /* Standard ON */
#define STD_OFF         0x00U       /* Standard OFF */
  
#define STD_HIGH        0x01U       /* Standard HIGH */
#define STD_LOW         0x00U       /* Standard LOW */

#define RETURN_ERROR    0x00U       /* There is Error */
#define RETURN_FINE     0x01U       /* There is No Error */

 #endif
