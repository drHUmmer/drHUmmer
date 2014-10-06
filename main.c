#include "main.h"

GPIO_InitTypeDef GPIO_InitStruct;
Sequencer_TypeDef sequencer;

int main(void)
{
	PLLInit();
	SysTick_Init();
	NVICTimer2Init();
	Timer2Init();

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13
	| GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	sequencer.BPM = 150;

	while(1)
    {
		while(sequencer.BPM <= 300)
		{
			sequencer.BPM += 10;
			Timer2BPMUpdate(sequencer.BPM);
			delay_nms(100);
		}
		while(sequencer.BPM >= 30)
		{
			sequencer.BPM -= 10;
			Timer2BPMUpdate(sequencer.BPM);
			delay_nms(100);
		}
    }
}

void SysTick_Handler(void)
{
	TimeTick_Decrement();
}
