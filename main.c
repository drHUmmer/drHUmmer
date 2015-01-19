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

	// Random button init (Demo 1)
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//	GPIO_Init(GPIOE, &GPIO_InitStruct);

//	UIInit();

	dacInit();
//	adcInit();
	NVICTimer2Init();
	NVICTimer5Init();
	Timer2Init();
	Timer5Init();

	BPMUpdate(sequencer.BPM);

	RingBufferInit();

#ifndef USE_OS
	SysTick_Init();
	UART2_init(57600);

	LCD_Init();
	LCD_Clear(ColourConverterDec(Black));

	FXsettings.fx1		= NONE;
	FXsettings.fx2		= NONE;
	FXsettings.bcBits 	= 5;
	FXsettings.dsFreq 	= 1000;
	FXsettings.lpfFreq 	= 1000;
	FXsettings.hpfFreq 	= 1000;

	sequencer.instr0.level 	= 100;
	sequencer.instr1.level 	= 100;
	sequencer.instr2.level 	= 100;
	sequencer.instr3.level 	= 5;

	sequencer.instr0.tone 	= 1;
	sequencer.instr1.tone 	= 1;
	sequencer.instr2.tone 	= 1;
	sequencer.instr3.tone 	= 1;

	settings.filterbookmarks.bookmark1.fx1_filter 	= DS;
	settings.filterbookmarks.bookmark1.fx1_value 	= 400;
	settings.filterbookmarks.bookmark1.fx2_filter 	= BC;
	settings.filterbookmarks.bookmark1.fx2_value 	= 8;

	settings.filterbookmarks.bookmark2.fx1_filter 	= DS;
	settings.filterbookmarks.bookmark2.fx1_value 	= 10000;
	settings.filterbookmarks.bookmark2.fx2_filter 	= BC;
	settings.filterbookmarks.bookmark2.fx2_value 	= 3;

	MenuSetup();

	settings.midi.channel 		= 0;

	gui.infobars.info1.setting = INFO_BPM;
	gui.infobars.info2.setting = INFO_INSTRUMENT;

	FXsettings.fx1				= NONE;
	FXsettings.fx2				= NONE;
	FXsettings.fxEnable			= 1;

	uint8_t rotaryNr			= 1;
	uint8_t runs				= 0;
	BPMUpdate(150);
	while (1) {

		if (runs % 3 == 0) {			// RUNS (30 ms) * 17 = 510 ms total
			if (rotaryNr < 12) {			// 1 2 3 ... 9 10 11
				UIUpdateRotary(rotaryNr);
				rotaryNr ++;
			} else if (rotaryNr < 16) {		// 12 13 14 15
				UIUpdateButton(rotaryNr - 11);
				rotaryNr ++;
			} else if (rotaryNr < 17) {		// 16
				UIhandler();
				rotaryNr++;
			} else {						// 17
				Menu_Update_handler();
				rotaryNr = 1;
			}
		}

		delay_nms(10);

		runs ++;
	}

	while(1) {};
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
