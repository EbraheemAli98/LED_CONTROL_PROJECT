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

/*************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 ************************************************************************************************/
#define NUM_OF_TIMER_CHANNELS   6u
#define GPT_PRESCALER_VALUE     250

#define GPT_CHL0_ID     0u
#define GPT_CHL1_ID     1u
#define GPT_CHL2_ID     2u
#define GPT_CHL3_ID     3u
#define GPT_CHL4_ID     4u
#define GPT_CHL5_ID     5u

#define GPT_TIMER_CFG_32BIT     0x0
#define GPT_TIMER_CFG_16BIT     0x4
#if 0
#define GPT_WT_CFG_16BIT        0x0
#define GPT_WT_CFG_32BIT        0x4
#endif
/*************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 ************************************************************************************************/
typedef uint8  Gpt_ChannelType;  /*Numeric ID of a GPT channel*/
typedef uint32 Gpt_ValueType;    /*Type for reading and setting the timer values (in number of ticks)*/
typedef uint32 Gpt_PredefTimerType; /*Type for GPT Predef Timers*/
typedef uint32 Gpt_ChannelTickFrequencyType; /*Specifies the tick frequency of the timer channel in Hz.*/
typedef void (*Gpt_CallBackPtr)(void);
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
#if 0
/*---------------------------------------------------------------------------------------------------
[Enumeration Name] : Gpt_PredefTimerType
[Description]      : Type for GPT Predef Timers
 ----------------------------------------------------------------------------------------------------*/
typedef enum
{
    GPT_PREDEF_TIMER_1US_16BIT, /*GPT Predef Timer with tick duration 1µs and range 16bit */
    GPT_PREDEF_TIMER_1US_24BIT, /*GPT Predef Timer with tick duration 1µs and range 24bit */
    GPT_PREDEF_TIMER_1US_32BIT, /*GPT Predef Timer with tick duration 1µs and range 32bit */
    GPT_PREDEF_TIMER_100US_32BIT/*GPT Predef Timer with tick duration 100µs and range 32bit */  
}Gpt_PredefTimerType;
#endif
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
    Gpt_CallBackPtr GptNotification;
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
 *  GLOBAL DATA 
 ************************************************************************************************/
extern const Gpt_ConfigType Gpt_ChannelConfigurationStr;

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
void Gpt_SetMode(Gpt_ChannelType Mode);

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
 Service Name     : Gpt_Notification_Channel0
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : None
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : void
 Description      : Function callback.
 ----------------------------------------------------------------------------------------*/
void Gpt_Notification_Channel0(void);

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
void Gpt_Notification_Channel1(void);


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
void Gpt_Notification_Channel2(void);

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
void Gpt_Notification_Channel3(void);

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
void Gpt_Notification_Channel4(void);

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
void Gpt_Notification_Channel5(void);


#endif /* GPT_H */