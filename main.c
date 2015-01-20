#include "main.h"

void task_a(void);
void task_b(void);
void leds(void);

extern uint32_t SDCnt;
extern uint8_t bufFlag;
extern uint8_t bufFillFlag;


#ifdef USE_OS
OS_STK taskA_stk[128];  /*!< define "taskA" task stack */
OS_STK taskB_stk[128];  /*!< define "taskB" task stack */
OS_STK led_stk [128];  /*!< define "led" task stack */

OS_FlagID a_flag,b_flag;

OS_EventID mbox0;
#endif

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

int main(void)
{
	PLLInit();
//	sequencerInit();
	//SPI3_Init();

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

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
/* End LED IO init */

//	UIInit();

	dacInit();
//	adcInit();
//	NVICTimer2Init();
//	NVICTimer5Init();
//	Timer2Init();
//	Timer5Init();

//	BPMUpdate(sequencer.BPM);

//	RingBufferInit();


//	SysTick_Init();

	uint32_t filesize;

#define FILENR 0

	GPIO_SetBits(GPIOD, GPIO_Pin_13);
	if( SDInit() == FR_OK ){
		SDGetNames("/"); 		// root directory
		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
	}


	bufFlag = BUFF_A;
	SDGet512(wavBufA, fnames[FILENR] ,44);
	bufFlag = BUFF_B;

	filesize = getFileSize(fnames[FILENR]);

	Timer5Init();

//	GPIO_SetBits(GPIOD, (GPIO_Pin_15 | GPIO_Pin_13));
//	GPIO_ResetBits(GPIOD, (GPIO_Pin_14 | GPIO_Pin_12));

	uint32_t i=44;
	while(1){
		if (bufFillFlag == BUFFF_NF){

			if(bufFlag == BUFF_A){
				if((i+=(WAV_BUF_SIZE*2)) > filesize){
					i = 44;
				}
				bufABusy = TRUE;
				SDGet512(wavBufA, fnames[FILENR], (DWORD)i);
				bufABusy = FALSE;
				bufFillFlag = BUFFF_F;

				GPIO_ToggleBits(GPIOD,GPIO_Pin_15);

			}else {
				if((i+=(WAV_BUF_SIZE*2)) > filesize){
					i = 44;
				}
				bufBBusy = TRUE;
				SDGet512(wavBufB, fnames[FILENR], (DWORD)i);
				bufBBusy = FALSE;
				bufFillFlag = BUFFF_F;

				GPIO_ToggleBits(GPIOD,GPIO_Pin_15);
			}
		}
	}
}

void EXTI1_IRQHandler(void)
{

}

#endif	/* end debug mode */


#ifndef USE_OS
/*
void SysTick_Handler(void)
{
	TimeTick_Decrement();
}
*/
#endif
