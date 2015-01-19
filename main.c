#include "main.h"

void task_a(void);
void task_b(void);
void leds(void);

extern uint32_t SDCnt;
extern uint8_t bufFlag;
extern uint8_t bufFillFlag;


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

int main(void)
{
	PLLInit();
//	sequencerInit();
//	SPI3_Init();

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

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
/* End LED IO init */

//	UIInit();

	GPIO_SetBits(GPIOD, GPIO_Pin_13);
	while(SDInit());
	GPIO_ResetBits(GPIOD, GPIO_Pin_13);

	CoInitOS();

	dacInit();
//	adcInit();
	NVICTimer2Init();
	NVICTimer5Init();
	Timer2Init();
	Timer5Init();

	BPMUpdate(sequencer.BPM);

//	RingBufferInit();



//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
//
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
//	GPIO_Init(GPIOA, &GPIO_InitStruct);
//
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource1);
//
//	EXTI_InitTypeDef EXTI_InitStruct;
//	EXTI_InitStruct.EXTI_Line = EXTI_Line1;
//	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
//	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
//	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
//	EXTI_Init(&EXTI_InitStruct);
//
//	/* EXTI1 NVIC (nested vectored interrupt controller) configuration */
//	NVIC_InitStruct.NVIC_IRQChannel 					= EXTI1_IRQn;
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority 	= 1;
//	NVIC_InitStruct.NVIC_IRQChannelSubPriority 			= 1;
//	NVIC_InitStruct.NVIC_IRQChannelCmd 					= ENABLE;
//	NVIC_Init(&NVIC_InitStruct);


	CoCreateTask((FUNCPtr)UI_task,(void *)0,UI_PRIO,&UI_task_stk[128-1],128);
	CoCreateTask((FUNCPtr)LCD_task,(void *)0,LCD_PRIO,&LCD_task_stk[128-1],128);
	CoCreateTask((FUNCPtr)SD_task,(void *)0,SD_PRIO,&SD_task_stk[128-1],128);
	CoCreateTask((FUNCPtr)Sequencer_task,(void *)0,SEQ_PRIO,&sequencer_task_stk[128-1],128);
	CoCreateTask((FUNCPtr)Filter_task,(void *)0,FILTER_PRIO,&filter_task_stk[128-1],128);
	CoCreateTask((FUNCPtr)MIDI_task,(void *)0,MIDI_PRIO,&MIDI_task_stk[128-1],128);

	CoStartOS();

	GPIO_SetBits(GPIOD, GPIO_Pin_15);

	while(1);

}

void UI_task(void)
{
	uint8_t i;
	uint8_t cur_buttons[4];
	int8_t cur_rotaries[11];

	for(;;)
	{
		GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
		SPI_PIC_Send(PIC_GET_BUTTON,0,PIC_BUTTONS_ALL);
		CoTickDelay(1);
		for(i=0;i<4;i++)
		{
			cur_buttons[i] = SPI_PIC_Receive();
		}
		CoTickDelay(1);

		SPI_PIC_Send(PIC_GET_ROTARY,0,PIC_ROTARY_ALL);
		CoTickDelay(1);
		for(i=0;i<11;i++)
		{
			cur_rotaries[i] = SPI_PIC_Receive();
		}
		CoTickDelay(1);

		SPI_LED_Send((cur_buttons[0] << 8) | cur_buttons[1]);
		CoTickDelay(40);
	}
}

void LCD_task(void)
{
	for(;;)
	{
//		GPIO_SetBits(GPIOD, GPIO_Pin_13);
//		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
		CoTickDelay(4);
	}
}

void SD_task(void)
{
	#define FILENR 0

	uint32_t filesize = getFileSize(fnames[FILENR]);
	uint32_t i=44;

	CoSchedLock();
	//if( SDInit() == FR_OK ){
		SDGetNames("/"); 		// root directory
	//}
	CoSchedUnlock();

	bufFlag = BUFF_A;
	CoSchedLock();
	SDGet512(wavBufA, fnames[FILENR] ,44);
	CoSchedUnlock();
	bufFlag = BUFF_B;

	for(;;)
	{
		if (bufFillFlag == BUFFF_NF){
			if(bufFlag == BUFF_A){
				if((i+=(WAV_BUF_SIZE*2)) > filesize){
					i = 44;
				}
				bufABusy = TRUE;
				CoSchedLock();
				SDGet512(wavBufA, fnames[FILENR], (DWORD)i);
				CoSchedUnlock();
				bufABusy = FALSE;
				bufFillFlag = BUFFF_F;

				//GPIO_ToggleBits(GPIOD, (GPIO_Pin_12 | GPIO_Pin_13));

			}else {
				if((i+=(WAV_BUF_SIZE*2)) > filesize){
					i = 44;
				}
				bufBBusy = TRUE;
				CoSchedLock();
				SDGet512(wavBufB, fnames[FILENR], (DWORD)i);
				CoSchedUnlock();
				bufBBusy = FALSE;
				bufFillFlag = BUFFF_F;

				//GPIO_ToggleBits(GPIOD, (GPIO_Pin_12 | GPIO_Pin_13));
			}
		}
		CoTickDelay(1);
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
//		GPIO_SetBits(GPIOD, GPIO_Pin_15);
//		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
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

//void EXTI1_IRQHandler(void)
//{
//	/*GPIO_SetBits(GPIOD, GPIO_Pin_12);
//	delay_us(10);
//	GPIO_ResetBits(GPIOD, GPIO_Pin_12);
//	EXTI_ClearFlag(EXTI_Line1);*/
//
//	if(++sequencer.beatclk >= 6)
//	{
//		sequencer.beatclk = 0;
//		if(++sequencer.stepcnt >= 16)
//		{
//			sequencer.stepcnt = 0;
//		}
//
//		sequencer.beatmask = (sequencer.beatmask >> 1) | (sequencer.beatmask << ((sizeof(sequencer.beatmask)*8) - 1));	//rotate right
//	}
//
//	if((sequencer.snaredrum.sequence &  sequencer.beatmask) && \
//			(sequencer.snaredrum.substeps[sequencer.stepcnt] &  sequencer.submask))
//	{
//		//GPIO_msk |= GPIO_Pin_12;				//red
//	}
//	if((sequencer.bassdrum.sequence &  sequencer.beatmask) && \
//			  (sequencer.bassdrum.substeps[sequencer.stepcnt] &  sequencer.submask))
//	{
//		//GPIO_msk |= GPIO_Pin_13;				//orange
//	}
//	if((sequencer.instr0.sequence &  sequencer.beatmask) && \
//			  (sequencer.instr0.substeps[sequencer.stepcnt] &  sequencer.submask))
//	{
//		//GPIO_msk |= GPIO_Pin_14;				//green
//		sequencer.instr0.triggerflag = 1;
//	}
//	if((sequencer.instr1.sequence &  sequencer.beatmask) && \
//			  (sequencer.instr1.substeps[sequencer.stepcnt] &  sequencer.submask))
//	{
//		//GPIO_msk |= GPIO_Pin_15;				//blu
//		sequencer.instr1.triggerflag = 1;
//	}
//	if((sequencer.instr2.sequence &  sequencer.beatmask) && \
//			  (sequencer.instr2.substeps[sequencer.stepcnt] &  sequencer.submask))
//	{
//		sequencer.instr2.triggerflag = 1;
//	}
//	if((sequencer.instr3.sequence &  sequencer.beatmask) && \
//			  (sequencer.instr3.substeps[sequencer.stepcnt] &  sequencer.submask))
//	{
//		sequencer.instr3.triggerflag = 1;
//	}
////	GPIO_SetBits(GPIOD, GPIO_msk);
//
//	sequencer.submask = (sequencer.submask >> 1) | ((sequencer.submask & 0x1) << 5);	//rotate right
//
//	delay_us(5);
//
//	EXTI_ClearFlag(EXTI_Line1);
//}


#ifndef USE_OS
/*
void SysTick_Handler(void)
{
	TimeTick_Decrement();
}
*/
#endif
