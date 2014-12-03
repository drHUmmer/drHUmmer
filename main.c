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


	LCD_Init();
	LCD_Clear(ColourConverterDec(Black));
//	LCD_CreateVertProgressbar(20, 20, 50, 200, Red, Yellow, 25);

//	LCD_CreateVertProgressbar(80, 20, 50, 200, Red, Yellow, 50);

//	LCD_CreateVertProgressbar(140, 20, 50, 200, Red, Yellow, 75);
	LCD_SetBackColor(ColourConverterDec(Black));
	LCD_SetTextColor(ColourConverterDec(Green));
	LCD_CharSize(24);
	LCD_PutChar(50, 50,   '0');
	LCD_PutChar(100, 100, '1');
	LCD_PutChar(150, 150, '2');
	LCD_PutChar(200, 200, '3');
	LCD_PutChar(230, 200, '4');
	LCD_PutChar(200, 230, '5');
	LCD_PutChar(200, 300, '6');
	LCD_StringLine(50, 200,"HalLo");
	LCD_StringLine(20, 200,"HALLO");
	while (1);

	LCD_CharSize(24);
	LCD_StringLine(100, 50,"JAN");

//	LCD_CreateVertProgressbar(00, 0, 50, 100, Red, Yellow, 25);

	while(1);

	u32 Q = 0;
	while (1) {
		LCD_CreateVertProgressbar(00, 0, 50, 100, Red, Yellow, 100 - (Q % 100));
		LCD_CreateVertProgressbar(50, 0, 50, 150, Red, Yellow, 100 - (Q % 100));
		LCD_CreateVertProgressbar(100, 0, 50, 200, Red, Yellow, 100 - (Q % 100));
		LCD_CreateVertProgressbar(150, 0, 50, 250, Red, Yellow, 100 - (Q % 100));
		LCD_CreateVertProgressbar(200, 0, 50, 320, Red, Yellow, 100 - (Q % 100));
		Q += 2;
	}

//
//	initGPIO();
//	initFSMC();
//	reset();
//	initDisplay();
//
//	delayMillis(2000);
//
//	drawCircle(50, 50, 10, BLUE);
//	fillCircle(50, 50, 10, RED);

//	delay_nms(500);
//	LCD_Init();
//	delay_nms(500);
//	LCD_Clear(WHITE);
//	int q = 1;
//
//	LCD_Clear(YELLOW);
//	LCD_BackLight(100);
//
//	while(1)
//	{
//		LCD_Clear(WHITE);
//		LCD_Clear(BLACK);
//	}
//	while (1) {
//		LCD_SetTextColor(CYAN);
//		LCD_DrawCircle(120,120, (q % 75) + 1);
//		LCD_DrawCircle(120,120, (q % 75) + 10);
//		LCD_DrawCircle(120,120, (q % 75) + 20);
////		Julia2(240,320,120,160,q);
//		q+=1;
////		if(q>100)
////		q=0;
//
////		LCD_BackLight(q % 100);
//		delay_nms(10);
//	}

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
