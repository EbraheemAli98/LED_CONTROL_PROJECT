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
 Description      : Function to initialize the button
 -------------------------------------------------------------------------------------------*/
void Button_Init(void)
{
    ExtInt_Init(&ExtInterruptConfig);
    ExtInt_SetCallBack(&Button_Notification);
}

/*-----------------------------------------------------------------------------------------
 Service Name     : Button_Init
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : None
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to Check which Button is pressed and implement its statement.
                    it is an Event-Based task.
 -------------------------------------------------------------------------------------------*/
  void Button_Notification(void)
{
     if (ExtInt_InterruptStatus(ON_BUTTON_INDEX))
    {
        g_on_time++;
        if(g_off_time > 1)
        {
          g_off_time--;
        }
        else
        {

        }
        ExtInt_InterruptClear(ON_BUTTON_INDEX);
    }
    else if (ExtInt_InterruptStatus(OFF_BUTTON_INDEX))
    {
        g_off_time++;
        if(g_on_time > 1)
        {
          g_on_time--;
        }
        else
        {
            
        }
        
        ExtInt_InterruptClear(OFF_BUTTON_INDEX);
    }
    else
    {
        /* Do Nothing... */
    }
    
}