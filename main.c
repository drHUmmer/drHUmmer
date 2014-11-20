#include "main.h"

void task_a(void);
#ifndef DEBUG	/* DEBUG not defined; regular operation (define located in main.h) */
void task_b(void);
void leds(void);

OS_STK taskA_stk[128];  /*!< define "taskA" task stack */
OS_STK taskB_stk[128];  /*!< define "taskB" task stack */
OS_STK led_stk [128];  /*!< define "led" task stack */

OS_FlagID a_flag,b_flag;

OS_EventID mbox0;
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
	//SysTick_Init();
	sequencerInit();
	SPI3_Init();

/*****************
 * 	LED IO init
 * 	PD12 =
 * 	PD13 =
 * 	PD14 =
 * 	PD15 =
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


/*****************
 * 	SPI config & init
 * 	PC8  = PIC NSS
 * 	PC9  = LED NSS
 * 	PC10 = SCLK
 * 	PC11 = MISO
 * 	PC12 = MOSI
 *****************/

/*	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);				//enable(?) APB clock for SPI3
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);				//enable AHB peripheral clock for GPIO bank C

	//NSS pins configured as GPIO outputs; software managed
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_11 | GPIO_Pin_10;	//MOSI | MISO | CLK
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;			//DOWN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_SPI3);		//connect alt functions to pins
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_SPI3);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_SPI3);
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	SPI_InitTypeDef SPI3_InitStruct;
	SPI3_InitStruct.SPI_CPOL = SPI_CPOL_Low;							//clock idle low
	SPI3_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;							//capture on 1st edge
	SPI3_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;					//Shift MSB first
	SPI3_InitStruct.SPI_DataSize = SPI_DataSize_8b;						//8 bits per transfer
	SPI3_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;	//BaudRate = APB1 / Prescaler = 42MHz / 8 = 2.625MHz
	SPI3_InitStruct.SPI_Mode = SPI_Mode_Master;							//Master mode
	SPI3_InitStruct.SPI_NSS = SPI_NSS_Soft;								//Software managed Slave Select to leave pin available
	SPI3_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	//Full duplex over 2 data lines
	SPI3_InitStruct.SPI_CRCPolynomial = 0x1;							//Not using this, but needs to be >= 0x1
	SPI_Init(SPI3, &SPI3_InitStruct);

	SPI_CalculateCRC(SPI3, DISABLE);									//Don't calculate CRC
	SPI_Cmd(SPI3, ENABLE);												//Enable SPI3
*/
/*	End SPI config & init	*/

//	UIInit();

//	dacInit();
//	adcInit();
//	NVICTimer2Init();
//	NVICTimer5Init();
//	Timer2Init();
//	Timer5Init();

//	BPMUpdate(sequencer.BPM);

//	RingBufferInit();

	CoInitOS();
	CoCreateTask ((FUNCPtr)task_a,(void *)0,0,&taskA_stk[128-1],128);
	CoCreateTask ((FUNCPtr)task_b,(void *)0,1,&taskB_stk[128-1],128);
	CoCreateTask ((FUNCPtr)leds ,(void *)0,2,&led_stk[128-1] ,128);
		uint8_t i,debug;
//		uint16_t i;
//		uint16_t bpm = 60;

	CoStartOS();
		for(i=0;i<0xff;i++)



	for(;;);

/*		for(i=0;i<100;i++)
		{
			debug = SPI_PIC_Receive();
			if(!debug)

			{
				SPI_LED_Send(i);
			}
			else
			{
				SPI_LED_Send(~i);
			}
			delay_nms(100);
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
