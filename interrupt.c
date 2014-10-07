#include "interrupt.h"

void TIM2_IRQHandler(void)
{
	uint16_t GPIO_msk = 0;

	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		sequencer.beatclk++;
		if(sequencer.beatclk >= 24)
		{
			sequencer.beatclk = 0;
			sequencer.beatmask = (sequencer.beatmask >> 1) | (sequencer.beatmask << ((sizeof(sequencer.beatmask)*8) - 1));	//rotate right

			if(sequencer.snaredrum.sequence &  sequencer.beatmask)
			{
				GPIO_msk |= GPIO_Pin_12;
			}
			if(sequencer.bassdrum.sequence &  sequencer.beatmask)
			{
				GPIO_msk |= GPIO_Pin_13;
			}
			if(sequencer.instr0.sequence &  sequencer.beatmask)
			{
				GPIO_msk |= GPIO_Pin_14;
			}
			if(sequencer.instr1.sequence &  sequencer.beatmask)
			{
				GPIO_msk |= GPIO_Pin_15;
			}
	/*		if(sequencer.instr2.sequence &  sequencer.beatmask)
			{
				GPIO_msk |= GPIO_Pin_??;
			}
			if(sequencer.instr3.sequence &  sequencer.beatmask)
			{
				GPIO_msk |= GPIO_Pin_??;
			}*/
			GPIO_SetBits(GPIOD, GPIO_msk);
		}
	}
	else if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
		GPIO_ResetBits(GPIOD, (GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15));
	}

}

void NVICTimer2Init(void)
{
	/* TIM2 NVIC (nested vectored interrupt controller) configuration */
	NVIC_InitStruct.NVIC_IRQChannel 					= TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority 	= 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority 			= 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd 					= ENABLE;
	NVIC_Init(&NVIC_InitStruct);

}
