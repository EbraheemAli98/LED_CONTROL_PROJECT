/**************************************************************************************************
 * File Description
 * -----------------------------------------------------------------------------------------------
 *      File: Comman_Macro.h
 *    Module: Comman_Macro_MODULE
 * 
 * Description: Header file for Bit Masking manipulation.
 * 
 **************************************************************************************************/

#ifndef COMMAN_MACRO_H
#define COMMAN_MACRO_H

/*************************************************************************************************
 * GLOBAL MACROS DEFINITION
 ************************************************************************************************/

#define SET_BIT(REG,BIT)           (REG = (REG | (1<<BIT)))
#define CLEAR_BIT(REG,BIT)         (REG = (REG & ~(1<<BIT)))
#define TOGGLE_BIT(REG,BIT)        (REG = (REG ^ (1<<BIT)))
#define GET_BIT(REG,BIT)           (REG = ((REG & (1<<BIT))>>BIT))
#define ROR(REG,SHIFT_VALUE)       (REG = ((REG>>SHIFT_VALUE) | (REG<<((8*sizeof(REG))-SHIFT_VALUE))))
#define ROL(REG,SHIFT_VALUE)       (REG = ((REG<<SHIFT_VALUE) | (REG>>((8*sizeof(REG))-SHIFT_VALUE))))
#define BIT_IS_SET(REG,BIT)        (REG = ((REG & (1<<BIT))>>BIT))
#define BIT_IS_CLEAR(REG,BIT)      (REG = !((REG & (1<<BIT))>>BIT)) 

#define WRITE_PORT_MASK(REG,VALUE)       (REG = (REG)|(VALUE))



#endif /* COMMAN_MACRO_H */

/***************************************************************************************
*   END OF FILE: Comman_Macro.h
***************************************************************************************/