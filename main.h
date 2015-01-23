#ifndef MAIN_HEADER
#define MAIN_HEADER

//#define DEBUG	// uncomment this line for debug mode
#define USE_OS

#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"
#include "ADC.h"
#include "DAC.h"
#include "PLL.h"
#include "UART.h"
#include "interrupt.h"
#include "timers.h"
#include "UI.h"
#include "UIhandler.h"

#include "ILI9325.h"
#include "menu.h"
#include "LCDitems.h"
#include "menuHandlers.h"
#include "menuScreens.h"

#include "CoOS/OsConfig.h"  /*!< CoOS configure header file*/
#include "CoOS/kernel/coocox.h"  /*!< CoOS header file  */

#include "sequencer.h"
#include "UI.h"
#include "filter.h"
#include "SPI.h"
#include "ringbuff.h"
#include "SD.h"

//#define MIDI_PRIO	0
//#define SEQ_PRIO	4
#define SD_PRIO		2
//#define FILTER_PRIO	3
#define	UI_PRIO		1
#define LCD_PRIO	5

#define	UIHANDLER_PRIO		3		//TEST

#define MIDI_STK_SIZE		256 //128
#define SEQ_STK_SIZE		256 //128
#define SD_STK_SIZE			516
#define FILTER_STK_SIZE		256 //128
#define UI_STK_SIZE			256 //128
#define LCD_STK_SIZE		516//128

int main(void);

void UIhandler_task(void);
void UI_task(void);
void LCD_task(void);
void SD_task(void);
void Sequencer_task(void);
void Filter_task(void);
void MIDI_task(void);

#endif /* MAIN_HEADER */
