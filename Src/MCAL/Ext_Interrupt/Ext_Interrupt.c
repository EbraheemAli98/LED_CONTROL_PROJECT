/********************************************************************************************
 * File Description
 * ------------------------------------------------------------------------------------------*/
/**      @file Ext_Interrupt.c
 *       @brief
 * 
 *     @details
 * 
 *********************************************************************************************/

/***************************************************************************************
 * INCLUDES
****************************************************************************************/
#include "Ext_Interrupt.h"
#include "../Comman/MemMap.h"
#include "../../SERVICES/Comman_Macro.h"

/*************************************************************************************************
 *  GLOBAL DATA
 ************************************************************************************************/
const ExtInt_ConfigType ExtInterruptConfig = 
{
    {{TIME_ON_INTERRUPT_PIN_ID,TIME_ON_INTERRUPT_PORT_ID,EDGE,FALLING,ENABLE},
    {TIME_OFF_INTERRUPT_PIN_ID,TIME_OFF_INTERRUPT_PORT_ID,EDGE,FALLING,ENABLE}}
};


/*************************************************************************************************
 * LOCAL DATA
 ************************************************************************************************/
static volatile uint32 (*g_GPIOF_CallBck_Ptr)(void) = NULL_PTR; 
static const ExtInt_ConfigType *InterruptConfigPtr = NULL_PTR;


/******************************************************************************************************
 *  APIs IMPLEMENTATION
 ******************************************************************************************************/
/*-----------------------------------------------------------------------------------
 Service Name     : ExtInt_Init
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : ConfigPtr -> Pointer to structure hold all the External interrupt
                    configurations.
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to set the External interrupt configurations.
 -----------------------------------------------------------------------------------*/
 void ExtInt_Init(const ExtInt_ConfigType *ConfigPtr)
 {
    ExtInt_PinType PinIndex;
    if (ConfigPtr != NULL_PTR)
    {
        for (PinIndex = 0; PinIndex < EXT_CONFIGURED_INTERRUPTS; PinIndex++)
        {
            InterruptConfigPtr = ConfigPtr;
            /* Enable/Disable External Interrupt */
            switch (ConfigPtr->Config[PinIndex].permission)
            {
            case ENABLE:
            /* Select the Sense Trigger value */
                switch (InterruptConfigPtr->Config[PinIndex].SenseTriggerValue)
                {
                case LEVEL:
                    SET_BIT(GPIOIS(InterruptConfigPtr->Config[PinIndex].portId), InterruptConfigPtr->Config[PinIndex].pinId);
                    break;
                case EDGE:
                    CLEAR_BIT(GPIOIS(InterruptConfigPtr->Config[PinIndex].portId), InterruptConfigPtr->Config[PinIndex].pinId);
                    break;
                default:
                    break;
                }
            /* Select the Edge Type */
                switch (InterruptConfigPtr->Config[PinIndex].EdgeValue)
                {
                case RISING:
                    CLEAR_BIT(GPIOIBE(InterruptConfigPtr->Config[PinIndex].portId), InterruptConfigPtr->Config[PinIndex].pinId);
                    SET_BIT(GPIOIEV(InterruptConfigPtr->Config[PinIndex].portId), InterruptConfigPtr->Config[PinIndex].pinId);
                    break;
                case FALLING:
                    CLEAR_BIT(GPIOIBE(InterruptConfigPtr->Config[PinIndex].portId), InterruptConfigPtr->Config[PinIndex].pinId);
                    CLEAR_BIT(GPIOIEV(InterruptConfigPtr->Config[PinIndex].portId), InterruptConfigPtr->Config[PinIndex].pinId);
                    break;
                case BOTH_EDGES:
                    SET_BIT(GPIOIBE(InterruptConfigPtr->Config[PinIndex].portId), InterruptConfigPtr->Config[PinIndex].pinId);
                    break;
                default:
                    break;
                }
            /* Clear the prior interrupt */
                SET_BIT(GPIOICR(InterruptConfigPtr->Config[PinIndex].portId), InterruptConfigPtr->Config[PinIndex].pinId);
            /* Enable the interrupt */
                SET_BIT(GPIOIM(InterruptConfigPtr->Config[PinIndex].portId), InterruptConfigPtr->Config[PinIndex].pinId);
                break;

            /* Disable the interrupt */
            case DISABLE:
                SET_BIT(GPIOICR(InterruptConfigPtr->Config[PinIndex].portId), InterruptConfigPtr->Config[PinIndex].pinId);
                CLEAR_BIT(GPIOIM(InterruptConfigPtr->Config[PinIndex].portId), InterruptConfigPtr->Config[PinIndex].pinId);
                break;
            default:
                break;
            }
        }
    }
    else
    {
        /* Do Nothing..  */
    }
 }

/*-----------------------------------------------------------------------------------
 Service Name     : ExtInt_Disable
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : ExtIntIndex  : Interrupt Pin index in the configuration sturcture.
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to clear Interrupt flag.
 -----------------------------------------------------------------------------------*/
void ExtInt_Disable(ExtInt_PinType ExtIntIndex)
{
    SET_BIT(GPIOICR(InterruptConfigPtr->Config[ExtIntIndex].portId),InterruptConfigPtr->Config[ExtIntIndex].pinId);
    CLEAR_BIT(GPIOIM(InterruptConfigPtr->Config[ExtIntIndex].portId),InterruptConfigPtr->Config[ExtIntIndex].pinId);
}

 /*-----------------------------------------------------------------------------------
 Service Name     : ExtInt_InterruptClear
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : PinIndex  : Interrupt Pin index in the configuration sturcture.
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to clear Interrupt flag.
 -----------------------------------------------------------------------------------*/
void ExtInt_InterruptClear(ExtInt_PinType PinIndex)
{
    SET_BIT(GPIOICR(InterruptConfigPtr->Config[PinIndex].portId),InterruptConfigPtr->Config[PinIndex].pinId);
}

/*-----------------------------------------------------------------------------------
 Service Name     : ExtInt_InterruptStatus
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : PinIndex  : Interrupt Pin index in the configuration sturcture.
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to clear Interrupt flag.
 -----------------------------------------------------------------------------------*/
ExtInt_StateType ExtInt_InterruptStatus(ExtInt_PinType PinIndex)
{
    ExtInt_StateType Status = STD_LOW;
    if (BIT_IS_SET(GPIOMIS(InterruptConfigPtr->Config[PinIndex].portId),InterruptConfigPtr->Config[PinIndex].pinId))
    {
        Status = STD_HIGH;
    }
    else
    {
        Status = STD_LOW;
    }
    return Status;
}

/*-----------------------------------------------------------------------------------
 Service Name     : ExtInt_Read
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : None
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to return the  pins.
 -----------------------------------------------------------------------------------*/
 void ExtInt_SetCallBack(void (*a_FunPtr)(void))
 {
    /* Save the address of the Call back function in a global variable */
    g_GPIOF_CallBck_Ptr = a_FunPtr;
 }

/*-----------------------------------------------------------------------------------
 Service Name     : ExtInt_Read
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : None
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to return the  pins.
 -----------------------------------------------------------------------------------*/
 void GPIOF_Handler(void)
 {
    if (g_GPIOF_CallBck_Ptr != NULL_PTR)
    {
        (*g_GPIOF_CallBck_Ptr)();
    }
 }