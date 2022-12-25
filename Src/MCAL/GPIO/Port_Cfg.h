/**************************************************************************************************
 * File Description
 * -----------------------------------------------------------------------------------------------
 *      File: Port_Cfg.h
 *    Module: PORT_MODULE
 * 
 * Description: <Header file contains the Pre-Compile time configuration of Port_module >
 * 
 **************************************************************************************************/


#ifndef PORT_CFG_H
#define PORT_CFG_H

/*************************************************************************************************
 * GLOBAL CONSTANT MACROS
 ************************************************************************************************/
#define PORT_CONFIGURED_PORT_PINS         (3U)
#define PORT_PIN_LEVEL_LOW                STD_LOW
#define PORT_PIN_LEVEL_HIGH               STD_HIGH

#define PORT_LED_CHL_INDEX                       (0U)
#define PORT_ON_TIME_BUTTON_CHL_INDEX            (1U)
#define PORT_OFF_TIME_BUTTON_CHL_INDEX           (2U)

#define PORT_LED_CHL_ID                         (PIN2_ID)   /* Pin1 */
#define ON_TIME_BUTTON_CHL_ID                   (PIN0_ID)   /* Pin0 */
#define OFF_TIME_BUTTON_CHL_ID                  (PIN4_ID)   /* Pin4 */

#define PORT_LED_PORT_ID                        (PORTF_ID)  /* PORTF */
#define ON_TIME_BUTTON_PORT_ID                  (PORTF_ID) 
#define OFF_TIME_BUTTON_PORT_ID                 (PORTF_ID)

/*************************************************************************************************
 * LOCAL MACROS 
 ************************************************************************************************/
#define PORT_LOCK_VALUE         (uint32)0x4C4F434B


#endif  /* PORT_CFG_H */
