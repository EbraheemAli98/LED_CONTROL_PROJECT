/**************************************************************************************************
 * File Description
 * -----------------------------------------------------------------------------------------------
 *      File: GPT.h
 *    Module: GPT_MODULE
 * 
 * Description: <write file decription here>
 * 
 **************************************************************************************************/
#ifndef GPT_H
#define GPT_H

/*************************************************************************************************
 * INCLUDES
 ************************************************************************************************/
#include "../../SERVICES/Std_Types.h"
#include "../Comman/PortPin_Macros.h"
#include "Gpt_Cfg.h"

/*************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 ************************************************************************************************/
#define NUM_OF_WIDE_TIMERS                  6u
#define TA_INT_ENABLE_BIT                   PIN0_ID
#define TA_TIMEOUT_IM_BIT                   PIN0_ID
#define TA_TIMEOUT_CINT_BIT                 PIN0_ID
#define TA_TIMEOUT_RIS_BIT                  PIN0_ID
#define TA_TIMEOUT_MIS_BIT                  PIN0_ID

/*************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 ************************************************************************************************/
typedef uint8 Gpt_ChannelType;  /*Numeric ID of a GPT channel*/
typedef uint32 Gpt_ValueType;    /*Type for reading and setting the timer values (in number of ticks)*/
typedef uint32 Gpt_ChannelTickFrequencyType; /*Specifies the tick frequency of the timer channel in Hz.*/
//typedef volatile void (*Gpt_CallBackPtrType)(void);
/*---------------------------------------------------------------------------------------------------
[Enumeration Name] : Gpt_ModeType
[Description]      : Modes of the GPT driver.
 ----------------------------------------------------------------------------------------------------*/
typedef enum
{
    /*After reaching the target time, the timer stops automatically (timerexpired).*/ 
    GPT_CH_MODE_ONESHOT =0x1,
    /*After reaching the target time, the timer continues running with the value "zero" again*/
    GPT_CH_MODE_CONTINUOUS  
}Gpt_ModeType;

/*---------------------------------------------------------------------------------------------------
[Enumeration Name] : Gpt_PredefTimerType
[Description]      : Type for GPT Predef Timers
 ----------------------------------------------------------------------------------------------------*/
typedef enum
{
    GPT_PREDEF_TIMER_1MS_16BIT, /*GPT Predef Timer with tick duration 1ms and range 16bit */
    GPT_PREDEF_TIMER_1MS_24BIT, /*GPT Predef Timer with tick duration 1ms and range 24bit */
    GPT_PREDEF_TIMER_1SEC_32BIT, /*GPT Predef Timer with tick duration 1s and range 32bit */
    GPT_PREDEF_TIMER_100MS_32BIT/*GPT Predef Timer with tick duration 100ms and range 32bit */  
}Gpt_PredefTimerType;

/*---------------------------------------------------------------------------------------------------
[Stucture Name] : Gpt_ChannelConfigSet
[Description]   : This container contains the channel specific configuration of the GPT Driver.
 ----------------------------------------------------------------------------------------------------*/
 typedef struct 
 {
    Gpt_ChannelType GptChannelId;
    Gpt_ModeType GptChannelMode;/*Specifies the behavior of the timer channel after the target time is reached.*/
    Gpt_PredefTimerType GptChannelTickFrequency; /*Specifies the tick frequency of the timer channel in Hz.*/
    Gpt_ValueType GptChannelTickValueMax;
 }Gpt_ChannelConfigSet;
 
/*---------------------------------------------------------------------------------------------------
[Stucture Name] : Gpt_ConfigType
[Description]   : This is the type of the data structure including the configuration set required for
                initializing the GPT timer unit.
 ----------------------------------------------------------------------------------------------------*/
typedef struct 
{
    Gpt_ChannelConfigSet ChannelSelect[NUM_OF_TIMER_CHANNELS];
}Gpt_ConfigType;

/*************************************************************************************************
 * EXTERNAL SHARED DATA
 ************************************************************************************************/
#include "Gpt_Lcfg.h"

/*************************************************************************************************
 * APIs DECLARATION
 ************************************************************************************************/
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
 void Gpt_Init(const Gpt_ConfigType *ConfigPtr);
 
 /*-----------------------------------------------------------------------------------
 Service Name     : Gpt_DeInit
 Sync/Async       : Synchronous
 Reentrnacy       : Non-Reentrant
 Parameter(in)    : None
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to Deinitialize the GPT driver
 -----------------------------------------------------------------------------------*/
 void Gpt_DeInit(void);

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
void Gpt_EnableNotification(Gpt_ChannelType Channel);

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
void Gpt_DisableNotification(Gpt_ChannelType Channel);

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
void Gpt_SetMode(Gpt_ChannelType Channel,Gpt_ModeType Mode);

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
void Gpt_StartTimer(Gpt_ChannelType Channel,Gpt_ValueType Value);

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
void Gpt_StopTimer(Gpt_ChannelType Channel);

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
 void Gpt_InterruptFlagReset(Gpt_ChannelType Channel);

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
void Gpt_Notification_T0(void(*GptNotification)(void));

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
void Gpt_Notification_T1(void(*GptNotification)(void));


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
void Gpt_Notification_T2(void(*GptNotification)(void));

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
void Gpt_Notification_T0(void(*GptNotification)(void));

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
void Gpt_Notification_T4(void(*GptNotification)(void));

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
void Gpt_Notification_T5(void(*GptNotification)(void));


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
void Gpt_Notification_WT0(void(*GptNotification)(void));

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
void Gpt_Notification_WT1(void(*GptNotification)(void));

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
void Gpt_Notification_WT2(void(*GptNotification)(void));

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
void Gpt_Notification_WT3(void(*GptNotification)(void));

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
void Gpt_Notification_WT4(void(*GptNotification)(void));

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
void Gpt_Notification_WT5(void(*GptNotification)(void));

#endif /* GPT_H */