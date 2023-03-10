/**************************************************************************************************
 * File Description
 * -----------------------------------------------------------------------------------------------
 *      File: Mcu_Hw.h
 *    Module: Mcu_Hw
 * 
 * Description: Header file for Register definition.
 * 
 **************************************************************************************************/

#ifndef MCU_HW_H
#define MCU_HW_H

/*************************************************************************************************
 * INCLUDES
 ************************************************************************************************/
#include "../../SERVICES/Std_Types.h"

/*************************************************************************************************
 * GLOBAL CONSTANT MACROS
 ************************************************************************************************/ 

/*-----------------------------------------------------------------------------------------------
  GPIO DRIVER CONSTANT MACROS
 ------------------------------------------------------------------------------------------------*/
#define GPIO_OFFSET_ADDRESS(i)          (i<4? ((0x40004000)+((i)*0x1000)):(0x40024000)+((i-4)*0x1000))
#define GPIODATA(i)                     *(volatile uint32*)((GPIO_OFFSET_ADDRESS(i)+0x3FC))
#define GPIODIR(i)                      *((volatile uint32*)(GPIO_OFFSET_ADDRESS(i)+0x400))
#define GPIOIS(i)                       *((volatile uint32*)(GPIO_OFFSET_ADDRESS(i)+0x404))
#define GPIOIBE(i)                      *((volatile uint32*)(GPIO_OFFSET_ADDRESS(i)+0x408))
#define GPIOIEV(i)                      *((volatile uint32*)(GPIO_OFFSET_ADDRESS(i)+0x40C))
#define GPIOIM(i)                       *((volatile uint32*)(GPIO_OFFSET_ADDRESS(i)+0x410))
#define GPIORIS(i)                      *((volatile uint32*)(GPIO_OFFSET_ADDRESS(i)+0x414))
#define GPIOMIS(i)                      *((volatile uint32*)(GPIO_OFFSET_ADDRESS(i)+0x418))
#define GPIOICR(i)                      *((volatile uint32*)(GPIO_OFFSET_ADDRESS(i)+0x41C))
#define GPIOAFSEL(i)                    *((volatile uint32*)(GPIO_OFFSET_ADDRESS(i)+0x420))
#define GPIOR2R(i)                      *((volatile uint32*)(GPIO_OFFSET_ADDRESS(i)+0x500))
#define GPIOR4R(i)                      *((volatile uint32*)(GPIO_OFFSET_ADDRESS(i)+0x504))
#define GPIOR8R(i)                      *((volatile uint32*)(GPIO_OFFSET_ADDRESS(i)+0x508))
#define GPIOODR(i)                      *((volatile uint32*)(GPIO_OFFSET_ADDRESS(i)+0x50C))
#define GPIOPUR(i)                      *((volatile uint32*)(GPIO_OFFSET_ADDRESS(i)+0x510))
#define GPIOPDR(i)                      *((volatile uint32*)(GPIO_OFFSET_ADDRESS(i)+0x514))
#define GPIOSLR(i)                      *((volatile uint32*)(GPIO_OFFSET_ADDRESS(i)+0x518))
#define GPIODEN(i)                      *((volatile uint32*)(GPIO_OFFSET_ADDRESS(i)+0x51C))
#define GPIOLOCK(i)                     *((volatile uint32*)(GPIO_OFFSET_ADDRESS(i)+0x520))
#define GPIOCR(i)                       *((volatile uint32*)(GPIO_OFFSET_ADDRESS(i)+0x524))
#define GPIOAMSEL(i)                    *((volatile uint32*)(GPIO_OFFSET_ADDRESS(i)+0x528))
#define GPIOPCTL(i)                     *((volatile uint32*)(GPIO_OFFSET_ADDRESS(i)+0x52C))
/*-----------------------------------------------------------------------------------------------
  INTCTRL DRIVER CONSTANT MACROS
 ------------------------------------------------------------------------------------------------*/
#define CORTEXM4_PERI_BASE_ADDRESS      0xE000E000
#define PRIx(i)                         (*((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS+0x00000400+((i/4)*4))))
#define ENx(i)                          (*((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS+0x00000100+((i/32)*4))))
#define DISx(i)                         (*((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS+0x00000180+((i/32)*4))))
#define APINT                           *((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS+0xD0C))
#define INTCTRL                         *((volatile INTCTRL_Tag*)(CORTEXM4_PERI_BASE_ADDRESS+0xD04))
/*-----------------------------------------------------------------------------------------------
  GPT DRIVER CONSTANT MACROS
 ------------------------------------------------------------------------------------------------*/
#define TIMER_BASE_ADDRESS           0x40030000
     
#define GPTMCFG                      (0x000u)
#define GPTMTAMR                     (0x004u)
#define GPTMCTL                      (0x00Cu)
#define GPTMIMR                      (0x018u)
#define GPTMRIS                      (0x01Cu)
#define GPTMMIS                      (0x020u)
#define GPTMICR                      (0x024u)
#define GPTMTAILR                    (0x028u)
#define GPTMTAPR                     (0x038u)
#define GPTMTAV                      (0x050u) 

/*-----------------------------------------------------------------------------------------------
  SYSCTRL CONSTANT MACROS
 ------------------------------------------------------------------------------------------------*/
#define SYSCTL_RCGCTIMER                *((volatile uint32*)(0x400FE000+0x604))
#define SYSCTL_RCGCGPIO                 *((volatile uint32*)(0x400FE000+0x608))
#define SYSCTL_RCGCWTIMER               *((volatile uint32*)(0x400FE000+0x65C))

#endif /* MCU_HW_H */

/***************************************************************************************
*   END OF FILE: Mcu_Hw.h
***************************************************************************************/
