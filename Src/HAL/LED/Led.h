/**************************************************************************************************
 * File Description
 * -----------------------------------------------------------------------------------------------
 *      File: Led.h
 *    Module: LED_MODULE
 * 
 * Description: <write file decription here>
 * 
 **************************************************************************************************/


#ifndef LED_H
#define LED_H

/*************************************************************************************************
 * INCLUDES
 ************************************************************************************************/
#include "../../MCAL/GPIO/Dio.h"

/*************************************************************************************************
 * GLOBAL CONSTANT MACROS
 ************************************************************************************************/
#define LED_ON      STD_HIGH
#define LED_OFF     STD_LOW

#define LED_PORT_ID         DIO_LED_PORT_ID
#define LED_CHANNEL_ID      DIO_LED_CHL_ID


/*************************************************************************************************
 *  APIs DECLARATION
 ************************************************************************************************/
/*-----------------------------------------------------------------------------------
 Service Name     : LED_Init
 Sync/Async       : Synchronous
 Reentrnacy       : Non-Reentrant
 Parameter(in)    : None
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to initialize Led.
 -----------------------------------------------------------------------------------*/
 void LED_Init(void);

 /*-----------------------------------------------------------------------------------
 Service Name     : LED_WriteHigh
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : None
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to Turn on Led.
 -----------------------------------------------------------------------------------*/
 void LED_WriteHigh(void);

 /*-----------------------------------------------------------------------------------
 Service Name     : LED_WriteLow
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : None
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to turn off Led.
 -----------------------------------------------------------------------------------*/
 void LED_WriteLow(void);

 
#endif /* LED_H */
/***************************************************************************************
*   END OF FILE: Led.h
***************************************************************************************/