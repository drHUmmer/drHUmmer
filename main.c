#include "main.h"

void task_a(void);
void task_b(void);
void leds(void);

OS_STK taskA_stk[128];  /*!< define "taskA" task stack */
OS_STK taskB_stk[128];  /*!< define "taskB" task stack */
OS_STK led_stk [128];  /*!< define "led" task stack */

OS_FlagID a_flag,b_flag;

OS_EventID mbox0;
GPIO_InitTypeDef GPIO_InitStruct;

#ifndef DEBUG	/* DEBUG not defined; regular operation */
int main(void)
{
	PLLInit();
	//SysTick_Init();
	sequencerInit();

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

	while(1);
}

#else	/* if debug mode */

int main(void)
{
	PLLInit();
	//SysTick_Init();
	sequencerInit();

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

	RingBufferInit();

	CoInitOS();
	CoCreateTask ((FUNCPtr)task_a,(void *)0,0,&taskA_stk[128-1],128);
	CoCreateTask ((FUNCPtr)task_b,(void *)0,1,&taskB_stk[128-1],128);
	CoCreateTask ((FUNCPtr)leds ,(void *)0,2,&led_stk[128-1] ,128);
//		uint16_t i;
//		uint16_t bpm = 60;

	CoStartOS();



	for(;;);

/*		for(i=0;i<100;i++)
		{
			if(Write_Rbuffer(debug_buff_p, i + 60))
			{
				error_blink();
			}


			bpm = Read_Rbuffer(debug_buff_p);
			if(bpm == -1)
			{
				error_blink();
			}
			else
			{
				BPMUpdate(bpm);
			}
			delay_nms(200);
		}*/


/*		//	uint16_t adval[3] = {2048,2048,2048};
		//	uint16_t butt_data = 0;

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

		delay_nms(100);*/



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

void error_blink(void)
{
	uint8_t k;
	uint16_t leds = (GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12);
	for(k=0;k<5;k++)
	{
		GPIO_SetBits(GPIOD, leds);
		delay_nms(100);
		GPIO_ResetBits(GPIOD, leds);
		delay_nms(100);
	}
}

void task_a(void)
{
	a_flag = CoCreateFlag (Co_TRUE,0);
	uint8_t msg = 'A';

	for(;;)
	{
		CoWaitForSingleFlag (a_flag,0);
		CoTickDelay(20);
		CoPostMail(mbox0,&msg);

	}
}

void task_b(void)
{
	b_flag = CoCreateFlag (Co_TRUE,0);
	uint8_t msg = 'B';

	for(;;)
	{
		CoWaitForSingleFlag (b_flag,0);
		CoTickDelay(20);
		CoPostMail(mbox0,&msg);

	}
}

void leds(void)
{
	void* pmail;
	StatusType err;

	mbox0 = CoCreateMbox(EVENT_SORT_TYPE_PRIO); //Sort by preemptive priority

	for(;;)
	{
		pmail = CoPendMail(mbox0,1,&err);
		char data = (char)pmail;

		if (data == 'A')
		{
			CoSetFlag(b_flag);
		}
		else
		{
			CoSetFlag(a_flag);
		}

	}
}

#endif	/* end debug mode */



/*void SysTick_Handler(void)
{
	TimeTick_Decrement();
}*/
