/*********************************************************************************************
 * File Description
 * ------------------------------------------------------------------------------------------*/
/**      @file  Dio.c
 *       @brief 
 * 
 *     @details
 *     @author  Ebraheem Ali
 *********************************************************************************************/

/***************************************************************************************
 * INCLUDES
****************************************************************************************/
#include "../../SERVICES/Comman_Macro.h"
#include "../Comman/MemMap.h"
#include "Dio.h"

/*************************************************************************************************
 * LOCAL DATA
 ************************************************************************************************/


/*************************************************************************************************
 *  GLOBAL DATA
 ************************************************************************************************/
const Dio_ConfigType Dio_Config =
    {
        {{LED_PORT_ID, LED_CHL_ID},
         {ON_TIME_BUTTON_PORT_ID, ON_TIME_BUTTON_CHL_ID},
         {OFF_TIME_BUTTON_PORT_ID, OFF_TIME_BUTTON_CHL_ID}
        }
    };

/*************************************************************************************************
 * LOCAL FUNCTION PROTOTYPE
 ************************************************************************************************/


/*************************************************************************************************
 * LOCAL FUNCTIONS
 ************************************************************************************************/


/*************************************************************************************************
 * APIs IMPLEMENTATION
 ************************************************************************************************/
/*-----------------------------------------------------------------------------------
 Service Name     : DioReadChannel
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : ChannelIndex -> Id of the Dio channel(pin).
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : Channel_Level -> Level of the Dio pin. (HIGH/LOW).
 Description      : Function to read the channel level and return it.
 -----------------------------------------------------------------------------------*/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelIndex)
{
    Dio_LevelType CHL_Level = STD_LOW;
    if(ChannelIndex < DIO_NUM_OF_CONFIGURED_CHANNELS)
    {
        if (BIT_IS_SET(GPIODATA(Dio_Config.Conf_Channel[ChannelIndex].PortId),Dio_Config.Conf_Channel[ChannelIndex].ChannelId))
        {
            CHL_Level = STD_HIGH;
        }
        else
        {
            CHL_Level = STD_LOW;
        }
        
    }
    else
    {
        /* Do nothing */
    }
    return CHL_Level;
}

/*-----------------------------------------------------------------------------------
 Service Name     : DioWriteChannel
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : ChannelIndex -> Id of the Dio channel(pin).
                    Level     -> Dio pin level.
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to set the channel level.
 -----------------------------------------------------------------------------------*/
void Dio_WriteChannel(Dio_ChannelType ChannelIndex, Dio_LevelType Level)
{
    if (DIO_NUM_OF_CONFIGURED_CHANNELS > ChannelIndex)
    {
        switch (Level)
        {
        case STD_HIGH:
            SET_BIT(GPIODATA(Dio_Config.Conf_Channel[ChannelIndex].PortId), Dio_Config.Conf_Channel[ChannelIndex].ChannelId);
            break;
        case STD_LOW:
            CLEAR_BIT(GPIODATA(Dio_Config.Conf_Channel[ChannelIndex].PortId), Dio_Config.Conf_Channel[ChannelIndex].ChannelId);
            break;
        default:
            break;
        }
    }
    else
    {
        /* Do nothing */
    }
}

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
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
    Dio_PortLevelType PortValue = 0;
    if(PortId >=0 && PortId <=5)
    {
        PortValue = GPIODATA(PortId) & 0xFF;
    }
    else
    {
        /* Do nothing */
    }
    return PortValue;
}

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
void Dio_WritePort(Dio_PortType PortId,Dio_PortLevelType Level)
{
    if(PortId >=0 && PortId <= 5)
    {
        switch (Level)
        {
        case STD_HIGH:
            GPIODATA(PortId) = 0xFF;
            break;
        case STD_LOW:
            GPIODATA(PortId) = 0x00;
            break;
        default:
            break;
        }
    }
    else
    {
        /* Do nothing */
    }    
}

/*-----------------------------------------------------------------------------------
 Service Name     : Dio_FlipChannel
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : ChannelIndex -> Id of the Dio channel(pin).
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : Channel_Level -> Level of the Dio pin. (HIGH/LOW).
 Description      : Function to flip the channel level and return it after flipping.
 -----------------------------------------------------------------------------------*/
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelIndex)
{
    Dio_LevelType CHL_Level = STD_LOW;
    if(ChannelIndex < DIO_NUM_OF_CONFIGURED_CHANNELS)
    {
        if (BIT_IS_SET(GPIODATA(Dio_Config.Conf_Channel[ChannelIndex].PortId),Dio_Config.Conf_Channel[ChannelIndex].ChannelId))
        {
            CHL_Level = STD_LOW;
        }
        else /* Channel level is LOW */
        {
            CHL_Level = STD_HIGH;
        }
        
    }
    else
    {
        /* Do nothing */
    }
    return CHL_Level;
}


/***************************************************************************************
*   END OF FILE: Dio.c
***************************************************************************************/