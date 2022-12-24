/********************************************************************************************
 * File Description
 * ------------------------------------------------------------------------------------------*/
/**      @file Gpt_Lcfg.c
 *       @brief
 *
 *     @details
 *
 *********************************************************************************************/

/*************************************************************************************************
 * INCLUDES
 ************************************************************************************************/
#include "Gpt.h"


const Gpt_ConfigType Gpt_ChannelConfigurationStr =
    {
        {
         {GPT_CHL0_ID, GPT_CH_MODE_CONTINUOUS, GPT_PREDEF_TIMER_1MS_16BIT, 0},
         {GPT_CHL1_ID, GPT_CH_MODE_CONTINUOUS, GPT_PREDEF_TIMER_1MS_16BIT, 0},
         {GPT_CHL2_ID, GPT_CH_MODE_CONTINUOUS, GPT_PREDEF_TIMER_1MS_16BIT, 0},
         {GPT_CHL3_ID, GPT_CH_MODE_CONTINUOUS, GPT_PREDEF_TIMER_1MS_16BIT, 0},
         {GPT_CHL4_ID, GPT_CH_MODE_CONTINUOUS, GPT_PREDEF_TIMER_1MS_16BIT, 0},
         {GPT_CHL5_ID, GPT_CH_MODE_CONTINUOUS, GPT_PREDEF_TIMER_1MS_16BIT, 0},
         {GPT_WT_CHL0_ID,GPT_CH_MODE_CONTINUOUS,GPT_PREDEF_TIMER_1SEC_32BIT,GPT_TICK_VALUE_MAX_32BIT},
         {GPT_WT_CHL1_ID,GPT_CH_MODE_CONTINUOUS,GPT_PREDEF_TIMER_100MS_32BIT,0},
         {GPT_WT_CHL2_ID,GPT_CH_MODE_CONTINUOUS,GPT_PREDEF_TIMER_100MS_32BIT,0},
         {GPT_WT_CHL3_ID,GPT_CH_MODE_CONTINUOUS,GPT_PREDEF_TIMER_100MS_32BIT,0},
         {GPT_WT_CHL4_ID,GPT_CH_MODE_CONTINUOUS,GPT_PREDEF_TIMER_100MS_32BIT,0},
         {GPT_WT_CHL5_ID,GPT_CH_MODE_CONTINUOUS,GPT_PREDEF_TIMER_100MS_32BIT,0}
         }
    };