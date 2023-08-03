/********************************** (C) COPYRIGHT *******************************
* File Name          : ch32v30x_it.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : Main Interrupt Service Routines.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#include <stdint.h>
#include "ch32v30x_it.h"
#include "UART.h"

__attribute__((naked)) void TIM7_IRQHandler() {
    __asm volatile ("call TIM7_IRQHandler_real; mret");
}

volatile uint32_t micros;
/*********************************************************************
 * @fn      TIM7_IRQHandler
 *
 * @brief   This function handles TIM7 exception.
 *
 * @return  none
 */
__attribute__((used)) void TIM7_IRQHandler_real( void )
{
    /* uart timeout counts */
    Uart.Rx_TimeOut++;
    Uart.USB_Up_TimeOut++;

    /* clear status */
    TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
}
