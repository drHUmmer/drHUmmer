#include "timer.h"


void Timer2Init(void)
{
	NVICTimer2Init();

	/* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //Timer CLK = 2 * PCLK1

	RCC_ClocksTypeDef Clk_freqs;
	RCC_GetClocksFreq(&Clk_freqs);

	/* Time base configuration */
	TIM_TimeBaseInitStruct.TIM_Period 			= (2*Clk_freqs.PCLK1_Frequency);		//init @ 60 BPM
	TIM_TimeBaseInitStruct.TIM_Prescaler 		= 0;
	TIM_TimeBaseInitStruct.TIM_ClockDivision 	= TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode 		= TIM_CounterMode_Down;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	/* TIM IT enable */
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	/* TIM2 enable counter */
	TIM_Cmd(TIM2, ENABLE);
}

void Timer2BPMUpdate(uint32_t BPM)
{
	RCC_ClocksTypeDef Clk_freqs;
	RCC_GetClocksFreq(&Clk_freqs);

	uint32_t TIM2_AAR = (((2*Clk_freqs.PCLK1_Frequency)/BPM)*60);		// TIM2_CLK = 2*PCLK1;

	TIM_SetAutoreload(TIM2, TIM2_AAR);
}
