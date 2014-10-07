#ifndef TIMER_HEADER
#define TIMER_HEADER

#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "interrupt.h"

TIM_TimeBaseInitTypeDef TIM2_TimeBaseInitStruct;
TIM_TimeBaseInitTypeDef TIM5_TimeBaseInitStruct;
TIM_OCInitTypeDef TIM2_OCInitStruct;

void Timer2Init(void);
void Timer5Init(void);
void BPMUpdate(uint32_t BPM);

#endif /* TIMER_HEADER */
