#ifndef INTERRUPT_HEADER
#define INTERRUPT_HEADER

#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "misc.h"
#include "sequencer.h"
#include "DAC.h"
#include "SD.h"

//#define TONE 1

//extern float wavCnt;

NVIC_InitTypeDef NVIC_InitStruct;
#define BUFF_A 0
#define BUFF_B 1

#define BUFFF_NF 0
#define BUFFF_F	 1

extern uint32_t SDCnt;
extern uint8_t bufFlag;
extern uint8_t bufFillFlag;


void NVICTimer2Init(void);
void NVICTimer5Init(void);

#endif /* INTERRUPT_HEADER */
