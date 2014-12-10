#include "main.h"

void task_a(void);
void task_b(void);
void leds(void);

#ifdef USE_OS
OS_STK taskA_stk[128];  /*!< define "taskA" task stack */
OS_STK taskB_stk[128];  /*!< define "taskB" task stack */
OS_STK led_stk [128];  /*!< define "led" task stack */

OS_STK UI_task_stk[128];
OS_STK LCD_task_stk[128];
OS_STK SD_task_stk[128];
OS_STK sequencer_task_stk[128];
OS_STK filter_task_stk[128];
OS_STK MIDI_task_stk[128];

OS_FlagID a_flag,b_flag;

OS_EventID mbox0;
#endif

#ifndef DEBUG	/* DEBUG not defined; regular operation (define located in main.h) */
int main(void)
{
	PLLInit();
	//SysTick_Init();
	sequencerInit();

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13
	| GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

//	UIInit();

//	dacInit();
//	adcInit();
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
	sequencerInit();
	SPI3_Init();

/*****************
 * 	LED IO init
 * 	PD12 = Green
 * 	PD13 = Orange
 * 	PD14 = Red
 * 	PD15 = Blue
 *****************/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13
	| GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStruct);
/* End LED IO init */

//	UIInit();

//	dacInit();
//	adcInit();
//	NVICTimer2Init();
//	NVICTimer5Init();
//	Timer2Init();
//	Timer5Init();

//	BPMUpdate(sequencer.BPM);

//	RingBufferInit();


#ifdef USE_OS

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource1);

	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line1;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);

	/* EXTI1 NVIC (nested vectored interrupt controller) configuration */
	NVIC_InitStruct.NVIC_IRQChannel 					= EXTI1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority 	= 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority 			= 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd 					= ENABLE;
	NVIC_Init(&NVIC_InitStruct);


	CoInitOS();
	CoCreateTask((FUNCPtr)UI_task,(void *)0,UI_PRIO,&UI_task_stk[128-1],128);
	CoCreateTask((FUNCPtr)LCD_task,(void *)0,LCD_PRIO,&LCD_task_stk[128-1],128);
	CoCreateTask((FUNCPtr)SD_task,(void *)0,SD_PRIO,&SD_task_stk[128-1],128);
	CoCreateTask((FUNCPtr)Sequencer_task,(void *)0,SEQ_PRIO,&sequencer_task_stk[128-1],128);
	CoCreateTask((FUNCPtr)Filter_task,(void *)0,FILTER_PRIO,&filter_task_stk[128-1],128);
	CoCreateTask((FUNCPtr)MIDI_task,(void *)0,MIDI_PRIO,&MIDI_task_stk[128-1],128);


/*	CoCreateTask ((FUNCPtr)task_a,(void *)0,0,&taskA_stk[128-1],128);
	CoCreateTask ((FUNCPtr)task_b,(void *)0,1,&taskB_stk[128-1],128);
	CoCreateTask ((FUNCPtr)leds ,(void *)0,2,&led_stk[128-1] ,128);*/

	CoStartOS();

	for(;;);
}

void UI_task(void)
{
	for(;;)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		CoTickDelay(15);
	}
}

void LCD_task(void)
{
	for(;;)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
		CoTickDelay(4);
	}
}

void SD_task(void)
{
	for(;;)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_14);
		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		CoTickDelay(2);
	}
}

void Sequencer_task(void)
{
	for(;;)
	{
		CoTickDelay(1);
	}
}

void Filter_task(void)
{
	for(;;)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
		CoTickDelay(7);
	}
}

void MIDI_task(void)
{
	for(;;)
	{
		CoTickDelay(1);
	}
}

#endif

#ifndef USE_OS
	uint16_t i,j;
	int8_t	debug;
//		uint16_t i;
//		uint16_t bpm = 60;

	SysTick_Init();

	while(1)
	{
//		SPI_LED_Send(++i);
//		delay_nms(50);
	}


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

}

#else		/*	USE_OS	*/

void task_a(void)
{
	a_flag = CoCreateFlag (Co_TRUE,0);
	uint8_t msg = 'A';

	for(;;)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_14);
		CoWaitForSingleFlag (a_flag,0);

//		GPIO_SetBits(GPIOD, GPIO_Pin_15);
		//CoTickDelay(10);
		delay_us(10);
		CoPostMail(mbox0,&msg);
		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
//		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
	}
}

void task_b(void)
{
	b_flag = CoCreateFlag (Co_TRUE,0);
	uint8_t msg = 'B';

	for(;;)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
		CoWaitForSingleFlag (b_flag,0);
		//CoTickDelay(10);
		delay_us(5);
		CoPostMail(mbox0,&msg);
		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
	}
}

void leds(void)
{
	void* pmail;
	StatusType err;
	uint8_t* data;

	mbox0 = CoCreateMbox(EVENT_SORT_TYPE_PRIO); //Sort by preemptive priority

	for(;;)
	{
		//GPIO_SetBits(GPIOD, GPIO_Pin_12);
		pmail = CoPendMail(mbox0,2,&err);
		data = pmail;

		if (*data == 'A')
		{
			//debug = SPI_PIC_Receive();
			SPI_LED_Send(0x0000);
			CoSetFlag(b_flag);
		}
		else
		{
			//debug = SPI_PIC_Receive();
			//SPI_LED_Send(0x1234);
			CoSetFlag(a_flag);
		}
		//GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	}
}
#endif	/*	USE_OS	*/

void EXTI1_IRQHandler(void)
{
	/*GPIO_SetBits(GPIOD, GPIO_Pin_12);
	delay_us(10);
	GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	EXTI_ClearFlag(EXTI_Line1);*/

	if(++sequencer.beatclk >= 6)
	{
		sequencer.beatclk = 0;
		if(++sequencer.stepcnt >= 16)
		{
			sequencer.stepcnt = 0;
		}

		sequencer.beatmask = (sequencer.beatmask >> 1) | (sequencer.beatmask << ((sizeof(sequencer.beatmask)*8) - 1));	//rotate right
	}

	if((sequencer.snaredrum.sequence &  sequencer.beatmask) && \
			(sequencer.snaredrum.substeps[sequencer.stepcnt] &  sequencer.submask))
	{
		//GPIO_msk |= GPIO_Pin_12;				//red
	}
	if((sequencer.bassdrum.sequence &  sequencer.beatmask) && \
			  (sequencer.bassdrum.substeps[sequencer.stepcnt] &  sequencer.submask))
	{
		//GPIO_msk |= GPIO_Pin_13;				//orange
	}
	if((sequencer.instr0.sequence &  sequencer.beatmask) && \
			  (sequencer.instr0.substeps[sequencer.stepcnt] &  sequencer.submask))
	{
		//GPIO_msk |= GPIO_Pin_14;				//green
		sequencer.instr0.triggerflag = 1;
	}
	if((sequencer.instr1.sequence &  sequencer.beatmask) && \
			  (sequencer.instr1.substeps[sequencer.stepcnt] &  sequencer.submask))
	{
		//GPIO_msk |= GPIO_Pin_15;				//blu
		sequencer.instr1.triggerflag = 1;
	}
	if((sequencer.instr2.sequence &  sequencer.beatmask) && \
			  (sequencer.instr2.substeps[sequencer.stepcnt] &  sequencer.submask))
	{
		sequencer.instr2.triggerflag = 1;
	}
	if((sequencer.instr3.sequence &  sequencer.beatmask) && \
			  (sequencer.instr3.substeps[sequencer.stepcnt] &  sequencer.submask))
	{
		sequencer.instr3.triggerflag = 1;
	}
//	GPIO_SetBits(GPIOD, GPIO_msk);

	sequencer.submask = (sequencer.submask >> 1) | ((sequencer.submask & 0x1) << 5);	//rotate right

	delay_us(5);

	EXTI_ClearFlag(EXTI_Line1);
}

void delay_us(uint32_t delay)
/*****************************
 * +3.5% accuracy
 *****************************/
{
	uint32_t i,j;

	for(i=0;i<delay;i++)
	{
		for(j=0;j<15;j++);
	}

	return;
}

#endif	/* end debug mode */


#ifndef USE_OS
void SysTick_Handler(void)
{
	TimeTick_Decrement();
}
#endif
