/**************************************************************************************************
 * File Description
 * -----------------------------------------------------------------------------------------------
 *      File: IntCtrl.h
 *    Module: IntCtrl_MODULE
 * 
 * Description: <write file decription here>
 * 
 **************************************************************************************************/


#ifndef EXT_INTERRUPT_H
#define EXT_INTERRUPT_H

/*************************************************************************************************
 * INCLUDES
 ************************************************************************************************/
#include "../../SERVICES/Std_Types.h"
#include "../Comman/PortPin_Macros.h"
#include "Ext_Interrupt_Cfg.h"

/*************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 ************************************************************************************************/
typedef uint8 ExtInt_PinType;
typedef uint8 ExtInt_PortType;
typedef uint8 ExtInt_StateType;
typedef uint8 ExtInt_MaskPermissionType;

typedef enum
{
    LEVEL,EDGE
}ExtInt_SenseTriggerType;

typedef enum
{
    RISING,FALLING,BOTH_EDGES
}ExtInt_EdgeType;

typedef struct Ext_Interrupt
{
    ExtInt_PinType pinId;
    ExtInt_PinType portId;
    ExtInt_SenseTriggerType SenseTriggerValue;
    ExtInt_EdgeType EdgeValue;
    ExtInt_MaskPermissionType permission;
}ExtInt_Info;

typedef struct 
{
    ExtInt_Info Config[EXT_CONFIGURED_INTERRUPTS];
}ExtInt_ConfigType;

/*************************************************************************************************
 *  GLOBAL DATA 
 ************************************************************************************************/
#include "Ext_Interrupt_Lcfg.h"

/******************************************************************************************************
 *  APIs DECLARATIONS
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
 void ExtInt_Init(const ExtInt_ConfigType *ConfigPtr);
 
/*-----------------------------------------------------------------------------------
 Service Name     : ExtInt_SetCallBack
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : None
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to pass the callback function to the handler function.
 -----------------------------------------------------------------------------------*/
 void ExtInt_SetCallBack(void (*a_FunPtr)(void));

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
void ExtInt_InterruptClear(ExtInt_PinType PinIndex); 

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
ExtInt_StateType ExtInt_InterruptStatus(ExtInt_PinType PinIndex);

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
void ExtInt_Disable(ExtInt_PinType ExtIntIndex);

#endif /* EXT_INTERRUPT_H */

/***************************************************************************************
*   END OF FILE: IntCtrl.c
***************************************************************************************/