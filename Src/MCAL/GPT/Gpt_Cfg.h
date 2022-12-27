/**************************************************************************************************
 * File Description
 * -----------------------------------------------------------------------------------------------
 *      File: Gpt_Cfg.h
 *    Module: GPT_MODULE
 * 
 * Description: < Header file contains all Pre-compile time configurations >
 * 
 **************************************************************************************************/

#ifndef GPT_CFG_H
#define GPT_CFG_H

/*************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 ************************************************************************************************/
#define NUM_OF_WIDE_TIMERS           6u
#define NUM_OF_TIMER_CHANNELS        12u
#define GPT_8BIT_PRESCALER_VALUE     250u
#define GPT_16BIT_PRESCALER_VALUE    1024u    
#define GPT_1MSEC_TICK_VALUE         16000u  
#define GPT_1SEC_TICK_VALUE          16000000u

#define GPT_CHL0_ID        0u
#define GPT_CHL1_ID        1u
#define GPT_CHL2_ID        2u
#define GPT_CHL3_ID        3u
#define GPT_CHL4_ID        4u
#define GPT_CHL5_ID        5u

#define GPT_WT_CHL0_ID     6u
#define GPT_WT_CHL1_ID     7u
#define GPT_WT_CHL2_ID     8u
#define GPT_WT_CHL3_ID     9u
#define GPT_WT_CHL4_ID     10u
#define GPT_WT_CHL5_ID     11u

#define GPT_TIMER_CFG_CONCATENATED     0x0
#define GPT_TIMER_CFG_INDIVIDVAL       0x4

#endif /* GPH_CFG_H */