/********************************************************************************************
 * File Description
 * ------------------------------------------------------------------------------------------*/
/**      @file IntCtrl_Lcfg.c
 *       @brief Link-time configuration source file
 * 
 *     @details This file contains :
 *              1. Configuration of the module if the source code is not available.(Modules 
 *                  may be available as object files).
 *              2. Constant data outside the module. The data can be configured after the 
 *                 module has been compiled but before linking.
 *              3. Configuration change needs software relinking.
 * 
 *     @author  Ebraheem Ali
 *     @version V1.0.1
 *     @date    Dec 23, 2022
 * 
 *********************************************************************************************/

/*************************************************************************************************
 * INCLUDES
 ************************************************************************************************/
#include "IntCtrl.h"

/*************************************************************************************************
 *  GLOBAL DATA
 ************************************************************************************************/
const IntCtrl_ConfigType InterruptConfigInfo = 
{
    {{INT_ENABLE, LEVEL_ZERO ,GPIO_PORTF},
    {INT_ENABLE, LEVEL_ZERO, GPIO_PORTF},
    {INT_ENABLE, LEVEL_ONE, _32BIT_TIMER0A}}
};

