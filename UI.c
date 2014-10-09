#include "UI.h"

void UIInit(void) {
	UILEDInit();
	UIButtonInit();
	UIPlayInit();
}

void UIPlayInit(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitStructure.GPIO_OType 				= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	 			= GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed 				= GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin 				= UI_BUTT_PLAY;
	GPIO_InitStructure.GPIO_Mode 				= GPIO_Mode_IN;					// Play button
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void UILEDInit(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitStructure.GPIO_OType 				= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	 			= GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed 				= GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin 				= UI_LED_CLOCK | UI_LED_DATA | UI_LED_LATCH;
	GPIO_InitStructure.GPIO_Mode 				= GPIO_Mode_OUT;				// Data in, clocks out
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void UIButtonInit(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitStructure.GPIO_OType 				= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	 			= GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed 				= GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin 				= UI_BUTT_DATA;					// Data in
	GPIO_InitStructure.GPIO_Mode 				= GPIO_Mode_IN;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin 				= UI_BUTT_CLOCK | UI_BUTT_LOAD;	// Clock & Load
	GPIO_InitStructure.GPIO_Mode 				= GPIO_Mode_OUT;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void UILed(uint16_t value) {
	uint8_t counter = 0x00;
	uint8_t data	= 0x00;
	for (counter = 0; counter < 16; counter ++) {
		data 	= value & 0x01;
		value >>= 1;
		GPIO_WriteBit(GPIOE, UI_LED_DATA, data);
		GPIO_WriteBit(GPIOE, UI_LED_CLOCK, SET);		// Clock
		GPIO_WriteBit(GPIOE, UI_LED_CLOCK, RESET);		// Pulse
	}
	GPIO_WriteBit(GPIOE, UI_LED_LATCH, SET);
	GPIO_WriteBit(GPIOE, UI_LED_LATCH, RESET);
}

uint16_t UIButtonRead(void) {
	static uint16_t buttonHistory 	= 0x00;
	uint16_t returnValue 			= 0x00;

	uint8_t counter = 0;
	for (counter = 0; counter < 16; counter++) {
		buttonHistory = 1;		// Bla
	}

	return returnValue;
}
