#include "debug.h"
#include "timer.h"

/*
 *@Note
Input capture routine:
 TIM1_CH1(PA8)
 This example demonstrates the TIM1_CH1(PA8) pin floating input, which detects an edge
  transition to trigger a TIM1 capture interrupt,
 The rising edge triggers the TIM_IT_CC1 interrupt
 TIM1 is used as a prescaler for TIM2, creating effectively a 32 bit timer
*/

void TIM1_Init() {
    GPIO_InitTypeDef GPIO_InitStructure={0};
    TIM_ICInitTypeDef TIM_ICInitStructure={0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure={0};
    NVIC_InitTypeDef NVIC_InitStructure={0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_TIM1, ENABLE );
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init( GPIOA, &GPIO_InitStructure);
    GPIO_ResetBits( GPIOA, GPIO_Pin_8 );

    TIM_TimeBaseInitStructure.TIM_Period = 0xFFFF;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter =  0x00;
    TIM_TimeBaseInit( TIM1, &TIM_TimeBaseInitStructure);

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter = 0x00;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;

    TIM_PWMIConfig( TIM1, &TIM_ICInitStructure );

    NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_ITConfig( TIM1, TIM_IT_CC1, ENABLE );
    TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Update);

    TIM_TimeBaseInitStructure.TIM_Period = 0xFFFF;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter =  0x00;
    TIM_TimeBaseInit( TIM2, &TIM_TimeBaseInitStructure);

    TIM_ITRxExternalClockConfig(TIM2, TIM_TS_ITR0);
    TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_External1);

    TIM_Cmd(TIM1, ENABLE );
    TIM_Cmd(TIM2, ENABLE);
}
