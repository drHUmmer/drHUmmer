#ifndef TIMER_HEADER
#define TIMER_HEADER

#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "interrupt.h"

TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

void Timer2Init(void);
void Timer2BPMUpdate(uint32_t BPM);

#endif /* TIMER_HEADER */
