#ifndef MAIN_HEADER
#define MAIN_HEADER

#define DEBUG	// uncomment this line for debug mode
//#define USE_OS

#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
//#include "stm32f4xx_spi.h"
#include "misc.h"
#include "ADC.h"
#include "DAC.h"
#include "PLL.h"
#include "UART.h"
#include "interrupt.h"
#include "timers.h"


#include "ILI9325.h"
#include "menu.h"
#include "LCDitems.h"
#include "menuHandlers.h"
#include "menuScreens.h"

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
#include "filter.h"
#include "SPI.h"

int main(void);

#ifdef DEBUG
void error_blink(void);
#endif /* DEBUG */

#endif /* MAIN_HEADER */
