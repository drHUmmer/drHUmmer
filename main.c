#include "main.h"

GPIO_InitTypeDef GPIO_InitStruct;

int main(void)
{
	PLLInit();
	SysTick_Init();

	sequencer.BPM = 60;
	sequencer.beatclk = 0;
	sequencer.beatmask = 0x8000;	// MSB, first beat

	sequencer.snaredrum.sequence = 0xAAAA;
	sequencer.bassdrum.sequence = 0x8080;
	sequencer.instr0.sequence = 0xFFFF;
	sequencer.instr1.sequence = 0x5555;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13
	| GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	dacInit();
	NVICTimer2Init();
	NVICTimer5Init();
	Timer2Init();
	Timer5Init();

	while(1)
    {
		while(sequencer.BPM <= 300)
		{
			sequencer.BPM += 10;
			BPMUpdate(sequencer.BPM);
			delay_nms(1000);
		}
		while(sequencer.BPM >= 30)
		{
			sequencer.BPM -= 10;
			BPMUpdate(sequencer.BPM);
			delay_nms(1000);
		}
    }
}

void SysTick_Handler(void)
{
	TimeTick_Decrement();
}
