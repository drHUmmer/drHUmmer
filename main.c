#include "main.h"

/*void us_delay(uint32_t time)
{
	RCC_ClocksTypeDef Clk_freqs;
	uint32_t i,j;

	RCC_GetClocksFreq(&Clk_freqs);

	j = Clk_freqs.HCLK_Frequency/6;

	for(i=0;i<time;i++)
	{
		while(j--);
	}
}*/

GPIO_InitTypeDef GPIO_InitStruct;

int main(void)
{
	uint32_t BPM = 60;

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

	while(1)
    {
		while(BPM <= 600)
		{
			delay_nms(100);
			BPM++;
			Timer2BPMUpdate(BPM);
		}
		while(BPM >= 30)
		{
			delay_nms(100);
			BPM--;
			Timer2BPMUpdate(BPM);
		}
    }
}

void SysTick_Handler(void)
{
	TimeTick_Decrement();
}
