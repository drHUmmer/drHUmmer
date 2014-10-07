#ifndef INTERRUPT_HEADER
#define INTERRUPT_HEADER

#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "misc.h"
#include "sequencer.h"
#include "DAC.h"

#define FRAMES 16060
#define TONE 0.3

extern uint16_t wavFile[FRAMES];
extern float wavCnt;

NVIC_InitTypeDef NVIC_InitStruct;

void TIM2_IRQHandler(void);
void NVICTimer2Init(void);
void NVICTimer5Init(void);

#endif /* INTERRUPT_HEADER */
