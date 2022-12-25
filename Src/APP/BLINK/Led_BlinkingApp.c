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
#include "../../MCAL/INTCTRL/IntCtrl.h"
#include "../../HAL/LED/Led.h"
#include "../../MCAL/Gpt/Gpt.h"
#include "Led_BlinkingApp.h"

/***************************************************************************************
 * GLOBAL DATA
****************************************************************************************/
volatile uint8 g_Int_flag = 0;
volatile uint8 g_on_time = 0;
volatile uint8 g_off_time = 0;

/******************************************************************************************************
 *  APIs Implementation
 ******************************************************************************************************/
/*-----------------------------------------------------------------------------------
 Service Name     : App_Init
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : None
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to initiate all configured pins.
 -----------------------------------------------------------------------------------*/
void App_Init(void)
{
    Port_Init(&Port_PinConfig);
    Gpt_Init(&Gpt_ChannelConfigurationStr);
    Gpt_Notification_WT0(App_Notification);
    Button_Init();
    IntCtrl_Init(&InterruptConfigInfo);
}

/*-----------------------------------------------------------------------------------
 Service Name     : App_Start
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : None
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to set the timer on and of value all configured pins.
 -----------------------------------------------------------------------------------*/
void App_Start(uint8 TimeON,uint8 TimeOFF)
{
    g_on_time = TimeON;
    g_off_time = TimeOFF;
    Gpt_StartTimer(GPT_WT_CHL0_ID,g_on_time);
    Gpt_EnableNotification(GPT_WT_CHL0_ID);
}

/*-----------------------------------------------------------------------------------
 Service Name     : App_Notification
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : None
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to implemented when the interrupt fires.
 -----------------------------------------------------------------------------------*/
void App_Notification(void)
{
    g_Int_flag++;
    if (g_Int_flag == 1)
    {
        LED_WriteHigh();
        Gpt_StartTimer(GPT_WT_CHL0_ID,g_on_time);
    }
    else if (g_Int_flag == 2)
    {
        LED_WriteLow();
        Gpt_StartTimer(GPT_WT_CHL0_ID,g_off_time);
        g_Int_flag = 0;
    }
    Gpt_InterruptFlagReset(GPT_WT_CHL0_ID);
}