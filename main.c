#include "main.h"

/*VARIABLES*/
void task_a(void);
void task_b(void);
extern IIRfilter_t testFilter;
extern uint16_t filterStatus;

#ifdef FILTER_DEMO
extern uint8_t filterDemo;
#endif
void leds(void);

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
#ifdef FILTER_DEMO
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
#endif


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

	UIInit();

	dacInit();
	adcInit();
	NVICTimer2Init();
	NVICTimer5Init();
	Timer2Init();
	Timer5Init();

	BPMUpdate(sequencer.BPM);

	RingBufferInit();

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

	FXsettings.fx1	= NONE;
	FXsettings.fx2	= NONE;
	FXsettings.bcBits = 3;
	FXsettings.dsFreq = 800;
	FXsettings.lpfFreq = 3000;
	FXsettings.hpfFreq = 150;

	while (1) {
		uint16_t buttonvalue = UIButtonRead();
		if (buttonvalue & 0x1000) {
			buttonz.buttonOK = 1;
			GPIO_SetBits(GPIOD, GPIO_Pin_12);
		}

		if (buttonvalue & 0x2000) {
			buttonz.buttonBack = 1;
			GPIO_SetBits(GPIOD, GPIO_Pin_13);
		}

		if (buttonvalue & 0x4000) {
			GPIO_SetBits(GPIOD, GPIO_Pin_14);
			buttonz.rotaryValue = 1;
		}

		if (buttonvalue & 0x8000) {
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

	#ifdef FILTER_DEMO	//quick 'n dirty user button read, no debouncing
			uint8_t userButt=0;

			userButt = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
			if(userButt)
			{
				filterDemo++;
			}
	#endif

	delay_nms(100);
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
