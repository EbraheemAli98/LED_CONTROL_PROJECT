/********************************************************************************************
 * File Description
 * ------------------------------------------------------------------------------------------*/
/**      @file Gpt_Lcfg.c
 *       @brief Link-time configuration source file
 * 
 *     @details This file contains :
 *              1. Configuration of the module if the source code is not available.(Modules 
 *                  may be available as object files).
 *              2. Constant data outside the module. The data can be configured after the 
 *                 module has been compiled but before linking.
 *              3. Configuration change needs software relinking.
 * 
 *     @author  Ebraheem Ali
 *     @version V1.0.0
 *     @date    Dec 23, 2022
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
         {GPT_WT_CHL0_ID,GPT_CH_MODE_CONTINUOUS,GPT_PREDEF_TIMER_1SEC_32BIT,GPT_1SEC_TICK_VALUE},
         {GPT_WT_CHL1_ID,GPT_CH_MODE_CONTINUOUS,GPT_PREDEF_TIMER_100MS_32BIT,0},
         {GPT_WT_CHL2_ID,GPT_CH_MODE_CONTINUOUS,GPT_PREDEF_TIMER_100MS_32BIT,0},
         {GPT_WT_CHL3_ID,GPT_CH_MODE_CONTINUOUS,GPT_PREDEF_TIMER_100MS_32BIT,0},
         {GPT_WT_CHL4_ID,GPT_CH_MODE_CONTINUOUS,GPT_PREDEF_TIMER_100MS_32BIT,0},
         {GPT_WT_CHL5_ID,GPT_CH_MODE_CONTINUOUS,GPT_PREDEF_TIMER_100MS_32BIT,0}
         }
    };