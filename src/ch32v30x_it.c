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
#include "timer.h"

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
__attribute__((used)) void TIM7_IRQHandler_real( void ) {
    /* uart timeout counts */
    Uart.Rx_TimeOut++;
    Uart.USB_Up_TimeOut++;
    micros += 100;

    /* clear status */
    TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
}

__attribute__((naked)) void TIM1_CC_IRQHandler() {
    __asm volatile ("call TIM1_CC_IRQHandler_real; mret");
}

volatile uint8_t pendingPPS = 0;
volatile uint16_t cap_ch1 = 0;
volatile uint32_t cap_micros = 0, cap_count = 0;
void TIM1_CC_IRQHandler_real(void) {
  if( TIM_GetITStatus( TIM1, TIM_IT_CC1 ) != RESET ) {
    cap_count = get_counters();
    cap_micros = micros;
    cap_ch1 = TIM_GetCapture1( TIM1 );
    pendingPPS = 1;
  }

  TIM_ClearITPendingBit( TIM1, TIM_IT_CC1);
}
