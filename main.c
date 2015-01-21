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

// DELETE ME vv
static void DEBUG_SPI_LED(uint32_t data) {
		uint16_t dummy;
		uint8_t data1 = ((data & 0xFF000000)>>24);
		uint8_t data2 = ((data & 0x00FF0000)>>16);
		uint8_t data3 = ((data & 0x0000FF00)>>8);
		uint8_t data4 = ((data & 0x000000FF)>>0);

		while(!(SPI3->SR & SPI_I2S_FLAG_TXE));								//wait until SPI3 is available
		while(SPI3->SR & SPI_I2S_FLAG_BSY);

		if(SPI3->CR1 & SPI_CPHA_2Edge)
		{
			SPI3->CR1 &= (uint16_t)~((uint16_t)SPI_CR1_SPE);
			SPI3->CR1 &= (uint16_t)~((uint16_t)SPI_CPHA_2Edge);
			SPI3->CR1 |= SPI_CR1_SPE;
		}

		SPI3->DR = data4;
		while(!(SPI3->SR & SPI_I2S_FLAG_TXE));
		while(SPI3->SR & SPI_I2S_FLAG_BSY);

		SPI3->DR = data3;
		while(!(SPI3->SR & SPI_I2S_FLAG_TXE));
		while(SPI3->SR & SPI_I2S_FLAG_BSY);

		SPI3->DR = data2;
		while(!(SPI3->SR & SPI_I2S_FLAG_TXE));
		while(SPI3->SR & SPI_I2S_FLAG_BSY);

		SPI3->DR = data1;
		while(!(SPI3->SR & SPI_I2S_FLAG_TXE));
		while(SPI3->SR & SPI_I2S_FLAG_BSY);

	//	SPI3->DR = ~data;													//send data (
	//	while(!(SPI3->SR & SPI_I2S_FLAG_TXE));								//wait until finished sending data
	//	while(SPI3->SR & SPI_I2S_FLAG_BSY);									//
	//	SPI3->DR = dataLSB;													//send LSByte
	//	while(!(SPI3->SR & SPI_I2S_FLAG_TXE));								//wait until finished sending data
	//	while(SPI3->SR & SPI_I2S_FLAG_BSY);									//

		GPIO_SetBits(GPIOC, LED_SS);										// Latch Data
		delay_nms(1);
		GPIO_ResetBits(GPIOC, LED_SS);										// Delatch Data
		delay_nms(1);

		dummy = SPI3->DR;
	}
// DELETE ME ^^

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

	MenuSetup();

	uint8_t rotaryNr			= 1;
	uint8_t runs				= 0;
	BPMUpdate(150);


//	while (1) {
//		// DELETE ME AFTER TESTING
//
//		DEBUG_SPI_LED(0x00000001);
//		delay_nms(100);
//		DEBUG_SPI_LED(0x00000000);
//		delay_nms(100);
//		DEBUG_SPI_LED(0x00000001);
//		delay_nms(100);
//		DEBUG_SPI_LED(0x00000000);
//		delay_nms(100);
//		DEBUG_SPI_LED(0x00000001);
//		delay_nms(100);
//		DEBUG_SPI_LED(0x00000000);
//		delay_nms(100);
//
//		char i;
//		for (i = 0; i < 32; i++) {
//			DEBUG_SPI_LED(1<<i);
//			delay_nms(100);
//		}
//
//		// END OF DELETION
//	}

	while (1) {

//		if (runs % 3 == 0) {			// RUNS (30 ms) * 17 = 510 ms total
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
//		}
//		delay_nms(10);
//		runs ++;
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
