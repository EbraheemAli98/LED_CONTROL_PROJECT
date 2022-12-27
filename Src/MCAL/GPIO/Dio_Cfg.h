/**************************************************************************************************
 * File Description
 * -----------------------------------------------------------------------------------------------
 *      File: Dio.h
 *    Module: DIO_MODULE
 * 
 * Description: <Header file contains the Pre-Compile time configuration of Dio_module >
 * 
 **************************************************************************************************/


#ifndef DIO_CFG_H
#define DIO_CFG_H


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

#endif  /* DIO_CFG_H */

/***************************************************
 * End of FILE: Dio_Cfg.h
 ***************************************************/