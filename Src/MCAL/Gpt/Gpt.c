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
    {
        {GPT_CHL0_ID,GPT_CH_MODE_CONTINUOUS,GPT_PRESCALER_VALUE,0xFA00,NULL_PTR},
        {GPT_CHL1_ID,GPT_CH_MODE_CONTINUOUS,0,0,NULL_PTR},
        {GPT_CHL2_ID,GPT_CH_MODE_CONTINUOUS,0,0,NULL_PTR},
        {GPT_CHL3_ID,GPT_CH_MODE_CONTINUOUS,0,0,NULL_PTR},
        {GPT_CHL4_ID,GPT_CH_MODE_CONTINUOUS,0,0,NULL_PTR},
        {GPT_CHL5_ID,GPT_CH_MODE_CONTINUOUS,0,0,NULL_PTR}
    }
};

/*************************************************************************************************
 *  LOCAL DATA
 ************************************************************************************************/
static const Gpt_ConfigType *STR_GptConfigSet;
static volatile Gpt_CallBackPtr g_GptCallBack_Ptr = NULL_PTR;

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
        STR_GptConfigSet = ConfigPtr;
        for (ChannelIndex = 0; ChannelIndex < NUM_OF_TIMER_CHANNELS; ChannelIndex++)
        {
            /*TODO  : Enable clock to the timer block */
            SET_BIT(SYSCTL_RCGCTIMER, ConfigPtr->ChannelSelect[ChannelIndex].GptChannelId);
            /*TODO  : Disable timer by clearing TnEN bit in GPTMCTL register */
            GPTMCTL(ConfigPtr->ChannelSelect[ChannelIndex].GptChannelId) = 0;
            /*TODO  : Write the GPTMCFG register with value of 0x00000000 */
            GPTMCFG(ConfigPtr->ChannelSelect[ChannelIndex].GptChannelId) = GPT_TIMER_CFG_16BIT;
            /*TODO  : Configure the TnMR field in the GPTMTnMR register to set the TIMER Conuter Mode */
            switch (ConfigPtr->ChannelSelect[ChannelIndex].GptChannelMode)
            {
            case GPT_CH_MODE_ONESHOT:
                GPTMTAMR(ConfigPtr->ChannelSelect[ChannelIndex].GptChannelId) = (GPTMTAMR(ConfigPtr->ChannelSelect[ChannelIndex].GptChannelId) & 0xFFC) | GPT_CH_MODE_ONESHOT;
                break;
            case GPT_CH_MODE_CONTINUOUS:
                GPTMTAMR(ConfigPtr->ChannelSelect[ChannelIndex].GptChannelId) = (GPTMTAMR(ConfigPtr->ChannelSelect[ChannelIndex].GptChannelId) & 0xFFC) |GPT_CH_MODE_CONTINUOUS;
                break;
            default:
                break;
            }

            /*TODO  : Load the Prescaler value into the GPTMTAPR register */
            GPTMTAPR(ConfigPtr->ChannelSelect[ChannelIndex].GptChannelId) = ConfigPtr->ChannelSelect[ChannelIndex].GptChannelTickFrequency - 1;

            /*TODO  : Load the start value into the GPTMTAILR register */
            if (ConfigPtr->ChannelSelect[ChannelIndex].GptChannelTickValueMax != 0)
            {
                GPTMTAILR(ConfigPtr->ChannelSelect[ChannelIndex].GptChannelId) = ConfigPtr->ChannelSelect[ChannelIndex].GptChannelTickValueMax - 1;
            }
            else
            {
                GPTMTAILR(ConfigPtr->ChannelSelect[ChannelIndex].GptChannelId) = ConfigPtr->ChannelSelect[ChannelIndex].GptChannelTickValueMax;
            }
            /*  only Enable the requred Timers resources.*/
            if (ConfigPtr->ChannelSelect[ChannelIndex].GptChannelTickValueMax == 0)
            {
                CLEAR_BIT(GPTMCTL(ConfigPtr->ChannelSelect[ChannelIndex].GptChannelId),ConfigPtr->ChannelSelect[ChannelIndex].GptChannelId);
            }
            else
            {
                SET_BIT(GPTMCTL(ConfigPtr->ChannelSelect[ChannelIndex].GptChannelId),ConfigPtr->ChannelSelect[ChannelIndex].GptChannelId);
            }
            /* Disable all interrupts */
            SET_BIT(GPTMMIS(ConfigPtr->ChannelSelect[ChannelIndex].GptChannelId), ConfigPtr->ChannelSelect[ChannelIndex].GptChannelId);
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
void Gpt_StartTimer(Gpt_ChannelType Channel,Gpt_ValueType Value)
{
    /*TODO  : Load the Prescaler value into the GPTMTAPR register */
    GPTMTAPR(STR_GptConfigSet->ChannelSelect[Channel].GptChannelId) = STR_GptConfigSet->ChannelSelect[Channel].GptChannelTickFrequency;
    /*TODO  : Load the start value into the GPTMTAILR register */
    if (STR_GptConfigSet->ChannelSelect[Channel].GptChannelTickValueMax != 0)
    {
        GPTMTAILR(STR_GptConfigSet->ChannelSelect[Channel].GptChannelId) = STR_GptConfigSet->ChannelSelect[Channel].GptChannelTickValueMax - 1;
    }
    else
    {
        GPTMTAILR(STR_GptConfigSet->ChannelSelect[Channel].GptChannelId) = STR_GptConfigSet->ChannelSelect[Channel].GptChannelTickValueMax;
    }
    /*TODO  : Enable timer by setting TnEN bit in GPTMCTL register */
    SET_BIT(GPTMCTL(STR_GptConfigSet->ChannelSelect[Channel].GptChannelId),STR_GptConfigSet->ChannelSelect[Channel].GptChannelId);
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
    /* Disable the timer to stop counting */
    CLEAR_BIT(GPTMCTL(STR_GptConfigSet->ChannelSelect[Channel].GptChannelId),STR_GptConfigSet->ChannelSelect[Channel].GptChannelId);
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
    SET_BIT(GPTMMIS(STR_GptConfigSet->ChannelSelect[Channel].GptChannelId),STR_GptConfigSet->ChannelSelect[Channel].GptChannelId);
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
    CLEAR_BIT(GPTMMIS(STR_GptConfigSet->ChannelSelect[Channel].GptChannelId),STR_GptConfigSet->ChannelSelect[Channel].GptChannelId);
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
void Gpt_SetMode(Gpt_ChannelType Mode)
{
    switch (STR_GptConfigSet->ChannelSelect[Mode].GptChannelMode)
    {
    case GPT_CH_MODE_ONESHOT:
        GPTMTAMR(STR_GptConfigSet->ChannelSelect[Mode].GptChannelId) = (GPTMTAMR(STR_GptConfigSet->ChannelSelect[Mode].GptChannelId) & 0xFFC) | GPT_CH_MODE_ONESHOT;
        break;
    case GPT_CH_MODE_CONTINUOUS:
        GPTMTAMR(STR_GptConfigSet->ChannelSelect[Mode].GptChannelId) = (GPTMTAMR(STR_GptConfigSet->ChannelSelect[Mode].GptChannelId) & 0xFFC) | GPT_CH_MODE_CONTINUOUS;
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
    CLEAR_BIT(GPTMICR(STR_GptConfigSet->ChannelSelect[Channel].GptChannelId),STR_GptConfigSet->ChannelSelect[Channel].GptChannelId);
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
void Gpt_Notification_Channel0(void)
{
    if (STR_GptConfigSet->ChannelSelect[GPT_CHL0_ID].GptNotification != NULL_PTR)
    {
        g_GptCallBack_Ptr = STR_GptConfigSet->ChannelSelect[GPT_CHL0_ID].GptNotification;
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
void Gpt_Notification_Channel1(void)
{
    if (STR_GptConfigSet->ChannelSelect[GPT_CHL1_ID].GptNotification != NULL_PTR)
    {
        g_GptCallBack_Ptr = STR_GptConfigSet->ChannelSelect[GPT_CHL1_ID].GptNotification;
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
void Gpt_Notification_Channel2(void)
{
    if (STR_GptConfigSet->ChannelSelect[GPT_CHL2_ID].GptNotification != NULL_PTR)
    {
        g_GptCallBack_Ptr = STR_GptConfigSet->ChannelSelect[GPT_CHL2_ID].GptNotification;
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
void Gpt_Notification_Channel3(void)
{
    if (STR_GptConfigSet->ChannelSelect[GPT_CHL3_ID].GptNotification != NULL_PTR)
    {
        g_GptCallBack_Ptr = STR_GptConfigSet->ChannelSelect[GPT_CHL3_ID].GptNotification;
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
void Gpt_Notification_Channel4(void)
{
    if (STR_GptConfigSet->ChannelSelect[GPT_CHL4_ID].GptNotification != NULL_PTR)
    {
        g_GptCallBack_Ptr = STR_GptConfigSet->ChannelSelect[GPT_CHL4_ID].GptNotification;
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
void Gpt_Notification_Channel5(void)
{
    if (STR_GptConfigSet->ChannelSelect[GPT_CHL5_ID].GptNotification != NULL_PTR)
    {
        g_GptCallBack_Ptr = STR_GptConfigSet->ChannelSelect[GPT_CHL5_ID].GptNotification;
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

