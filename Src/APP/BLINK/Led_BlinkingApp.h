
#define ONE_MSEC 0   

/******************************************************************************************************
 *  APIs Implementation
 ******************************************************************************************************/
/*-----------------------------------------------------------------------------------
 Service Name     : LedBlinkingApp_Init
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : None
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to initiate all configured pins.
 -----------------------------------------------------------------------------------*/
void LedBlinkingApp_Init(void);

/*-----------------------------------------------------------------------------------
 Service Name     : LedBlinkingApp_Start
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : None
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to initiate all configured pins.
 -----------------------------------------------------------------------------------*/
void LedBlinkingApp_Start(uint32 TimeON,uint32 TimeOFF);