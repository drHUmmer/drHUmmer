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

	UIInit();

	dacInit();
//	adcInit();
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

//	buttonz.buttonBack 	= 0;
//	buttonz.buttonOK 	= 0;
//	buttonz.rotaryValue	= 0;

	LCD_Init();
	LCD_Clear(ColourConverterDec(Black));

	FXsettings.fx1	= NONE;
	FXsettings.fx2	= NONE;
	FXsettings.bcBits = 3;
	FXsettings.dsFreq = 800;
	FXsettings.lpfFreq = 900;		// 3000
	FXsettings.hpfFreq = 1000;		// 15000

	sequencer.instr0.level 	= 100;
	sequencer.instr1.level 	= 100;
	sequencer.instr2.level 	= 100;
	sequencer.instr3.level 	= 100;

	sequencer.instr0.tone 	= 1;
	sequencer.instr1.tone 	= 1;
	sequencer.instr2.tone 	= 1;
	sequencer.instr3.tone 	= 1;

	settings.filterbookmarks.bookmark1.fx1_filter 	= HPF;
	settings.filterbookmarks.bookmark1.fx1_value 	= 12345;
	settings.filterbookmarks.bookmark1.fx2_filter 	= LPF;
	settings.filterbookmarks.bookmark1.fx2_value 	= 54321;

	settings.filterbookmarks.bookmark2.fx1_filter 	= DS;
	settings.filterbookmarks.bookmark2.fx1_value 	= 10101;
	settings.filterbookmarks.bookmark2.fx2_filter 	= BC;
	settings.filterbookmarks.bookmark2.fx2_value 	= 99;

	MenuSetup();

	uint16_t sequencerButtons 	= 0;

	settings.midi.channel 		= 0;

	gui.infobars.info1.setting = INFO_PATT_LIVE_MODE;
	gui.infobars.info2.setting = INFO_PATT_LIVE_MODE;

	FXsettings.fx1				= LPF;
	FXsettings.fx2				= BC;

	while (1) {
//		uint16_t buttonvalue = UIButtonRead();
//		if (buttonvalue & 0x1000) {
//			buttonz.buttonOK = 1;
//			GPIO_SetBits(GPIOD, GPIO_Pin_12);
//		}
//
//		if (buttonvalue & 0x2000) {
//			buttonz.buttonBack = 1;
//			GPIO_SetBits(GPIOD, GPIO_Pin_13);
//		}
//
//		if (buttonvalue & 0x4000) {
//			GPIO_SetBits(GPIOD, GPIO_Pin_14);
//			buttonz.rotaryValue = 1;
//		}
//
//		if (buttonvalue & 0x8000) {
//			GPIO_SetBits(GPIOD, GPIO_Pin_15);
//			buttonz.rotaryValue = -1;
//		}

		// BLUE BUTTON
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
			sequencer.instrID ++;
			sequencer.instrID %= 6;
		}

		// Rotary get
		SPI_PIC_Send(PIC_GET_ROTARY, 0, PIC_ROTARY_1);
		delay_1ms();
		buttonz.rotaryValue = SPI_PIC_Receive();

		// Button get
		sequencerButtons = UIButtonRead();

		buttonz.buttonOK = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0);
		buttonz.buttonBack = 0;

		switch (sequencer.instrID) {
		case 0: sequencer.bassdrum.sequence ^= sequencerButtons; 	break;	// A1
		case 1: sequencer.snaredrum.sequence ^= sequencerButtons;	break;	// A2
		case 2: sequencer.instr0.sequence ^= sequencerButtons;		break;	// D1
		case 3: sequencer.instr1.sequence ^= sequencerButtons;		break;	// D2
		case 4: sequencer.instr2.sequence ^= sequencerButtons;		break;	// D3
		case 5: sequencer.instr3.sequence ^= sequencerButtons;		break;	// D4
		}

		switch (sequencer.instrID) {
		case 0: SPI_LED_Send(sequencer.bassdrum.sequence);			break;	// A1
		case 1: SPI_LED_Send(sequencer.snaredrum.sequence);			break;	// A2
		case 2: SPI_LED_Send(sequencer.instr0.sequence);			break;	// D1
		case 3: SPI_LED_Send(sequencer.instr1.sequence);			break;	// D2
		case 4: SPI_LED_Send(sequencer.instr2.sequence);			break;	// D3
		case 5: SPI_LED_Send(sequencer.instr3.sequence);			break;	// D4
		}

		Menu_Update_handler();
		delay_nms(100);

		// TONE
//		sequencer.instr0.tone += 1;
//		if (sequencer.instr0.tone > 200)
//			sequencer.instr0.tone = 0;
//
//		sequencer.instr1.tone -= 10;
//		if (sequencer.instr1.tone < 0)
//			sequencer.instr1.tone = 200;
//
//		sequencer.instr2.tone = 200 - sequencer.instr0.tone;
//		sequencer.instr3.tone = 200 - sequencer.instr1.tone;
//
//		// LEVEL
//		sequencer.instr0.level += 1;
//		if (sequencer.instr0.level > 100)
//			sequencer.instr0.level = 0;
//
//		sequencer.instr1.level -= 5;
//		if (sequencer.instr1.level > 100)
//			sequencer.instr1.level = 100;
//
//		sequencer.instr2.level = 100 - sequencer.instr0.level;
//		sequencer.instr3.level = 100 - sequencer.instr1.level;
	}

	while(1) {};

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
