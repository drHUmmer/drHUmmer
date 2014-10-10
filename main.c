#include "main.h"

int main(void)
{
	PLLInit();
	UIInit();

	uint16_t counter = 0;
	uint32_t delay  = 10000;
	while(1)
    {
//		UILed(0x000F);
//		for (delay = 16000000; delay > 0; delay--);
//
//		UILed(0x00F0);
//		for (delay = 16000000; delay > 0; delay--);
//
//		UILed(0x0F00);
//		for (delay = 16000000; delay > 0; delay--);
//
//		UILed(0xF000);
//		for (delay = 16000000; delay > 0; delay--);
//
//		// Rond
//		for (counter = 0; counter < 16; counter ++) {
//			UILed((1 << counter));
//			for (delay = 4000000; delay > 0; delay--);
//		}



		uint16_t valueRead = UIPlayRead();

//		UILed(valueRead);
//		for (delay = 4000000; delay > 0; delay--);
    }
}
