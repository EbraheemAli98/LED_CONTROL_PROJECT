/**************************************************************************************************
 * File Description
 * -----------------------------------------------------------------------------------------------
 *      File: Dio.h
 *    Module: DIO_MODULE
 * 
 * Description: <Header file contains the Functions' declaration and configuration of Dio_module >
 * 
 **************************************************************************************************/


#ifndef DIO_H
#define DIO_H

/*************************************************************************************************
 * INCLUDES
 ************************************************************************************************/
#include "../../SERVICES/Std_Types.h"
#include "../Comman/PortPin_Macros.h"

/*************************************************************************************************
 * GLOBAL CONSTANT MACROS
 ************************************************************************************************/

#define DIO_NUM_OF_CONFIGURED_CHANNELS          (3)

#define DIO_LED_CHL_INDEX                       (0)
#define DIO_ON_TIME_BUTTON_CHL_INDEX            (1)
#define DIO_OFF_TIME_BUTTON_CHL_INDEX           (2)

#define DIO_LED_PORT_ID                         (PORTF_ID)  /* PORTF */
#define ON_TIME_BUTTON_PORT_ID                  (PORTF_ID) 
#define OFF_TIME_BUTTON_PORT_ID                 (PORTF_ID)

#define DIO_LED_CHL_ID                          (PIN2_ID)   /* Pin1 */
#define ON_TIME_BUTTON_CHL_ID                   (PIN0_ID)   /* Pin0 */
#define OFF_TIME_BUTTON_CHL_ID                  (PIN4_ID)   /* Pin4 */

/*************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 ************************************************************************************************/
typedef uint8 Dio_ChannelType;
typedef uint8 Dio_PortType;
typedef uint8 Dio_LevelType;
typedef uint8 Dio_PortLevelType;

typedef struct 
{
    Dio_PortType PortId;
    Dio_ChannelType ChannelId;
}Dio_ConfigChannelType;


typedef struct 
{
    Dio_ConfigChannelType Conf_Channel[DIO_NUM_OF_CONFIGURED_CHANNELS];
}Dio_ConfigType;


/*************************************************************************************************
 *  GLOBAL DATA
 ************************************************************************************************/
extern const Dio_ConfigType Dio_Config;

/*************************************************************************************************
 *  APIs DECLARATION
 ************************************************************************************************/
/*-----------------------------------------------------------------------------------
 Service Name     : DioReadChannel
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : ChannelId -> Id of the Dio channel(pin).
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : Channel_Level -> Level of the Dio pin. (HIGH/LOW).
 Description      : Function to read the channel level and return it.
 -----------------------------------------------------------------------------------*/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelIndex);

/*-----------------------------------------------------------------------------------
 Service Name     : DioWriteChannel
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : ChannelId -> Id of the Dio channel(pin).
                    Level     -> Dio pin level.
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to set the channel level.
 -----------------------------------------------------------------------------------*/
void Dio_WriteChannel(Dio_ChannelType ChannelIndex, Dio_LevelType Level);

/*-----------------------------------------------------------------------------------
 Service Name     : Dio_ReadPort
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : PortId -> Id of the Dio port.
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : Port_Level -> Level of the Dio Port. (HIGH/LOW).
 Description      : Function to read the Port level and return it.
 -----------------------------------------------------------------------------------*/
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);

/*-----------------------------------------------------------------------------------
 Service Name     : Dio_WritePort
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : PortId -> Id of the Dio Port.
                    Level  -> Level of the Port.
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to set the Port level.
 -----------------------------------------------------------------------------------*/
void Dio_WritePort(Dio_PortType PortId,Dio_PortLevelType Level);

/*-----------------------------------------------------------------------------------
 Service Name     : Dio_FlipChannel
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : ChannelId -> Id of the Dio channel(pin).
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : Channel_Level -> Level of the Dio pin. (HIGH/LOW).
 Description      : Function to flip the channel level and return it after flipping.
 -----------------------------------------------------------------------------------*/
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelIndex);

#endif /* DIO_H */

/***************************************************************************************
*   END OF FILE: Dio.h
***************************************************************************************/