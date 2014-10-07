#include "timer.h"


void Timer2Init(void)
{
	NVICTimer2Init();

	/* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //Timer CLK = 2 * PCLK1

	RCC_ClocksTypeDef Clk_freqs;
	RCC_GetClocksFreq(&Clk_freqs);

	/* Time base configuration */
	TIM2_TimeBaseInitStruct.TIM_Period 			= ((2*Clk_freqs.PCLK1_Frequency)/24)-1;		// init @ 60 BPM
	TIM2_TimeBaseInitStruct.TIM_Prescaler 		= 0x0;
	TIM2_TimeBaseInitStruct.TIM_ClockDivision 	= TIM_CKD_DIV1;
	TIM2_TimeBaseInitStruct.TIM_CounterMode 	= TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM2_TimeBaseInitStruct);

	/* Output compare config */
	TIM2_OCInitStruct.TIM_OCMode				= TIM_OCMode_Timing;
	TIM2_OCInitStruct.TIM_OutputState			= TIM_OutputState_Enable;
	TIM2_OCInitStruct.TIM_Pulse					= (2*Clk_freqs.PCLK1_Frequency)/200;	// TimerClkFreq / 200 = 5ms
	TIM2_OCInitStruct.TIM_OCPolarity			= TIM_OCPolarity_High;
	TIM_OC1Init(TIM2, &TIM2_OCInitStruct);

	/* TIM IT enable */
	TIM_ITConfig(TIM2, (TIM_IT_Update | TIM_IT_CC1), ENABLE);

	/* TIM2 enable counter */
	TIM_Cmd(TIM2, ENABLE);
}

void BPMUpdate(uint32_t BPM)
{
	RCC_ClocksTypeDef Clk_freqs;
	RCC_GetClocksFreq(&Clk_freqs);
	uint32_t TIM2_AAR = ((2*Clk_freqs.PCLK1_Frequency)/(BPM*24))*60;	//((120*Clk_freqs.PCLK1_Frequency)/(BPM*24))-1;		// TIM2_CLK = 2*PCLK1;

	TIM_SetAutoreload(TIM2, TIM2_AAR);
	uint32_t TIM2_cnt = TIM_GetCounter(TIM2);
	if(TIM2_cnt >= TIM2_AAR)						// if somehow Timer2 goes out of range (which is bad
	{												// and really shouldn't happen)
		TIM_SetCounter(TIM2, 0);					// then reset the counter...
	}
}
