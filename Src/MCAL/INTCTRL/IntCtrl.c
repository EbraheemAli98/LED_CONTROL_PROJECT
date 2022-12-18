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
 * LOCAL DATA
 ************************************************************************************************/
#define PRIx(i)     (*((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS+(0x00000400+((i/4)*4)))))
#define ENx(i)      (*((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS+(0x00000100+((i/32)*32)))))
#define DISx(i)     (*((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS+(0x00000180+((i/32)*32)))))

/*************************************************************************************************
 *  GLOBAL DATA
 ************************************************************************************************/
//extern const User_data_type g_user_data;

/*************************************************************************************************
 * LOCAL FUNCTION PROTOTYPE
 ************************************************************************************************/
static void SetPriorityGrouping(Group_SubGroupType PriorityGrouping);
static void SetPriority(IntCtrl_InterruptType IntNum,IntCtrl_PriorityNum PriorityLevel);
static void InterruptEnable(IntCtrl_InterruptType IntNum);
static void InterruptDisable(IntCtrl_InterruptType IntNum);

/*************************************************************************************************
 * LOCAL FUNCTIONS
 ************************************************************************************************/
static void SetPriorityGrouping(Group_SubGroupType PriorityGrouping)
{
    if(PriorityGrouping == EGIHT_GROUP_NONE_SUBGROUP)
         APINT = APINT_KEY|(EGIHT_GROUP_NONE_SUBGROUP);
}

static void SetPriority(IntCtrl_InterruptType IntNum,IntCtrl_PriorityNum PriorityLevel)
{
    GPIOx_RegAccess GPIO;

}


/***************************************************************************************************   
 * \Syntax        : void IntCtrl_Init(void)
 * \Description   : initialize Nvic/SCB Modules by parsing the Configuration into Nvic/SCB registers 
 * 
 * \Sync\Async    : Synchronous
 * \Reentrancy    : Non-reentrant
 * \Parameter(in) : None
 * \Parameter(out): None
 * \Return Value  : None
 **************************************************************************************************/
void IntCtrl_Init(void)
{
    /*TODO : Configure Grouping/SubGrouping system in APINT register in SCB */
    
    /*TODO : Assign Group/Subgroup priorty in NIVC_PRIx and SCB_SYSPRIx registers */

    /*TODO : ENABLE/DISABLE interrupts based on user configuration in NVIC_ENx and SCB_sys registers */
}

/***************************************************************************************
*   END OF FILE: IntCtrl.c
***************************************************************************************/