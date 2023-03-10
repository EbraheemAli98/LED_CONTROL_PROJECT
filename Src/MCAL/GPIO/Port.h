/**************************************************************************************************
 * File Description
 * -----------------------------------------------------------------------------------------------
 *      File: Port.h
 *    Module: PORT_MODULE
 * 
 * Description: <Header file for Port_pins configurations and functions' declarations>
 * 
 **************************************************************************************************/

#ifndef PORT_H
#define PORT_H

/*************************************************************************************************
 * INCLUDES
 ************************************************************************************************/
#include "../../SERVICES/Std_Types.h"
#include "../Comman/PortPin_Macros.h"
#include "Port_Cfg.h" 

/*************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 ************************************************************************************************/
typedef uint8 Port_PinType;
typedef uint8 Port_PinLevelType;


typedef enum
{
    PORT_PIN_DIO_MODE,
    PORT_PIN_PWM_MODE,
    PORT_PIN_GPT_MODE,
    PORT_PIN_ADC_MODE
}Port_PinModeType;

typedef enum
{
    PORT_PIN_CURRENT_2MA,
    PORT_PIN_CURRENT_4MA,
    PORT_PIN_CURRENT_8MA
}Port_PinOutputCurrentType;

typedef enum 
{
    RES_OFF,PULL_UP,PULL_DOWN,OPEN_DRAIN
}Port_PinInternalAttachType;

typedef enum
{
    PORT_PIN_INPUT,PORT_PIN_OUTPUT
}Port_PinDirectionType;

typedef struct
{
    Port_PinType PortPinId;
    Port_PinModeType PortPinMode;
    Port_PinLevelType PortPinLevelValue;
    Port_PinDirectionType PortPinDirection;
    Port_PinOutputCurrentType PortPinOutputCurrent; 
    Port_PinInternalAttachType PortPinInternalAttach;  
}Port_PinConfigType;


typedef struct
{
    Port_PinConfigType PinStruct[PORT_CONFIGURED_PORT_PINS];
}Port_ConfigType;


/*************************************************************************************************
 *  GLOBAL DATA
 ************************************************************************************************/
#include "Port_Lcfg.h"


/*************************************************************************************************
 *  APIs DECLARATION
 ************************************************************************************************/
/*-----------------------------------------------------------------------------------
 Service Name     : Port_Init
 Sync/Async       : Synchronous
 Reentrnacy       : Non-Reentrant
 Parameter(in)    : ConfigPtr -> pointer to the configuration structure.
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to initiate all configured pins.
 -----------------------------------------------------------------------------------*/
void Port_Init(const Port_ConfigType* ConfigPtr);

#endif /* PORT_H */

/***************************************************************************************
*   END OF FILE: Port.h
***************************************************************************************/