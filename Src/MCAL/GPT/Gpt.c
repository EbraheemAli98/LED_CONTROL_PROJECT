/********************************************************************************************
 * File Description
 * ------------------------------------------------------------------------------------------*/
/**      @file Gpt.c
 *       @brief Source file to initialize and implement General Purpose Timer.
 *
 *     @details 1- Count up is not configured in this module.
 *              2- Only Individual mode is implemented in this module.
 *              3- Both 16/32Bit Timer and 32/64Bit Wide Timer is implemented.
 *              4- Only one-shot and periodic modes are implemented.
 *              5- Only Timer channel A is configured and implemented.
 *  NOTE :The prescaler can yield proper division only when the timer is configured as a down counter.
 *      
 *      @author  Ebraheem Ali
 *      @version V1.1.1
 *      @date  Dec 23, 2022
 *
 *********************************************************************************************/

/***************************************************************************************
 * INCLUDES
 ****************************************************************************************/
#include "Gpt.h"
#include "../../SERVICES/Comman_Macro.h"
#include "../Comman/MemMap.h"


/*************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 ************************************************************************************************/
static void GetTimerBaseAddress(Gpt_ChannelType Timer_ID,volatile uint32 **BaseAddressPtr); 

/*************************************************************************************************
 *  LOCAL FUNCTION 
 ************************************************************************************************/
static void GetTimerBaseAddress(Gpt_ChannelType Timer_ID,volatile uint32 **BaseAddressPtr)  
{
    switch (Timer_ID)
            {
            case GPT_CHL0_ID:
                *BaseAddressPtr = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL0_ID * 0x1000));
                break;
            case GPT_CHL1_ID:
                *BaseAddressPtr = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL1_ID * 0x1000));
                break;
            case GPT_CHL2_ID:
                *BaseAddressPtr = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL2_ID * 0x1000));
                break;
            case GPT_CHL3_ID:
                *BaseAddressPtr = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL3_ID * 0x1000));
                break;
            case GPT_CHL4_ID:
                *BaseAddressPtr = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL4_ID * 0x1000));
                break;
            case GPT_CHL5_ID:
                *BaseAddressPtr = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_CHL5_ID * 0x1000));
                break;
            case GPT_WT_CHL0_ID:
               *BaseAddressPtr = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_WT_CHL0_ID * 0x1000));
                break;
            case GPT_WT_CHL1_ID:
                *BaseAddressPtr = (volatile uint32 *)(TIMER_BASE_ADDRESS + (GPT_WT_CHL1_ID * 0x1000));
                break;
            case GPT_WT_CHL2_ID:
                *BaseAddressPtr = (volatile uint32 *)(TIMER_BASE_ADDRESS + 0x1C000);
                break;
            case GPT_WT_CHL3_ID:
                *BaseAddressPtr = (volatile uint32 *)(TIMER_BASE_ADDRESS + 0x1D000);
                break;
            case GPT_WT_CHL4_ID:
                *BaseAddressPtr = (volatile uint32 *)(TIMER_BASE_ADDRESS + 0x1E000);
                break;
            case GPT_WT_CHL5_ID:
                *BaseAddressPtr = (volatile uint32 *)(TIMER_BASE_ADDRESS + 0x1F000);
                break;
            default:
                break;
            }
}

/*************************************************************************************************
 *  LOCAL DATA
 ************************************************************************************************/
static const Gpt_ConfigType *STR_GptConfigSet;
static void (*g_GptCallBack_Ptr)(void) = NULL_PTR;

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
        volatile uint32 *Base_Address = NULL_PTR; /*pointer to the base address of the timer*/

        for (ChannelIndex = 0; ChannelIndex < NUM_OF_TIMER_CHANNELS; ChannelIndex++)
        {
            /* 
             * Enable clock to the timer block
             */
            if(ChannelIndex >= GPT_CHL0_ID && ChannelIndex <= GPT_CHL5_ID)
            {
              SET_BIT(SYSCTL_RCGCTIMER, ConfigPtr->ChannelSelect[ChannelIndex].GptChannelId);
              dump = SYSCTL_RCGCTIMER;
            }
            else if(ChannelIndex >=  GPT_WT_CHL0_ID && ChannelIndex <= GPT_WT_CHL5_ID)
            {
              SET_BIT(SYSCTL_RCGCWTIMER, (ConfigPtr->ChannelSelect[ChannelIndex].GptChannelId)-NUM_OF_WIDE_TIMERS);
              dump = SYSCTL_RCGCWTIMER;
            }
            else
            {
              
            }

            /*
             * Get the value of the Timer Channel Base Address
             */
            GetTimerBaseAddress(ConfigPtr->ChannelSelect[ChannelIndex].GptChannelId,&Base_Address);

            /* 
             * Disable timer by clearing TnEN bit in GPTMCTL register
             */
            *(volatile uint32 *)((volatile uint8*)Base_Address + GPTMCTL) = 0;

            /*
             * Write the GPTMCFG register to choose the timer configuration.
             */
            *(volatile uint32 *)((volatile uint8*)Base_Address + GPTMCFG) = GPT_TIMER_CFG_INDIVIDVAL;

            /*
             * Configure the TnMR field in the GPTMTnMR register to set the TIMER behaviour when reaching the overflow value.
             */
            switch (ConfigPtr->ChannelSelect[ChannelIndex].GptChannelMode)
            {
            case GPT_CH_MODE_ONESHOT:      /* Configure The ONE-SHOT mode */
                *(volatile uint32 *)((volatile uint8*)Base_Address + GPTMTAMR) = (*(volatile uint32 *)((volatile uint8*)Base_Address + GPTMTAMR) & 0xFFC) | GPT_CH_MODE_ONESHOT;
                break;
            case GPT_CH_MODE_CONTINUOUS:   /* Configure The Periodic/Continuous mode */
                *(volatile uint32 *)((volatile uint8*)Base_Address + GPTMTAMR) = (*(volatile uint32 *)((volatile uint8*)Base_Address + GPTMTAMR) & 0xFFC) | GPT_CH_MODE_CONTINUOUS;
                break;
            default:
                break;
            }

            /*/////////////////////////////////////////////////// Confiuring the timer frequancey ////////////////////////////////////////////*/
           
            switch (ConfigPtr->ChannelSelect[ChannelIndex].GptChannelTickFrequency)
            {
            case GPT_PREDEF_TIMER_1MS_16BIT:     /* if the user wants to use the processor frequancey (without prescaler) */
                /*============================================================================================================================================
                 * 1. Load the start value into the GPTMTAILR register.
                 * NOTE :This is configured for 16/32Bit Individual Timer configuration.
                 * NOTE :The CPU frequency of 16 MHz means clock period of 1/16MHz = 62.5ns (nanosecond) being fed to TimerA.
                 *       To get 1msec delay we need 1msec/62.5ns = 16,000 clocks.[number_of_ticks = T(req)/T(clock)]
                 * NOTE :In 16-Bit mode the interval mode register is limited by 4msec ((2^16)*62.5nsec = 4.096msec),For longer delay it is recommended to use
                 *       incorporate prescaler or use a 32-Bit timer mode.
                 *=============================================================================================================================================*/
                *(volatile uint32 *)((volatile uint8*)Base_Address + GPTMTAILR) = ConfigPtr->ChannelSelect[ChannelIndex].GptChannelTickValueMax - 1;
                break;
            
            case GPT_PREDEF_TIMER_1MS_24BIT:  /* If the user wants to divide the processor frequancey by a prescaler value */
                /*===========================================================================================================================================
                 * 1. Load the Prescaler value into the GPTMTAPR register.
                 * 2. Load the start value into the GPTMTAILR register.                 
                 * NOTE :The value of the prescaler must defined first in the pre-compile configuration file.
                 * NOTE :This is configured for 16/32Bit Individual Timer configuration. 
                 * NOTE :TimerA in 16-bit mode has an 8-bit prescaler register whose value can go from 0x00 to 0xFF.
                 * Hint :The prescaler register allows system frequency to be divided by a value between 1 and 256 before it is fed to the TimerA.
                 * Example-1: To generate a 1-second delay using prescaler, T(max)=(2^16)*(Tclock)*Prescaler_value = 65535 * 62.5nsec * 256 = 1.0485 second.
                 * Example-2: Using prescaler of 250 gives us 16MHz/250=64000Hz. That means the clock fed to timer A is 1/64000Hz=15.625 msec.
                 *            To get one second delay, we need 1sec/15.625ms=64000 for the match(GPTMTAILR) register.
                 *=============================================================================================================================================*/
                *(volatile uint32 *)((volatile uint8*)Base_Address + GPTMTAPR) = GPT_8BIT_PRESCALER_VALUE - 1;
                *(volatile uint32 *)((volatile uint8*)Base_Address + GPTMTAILR) = ConfigPtr->ChannelSelect[ChannelIndex].GptChannelTickValueMax - 1;
                break;
            
            case GPT_PREDEF_TIMER_1SEC_32BIT:   /* If the user wants to use the processor frequency(without prescaler) */ 
                /*========================================================================================================================================
                 * 1. Load the start value int the GPTMTAILR register.
                 * NOTE :This is configured for 32/64Bit Individual Timer configuration. 
                 * Hint :The maximum time can be generated in this mode is..
                 *       Tmax = (2^32)* Tclock = (2^32) * 62.5ns = 268.4 seconds, So we can calculate any required
                 *       time under this range by simply applying this equation:
                 *          TickMaxValue = Treq / Tclock
                 * Example :To generate a 1-second delay,we should apply a count value equal to:
                 *             TickValueMax = 1sec/62.5ns = 1*(10^9)ns/62.5ns =16,000,000  , (1sec = 10^9 nanoseconds).
                 *========================================================================================================================================*/
                *(volatile uint32 *)((volatile uint8*)Base_Address + GPTMTAILR) = ConfigPtr->ChannelSelect[ChannelIndex].GptChannelTickValueMax - 1;
                break;

            case GPT_PREDEF_TIMER_100MS_32BIT:  /* If the user wants to use the processor frequency with 16-bit prescaler register */ 
                /*========================================================================================================================================
                 * 1. Load the Prescaler value into the GPTMTAPR register.
                 * 2. Load the start value int the GPTMTAILR register.
                 * NOTE :The value of the prescaler must defined first in the pre-compile configuration file.
                 * NOTE :This is configured for 32/64Bit Individual Timer configuration. 
                 *========================================================================================================================================*/
                *(volatile uint32 *)((volatile uint8*)Base_Address + GPTMTAPR) = GPT_16BIT_PRESCALER_VALUE - 1;
                *(volatile uint32 *)((volatile uint8*)Base_Address + GPTMTAILR) = ConfigPtr->ChannelSelect[ChannelIndex].GptChannelTickValueMax - 1;
                break;

            default:
                break;
            }

            /*=========================================================================================================================  
             * Enable only the Timers Defines with value Ohter than the Default values...
             *  - GPT_PREDEF_TIMER_100US_32BIT : Default value for 32/64 Bit Wide Timers.
             *  - GPT_PREDEF_TIMER_1US_16BIT   : Default value for 16/32 Bit Timer.
             * Enable Steps:-
             *  1. Clear the Interrupt Flag.
             *  2. Enable Timer From GPTMCTL register to start counting.
             *=========================================================================================================================*/
            if (ConfigPtr->ChannelSelect[ChannelIndex].GptChannelTickValueMax == GPT_PREDEF_TIMER_100MS_32BIT && ConfigPtr->ChannelSelect[ChannelIndex].GptChannelTickValueMax == GPT_PREDEF_TIMER_1MS_16BIT)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8*)Base_Address + GPTMICR), TA_TIMEOUT_MIS_BIT);
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8*)Base_Address + GPTMCTL), TA_INT_ENABLE_BIT);
            }
            else
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8*)Base_Address + GPTMICR), TA_TIMEOUT_CINT_BIT);
                SET_BIT(*(volatile uint32 *)((volatile uint8*)Base_Address + GPTMCTL), TA_INT_ENABLE_BIT);
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
void Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType StartValue)
{
    /*============================================================================================================
     * Get the value of the Timer Channel Base Address
     =============================================================================================================*/
    volatile uint32 *Base_Address = NULL_PTR;
    GetTimerBaseAddress(Channel,&Base_Address);

    switch (STR_GptConfigSet->ChannelSelect[Channel].GptChannelTickFrequency)
    {
    case GPT_PREDEF_TIMER_1MS_16BIT: /* |If the user wants to use the same processor frequancey (without prescaler) */
        /*========================================================================================================
         * 1. Load the start value into the GPTMTAILR register.
         * NOTE :This is configured for 16/32Bit Individual Timer configuration.
         *========================================================================================================*/
        *(volatile uint32 *)((volatile uint8 *)Base_Address + GPTMTAILR) = (StartValue * STR_GptConfigSet->ChannelSelect[Channel].GptChannelTickValueMax) - 1;
        break;

    case GPT_PREDEF_TIMER_1MS_24BIT: /* If the user wants to divide the processor frequancey by a prescaler value */
        /*=========================================================================================================
         * 1. Load the Prescaler value into the GPTMTAPR register.
         * 2. Load the start value int the GPTMTAILR register.
         * NOTE :The value of the prescaler must defined first in the pre-compile configuration file.
         * NOTE :This is configured for 16/32Bit Individual Timer configuration.
         *========================================================================================================*/
        /*TODO  : Calculate the TICK Value required for this mode */
        *(volatile uint32 *)((volatile uint8 *)Base_Address + GPTMTAPR) = GPT_8BIT_PRESCALER_VALUE - 1;
        *(volatile uint32 *)((volatile uint8 *)Base_Address + GPTMTAILR) = (StartValue * STR_GptConfigSet->ChannelSelect[Channel].GptChannelTickValueMax) - 1;
        break;

    case GPT_PREDEF_TIMER_1SEC_32BIT: /* If the user wants to use the same processor frequency(without prescaler) */
        /*========================================================================================================
         * 1. Load the start value into the GPTMTAILR register.
         * NOTE :This is configured for 32/64Bit Individual Timer configuration.
         *========================================================================================================*/
        *(volatile uint32 *)((volatile uint8 *)Base_Address + GPTMTAILR) = (StartValue * STR_GptConfigSet->ChannelSelect[Channel].GptChannelTickValueMax) - 1;
        break;

    case GPT_PREDEF_TIMER_100MS_32BIT:
        /*=========================================================================================================
         * 1. Load the Prescaler value into the GPTMTAPR register.
         * 2. Load the start value int the GPTMTAILR register.
         * NOTE :The value of the prescaler must defined first in the pre-compile configuration file.
         * NOTE :This is configured for 32/64Bit Individual Timer configuration.
         *========================================================================================================*/
        /*TODO  : Calculate the TICK Value required for this mode */
        *(volatile uint32 *)((volatile uint8 *)Base_Address + GPTMTAPR) = GPT_16BIT_PRESCALER_VALUE - 1;
        *(volatile uint32 *)((volatile uint8 *)Base_Address + GPTMTAILR) = (StartValue * STR_GptConfigSet->ChannelSelect[Channel].GptChannelTickValueMax) - 1;
        break;

    default:
        break;
    }

    /*=============================================================================================================
     * Enable timer by setting TnEN bit in GPTMCTL register.
     *=============================================================================================================*/
    SET_BIT(*(volatile uint32 *)((volatile uint8*)Base_Address + GPTMCTL), TA_INT_ENABLE_BIT);
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
    /*===========================================================================================================
     * Get the value of the Timer Channel Base Address
     *===========================================================================================================*/
    volatile uint32 *Base_Address = NULL_PTR;
    GetTimerBaseAddress(Channel,&Base_Address);

    /*============================================================================================================
     * Disable the timer to stop counting by clearing the corresponding bit in GPTMCTL.
     *============================================================================================================*/
    CLEAR_BIT(*(volatile uint32 *)((volatile uint8*)Base_Address + GPTMCTL), TA_INT_ENABLE_BIT);
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
    /*
     * Get the value of the Timer Channel Base Address
     */
    volatile uint32 *Base_Address = NULL_PTR;
    GetTimerBaseAddress(Channel,&Base_Address);

    /*
     * 1. Enable Interrupt by setting the corresponding bit into GPTMIMR register.
     * 3. Clear the TATOIM bit in GPTMMIS register by setting (TATOCINT) bit in GPTMICR register.
     * NOTE :The last two steps to make
     */
    *(volatile uint32 *)((volatile uint8*)Base_Address + GPTMIMR) |= (1<<TA_TIMEOUT_IM_BIT) ;
    SET_BIT(*(volatile uint32 *)((volatile uint8*)Base_Address + GPTMICR), TA_TIMEOUT_CINT_BIT);
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
    /*
     * Get the value of the Timer Channel Base Address
     */
    volatile uint32 *Base_Address = NULL_PTR;
    GetTimerBaseAddress(Channel,&Base_Address);

    CLEAR_BIT(*(volatile uint32 *)((volatile uint8*)Base_Address + GPTMIMR), TA_TIMEOUT_IM_BIT);
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
void Gpt_SetMode(Gpt_ChannelType Channel,Gpt_ModeType Mode)
{
    /*
     * Get the value of the Timer Channel Base Address
     */
    volatile uint32 *Base_Address = NULL_PTR;
    GetTimerBaseAddress(Channel,&Base_Address);

    /*  
     * Stop timer before re-setting the timer mode again.
     */
    CLEAR_BIT(*(volatile uint32*)((volatile uint8*)Base_Address + GPTMCTL),TA_TIMEOUT_CINT_BIT );
    
    /*
     * Configure the TnMR field in the GPTMTnMR register to set the TIMER behaviour when reaching the overflow value.
     */
    switch (Mode)
    {
    case GPT_CH_MODE_ONESHOT: /* Configure The ONE-SHOT mode */
        *(volatile uint32 *)((volatile uint8 *)Base_Address + GPTMTAMR) = (*(volatile uint32 *)((volatile uint8 *)Base_Address + GPTMTAMR) & 0xFFC) | GPT_CH_MODE_ONESHOT;
        break;
    case GPT_CH_MODE_CONTINUOUS: /* Configure The Periodic/Continuous mode */
        *(volatile uint32 *)((volatile uint8 *)Base_Address + GPTMTAMR) = (*(volatile uint32 *)((volatile uint8 *)Base_Address + GPTMTAMR) & 0xFFC) | GPT_CH_MODE_CONTINUOUS;
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
    /*
     * Get the value of the Timer Channel Base Address
     */
    volatile uint32 *Base_Address = NULL_PTR;
    GetTimerBaseAddress(Channel,&Base_Address);

    SET_BIT(*(volatile uint32 *)((volatile uint8*)Base_Address + GPTMICR), TA_TIMEOUT_CINT_BIT );
}

/*-------------------------------------------------------------------------------------
Service Name     : Gpt_Notification_T0
Sync/Async       : Synchronous
Reentrnacy       : Reentrant
Parameter(in)    : None
Parameter(in/out): None
Parameter(out)   : None
Return Value     : void
Description      : Function callback.
----------------------------------------------------------------------------------------*/
void Gpt_Notification_T0(void(*GptNotification)(void))
{
    if (GptNotification != NULL_PTR)
    {
        g_GptCallBack_Ptr = GptNotification;
    }
}

/*-------------------------------------------------------------------------------------
Service Name     : Gpt_Notification_T1
Sync/Async       : Synchronous
Reentrnacy       : Reentrant
Parameter(in)    : None
Parameter(in/out): None
Parameter(out)   : None
Return Value     : void
Description      : Function callback.
----------------------------------------------------------------------------------------*/
void Gpt_Notification_T1(void(*GptNotification)(void))
{
    if (GptNotification != NULL_PTR)
    {
        g_GptCallBack_Ptr = GptNotification;
    }
}

/*-------------------------------------------------------------------------------------
Service Name     : Gpt_Notification_T2
Sync/Async       : Synchronous
Reentrnacy       : Reentrant
Parameter(in)    : None
Parameter(in/out): None
Parameter(out)   : None
Return Value     : void
Description      : Function callback.
----------------------------------------------------------------------------------------*/
void Gpt_Notification_T2(void(*GptNotification)(void))
{
    if (GptNotification != NULL_PTR)
    {
        g_GptCallBack_Ptr = GptNotification;
    }
}

/*-------------------------------------------------------------------------------------
Service Name     : Gpt_Notification_T3
Sync/Async       : Synchronous
Reentrnacy       : Reentrant
Parameter(in)    : None
Parameter(in/out): None
Parameter(out)   : None
Return Value     : void
Description      : Function callback.
----------------------------------------------------------------------------------------*/
void Gpt_Notification_T3(void(*GptNotification)(void))
{
    if (GptNotification != NULL_PTR)
    {
        g_GptCallBack_Ptr = GptNotification;
    }
}

/*-------------------------------------------------------------------------------------
Service Name     : Gpt_Notification_T4
Sync/Async       : Synchronous
Reentrnacy       : Reentrant
Parameter(in)    : None
Parameter(in/out): None
Parameter(out)   : None
Return Value     : void
Description      : Function callback.
----------------------------------------------------------------------------------------*/
void Gpt_Notification_T4(void(*GptNotification)(void))
{
    if (GptNotification != NULL_PTR)
    {
        g_GptCallBack_Ptr = GptNotification;
    }
}

/*-------------------------------------------------------------------------------------
Service Name     : Gpt_Notification_T5
Sync/Async       : Synchronous
Reentrnacy       : Reentrant
Parameter(in)    : None
Parameter(in/out): None
Parameter(out)   : None
Return Value     : void
Description      : Function callback.
----------------------------------------------------------------------------------------*/
void Gpt_Notification_T5(void(*GptNotification)(void))
{
    if (GptNotification != NULL_PTR)
    {
        g_GptCallBack_Ptr = GptNotification;
    }
}

/*-------------------------------------------------------------------------------------
Service Name     : Gpt_Notification_WT0
Sync/Async       : Synchronous
Reentrnacy       : Reentrant
Parameter(in)    : None
Parameter(in/out): None
Parameter(out)   : None
Return Value     : void
Description      : Function callback.
----------------------------------------------------------------------------------------*/
void Gpt_Notification_WT0(void(*GptNotification)(void))
{
    if (GptNotification != NULL_PTR)
    {
        g_GptCallBack_Ptr = GptNotification;
    }
}

/*-------------------------------------------------------------------------------------
Service Name     : Gpt_Notification_WT1
Sync/Async       : Synchronous
Reentrnacy       : Reentrant
Parameter(in)    : None
Parameter(in/out): None
Parameter(out)   : None
Return Value     : void
Description      : Function callback.
----------------------------------------------------------------------------------------*/
void Gpt_Notification_WT1(void(*GptNotification)(void))
{
    if (GptNotification != NULL_PTR)
    {
        g_GptCallBack_Ptr = GptNotification;
    }
}

/*-------------------------------------------------------------------------------------
Service Name     : Gpt_Notification_WT2
Sync/Async       : Synchronous
Reentrnacy       : Reentrant
Parameter(in)    : None
Parameter(in/out): None
Parameter(out)   : None
Return Value     : void
Description      : Function callback.
----------------------------------------------------------------------------------------*/
void Gpt_Notification_WT2(void(*GptNotification)(void))
{
    if (GptNotification != NULL_PTR)
    {
        g_GptCallBack_Ptr = GptNotification;
    }
}

/*-------------------------------------------------------------------------------------
Service Name     : Gpt_Notification_WT3
Sync/Async       : Synchronous
Reentrnacy       : Reentrant
Parameter(in)    : None
Parameter(in/out): None
Parameter(out)   : None
Return Value     : void
Description      : Function callback.
----------------------------------------------------------------------------------------*/
void Gpt_Notification_WT3(void(*GptNotification)(void))
{
    if (GptNotification != NULL_PTR)
    {
        g_GptCallBack_Ptr = GptNotification;
    }
}

/*-------------------------------------------------------------------------------------
Service Name     : Gpt_Notification_WT4
Sync/Async       : Synchronous
Reentrnacy       : Reentrant
Parameter(in)    : None
Parameter(in/out): None
Parameter(out)   : None
Return Value     : void
Description      : Function callback.
----------------------------------------------------------------------------------------*/
void Gpt_Notification_WT4(void(*GptNotification)(void))
{
    if (GptNotification != NULL_PTR)
    {
        g_GptCallBack_Ptr = GptNotification;
    }
}

/*-------------------------------------------------------------------------------------
Service Name     : Gpt_Notification_WT5
Sync/Async       : Synchronous
Reentrnacy       : Reentrant
Parameter(in)    : None
Parameter(in/out): None
Parameter(out)   : None
Return Value     : void
Description      : Function callback.
----------------------------------------------------------------------------------------*/
void Gpt_Notification_WT5(void(*GptNotification)(void))
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

/*----------------------------------------------------------------------*/
void WTIMER0A_Handler(void)
{
    if (g_GptCallBack_Ptr != NULL_PTR)
    {
        (*g_GptCallBack_Ptr)();
    }
}
