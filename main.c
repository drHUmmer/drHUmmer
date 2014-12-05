#include "main.h"

void task_a(void);
void task_b(void);
void leds(void);

#ifdef USE_OS
OS_STK taskA_stk[128];  /*!< define "taskA" task stack */
OS_STK taskB_stk[128];  /*!< define "taskB" task stack */
OS_STK led_stk [128];  /*!< define "led" task stack */

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
	CoInitOS();
	CoCreateTask ((FUNCPtr)task_a,(void *)0,0,&taskA_stk[128-1],128);
	CoCreateTask ((FUNCPtr)task_b,(void *)0,1,&taskB_stk[128-1],128);
	CoCreateTask ((FUNCPtr)leds ,(void *)0,2,&led_stk[128-1] ,128);

	CoStartOS();

	for(;;);
#endif

#ifndef USE_OS
	uint16_t i=0x00FF;
	int8_t	debug;
//		uint16_t i;
//		uint16_t bpm = 60;

	SysTick_Init();
	UART2_init(57600);

	buttonz.buttonBack 	= 0;
	buttonz.buttonOK 	= 0;
	buttonz.rotaryValue	= 0;

	LCD_Init();
	LCD_Clear(ColourConverterDec(Black));

	LCD_CharSize(24);
	MenuSetup();
	UIInit();

	while (1) {
		uint16_t buttonvalue = UIButtonRead();
		if (buttonvalue & 0x10) {
			buttonz.buttonOK = 1;
			GPIO_SetBits(GPIOD, GPIO_Pin_12);
		}

		if (buttonvalue & 0x20) {
			buttonz.buttonBack = 1;
			GPIO_SetBits(GPIOD, GPIO_Pin_13);
		}

		if (buttonvalue & 0x40) {
			GPIO_SetBits(GPIOD, GPIO_Pin_14);
			buttonz.rotaryValue = 1;
		}

		if (buttonvalue & 0x80) {
			GPIO_SetBits(GPIOD, GPIO_Pin_15);
			buttonz.rotaryValue = -1;
		}


		Menu_UpdateHandler();
		delay_nms(100);
		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
	}

	while(1)
	{
		delay_nms(50);
	}
}

#else		/*	USE_OS	*/

void task_a(void)
{
	a_flag = CoCreateFlag (Co_TRUE,0);
	uint8_t msg = 'A';

	for(;;)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
		CoWaitForSingleFlag (a_flag,0);
		CoTickDelay(20);
		CoPostMail(mbox0,&msg);
		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
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
		CoTickDelay(20);
		CoPostMail(mbox0,&msg);
		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
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
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
		pmail = CoPendMail(mbox0,2,&err);
		data = pmail;

		if (*data == 'A')
		{
			//debug = SPI_PIC_Receive();
			SPI_LED_Send(0xC0);
			CoSetFlag(b_flag);
		}
		else
		{
			//debug = SPI_PIC_Receive();
			SPI_LED_Send(0xA3);
			CoSetFlag(a_flag);
		}
		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	}
}
#endif	/*	USE_OS	*/

void EXTI1_IRQHandler(void)
{

}

#endif	/* end debug mode */


#ifndef USE_OS
void SysTick_Handler(void)
{
	TimeTick_Decrement();
}
#endif
