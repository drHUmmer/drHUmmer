#ifndef UI_H
#define UI_H

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

// Defines
#define UI_GPIO_PORT		GPIOE
#define UI_GPIO_PORT_PERIPH	RCC_AHB1Periph_GPIOE
#define UI_LED_CLOCK		GPIO_Pin_0
#define UI_LED_DATA			GPIO_Pin_1
#define UI_LED_LATCH		GPIO_Pin_2
#define UI_BUTT_PLAY		GPIO_Pin_3
#define UI_BUTT_DATA		GPIO_Pin_4
#define UI_BUTT_CLOCK		GPIO_Pin_5
#define UI_BUTT_LOAD		GPIO_Pin_6

// Function prototypes
// Initialization functions
void UIInit(void);				// Main UI initialization
void UILEDInit(void);			// LED initialization
void UIButtonInit(void);		// Button initialization
void UIPlayInit(void);			// Play button init

// User functions
uint16_t UIButtonRead();		// UI button read function
void UILed(uint16_t value);		// Led write function
uint8_t UIPlayRead(void);		// Play button read

#endif // UI_H
