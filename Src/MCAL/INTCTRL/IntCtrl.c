/********************************************************************************************
 * File Description
 * ------------------------------------------------------------------------------------------*/
/**      @file IntCtrl.c
 *       @brief
 * 
 *     @details
 * 
 *********************************************************************************************/

/***************************************************************************************
 * INCLUDES
****************************************************************************************/
#include "IntCtrl.h"
#include "../Comman/MemMap.h"


/*************************************************************************************************
 * LOCAL FUNCTION PROTOTYPE
 ************************************************************************************************/
static void SetPriority(IntCtrl_InterruptType IntNum,IntCtrl_PriorityNum PriorityLevel);
#if 0
static void SetPriorityGrouping(Group_SubGroupType PriorityGrouping);
#endif
static void InterruptEnable(IntCtrl_InterruptType IntNum);
static void InterruptDisable(IntCtrl_InterruptType IntNum);

/*************************************************************************************************
 * LOCAL FUNCTIONS
 ************************************************************************************************/
static void InterruptEnable(IntCtrl_InterruptType IntNum)
{
    uint8 BitNum = 0;
    if (IntNum > 31)
    {
        if (&ENx(IntNum) == (uint32*)(CORTEXM4_PERI_BASE_ADDRESS+0x104))
        {
            BitNum = IntNum - 32;
        }
        else if (&ENx(IntNum) == (uint32*)(CORTEXM4_PERI_BASE_ADDRESS+0x108))
        {
            BitNum = IntNum - (2 * 32);
        }
        else if (&ENx(IntNum) == (uint32*)(CORTEXM4_PERI_BASE_ADDRESS+0x10C))
        {
            BitNum = IntNum - (3 * 32);
        }
        else
        {

        }
    }
    else
    {
        BitNum = IntNum;
    }
    SET_BIT(ENx(IntNum),BitNum); 
}
static void InterruptDisable(IntCtrl_InterruptType IntNum)
{
    uint8 BitNum = 0;
    if (IntNum > 31)
    {
        if (&ENx(IntNum) == (uint32*)(CORTEXM4_PERI_BASE_ADDRESS+0x104))
        {
            BitNum = IntNum - 32;
        }
        else if (&ENx(IntNum) == (uint32*)(CORTEXM4_PERI_BASE_ADDRESS+0x108))
        {
            BitNum = IntNum - (2 * 32);
        }
        else if (&ENx(IntNum) == (uint32*)(CORTEXM4_PERI_BASE_ADDRESS+0x10C))
        {
            BitNum = IntNum - (3 * 32);
        }
        else
        {

        }
    }
    else
    {
        BitNum = IntNum;
    }
    SET_BIT(DISx(IntNum),IntNum);
}
#if 0
static void SetPriorityGrouping(Group_SubGroupType PriorityGrouping)
{
    switch (PriorityGrouping)
    {
    case EGIHT_GROUP_NONE_SUBGROUP:
        WRITE_PORT_MASK(APINT,APINT_KEY|EGIHT_GROUP_NONE_SUBGROUP);
        break;
    case FOUR_GROUP_TWO_SUBGROUP:
        WRITE_PORT_MASK(APINT,APINT_KEY|FOUR_GROUP_TWO_SUBGROUP);
        break;
    case TWO_GROUP_FOUR_SUBGROUP:
        WRITE_PORT_MASK(APINT,APINT_KEY|TWO_GROUP_FOUR_SUBGROUP);
        break;
    case ONE_GROUP_EGIHT_SUBGROUP:
        WRITE_PORT_MASK(APINT,APINT_KEY|ONE_GROUP_EGIHT_SUBGROUP);
        break;
    default:
        break;
    }
}
#endif

static void SetPriority(IntCtrl_InterruptType IntNum,IntCtrl_PriorityNum PriorityLevel)
{
    uint8 InterruptPriorityNum = IntNum/4; /* it represents the priortiy register number(n) in the PRI(n) */
    uint8 pos;
    if (IntNum == InterruptPriorityNum * 4)
    {
        pos = INTA;
    }
    else if (IntNum == (InterruptPriorityNum * 4)+1)
    {
        pos = INTB;
    }
    else if (IntNum == (InterruptPriorityNum * 4)+2)
    {
        pos = INTC;
    }
    else if (IntNum == (InterruptPriorityNum * 4)+3)
    {
        pos = INTD;
    }
    else
    {
        /* Do Nothing... */
    }
    
    switch (PriorityLevel)
    {
    case LEVEL_ZERO:
        WRITE_PORT_MASK(PRIx(IntNum),(LEVEL_ZERO << pos));
        break;
    case LEVEL_ONE:
        WRITE_PORT_MASK(PRIx(IntNum), (LEVEL_ONE << pos));
        break;
    case LEVEL_TWO:
        WRITE_PORT_MASK(PRIx(IntNum),(LEVEL_TWO << pos));
        break;
    case LEVEL_THREE:
        WRITE_PORT_MASK(PRIx(IntNum),(LEVEL_THREE << pos));
        break;
    case LEVEL_FOUR:
        WRITE_PORT_MASK(PRIx(IntNum),(LEVEL_FOUR << pos));
        break;
    case LEVEL_FIVE:
        WRITE_PORT_MASK(PRIx(IntNum),(LEVEL_FIVE << pos));
        break;
    case LEVEL_SIX:
        WRITE_PORT_MASK(PRIx(IntNum),(LEVEL_SIX << pos));
        break;
    case LEVEL_SEVEN:
        WRITE_PORT_MASK(PRIx(IntNum),(LEVEL_SEVEN << pos));
        break;
    default:
        break;
    }

}
/*************************************************************************************************
 *  GLOBAL DATA
 ************************************************************************************************/
#include "IntCtrl_Lcfg.h"

/******************************************************************************************************
 *  APIs IMPLEMENTATION
 ******************************************************************************************************/
/*-----------------------------------------------------------------------------------
 Service Name     : IntCtrl_Init
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : None
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to initiate all configured interrupts.
 -----------------------------------------------------------------------------------*/
void IntCtrl_Init(const IntCtrl_ConfigType *ConfigPtr)
{
    uint8 IntPinIndex;
    for (IntPinIndex = 0; IntPinIndex < NUM_OF_CONFIGURED_INTERRUPTS; IntPinIndex++)
    {
        switch (ConfigPtr->IntConfig[IntPinIndex].MaskPermission)
        {
        case ENABLE:
        #if 0
            /* Configure Grouping/SubGrouping system in APINT register in SCB */
            SetPriorityGrouping(ConfigPtr->SubGroup);
        #endif
            /* Assign Group/Subgroup priorty in NIVC_PRIx and SCB_SYSPRIx registers */
            SetPriority(ConfigPtr->IntConfig[IntPinIndex].IntNum, ConfigPtr->IntConfig[IntPinIndex].Priortiy_Level);
            /* ENABLE interrupts based on user configuration in NVIC_ENx and SCB_sys registers */
            InterruptEnable(ConfigPtr->IntConfig[IntPinIndex].IntNum);
            break;
        case DISABLE:
            /* DISABLE interrupts based on user configuration in NVIC_ENx and SCB_sys registers */
            InterruptDisable(ConfigPtr->IntConfig[IntPinIndex].IntNum);
            break;
        default:
            break;
        }
    }
}

/***************************************************************************************
*   END OF FILE: IntCtrl.c
***************************************************************************************/
