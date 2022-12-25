/********************************************************************************************
 * File Description
 * ------------------------------------------------------------------------------------------*/
/**      @file PortLcfg.c
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
#include "Port.h"


/*************************************************************************************************
 *  GLOBAL DATA
 ************************************************************************************************/
const Port_ConfigType Port_PinConfig =
    {
        {{PORT_LED_CHL_ID, PORT_PIN_DIO_MODE, PORT_PIN_LEVEL_LOW, PORT_PIN_OUTPUT, PORT_PIN_CURRENT_8MA, RES_OFF},
         {ON_TIME_BUTTON_CHL_ID, PORT_PIN_DIO_MODE, PORT_PIN_LEVEL_HIGH, PORT_PIN_INPUT, PORT_PIN_CURRENT_8MA, PULL_UP},
         {OFF_TIME_BUTTON_CHL_ID, PORT_PIN_DIO_MODE, PORT_PIN_LEVEL_HIGH, PORT_PIN_INPUT, PORT_PIN_CURRENT_8MA, PULL_UP}
        }
    };

/***********************************************
 * End of FILE: Port_Lcfg.c
 ***********************************************/