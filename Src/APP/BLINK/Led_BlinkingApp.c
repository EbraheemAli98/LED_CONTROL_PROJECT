/*********************************************************************************************
 * File Description
 * ------------------------------------------------------------------------------------------*/
/**      @file  Led_Blinking.c
 *       @brief 
 * 
 *     @details
 * 
 *********************************************************************************************/

/***************************************************************************************
 * INCLUDES
****************************************************************************************/
#include "../../MCAL/GPIO/Port.h"
#include "../../MCAL/GPIO/Dio.h"
#include "../../HAL/BUTTON/Button.h"
#include "../../HAL/LED/Led.h"

/******************************************************************************************************
 *  APIs Implementation
 ******************************************************************************************************/
/*-----------------------------------------------------------------------------------
 Service Name     : LedBlinkingApp_Init
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : None
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to initiate all configured pins.
 -----------------------------------------------------------------------------------*/
void LedBlinkingApp_Init(void)
{
    Port_Init(&Port_ConfigType);
    Button_Init();
}

/*-----------------------------------------------------------------------------------
 Service Name     : LedBlinkingApp_Start
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : None
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to initiate all configured pins.
 -----------------------------------------------------------------------------------*/
void LedBlinkingApp_Start(uint32 TimeON,uint32 TimeOFF)
{
/*TODO  : Lights the LED for the given TimeON period */
/*TODO  : Switch off the LED for the given TimeOFF period*/
}