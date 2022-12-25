/**************************************************************************************************
 * File Description
 * -----------------------------------------------------------------------------------------------
 *      File: Led_BlinkingApp.h
 *    Module: Led_BlinkingApp_MODULE
 * 
 * Description: <Header file contains the function declaration of the app >
 * 
 **************************************************************************************************/

#include "../../SERVICES/Std_Types.h"
/******************************************************************************************************
 *  APIs Implementation
 ******************************************************************************************************/
/*-----------------------------------------------------------------------------------
 Service Name     : App_Init
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : None
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to initiate all configured pins.
 -----------------------------------------------------------------------------------*/
void App_Init(void);

/*-----------------------------------------------------------------------------------
 Service Name     : App_Start
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : None
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to set the timer ON/oFF values all configured pins.
 -----------------------------------------------------------------------------------*/
void App_Start(uint8 TimeON,uint8 TimeOFF);

/*-----------------------------------------------------------------------------------
 Service Name     : App_Notification
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : None
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to initiate all configured pins.
 -----------------------------------------------------------------------------------*/
void App_Notification(void);
