/**************************************************************************************************
 * File Description
 * -----------------------------------------------------------------------------------------------
 *      File: Bit_Mask.h
 *    Module: Bit_Mask
 * 
 * Description: Header file for Bit Masking manipulation.
 * 
 **************************************************************************************************/

#ifndef BIT_MASK_H
#define BIT_MASK_H

/*************************************************************************************************
 * INCLUDES
 ************************************************************************************************/

#define SET_BIT(REG,BIT)           (REG = (REG | (1<<BIT)))
#define CLEAR_BIT(REG,BIT)         (REG = (REG & ~(1<<BIT)))
#define TOGGLE_BIT(REG,BIT)        (REG = (REG ^ (1<<BIT)))
#define GET_BIT(REG,BIT)           (REG = ((REG & (1<<BIT))>>BIT))
#define ROR(REG,SHIFT_VALUE)       (REG = ((REG>>SHIFT_VALUE) | (REG<<((8*sizeof(REG))-SHIFT_VALUE))))
#define ROL(REG,SHIFT_VALUE)       (REG = ((REG<<SHIFT_VALUE) | (REG>>((8*sizeof(REG))-SHIFT_VALUE))))
#define BIT_IS_SET(REG,BIT)        (REG = ((REG & (1<<BIT))>>BIT))
#define BIT_IS_CLEAR(REG,BIT)      (REG = !((REG & (1<<BIT))>>BIT)) 


#endif /* BIT_MASK_H */

/***************************************************************************************
*   END OF FILE: Bit_Mask.h
***************************************************************************************/