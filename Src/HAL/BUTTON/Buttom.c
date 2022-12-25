/********************************************************************************************
 * File Description
 * ------------------------------------------------------------------------------------------*/
/**      @file Button.c
 *       @brief
 * 
 *     @details
 * 
 *********************************************************************************************/

/***************************************************************************************
 * INCLUDES
****************************************************************************************/
#include "../../MCAL/Ext_Interrupt/Ext_Interrupt.h"
#include "Button.h"

/*************************************************************************************************
 *  GLOBAL DATA
 ************************************************************************************************/
extern volatile uint8 g_on_time;
extern volatile uint8 g_off_time;

/******************************************************************************************************
 *  APIs IMPLEMENTATION
 ******************************************************************************************************/
/*-----------------------------------------------------------------------------------------
 Service Name     : Button_Init
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : None
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to Check which Button is pressed and implement its statement.
 -------------------------------------------------------------------------------------------*/
void Button_Init(void)
{
    ExtInt_Init(&ExtInterruptConfig);
    ExtInt_SetCallBack(&Button_Notification);
}


 void Button_Notification(void)
{
     if (ExtInt_InterruptStatus(ON_BUTTON_INDEX))
    {
        g_on_time++;
        ExtInt_InterruptClear(ON_BUTTON_INDEX);
    }
    else if (ExtInt_InterruptStatus(OFF_BUTTON_INDEX))
    {
        g_off_time++;
        ExtInt_InterruptClear(OFF_BUTTON_INDEX);
    }
}