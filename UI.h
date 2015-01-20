#ifndef UI_H
#define UI_H

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "SPI.h"
#include "menu.h"

// Defines
//#define UI_GPIO_PORT		GPIOE
//#define UI_GPIO_PORT_PERIPH	RCC_AHB1Periph_GPIOE
//#define UI_LED_CLOCK		GPIO_Pin_0
//#define UI_LED_DATA			GPIO_Pin_1
//#define UI_LED_LATCH		GPIO_Pin_2
//#define UI_BUTT_PLAY		GPIO_Pin_3
//#define UI_BUTT_DATA		GPIO_Pin_4
//#define UI_BUTT_CLOCK		GPIO_Pin_5
//#define UI_BUTT_LOAD		GPIO_Pin_6

// Function prototypes
// Initialization functions
//void UIInit(void);				// Main UI initialization
//void UILEDInit(void);			// LED initialization
//void UIButtonInit(void);		// Button initialization
//void UIPlayInit(void);			// Play button init

uint8_t UIGetButton	(uint8_t nr);
int8_t 	UIGetRotary	(uint8_t nr);

void UIUpdateButton(uint8_t nr);
void UIUpdateButtons(void);
void UIUpdateRotary(uint8_t nr);

typedef struct {
	uint32_t	buttons;
	int8_t		rotary1;
	int8_t		rotary2;
	int8_t		rotary3;
	int8_t		rotary4;
	int8_t		rotary5;
	int8_t		rotary6;
	int8_t		rotary7;
	int8_t		rotary8;
	int8_t		rotary9;
	int8_t		rotary10;
	int8_t		rotary11;
} UIInput_Typedef;

UIInput_Typedef uiInput;


#define ROTARY_DRUM_LEVEL_1	uiInput.rotary1
#define ROTARY_DRUM_TONE_1	uiInput.rotary2

#define ROTARY_DRUM_LEVEL_2	uiInput.rotary3
#define ROTARY_DRUM_TONE_2	uiInput.rotary4

#define ROTARY_DRUM_LEVEL_3	uiInput.rotary5
#define ROTARY_DRUM_TONE_3	uiInput.rotary6

#define ROTARY_DRUM_LEVEL_4	uiInput.rotary7
#define ROTARY_DRUM_TONE_4	uiInput.rotary8

#define ROTARY_MENU			uiInput.rotary9

#define ROTARY_FX_1			uiInput.rotary10
#define ROTARY_FX_2			uiInput.rotary11

#define BUTTON_SEQ_1		(uiInput.buttons & (1<<BUTTON_SEQ_1_NR))
#define BUTTON_SEQ_2		(uiInput.buttons & (1<<BUTTON_SEQ_2_NR))
#define BUTTON_SEQ_3		(uiInput.buttons & (1<<BUTTON_SEQ_3_NR))
#define BUTTON_SEQ_4		(uiInput.buttons & (1<<BUTTON_SEQ_4_NR))
#define BUTTON_SEQ_5		(uiInput.buttons & (1<<BUTTON_SEQ_5_NR))
#define BUTTON_SEQ_6		(uiInput.buttons & (1<<BUTTON_SEQ_6_NR))
#define BUTTON_SEQ_7		(uiInput.buttons & (1<<BUTTON_SEQ_7_NR))
#define BUTTON_SEQ_8		(uiInput.buttons & (1<<BUTTON_SEQ_8_NR))
#define BUTTON_SEQ_9		(uiInput.buttons & (1<<BUTTON_SEQ_9_NR))
#define BUTTON_SEQ_10		(uiInput.buttons & (1<<BUTTON_SEQ_10_NR))
#define BUTTON_SEQ_11		(uiInput.buttons & (1<<BUTTON_SEQ_11_NR))
#define BUTTON_SEQ_12		(uiInput.buttons & (1<<BUTTON_SEQ_12_NR))
#define BUTTON_SEQ_13		(uiInput.buttons & (1<<BUTTON_SEQ_13_NR))
#define BUTTON_SEQ_14		(uiInput.buttons & (1<<BUTTON_SEQ_14_NR))
#define BUTTON_SEQ_15		(uiInput.buttons & (1<<BUTTON_SEQ_15_NR))
#define BUTTON_SEQ_16		(uiInput.buttons & (1<<BUTTON_SEQ_16_NR))

#define BUTTON_DRUM_1		(uiInput.buttons & (1<<BUTTON_DRUM_1_NR))
#define BUTTON_DRUM_2		(uiInput.buttons & (1<<BUTTON_DRUM_2_NR))
#define BUTTON_DRUM_3		(uiInput.buttons & (1<<BUTTON_DRUM_3_NR))
#define BUTTON_DRUM_4		(uiInput.buttons & (1<<BUTTON_DRUM_4_NR))
#define BUTTON_DRUM_5		(uiInput.buttons & (1<<BUTTON_DRUM_5_NR))
#define BUTTON_DRUM_6		(uiInput.buttons & (1<<BUTTON_DRUM_6_NR))

#define BUTTON_PLAY			(uiInput.buttons & (1<<BUTTON_PLAY_NR))
#define BUTTON_CLEAR		(uiInput.buttons & (1<<BUTTON_CLEAR_NR))
#define BUTTON_SHIFT		(uiInput.buttons & (1<<BUTTON_SHIFT_NR))
#define BUTTON_PATT_SEL		(uiInput.buttons & (1<<BUTTON_PATT_SELs_NR))
#define BUTTON_PATT_LEN		(uiInput.buttons & (1<<BUTTON_PATT_LEN_NR))

#define BUTTON_FX_ONOFF		(uiInput.buttons & (1<<BUTTON_FX_ONOFF_NR))
#define BUTTON_MENU_OK		(uiInput.buttons & (1<<BUTTON_MENU_OK_NR))
#define BUTTON_MENU_BACK	(uiInput.buttons & (1<<BUTTON_MENU_BACK_NR))
#define BUTTON_EXTRA_1		(uiInput.buttons & (1<<BUTTON_EXTRA_1_NR))
#define BUTTON_EXTRA_2		(uiInput.buttons & (1<<BUTTON_EXTRA_2_NR))

#define BUTTON_SEQ_1_NR		0
#define BUTTON_SEQ_2_NR		1
#define BUTTON_SEQ_3_NR		2
#define BUTTON_SEQ_4_NR		3
#define BUTTON_SEQ_5_NR		4
#define BUTTON_SEQ_6_NR		5
#define BUTTON_SEQ_7_NR		6
#define BUTTON_SEQ_8_NR		7

#define BUTTON_SEQ_9_NR		8
#define BUTTON_SEQ_10_NR	9
#define BUTTON_SEQ_11_NR	10
#define BUTTON_SEQ_12_NR	11
#define BUTTON_SEQ_13_NR	12
#define BUTTON_SEQ_14_NR	13
#define BUTTON_SEQ_15_NR	14
#define BUTTON_SEQ_16_NR	15

#define BUTTON_DRUM_1_NR	16
#define BUTTON_DRUM_2_NR	17
#define BUTTON_DRUM_3_NR	18
#define BUTTON_DRUM_4_NR	19
#define BUTTON_DRUM_5_NR	20
#define BUTTON_DRUM_6_NR	21

#define BUTTON_PLAY_NR		22
#define BUTTON_CLEAR_NR		23
#define BUTTON_SHIFT_NR		24
#define BUTTON_PATT_SEL_NR	25
#define BUTTON_PATT_LEN_NR	26

#define BUTTON_FX_ONOFF_NR	27
#define BUTTON_MENU_OK_NR	28
#define BUTTON_MENU_BACK_NR	29
#define BUTTON_EXTRA_1_NR	30
#define BUTTON_EXTRA_2_NR	31


// User functions
//uint16_t UIButtonRead();		// UI button read function
//void UILed(uint16_t value);		// Led write function
//uint8_t UIPlayRead(void);		// Play button read

#endif // UI_H
