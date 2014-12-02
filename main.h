#ifndef MAIN_HEADER
#define MAIN_HEADER

#define DEBUG	// uncomment this line for debug mode
//#define USE_OS

#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_spi.h"
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
#endif	/*	USE_OS	*/

#ifndef USE_OS
#include "delay.h"
#endif	/*	!USE_OS	*/

#include "sequencer.h"
#include "UI.h"
#include "ringbuff.h"

#include "defines.h"
#include "stm32f4xx.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_disco.h"
#include "tm_stm32f4_fatfs.h"
#include <stdio.h>
#include <string.h>

int main(void);

#ifdef DEBUG
void error_blink(void);
#endif /* DEBUG */

#endif /* MAIN_HEADER */
