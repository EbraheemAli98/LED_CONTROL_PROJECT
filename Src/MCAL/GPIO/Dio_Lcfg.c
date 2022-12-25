/********************************************************************************************
 * File Description
 * ------------------------------------------------------------------------------------------*/
/**      @file Dio_Lcfg.c
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
#include "Dio.h"


const Dio_ConfigType Dio_Config =
    {
        {{DIO_LED_PORT_ID, DIO_LED_CHL_ID},
         {ON_TIME_BUTTON_PORT_ID, ON_TIME_BUTTON_CHL_ID},
         {OFF_TIME_BUTTON_PORT_ID, OFF_TIME_BUTTON_CHL_ID}
        }
    };

/*************************************************
 * End of FILE: Dio_Lcfg.c
 *************************************************/