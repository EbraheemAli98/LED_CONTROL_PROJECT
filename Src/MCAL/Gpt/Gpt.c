/********************************************************************************************
 * File Description
 * ------------------------------------------------------------------------------------------*/
/**      @file Gpt.c
 *       @brief
 *
 *     @details
 *
 *********************************************************************************************/

/***************************************************************************************
 * INCLUDES
 ****************************************************************************************/
#include "Gpt.h"
#include "../../SERVICES/Comman_Macro.h"
#include "../Comman/MemMap.h"

/*************************************************************************************************
 *  GLOBAL DATA
 ************************************************************************************************/
const Gpt_ConfigType Gpt_ChannelConfigurationStr =
    {
        {{GPT_CHL0_ID, GPT_CH_MODE_CONTINUOUS, GPT_PRESCALER_VALUE, 0xFA00},
         {GPT_CHL1_ID, GPT_CH_MODE_CONTINUOUS, 0, 0},
         {GPT_CHL2_ID, GPT_CH_MODE_CONTINUOUS, 0, 0},
         {GPT_CHL3_ID, GPT_CH_MODE_CONTINUOUS, 0, 0},
         {GPT_CHL4_ID, GPT_CH_MODE_CONTINUOUS, 0, 0},
         {GPT_CHL5_ID, GPT_CH_MODE_CONTINUOUS, 0, 0}}};

/*************************************************************************************************
 *  LOCAL DATA
 ************************************************************************************************/
static const Gpt_ConfigType *STR_GptConfigSet;
static volatile Gpt_CallBackPtrType g_GptCallBack_Ptr = NULL_PTR;

/*****************************************************************************************************
 *  APIs IMPLEMENTATION
 ******************************************************************************************************/
/*-----------------------------------------------------------------------------------
 Service Name     : Gpt_Init
 Sync/Async       : Synchronous
 Reentrnacy       : Non-Reentrant
 Parameter(in)    : [ConfigPtr] : Pointer to a selected configuration structure.
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to Initialize the GPT driver
 -----------------------------------------------------------------------------------*/
void Gpt_Init(const Gpt_ConfigType *ConfigPtr)
{
    if (NULL_PTR != ConfigPtr)
    {
        uint8 ChannelIndex;
        volatile uint32 dump = 0;
        STR_GptConfigSet = ConfigPtr;
        volatile uint32 *Base_Address = NULL_PTR;
        for (ChannelIndex = 0; ChannelIndex < NUM_OF_TIMER_CHANNELS; ChannelIndex++)
        {
            /*TODO  : Enable clock to the timer block */
            SET_BIT(SYSCTL_RCGCTIMER, ConfigPtr->ChannelSelect[ChannelIndex].GptChannelId);
            dump = SYSCTL_RCGCTIMER;
            switch (ConfigPtr->ChannelSelect[ChannelIndex].GptChannelId)
            {
            case GPT_CHL0_ID:
                Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL0_ID * 0X1000));
                break;
            case GPT_CHL1_ID:
                Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL1_ID * 0X1000));
                break;
            case GPT_CHL2_ID:
                Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL2_ID * 0X1000));
                break;
            case GPT_CHL3_ID:
                Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL3_ID * 0X1000));
                break;
            case GPT_CHL4_ID:
                Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL4_ID * 0X1000));
                break;
            case GPT_CHL5_ID:
                Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL5_ID * 0X1000));
                break;
            default:
                break;
            }
            /*TODO  : Disable timer by clearing TnEN bit in GPTMCTL register */
            *(volatile uint32 *)((volatile uint8*)Base_Address + GPTMCTL) = 0;
            /*TODO  : Write the GPTMCFG register with value of 0x00000000 */
            *(volatile uint32 *)((volatile uint8*)Base_Address + GPTMCFG) = GPT_TIMER_CFG_16BIT;
            /*TODO  : Configure the TnMR field in the GPTMTnMR register to set the TIMER Conuter Mode */
            switch (ConfigPtr->ChannelSelect[ChannelIndex].GptChannelMode)
            {
            case GPT_CH_MODE_ONESHOT:
                *(volatile uint32 *)((volatile uint8*)Base_Address + GPTMTAMR) = (*(volatile uint32 *)((volatile uint8*)Base_Address + GPTMTAMR) & 0xFFC) | GPT_CH_MODE_ONESHOT;
                break;
            case GPT_CH_MODE_CONTINUOUS:
                *(volatile uint32 *)((volatile uint8*)Base_Address + GPTMTAMR) = (*(volatile uint32 *)((volatile uint8*)Base_Address + GPTMTAMR) & 0xFFC) | GPT_CH_MODE_CONTINUOUS;
                break;
            default:
                break;
            }

            /*TODO  : Load the Prescaler value into the GPTMTAPR register */
            *(volatile uint32 *)((volatile uint8*)Base_Address + GPTMTAPR) = ConfigPtr->ChannelSelect[ChannelIndex].GptChannelTickFrequency - 1;

            /*TODO  : Load the start value into the GPTMTAILR register */
            if (ConfigPtr->ChannelSelect[ChannelIndex].GptChannelTickValueMax != 0)
            {
                *(volatile uint32 *)((volatile uint8*)Base_Address + GPTMTAILR) = ConfigPtr->ChannelSelect[ChannelIndex].GptChannelTickValueMax - 1;
            }
            else
            {
                *(volatile uint32 *)((volatile uint8*)Base_Address + GPTMTAILR) = ConfigPtr->ChannelSelect[ChannelIndex].GptChannelTickValueMax;
            }
            /*  only Enable the requred Timers resources.*/
            if (ConfigPtr->ChannelSelect[ChannelIndex].GptChannelTickValueMax == 0)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8*)Base_Address + GPTMICR), ConfigPtr->ChannelSelect[ChannelIndex].GptChannelId);
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8*)Base_Address + GPTMCTL), ConfigPtr->ChannelSelect[ChannelIndex].GptChannelId);
            }
            else
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8*)Base_Address + GPTMICR), ConfigPtr->ChannelSelect[ChannelIndex].GptChannelId);
                SET_BIT(*(volatile uint32 *)((volatile uint8*)Base_Address + GPTMCTL), ConfigPtr->ChannelSelect[ChannelIndex].GptChannelId);
            }
        }
    }
    else
    {
    }
}

/*-------------------------------------------------------------------------------------
Service Name     : Gpt_StartTimer
Sync/Async       : Synchronous
Reentrnacy       : Reentrant
Parameter(in)    : [Channel] : Numeric identifier of the GPT channel.
                   [Value]   : Target time in number of ticks.
Parameter(in/out): None
Parameter(out)   : None
Return Value     : [Gpt_ValueType]  : Remaining timer value(in number of ticks).
Description      : Function Starts a timer channel.
----------------------------------------------------------------------------------------*/
void Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value)
{
    volatile uint32 *Base_Address = NULL_PTR;
    switch (STR_GptConfigSet->ChannelSelect[Channel].GptChannelId)
    {
    case GPT_CHL0_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL0_ID * 0X1000));
        break;
    case GPT_CHL1_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL1_ID * 0X1000));
        break;
    case GPT_CHL2_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL2_ID * 0X1000));
        break;
    case GPT_CHL3_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL3_ID * 0X1000));
        break;
    case GPT_CHL4_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL4_ID * 0X1000));
        break;
    case GPT_CHL5_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL5_ID * 0X1000));
        break;
    default:
        break;
    }
    /*TODO  : Load the Prescaler value into the GPTMTAPR register */
    *(volatile uint32 *)((volatile uint8*)Base_Address + GPTMTAPR) = STR_GptConfigSet->ChannelSelect[Channel].GptChannelTickFrequency;
    /*TODO  : Load the start value into the GPTMTAILR register */
    if (STR_GptConfigSet->ChannelSelect[Channel].GptChannelTickValueMax != 0)
    {
        *(volatile uint32 *)((volatile uint8*)Base_Address + GPTMTAILR) = STR_GptConfigSet->ChannelSelect[Channel].GptChannelTickValueMax - 1;
    }
    else
    {
        *(volatile uint32 *)((volatile uint8*)Base_Address + GPTMTAILR) = STR_GptConfigSet->ChannelSelect[Channel].GptChannelTickValueMax;
    }
    /*TODO  : Enable timer by setting TnEN bit in GPTMCTL register */
    SET_BIT(*(volatile uint32 *)((volatile uint8*)Base_Address + GPTMCTL), STR_GptConfigSet->ChannelSelect[Channel].GptChannelId);
}

/*-------------------------------------------------------------------------------------
Service Name     : Gpt_StopTimer
Sync/Async       : Synchronous
Reentrnacy       : Reentrant
Parameter(in)    : [Channel] : Numeric identifier of the GPT channel.
Parameter(in/out): None
Parameter(out)   : None
Return Value     : [Gpt_ValueType]  : Remaining timer value(in number of ticks).
Description      : Function Stops a timer channel.
----------------------------------------------------------------------------------------*/
void Gpt_StopTimer(Gpt_ChannelType Channel)
{
    volatile uint32 *Base_Address = NULL_PTR;
    switch (STR_GptConfigSet->ChannelSelect[Channel].GptChannelId)
    {
    case GPT_CHL0_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL0_ID * 0X1000));
        break;
    case GPT_CHL1_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL1_ID * 0X1000));
        break;
    case GPT_CHL2_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL2_ID * 0X1000));
        break;
    case GPT_CHL3_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL3_ID * 0X1000));
        break;
    case GPT_CHL4_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL4_ID * 0X1000));
        break;
    case GPT_CHL5_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL5_ID * 0X1000));
        break;
    default:
        break;
    }
    /* Disable the timer to stop counting */
    CLEAR_BIT(*(volatile uint32 *)((volatile uint8*)Base_Address + GPTMCTL), STR_GptConfigSet->ChannelSelect[Channel].GptChannelId);
}

/*-----------------------------------------------------------------------------------
Service Name     : Gpt_EnableNotification
Sync/Async       : Synchronous
Reentrnacy       : Reentrant
Parameter(in)    : [Channel] : Numeric identifier of the GPT channel.
Parameter(in/out): None
Parameter(out)   : None
Return Value     : None
Description      : Function enables the interrupt notification for a channel (relevant in normal mode).
-----------------------------------------------------------------------------------*/
void Gpt_EnableNotification(Gpt_ChannelType Channel)
{
    volatile uint32 *Base_Address = NULL_PTR;
    switch (STR_GptConfigSet->ChannelSelect[Channel].GptChannelId)
    {
    case GPT_CHL0_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL0_ID * 0X1000));
        break;
    case GPT_CHL1_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL1_ID * 0X1000));
        break;
    case GPT_CHL2_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL2_ID * 0X1000));
        break;
    case GPT_CHL3_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL3_ID * 0X1000));
        break;
    case GPT_CHL4_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL4_ID * 0X1000));
        break;
    case GPT_CHL5_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL5_ID * 0X1000));
        break;
    default:
        break;
    }
    *(volatile uint32 *)((volatile uint8*)Base_Address + GPTMIMR) = STR_GptConfigSet->ChannelSelect[Channel].GptChannelId;
    while (BIT_IS_CLEAR((*(volatile uint32 *)((volatile uint8*)Base_Address + GPTMMIS)), STR_GptConfigSet->ChannelSelect[Channel].GptChannelId))
        ;
    SET_BIT(*(volatile uint32 *)((volatile uint8*)Base_Address + GPTMICR), STR_GptConfigSet->ChannelSelect[Channel].GptChannelId);
}

/*-----------------------------------------------------------------------------------
Service Name     : Gpt_DisableNotification
Sync/Async       : Synchronous
Reentrnacy       : Reentrant
Parameter(in)    : [Channel] : Numeric identifier of the GPT channel.
Parameter(in/out): None
Parameter(out)   : None
Return Value     : None
Description      : Function disnables the interrupt notification for a channel (relevant in normal mode).
-----------------------------------------------------------------------------------*/
void Gpt_DisableNotification(Gpt_ChannelType Channel)
{
    volatile uint32 *Base_Address = NULL_PTR;
    switch (STR_GptConfigSet->ChannelSelect[Channel].GptChannelId)
    {
    case GPT_CHL0_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL0_ID * 0X1000));
        break;
    case GPT_CHL1_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL1_ID * 0X1000));
        break;
    case GPT_CHL2_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL2_ID * 0X1000));
        break;
    case GPT_CHL3_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL3_ID * 0X1000));
        break;
    case GPT_CHL4_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL4_ID * 0X1000));
        break;
    case GPT_CHL5_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL5_ID * 0X1000));
        break;
    default:
        break;
    }
    CLEAR_BIT(*(volatile uint32 *)((volatile uint8*)Base_Address + GPTMIMR), STR_GptConfigSet->ChannelSelect[Channel].GptChannelId);
}

/*-----------------------------------------------------------------------------------
Service Name     : Gpt_SetMode
Sync/Async       : Synchronous
Reentrnacy       : Reentrant
Parameter(in)    : [Mode] : specifies the behavior of the timer channel after the target time is reached.
Parameter(in/out): None
Parameter(out)   : None
Return Value     : None
Description      : Function Sets the Counter mode of the GPT.
-----------------------------------------------------------------------------------*/
void Gpt_SetMode(Gpt_ChannelType Channel,Gpt_ChannelType Mode)
{
    volatile uint32 *Base_Address = NULL_PTR;
    switch (STR_GptConfigSet->ChannelSelect[Channel].GptChannelId)
    {
    case GPT_CHL0_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL0_ID * 0X1000));
        break;
    case GPT_CHL1_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL1_ID * 0X1000));
        break;
    case GPT_CHL2_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL2_ID * 0X1000));
        break;
    case GPT_CHL3_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL3_ID * 0X1000));
        break;
    case GPT_CHL4_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL4_ID * 0X1000));
        break;
    case GPT_CHL5_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL5_ID * 0X1000));
        break;
    default:
        break;
    }
    switch (STR_GptConfigSet->ChannelSelect[Mode].GptChannelMode)
    {
    case GPT_CH_MODE_ONESHOT:
        *(volatile uint32 *)((volatile uint8*)Base_Address + GPTMTAMR) = (*(volatile uint32 *)(Base_Address + GPTMTAMR) & 0xFFC) | GPT_CH_MODE_ONESHOT;
        break;
    case GPT_CH_MODE_CONTINUOUS:
        *(volatile uint32 *)((volatile uint8*)Base_Address + GPTMTAMR) = (*(volatile uint32 *)(Base_Address + GPTMTAMR) & 0xFFC) | GPT_CH_MODE_CONTINUOUS;
        break;
    default:
        break;
    }
}

/*-------------------------------------------------------------------------------------
Service Name     : Gpt_InterruptFlagReset
Sync/Async       : Synchronous
Reentrnacy       : Reentrant
Parameter(in)    : [Channel] : Numeric identifier of the GPT channel.
Parameter(in/out): None
Parameter(out)   : None
Return Value     : void
Description      : Function callback.
----------------------------------------------------------------------------------------*/
void Gpt_InterruptFlagReset(Gpt_ChannelType Channel)
{
    volatile uint32 *Base_Address = NULL_PTR;
    switch (STR_GptConfigSet->ChannelSelect[Channel].GptChannelId)
    {
    case GPT_CHL0_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL0_ID * 0X1000));
        break;
    case GPT_CHL1_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL1_ID * 0X1000));
        break;
    case GPT_CHL2_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL2_ID * 0X1000));
        break;
    case GPT_CHL3_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL3_ID * 0X1000));
        break;
    case GPT_CHL4_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL4_ID * 0X1000));
        break;
    case GPT_CHL5_ID:
        Base_Address = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL5_ID * 0X1000));
        break;
    default:
        break;
    }
    SET_BIT(*(volatile uint32 *)((volatile uint8*)Base_Address + GPTMICR), STR_GptConfigSet->ChannelSelect[Channel].GptChannelId);
}

/*-------------------------------------------------------------------------------------
Service Name     : Gpt_Notification_Channel0
Sync/Async       : Synchronous
Reentrnacy       : Reentrant
Parameter(in)    : None
Parameter(in/out): None
Parameter(out)   : None
Return Value     : void
Description      : Function callback.
----------------------------------------------------------------------------------------*/
void Gpt_Notification_Channel0(Gpt_CallBackPtrType GptNotification)
{
    if (GptNotification != NULL_PTR)
    {
        g_GptCallBack_Ptr = GptNotification;
    }
}

/*-------------------------------------------------------------------------------------
Service Name     : Gpt_Notification_Channel1
Sync/Async       : Synchronous
Reentrnacy       : Reentrant
Parameter(in)    : None
Parameter(in/out): None
Parameter(out)   : None
Return Value     : void
Description      : Function callback.
----------------------------------------------------------------------------------------*/
void Gpt_Notification_Channel1(Gpt_CallBackPtrType GptNotification)
{
    if (GptNotification != NULL_PTR)
    {
        g_GptCallBack_Ptr = GptNotification;
    }
}

/*-------------------------------------------------------------------------------------
Service Name     : Gpt_Notification_Channel2
Sync/Async       : Synchronous
Reentrnacy       : Reentrant
Parameter(in)    : None
Parameter(in/out): None
Parameter(out)   : None
Return Value     : void
Description      : Function callback.
----------------------------------------------------------------------------------------*/
void Gpt_Notification_Channel2(Gpt_CallBackPtrType GptNotification)
{
    if (GptNotification != NULL_PTR)
    {
        g_GptCallBack_Ptr = GptNotification;
    }
}

/*-------------------------------------------------------------------------------------
Service Name     : Gpt_Notification_Channel3
Sync/Async       : Synchronous
Reentrnacy       : Reentrant
Parameter(in)    : None
Parameter(in/out): None
Parameter(out)   : None
Return Value     : void
Description      : Function callback.
----------------------------------------------------------------------------------------*/
void Gpt_Notification_Channel3(Gpt_CallBackPtrType GptNotification)
{
    if (GptNotification != NULL_PTR)
    {
        g_GptCallBack_Ptr = GptNotification;
    }
}

/*-------------------------------------------------------------------------------------
Service Name     : Gpt_Notification_Channel4
Sync/Async       : Synchronous
Reentrnacy       : Reentrant
Parameter(in)    : None
Parameter(in/out): None
Parameter(out)   : None
Return Value     : void
Description      : Function callback.
----------------------------------------------------------------------------------------*/
void Gpt_Notification_Channel4(Gpt_CallBackPtrType GptNotification)
{
    if (GptNotification != NULL_PTR)
    {
        g_GptCallBack_Ptr = GptNotification;
    }
}

/*-------------------------------------------------------------------------------------
Service Name     : Gpt_Notification_Channel5
Sync/Async       : Synchronous
Reentrnacy       : Reentrant
Parameter(in)    : None
Parameter(in/out): None
Parameter(out)   : None
Return Value     : void
Description      : Function callback.
----------------------------------------------------------------------------------------*/
void Gpt_Notification_Channel5(Gpt_CallBackPtrType GptNotification)
{
    if (GptNotification != NULL_PTR)
    {
        g_GptCallBack_Ptr = GptNotification;
    }
}

/******************************************************************************************************
 *  GPT INTERRUPT HANDLER IMPLEMENTATION
 ******************************************************************************************************/
void TIMER0A_Handler(void)
{
    if (g_GptCallBack_Ptr != NULL_PTR)
    {
        (*g_GptCallBack_Ptr)();
    }
}
/*----------------------------------------------------------------------*/
void TIMER1A_Handler(void)
{
    if (g_GptCallBack_Ptr != NULL_PTR)
    {
        (*g_GptCallBack_Ptr)();
    }
}
/*-----------------------------------------------------------------------*/
void TIMER2A_Handler(void)
{
    if (g_GptCallBack_Ptr != NULL_PTR)
    {
        (*g_GptCallBack_Ptr)();
    }
}
/*------------------------------------------------------------------------*/
void TIMER3A_Handler(void)
{
    if (g_GptCallBack_Ptr != NULL_PTR)
    {
        (*g_GptCallBack_Ptr)();
    }
}
/*------------------------------------------------------------------------*/
void TIMER4A_Handler(void)
{
    if (g_GptCallBack_Ptr != NULL_PTR)
    {
        (*g_GptCallBack_Ptr)();
    }
}
/*------------------------------------------------------------------------*/
void TIMER5A_Handler(void)
{
    if (g_GptCallBack_Ptr != NULL_PTR)
    {
        (*g_GptCallBack_Ptr)();
    }
}
