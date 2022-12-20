/**************************************************************************************************
 * File Description
 * -----------------------------------------------------------------------------------------------
 *      File: Std_Types.h
 *    Module: Std_Types
 * 
 * Description: Header file for stander definition.
 * 
 *************************************************************************************************/

#ifndef STD_TYPES_H
#define STD_TYPES_H

/*************************************************************************************************
 * INCLUDES
 ************************************************************************************************/



/*************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 ************************************************************************************************/
#define STD_HIGH        0x01U       /* Standard HIGH */
#define STD_LOW         0x00U       /* Standard LOW */

#define STD_ACTIVE      0x01U       /* Logical state active */
#define STD_IDLE        0x00U       /* Logical state idle */

#define STD_ON          0x01U       /* Standard ON */
#define STD_OFF         0x00U       /* Standard OFF */

#define E_OK            ((Std_ReturnType)0x00U)      /* Function Return OK */
#define E_NOT_OK        ((Std_ReturnType)0x01U)      /* Function Return NOT OK */

/*
 * Boolean Values if there are not defined by the plateform.
 */
#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif

#define NULL_PTR        ((void*)0)

#define NUM_OF_CHANNELS_IN_PORT         (8)

typedef unsigned char         boolean;

typedef unsigned char         uint8;          /*           0 .. 255             */
typedef signed char           sint8;          /*        -128 .. +127            */
typedef unsigned short        uint16;         /*           0 .. 65535           */
typedef signed short          sint16;         /*      -32768 .. +32767          */
typedef unsigned long         uint32;         /*           0 .. 4294967295      */
typedef signed long           sint32;         /* -2147483648 .. +2147483647     */
typedef unsigned long long    uint64;         /*       0..18446744073709551615  */
typedef signed long long      sint64;         /* -9223372036854775808 .. 9223372036854775807 */
typedef float                 float32;
typedef double                float64;

#endif /* STD_TYPES_H */

/***************************************************************************************
*   END OF FILE: STD_Types.h
***************************************************************************************/