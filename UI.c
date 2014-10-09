#include "UI.h"

void UIInit(void) {
	UILEDInit();
	UIButtonInit();
	UIPlayInit();
}

void UIPlayInit(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(UI_GPIO_PORT_PERIPH, ENABLE);

	GPIO_InitStructure.GPIO_OType 				= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	 			= GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed 				= GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin 				= UI_BUTT_PLAY;
	GPIO_InitStructure.GPIO_Mode 				= GPIO_Mode_IN;					// Play button
	GPIO_Init(UI_GPIO_PORT, &GPIO_InitStructure);
}

void UILEDInit(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(UI_GPIO_PORT_PERIPH, ENABLE);

	GPIO_InitStructure.GPIO_OType 				= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	 			= GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed 				= GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin 				= UI_LED_CLOCK | UI_LED_DATA | UI_LED_LATCH;
	GPIO_InitStructure.GPIO_Mode 				= GPIO_Mode_OUT;				// Data in, clocks out
	GPIO_Init(UI_GPIO_PORT, &GPIO_InitStructure);
}

void UIButtonInit(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(UI_GPIO_PORT_PERIPH, ENABLE);

	GPIO_InitStructure.GPIO_OType 				= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	 			= GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed 				= GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin 				= UI_BUTT_DATA;					// Data in
	GPIO_InitStructure.GPIO_Mode 				= GPIO_Mode_IN;
	GPIO_Init(UI_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin 				= UI_BUTT_CLOCK | UI_BUTT_LOAD;	// Clock & Load
	GPIO_InitStructure.GPIO_Mode 				= GPIO_Mode_OUT;
	GPIO_Init(UI_GPIO_PORT, &GPIO_InitStructure);
}

void UILed(uint16_t value) {
	uint8_t counter = 0x00;
	uint8_t data	= 0x00;

	for (counter = 0; counter < 16; counter ++) {
		data 	= value & 0x01;							// Check if the a bit is set or not
		value >>= 1;									// Shift data to the right
		GPIO_WriteBit(UI_GPIO_PORT, UI_LED_DATA, data);		// Set data according to value
		GPIO_WriteBit(UI_GPIO_PORT, UI_LED_CLOCK, SET);		// Clock
		GPIO_WriteBit(UI_GPIO_PORT, UI_LED_CLOCK, RESET);		// Pulse
	}
	GPIO_WriteBit(UI_GPIO_PORT, UI_LED_LATCH, SET);			// Latch the newly
	GPIO_WriteBit(UI_GPIO_PORT, UI_LED_LATCH, RESET);			// send data to output
}

uint16_t UIButtonRead(void) {
	static 	uint16_t buttonHistory 	= 0x00;				// Store previous button value
			uint16_t buttonValue	= 0x00;				// Current button value
			uint16_t returnValue 	= 0x00;				// Return value

			uint8_t	 counter 		= 0x00;				// Small counter
			uint16_t mask			= 0x01;				// Mask necessary for checks

	GPIO_WriteBit(UI_GPIO_PORT, UI_BUTT_LOAD, SET);			// Allow shifting bits
	for (counter = 0; counter < 16; counter++) {		// Shift data in
		buttonValue |= UI_BUTT_DATA;
		buttonValue <<= 1;
	}
	GPIO_WriteBit(UI_GPIO_PORT, UI_BUTT_LOAD, RESET);			// Disable shifting bits

	for (counter = 0; counter < 16; counter++) {
		if ((buttonValue && mask) != 0x00) {			// Check if button value is 1
			if ((buttonHistory && mask) == 0x00) {		// Check if history value is 0
				returnValue |= mask;					// Add value to return value
			}
		}
		mask <<= 1;										// Shift the mask
	}

	buttonHistory = buttonValue;						// Update the history values
	return returnValue;									// Return the newly pressed buttons
}
