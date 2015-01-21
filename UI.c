#include "UI.h"
#include "tm_stm32f4_delay.h"

//void UIInit(void) {
//	UILEDInit();
//	UIButtonInit();
//	UIPlayInit();
//}

uint8_t UIGetButton(uint8_t nr) {
	if (nr < 1 || nr > 4)						// Range check
		return 0;

	Delayms(1);
	SPI_PIC_Send (PIC_GET_BUTTON, 0, nr);		// Send
	Delayms(1);									// Wait (process)
	return SPI_PIC_Receive();					// Receive
}

int8_t UIGetRotary(uint8_t nr) {
	if (nr < 1 || nr > 11)						// Range check
		return 0;

	Delayms(1);
	SPI_PIC_Send(PIC_GET_ROTARY, 0, nr);		// Send
	Delayms(1);									// Wait (process)
	return SPI_PIC_Receive();					// Receive
}

void UIUpdateButton(uint8_t nr) {
	uiInput.buttons |= (UIGetButton(nr) << (nr - 1) * 8);

//	switch (nr) {		// Alternate solution //
//	case 1:	uiInput.buttons |= (UIGetButton(nr) << 0);	break;
//	case 2:	uiInput.buttons |= (UIGetButton(nr) << 8);	break;
//	case 3:	uiInput.buttons |= (UIGetButton(nr) << 16);	break;
//	case 4:	uiInput.buttons |= (UIGetButton(nr) << 24);	break;
//	}
}

void UIUpdateButtons(void) {
	UIUpdateButton(1);
	UIUpdateButton(2);
	UIUpdateButton(3);
	UIUpdateButton(4);
}

void UIUpdateRotary(uint8_t nr) {
	if (nr < 1 || nr > 11)				// Range check
		return;

	*(&uiInput.rotary1 + (nr - 1)) = UIGetRotary(nr);
}

//uint8_t UIPlayRead(void) {
//	static 	uint8_t buttonHistory	= 0x00;
//			uint8_t buttonValue 	= 0x00;
//			uint8_t returnValue		= 0x00;
//
//	buttonValue = GPIO_ReadInputDataBit(UI_GPIO_PORT, UI_BUTT_PLAY);
//
//	if ((buttonValue) != 0x00) {
//		if ((buttonHistory) == 0x00) {
//			returnValue = 0x01;
//		}
//	}
//
//	buttonHistory = buttonValue;
//	return returnValue;
//}
//
//void UIPlayInit(void) {
//	GPIO_InitTypeDef GPIO_InitStructure;
//	RCC_AHB1PeriphClockCmd(UI_GPIO_PORT_PERIPH, ENABLE);
//
//	GPIO_InitStructure.GPIO_OType 				= GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd	 			= GPIO_PuPd_DOWN;
//	GPIO_InitStructure.GPIO_Speed 				= GPIO_Speed_25MHz;
//
//	GPIO_InitStructure.GPIO_Pin 				= UI_BUTT_PLAY;
//	GPIO_InitStructure.GPIO_Mode 				= GPIO_Mode_IN;					// Play button
//	GPIO_Init(UI_GPIO_PORT, &GPIO_InitStructure);
//}
//
//void UILEDInit(void) {
//	GPIO_InitTypeDef GPIO_InitStructure;
//	RCC_AHB1PeriphClockCmd(UI_GPIO_PORT_PERIPH, ENABLE);
//
//	GPIO_InitStructure.GPIO_OType 				= GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd	 			= GPIO_PuPd_DOWN;
//	GPIO_InitStructure.GPIO_Speed 				= GPIO_Speed_25MHz;
//
//	GPIO_InitStructure.GPIO_Pin 				= UI_LED_CLOCK | UI_LED_DATA | UI_LED_LATCH;
//	GPIO_InitStructure.GPIO_Mode 				= GPIO_Mode_OUT;				// Data in, clocks out
//	GPIO_Init(UI_GPIO_PORT, &GPIO_InitStructure);
//}
//
//void UIButtonInit(void) {
//	GPIO_InitTypeDef GPIO_InitStructure;
//	RCC_AHB1PeriphClockCmd(UI_GPIO_PORT_PERIPH, ENABLE);
//
//	GPIO_InitStructure.GPIO_OType 				= GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd	 			= GPIO_PuPd_DOWN;
//	GPIO_InitStructure.GPIO_Speed 				= GPIO_Speed_25MHz;
//
//	GPIO_InitStructure.GPIO_Pin 				= UI_BUTT_DATA;					// Data in
//	GPIO_InitStructure.GPIO_Mode 				= GPIO_Mode_IN;
//	GPIO_Init(UI_GPIO_PORT, &GPIO_InitStructure);
//
//	GPIO_InitStructure.GPIO_Pin 				= UI_BUTT_CLOCK | UI_BUTT_LOAD;	// Clock & Load
//	GPIO_InitStructure.GPIO_Mode 				= GPIO_Mode_OUT;
//	GPIO_Init(UI_GPIO_PORT, &GPIO_InitStructure);
//
//	GPIO_WriteBit(UI_GPIO_PORT, UI_BUTT_CLOCK, Bit_RESET);
//	GPIO_WriteBit(UI_GPIO_PORT, UI_BUTT_LOAD, Bit_RESET);
//}
//
//void UILed(uint16_t value) {
//	uint8_t counter = 0x00;
//	uint8_t data	= 0x00;
////	uint8_t delay	= 0x00;
//
//	for (counter = 0; counter < 16; counter ++) {
//		data 	= !!(value & (1 << (15 - counter)));			// Check if the a bit is set or not
//
//		// Shift data to shift register
//		if (data)
//			GPIO_WriteBit(UI_GPIO_PORT, UI_LED_DATA, Bit_SET);
//		else
//			GPIO_WriteBit(UI_GPIO_PORT, UI_LED_DATA, Bit_RESET);
//
//		//for (delay = 200; delay > 0; delay --);
//
//		// Clock pulse
//		GPIO_WriteBit(UI_GPIO_PORT, UI_LED_CLOCK, Bit_SET);
//		//for (delay = 200; delay > 0; delay --);
//		GPIO_WriteBit(UI_GPIO_PORT, UI_LED_CLOCK, Bit_RESET);
//	}
//	// Toggle latch
//	GPIO_WriteBit(UI_GPIO_PORT, UI_LED_LATCH, Bit_SET);			// Latch the newly
//	//for (delay = 200; delay > 0; delay --);
//	GPIO_WriteBit(UI_GPIO_PORT, UI_LED_LATCH, Bit_RESET);		// send data to output
//
//	return;
//}
//
//uint16_t UIButtonRead(void) {
//	static 	uint16_t buttonHistory 	= 0x00;				// Store previous button value
//			uint16_t buttonValue	= 0x00;				// Current button value
//			uint16_t returnValue 	= 0x00;				// Return value
//			uint16_t delay			= 200;
//
//			uint8_t	 counter 		= 0x00;				// Small counter
//			uint16_t mask			= 0x01;				// Mask necessary for checks
//
//	GPIO_WriteBit(UI_GPIO_PORT, UI_BUTT_LOAD, Bit_SET);	// Allow shifting bits
//	for (delay = 20; delay > 0; delay --);
//
//	for (counter = 0; counter < 16; counter++) {		// Shift data in
//		mask = (15 - counter);
//		buttonValue |= (GPIO_ReadInputDataBit(UI_GPIO_PORT, UI_BUTT_DATA) << mask);
//
//		// Clock pulse
//		GPIO_WriteBit(UI_GPIO_PORT, UI_BUTT_CLOCK, Bit_SET);
//		GPIO_WriteBit(UI_GPIO_PORT, UI_BUTT_CLOCK, Bit_RESET);
//	}
//	GPIO_WriteBit(UI_GPIO_PORT, UI_BUTT_LOAD, Bit_RESET);// Disable shifting bits
//
//	for (counter = 0; counter < 16; counter++) {
//		mask = 1 << (15 - counter);
//		if ((buttonValue & mask) != 0x00) {				// Check if button value is 1
//			if ((buttonHistory & mask) == 0x00) {		// Check if history value is 0
//				returnValue |= mask;					// Add value to return value
//			}
//		}
//	}
//
//	buttonHistory = buttonValue;						// Update the history values
//	return returnValue;									// Return the newly pressed buttons
//}
