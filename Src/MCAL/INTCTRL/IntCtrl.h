/**************************************************************************************************
 * File Description
 * -----------------------------------------------------------------------------------------------
 *      File: IntCtrl.h
 *    Module: IntCtrl
 * 
 * Description: <write file decription here>
 * 
 **************************************************************************************************/


#ifndef INTCTRL_H
#define INTCTRL_H

/*************************************************************************************************
 * INCLUDES
 ************************************************************************************************/
#include "../../Confing/IntCtrl_Cfg.h"

/*************************************************************************************************
 * GLOBAL CONSTANT MACROS
 ************************************************************************************************/
#define APINT_KEY                  0xFA05U

/*************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 ************************************************************************************************/


/*************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 ************************************************************************************************/
typedef enum
{
    GPIO_PORTA,
    GPIO_PORTB,
    GPIO_PORTC,
    GPIO_PORTD,
    GPIO_PORTE,
    UART0,
    UART1,
    SSI0,
    I2C0,
    PWM0_FAULT,
    PWM0_GENETATOR0,
    PWM0_GENETATOR1,
    PWM0_GENETATOR2,
    QEI0,
    ADC0_SEQUENCE0,
    ADC0_SEQUENCE1,
    ADC0_SEQUENCE2,
    ADC0_SEQUENCE3,
    WDT0_AND_WDT1,
    _16BIT_TIMER0A,
    _16BIT_TIMER0B,
    _16BIT_TIMER1A,
    _16BIT_TIMER1B,
    _16BIT_TIMER2A,
    _16BIT_TIMER2B,
    ANALOG_COMP0,
    ANALOG_COMP1,
    SYSCTRL =28,
    FLASH_MEM_CTRL,
    GPIO_PORTF,
    UART2 =33,
    SSI1,
    _16BIT_TIMER3A,
    _16BIT_TIMER3B,
    I2C1,
    QEI1,
    CAN0,
    CAN1,
    HIBERNATION_MODULE,
    USB,
    PWM0_GENETATOR3,
    DMA_SW,
    DMA_ERROR,
    ADC1_SEQUENCE0,
    ADC1_SEQUENCE1,
    ADC1_SEQUENCE2,
    ADC1_SEQUENCE3,
    SSI2 =57,
    SSI3,
    UART3,
    UART4,
    UART5,
    UART6,
    UART7,
    I2C2 = 68,
    I2C3,
    _16BIT_TIMER4A,
    _16BIT_TIMER4B,
    _16BIT_TIMER5A =92,
    _16BIT_TIMER5B,
    _32BIT_TIMER0A,
    _32BIT_TIMER0B,
    _32BIT_TIMER1A,
    _32BIT_TIMER1B,
    _32BIT_TIMER2A,
    _32BIT_TIMER2B,
    _32BIT_TIMER3A,
    _32BIT_TIMER3B,
    _32BIT_TIMER4A,
    _32BIT_TIMER4B,
    _32BIT_TIMER5A,
    _32BIT_TIMER5B,
    SYS_EXCEPTION,
    PWM1_GENETATOR0 =134,
    PWM1_GENETATOR1,
    PWM1_GENETATOR2,
    PWM1_GENETATOR3,
    PWM1_FAULT

}IntCtrl_InterruptType;

typedef enum
{
    RESET =1,
    NMI,
    HARD_FAULT,
    MEM_MANAGEMENT,
    BUS_FAULT,
    USAGE_FAULT,
    SVCALL =11,
    DEBUG_MONITOR,
    PENDSV =14,
    SYSTICK
}IntCtrl_ExceptionType;

typedef enum
{
    EGIHT_GROUP_NONE_SUBGROUP = 0x00000400,
    FOUR_GROUP_TWO_SUBGROUP,
    TWO_GROUP_FOUR_SUBGROUP,
    ONE_GROUP_EGIHT_SUBGROUP
    
}Group_SubGroupType;

typedef enum
{
    LEVEL_ZERO,
    LEVEL_ONE,
    LEVEL_TWO,
    LEVEL_THREE,
    LEVEL_FOUR,
    LEVEL_FIVE,
    LEVEL_SIX,
    LEVEL_SEVEN

}IntCtrl_PriorityNum;

/*************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 ************************************************************************************************/


/***************************************************************************************************   
 * \Syntax        : void IntCtrl_Init(void)
 * \Description   : initialize Nvic/SCB Modules by parsing the Configuration into Nvic/SCB registers 
 * 
 * \Sync\Async    : Synchronous
 * \Reentrancy    : Non-reentrant
 * \Parameter(in) : None
 * \Parameter(out): None
 * \Return Value  : None
 **************************************************************************************************/
void IntCtrl_Init(void);


#endif /* INTCTRL_H */

/***************************************************************************************
*   END OF FILE: IntCtrl.c
***************************************************************************************/