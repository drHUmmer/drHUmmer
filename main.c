#include "main.h"

GPIO_InitTypeDef GPIO_InitStruct;

int main(void)
{
	PLLInit();
	SysTick_Init();

	sequencer.BPM = 200;
	sequencer.beatclk = 0;
	sequencer.beatmask = 0x8000;	// MSB, first beat

	sequencer.snaredrum.sequence = 0x3C3C;	// 0011 1100 0011 1100
	sequencer.bassdrum.sequence = 0xAAAA;	// 1010 1010 1010 1010
	sequencer.instr0.sequence = 0xFFFF;		// 1111 1111 1111 1111			//hihat
	sequencer.instr1.sequence = 0x55F5;		// 0101 0101 1111 0101			//snare
	sequencer.instr2.sequence = 0xAAAA;		// 1010 1010 1010 1010			//basskick
	sequencer.instr3.sequence = 0x0080;		// 0000 0000 1000 0000			//cymbal

	sequencer.instr0.tone = 1;
	sequencer.instr0.file_length = 16060;
	sequencer.instr1.tone = 1;
	sequencer.instr1.file_length = 22051;
	sequencer.instr2.tone = 1;
	sequencer.instr2.file_length = 18387;
	sequencer.instr3.tone = 1;
	sequencer.instr3.file_length = 65135;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13
	| GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	UIInit();

	dacInit();
	adcInit();
	NVICTimer2Init();
	NVICTimer5Init();
	Timer2Init();
	Timer5Init();

	BPMUpdate(sequencer.BPM);

//	uint8_t i = 0;
//	uint16_t adval[3] = {2048,2048,2048};

	uint16_t butt_data = 0;

	while(1)
    {
		if(UIPlayRead())
		{
			sequencer.instrID++;
			if(sequencer.instrID > 5)
			{
				sequencer.instrID = 0;
			}
		}

		butt_data = UIButtonRead();

		switch(sequencer.instrID)
		{
			case 0:
				sequencer.instr0.sequence ^= butt_data;
				UILed(sequencer.instr0.sequence);
				break;
			case 1:
				sequencer.instr1.sequence ^= butt_data;
				UILed(sequencer.instr1.sequence);
				break;
			case 2:
				sequencer.instr2.sequence ^= butt_data;
				UILed(sequencer.instr2.sequence);
				break;
			case 3:
				sequencer.instr3.sequence ^= butt_data;
				UILed(sequencer.instr3.sequence);
				break;
			case 4:
				sequencer.bassdrum.sequence ^= butt_data;
				UILed(sequencer.bassdrum.sequence);
				break;
			case 5:
				sequencer.snaredrum.sequence ^= butt_data;
				UILed(sequencer.snaredrum.sequence);
				break;
			default:
				break;
		}

		delay_nms(100);



/*		for(i=0;i<3;i++)
		{
			adval[i] = adcGet();
			delay_nms(50);
		}

		sequencer.BPM = (((adval[0]+adval[1]+adval[2])*10)/163);
		BPMUpdate(sequencer.BPM);*/

/*		while(sequencer.BPM <= 800)
		{
			sequencer.BPM += 10;
			BPMUpdate(sequencer.BPM);
			delay_nms(1000);
		}
		while(sequencer.BPM >= 60)
		{
			sequencer.BPM -= 10;
			BPMUpdate(sequencer.BPM);
			delay_nms(1000);
		}*/
    }
}

void SysTick_Handler(void)
{
	TimeTick_Decrement();
}
