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

	Delayms(2);
	SPI_PIC_Send (PIC_GET_BUTTON, 0, nr);		// Send
	Delayms(2);									// Wait (process)
	return SPI_PIC_Receive();					// Receive
}

int8_t UIGetRotary(uint8_t nr) {
	if (nr < 1 || nr > 11)						// Range check
		return 0;

	Delayms(4);
	SPI_PIC_Send(PIC_GET_ROTARY, 0, nr);		// Send
	Delayms(4);									// Wait (process)
	return SPI_PIC_Receive();					// Receive
}

void UIUpdateButton(uint8_t nr) {
//	uiInput.buttons |= (UIGetButton(nr) << ((nr - 1) * 8));

	switch (nr) {		// Alternate solution //
	case 1:	uiInput.buttons |= (UIGetButton(nr) << 0);	break;
	case 2:	uiInput.buttons |= (UIGetButton(nr) << 8);	break;
	case 3:	uiInput.buttons |= (UIGetButton(nr) << 16);	break;
	case 4:	uiInput.buttons |= (UIGetButton(nr) << 24);	break;
	}
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
