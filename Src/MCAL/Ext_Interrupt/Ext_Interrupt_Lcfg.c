/********************************************************************************************
 * File Description
 * ------------------------------------------------------------------------------------------*/
/**      @file Ext_Interrupt_Lcfg.c
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
 *     @version V1.0.0
 *     @date    Dec 23, 2022
 * 
 *********************************************************************************************/

/***************************************************************************************
 * INCLUDES
****************************************************************************************/
#include "Ext_Interrupt.h"

/*************************************************************************************************
 *  GLOBAL DATA
 ************************************************************************************************/
const ExtInt_ConfigType ExtInterruptConfig = 
{
    {{TIME_ON_INTERRUPT_PIN_ID, TIME_ON_INTERRUPT_PORT_ID, EDGE,FALLING, ENABLE},
    {TIME_OFF_INTERRUPT_PIN_ID, TIME_OFF_INTERRUPT_PORT_ID, EDGE,FALLING, ENABLE}}
};

/*********************************************************
 * End of FILE: Ext_Interrupt_Lcfg.c
 ********************************************************/