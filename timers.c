#include "timers.h"


void Timer2Init(void){

	NVICTimer2Init();

	/* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // PCLK1 = 42MHz Timer CLK =

	/* Time base configuration */
	TIM_TimeBaseInitStruct.TIM_Period 			= 1000000;
	TIM_TimeBaseInitStruct.TIM_Prescaler 		= 0;
	TIM_TimeBaseInitStruct.TIM_ClockDivision 	= TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode 		= TIM_CounterMode_Down;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	/* TIM IT enable */
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	/* TIM2 enable counter */
	TIM_Cmd(TIM2, ENABLE);


}
