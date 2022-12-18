/*********************************************************************************************
 * File Description
 * ------------------------------------------------------------------------------------------*/
/**      @file  Port.c
 *       @brief 
 * 
 *     @details
 *     @author  Ebraheem Ali
 *********************************************************************************************/

/***************************************************************************************
 * INCLUDES
****************************************************************************************/
#include "../Comman/MemMap.h"
#include "Port.h"

/*************************************************************************************************
 * LOCAL MACROS 
 ************************************************************************************************/
#define PORT_LOCK_VALUE         (uint32)0x4C4F434B


/*************************************************************************************************
 * LOCAL DATA
 ************************************************************************************************/
static uint8 port_pin[PORT_CONFIGURED_PORT_PINS] = {LED_PORT_ID,ON_TIME_BUTTON_PORT_ID,OFF_TIME_BUTTON_PORT_ID};
static const Port_ConfigType* Port_PinIndex = NULL_PTR;

/*************************************************************************************************
 *  GLOBAL DATA
 ************************************************************************************************/
const Port_ConfigType Port_PinConfig =
    {
        {{LED_CHL_ID,PORT_PIN_DIO_MODE,PORT_PIN_LEVEL_LOW,PORT_PIN_OUTPUT,PORT_PIN_CURRENT_8MA,RES_OFF},
         {ON_TIME_BUTTON_CHL_ID,PORT_PIN_DIO_MODE,PORT_PIN_LEVEL_HIGH,PORT_PIN_INPUT,PORT_PIN_CURRENT_8MA,PULL_UP},
         {OFF_TIME_BUTTON_CHL_ID,PORT_PIN_DIO_MODE,PORT_PIN_LEVEL_HIGH,PORT_PIN_INPUT,PORT_PIN_CURRENT_8MA,PULL_UP}
        }
    };

/*************************************************************************************************
 * LOCAL FUNCTION PROTOTYPE
 ************************************************************************************************/
static void Port_SetInternalAttach(Port_PinType PinIndex,Port_PinInternalAttachType InternalAttachType);
static void Port_SetOutputCurrent(Port_PinType PinIndex,Port_PinOutputCurrentType OutputCurrentType);
static void Port_SetDirection(Port_PinType PinIndex,Port_PinDirectionType Direction);
static void Port_SetMode(Port_PinType PinIndex,Port_PinModeType Mode);

/*************************************************************************************************
 * LOCAL FUNCTIONS
 ************************************************************************************************/
static void Port_SetDirection(Port_PinType PinIndex,Port_PinDirectionType Direction)
 {
     if (Port_PinIndex->PinStruct[PinIndex].PortPinId >= PIN0_ID && Port_PinIndex->PinStruct[PinIndex].PortPinId <= PIN7_ID)
     {
         if (PORT_PIN_OUTPUT == Direction)
         {
            /* Set the corresponding bit in GPIOPDIR Register to configure it as OUTPUT pin */
            SET_BIT(GPIODIR(port_pin[PinIndex]),Port_PinIndex->PinStruct[PinIndex].PortPinId);

            /* Set the initial value of the pin level */
            switch (Port_PinIndex->PinStruct[PinIndex].PortPinLevelValue)
            {
            case PORT_PIN_LEVEL_HIGH:
                SET_BIT(GPIODATA(port_pin[PinIndex]),Port_PinIndex->PinStruct[PinIndex].PortPinId);
                break;
            case PORT_PIN_LEVEL_LOW:
                CLEAR_BIT(GPIODATA(port_pin[PinIndex]),Port_PinIndex->PinStruct[PinIndex].PortPinId);
                break;
            default:
                break;
            }
            
         }
         else if (PORT_PIN_INPUT == Direction)
         {
            /* Clear the corresponding bit in GPIOPDIR Register to configure it as INTPUT pin */
            CLEAR_BIT(GPIODIR(port_pin[PinIndex]),Port_PinIndex->PinStruct[PinIndex].PortPinId);

            /* Set the internal attach resistor of the pin */
            switch (Port_PinIndex->PinStruct[PinIndex].PortPinInternalAttach)
            {
            case RES_OFF:
                CLEAR_BIT(GPIOPUR(port_pin[PinIndex]),Port_PinIndex->PinStruct[PinIndex].PortPinId);
            case PULL_UP:
                SET_BIT(GPIOPUR(port_pin[PinIndex]),Port_PinIndex->PinStruct[PinIndex].PortPinId);
                break;
            case PULL_DOWN:
                SET_BIT(GPIOPDR(port_pin[PinIndex]),Port_PinIndex->PinStruct[PinIndex].PortPinId);
                break;
            case OPEN_DRAIN:
                SET_BIT(GPIOODR(port_pin[PinIndex]),Port_PinIndex->PinStruct[PinIndex].PortPinId);
            default:
                break;
            }    
         }
         else
         {
            /* Do Nothing... */
         } 
     }
    else
    {
        /* Do Nothing... */
    }  
 }

static void Port_SetMode(Port_PinType PinIndex,Port_PinModeType Mode)
 {
    
    if (Port_PinIndex->PinStruct[PinIndex].PortPinId >= PIN0_ID && Port_PinIndex->PinStruct[PinIndex].PortPinId <= PIN7_ID)
    {
        if (PORT_PIN_DIO_MODE == Mode)
        {
            /* Select the GPIO mode of the pin by clearing the corresponding bit in the AMSEL register */
            CLEAR_BIT(GPIOAMSEL(port_pin[PinIndex]),Port_PinIndex->PinStruct[PinIndex].PortPinId);
            /* Select the GPIO function of the pin by clearing the corresponding bit in the AFSEL register */
            CLEAR_BIT(GPIOAFSEL(port_pin[PinIndex]),Port_PinIndex->PinStruct[PinIndex].PortPinId);
            /* Clear the PMCx Bit Field for the corresponding bit in GPIOPCTL Register to set GPIO Functionality */
            GPIOPCTL(port_pin[PinIndex]) &= ~(0x0000000F<<(4*Port_PinIndex->PinStruct[PinIndex].PortPinId));
            /* Set the corresponding bit in GPIOPDEN Register to configure it as Digital pin */
            SET_BIT(GPIODEN(port_pin[PinIndex]),Port_PinIndex->PinStruct[PinIndex].PortPinId);
        }
        else if (PORT_PIN_ADC_MODE == Mode)
        {
            /* Select the analog mode of the pin by setting the corresponding bit in the AMSEL register */
            SET_BIT(GPIOAMSEL(port_pin[PinIndex]),Port_PinIndex->PinStruct[PinIndex].PortPinId);
            /* Select the GPIO function of the pin by clearing the corresponding bit in the AFSEL register */
            CLEAR_BIT(GPIOAFSEL(port_pin[PinIndex]),Port_PinIndex->PinStruct[PinIndex].PortPinId);
            /* Clear the PMCx Bit Field for the corresponding bit in GPIOPCTL Register to set GPIO Functionality */
            GPIOPCTL(port_pin[PinIndex]) &= ~(0x0000000F<<(4*Port_PinIndex->PinStruct[PinIndex].PortPinId));
            /* Clear the corresponding bit in GPIOPDEN Register to configure it as Analog pin */
            CLEAR_BIT(GPIODEN(port_pin[PinIndex]),Port_PinIndex->PinStruct[PinIndex].PortPinId);
        }
        else
        {
            /* Select the  mode of the pin by setting the corresponding bit in the AMSEL register */
            SET_BIT(GPIOAMSEL(port_pin[PinIndex]),Port_PinIndex->PinStruct[PinIndex].PortPinId);
            /* Select the alternate function of the pin by setting the corresponding bit in the AFSEL register */
            SET_BIT(GPIOAFSEL(port_pin[PinIndex]),Port_PinIndex->PinStruct[PinIndex].PortPinId);
            /* Set the PMCx Bit Field for the corresponding bit in GPIOPCTL Register to set alternate Function */
            GPIOPCTL(port_pin[PinIndex]) |= ((Port_PinIndex->PinStruct[PinIndex].PortPinId & 0x0000000F) << (4*Port_PinIndex->PinStruct[PinIndex].PortPinId));
            /* Set the corresponding bit in GPIOPDEN Register to configure it as Digital pin */
            SET_BIT(GPIODEN(port_pin[PinIndex]),Port_PinIndex->PinStruct[PinIndex].PortPinId);
        } 
    }
    else
    {
        /* Do Nothing... */
    }
 }
/*************************************************************************************************
 * APIs IMPLEMENTATION
 ************************************************************************************************/
/*-----------------------------------------------------------------------------------
 Service Name     : Port_Init
 Sync/Async       : Synchronous
 Reentrnacy       : Reentrant
 Parameter(in)    : ConfigPtr -> Pointer to the configuration sturcture.
 Parameter(in/out): None
 Parameter(out)   : None
 Return Value     : None
 Description      : Function to initialize the configured pins.
 -----------------------------------------------------------------------------------*/
 void Port_Init(const Port_ConfigType* ConfigPtr)
 {
    uint8 PinIndex;
    uint8 port_pin_value = 10; /* Any value greater than 5 (PORTF_ID = 5, port_pin_value > PORTF_ID) */
    if(ConfigPtr == NULL_PTR)
    {
        /*Do nothing */
    }
    else
    {
        for (PinIndex = 0; PinIndex < PORT_CONFIGURED_PORT_PINS; PinIndex++)
        {
            if (port_pin[PinIndex] == port_pin_value)
            {
                /* Do nothing : This Port is Enabled before */
            }
            else
            {
                SET_BIT(SYSCTL_RCGCGPIO,port_pin[PinIndex]);
                port_pin_value = port_pin[PinIndex];
            }
            /* unlock the bit in Commit Register to the NMI PINs (PF0/PD7) if it is configured to use */
            if(((ConfigPtr->PinStruct[PinIndex].PortPinId == PIN0_ID) && (port_pin[PinIndex] == PORTF_ID))||((ConfigPtr->PinStruct[PinIndex].PortPinId==PIN7_ID)&&(port_pin[PinIndex]==PORTD_ID)))
            {
                GPIOLOCK(port_pin[PinIndex]) = PORT_LOCK_VALUE;
                SET_BIT(GPIOCR(port_pin[PinIndex]),ConfigPtr->PinStruct[PinIndex].PortPinId);
            }
            else if ((ConfigPtr->PinStruct[PinIndex].PortPinId <= PIN3_ID) && (port_pin[PinIndex] == PORTC_ID))
            {
                /* CAUTION: this is the JTAG pins */
                continue; /* increment and complete, don't go to the last else */
            }
            else
            {
                /* Do Nothing... */
            }
            Port_SetMode(PinIndex,ConfigPtr->PinStruct[PinIndex].PortPinMode);
            Port_SetDirection(PinIndex,ConfigPtr->PinStruct[PinIndex].PortPinDirection);
        }
    }
    
 }

/***************************************************************************************
*   END OF FILE: Port.c
***************************************************************************************/