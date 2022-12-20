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
#include "../../MCAL/INTCTRL/IntCtrl.h"
#include "../../MCAL/GPIO/Dio.h"
#include "Button.h"

/*************************************************************************************************
 *  GLOBAL DATA
 ************************************************************************************************/
volatile uint32 g_TimeON;
volatile uint32 g_TimeOFF;

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
    IntCtrl_Init(&InterruptConfigInfo);
    ExtInt_Init(&ExtInterruptConfig);
    ExtInt_SetCallBack(&Button_IntAction);
}

void Button_IntAction(void)
{
    if (ExtInt_InterruptStatus(ON_BUTTON_INDEX))
    {
        g_TimeON++;
        ExtInt_InterruptClear(ON_BUTTON_INDEX);
    }
    else if (ExtInt_InterruptStatus(OFF_BUTTON_INDEX))
    {
        g_TimeOFF++;
        ExtInt_InterruptClear(OFF_BUTTON_INDEX);
    }
}