/**************************************************************************************************
 * File Description
 * -----------------------------------------------------------------------------------------------
 *      File: EXT_Interrupt_Cfg.h
 *    Module: EXT_Interrupt_MODULE
 * 
 * Description: <Header file contains all the pre-compile time configureations >
 * 
 **************************************************************************************************/


#ifndef EXT_INTERRUPT_CFG_H
#define EXT_INTERRUPT_CFG_H

/*************************************************************************************************
 * INCLUDES
 ************************************************************************************************/
#include "../../SERVICES/Std_Types.h"
#include "../Comman/PortPin_Macros.h"

/*************************************************************************************************
 * GLOBAL CONSTANT MACROS
 ************************************************************************************************/
#define EXT_CONFIGURED_INTERRUPTS   2u
#define TIME_ON_INTERRUPT_PIN_ID    PIN0_ID
#define TIME_OFF_INTERRUPT_PIN_ID   PIN4_ID
#define TIME_ON_INTERRUPT_PORT_ID   PORTF_ID
#define TIME_OFF_INTERRUPT_PORT_ID  PORTF_ID

#ifndef ENABLE
#define ENABLE  1u
#endif

#ifndef DISABLE
#define DISABLE 0u
#endif


#endif  /* EXT_INTERRUPT_CFG_H */

/*******************************************************************
 * End of FILE: Ext_Interrupt_Cfg.h 
 *******************************************************************/