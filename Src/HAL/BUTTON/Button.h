/**************************************************************************************************
 * File Description
 * -----------------------------------------------------------------------------------------------
 *      File: Button.h
 *    Module: BUTTON_MODULE
 * 
 * Description: <write file decription here>
 * 
 **************************************************************************************************/
#ifndef BUTTON_H
#define BUTTON_H

/*************************************************************************************************
 * INCLUDES
 ************************************************************************************************/
#include "../../MCAL/Ext_Interrupt/Ext_Interrupt.h"


/*************************************************************************************************
 * GLOBAL CONSTANT MACROS
 ************************************************************************************************/
#define ON_BUTTON_INDEX     0
#define ON_BUTTON_CHANNEL   TIME_ON_INTERRUPT_PIN_ID
#define ON_BUTTOM_PORT      TIME_ON_INTERRUPT_PORT_ID

#define OFF_BUTTON_INDEX    1
#define OFF_BUTTON_CHANNEL  TIME_OFF_INTERRUPT_PIN_ID
#define OFF_BUTTON_PORT     TIME_OFF_INTERRUPT_PORT_ID


/******************************************************************************************************
 *  APIs DECLARATIONS
 ******************************************************************************************************/
/*-----------------------------------------------------------------------------------------
 Service Name     : Button_Init
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : None
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to init button module.
 -------------------------------------------------------------------------------------------*/
 void Button_Init(void);
 
/*-----------------------------------------------------------------------------------------
 Service Name     : Button_IntAction
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : None
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to Check which Button is pressed and implement its statement.
 -------------------------------------------------------------------------------------------*/
void Button_IntAction(void);

#endif /* BUTTON_H */