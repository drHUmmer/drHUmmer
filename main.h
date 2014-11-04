#ifndef MAIN_HEADER
#define MAIN_HEADER

#define DEBUG	// uncomment this line for debug mode

#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "misc.h"
#include "ADC.h"
#include "DAC.h"
#include "PLL.h"
#include "UART.h"
#include "interrupt.h"
#include "timer.h"
#include "delay.h"
#include "sequencer.h"
#include "UI.h"
#include "ringbuff.h"

int main(void);

#ifdef DEBUG
void error_blink(void);
#endif /* DEBUG */

#endif /* MAIN_HEADER */
