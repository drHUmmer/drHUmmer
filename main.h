#ifndef MAIN_HEADER
#define MAIN_HEADER

#define DEBUG	// uncomment this line for debug mode
#define USE_OS

#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
//#include "stm32f4xx_spi.h"
#include "misc.h"
#include "ADC.h"
#include "DAC.h"
#include "PLL.h"
#include "UART.h"
#include "interrupt.h"
#include "timers.h"

#ifdef USE_OS
#include "CoOS/OsConfig.h"  /*!< CoOS configure header file*/
#include "CoOS/kernel/coocox.h"  /*!< CoOS header file  */
#else
#include "delay.h"
#endif	/*	USE_OS	*/

#include "sequencer.h"
#include "UI.h"
#include "ringbuff.h"
#include "SPI.h"

#define MIDI_PRIO	0
#define SEQ_PRIO	1
#define SD_PRIO		2
#define FILTER_PRIO	3
#define	UI_PRIO		4
#define LCD_PRIO	5

int main(void);

#ifdef USE_OS
void UI_task(void);
void LCD_task(void);
void SD_task(void);
void Sequencer_task(void);
void Filter_task(void);
void MIDI_task(void);
#endif	/*	USE_OS	*/

#ifdef DEBUG
void error_blink(void);
void delay_us(uint32_t delay);
#endif /* DEBUG */

#endif /* MAIN_HEADER */
