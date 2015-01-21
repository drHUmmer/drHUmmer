#include "main.h"

extern uint32_t SDCnt;
extern uint8_t bufFlag;
extern uint8_t bufFillFlag;
extern IIRfilter_t testFilter;
extern uint16_t filterStatus;

OS_STK UI_task_stk[128];
OS_STK LCD_task_stk[128];
OS_STK SD_task_stk[SD_STK_SIZE];
OS_STK sequencer_task_stk[128];
OS_STK filter_task_stk[128];
OS_STK MIDI_task_stk[128];


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

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
/* End LED IO init */

//	UIInit();

	CoInitOS();

	dacInit();
	adcInit();

	LCD_Init();
	MenuSetup();



	BPMUpdate(sequencer.BPM);
	RingBufferInit();

	CoCreateTask((FUNCPtr)UI_task,(void *)0,UI_PRIO,&UI_task_stk[128-1],128);
	CoCreateTask((FUNCPtr)LCD_task,(void *)0,LCD_PRIO,&LCD_task_stk[128-1],128);
	CoCreateTask((FUNCPtr)SD_task,(void *)0,SD_PRIO,&SD_task_stk[SD_STK_SIZE-1],SD_STK_SIZE);
	CoCreateTask((FUNCPtr)Sequencer_task,(void *)0,SEQ_PRIO,&sequencer_task_stk[128-1],128);
	CoCreateTask((FUNCPtr)Filter_task,(void *)0,FILTER_PRIO,&filter_task_stk[128-1],128);
	CoCreateTask((FUNCPtr)MIDI_task,(void *)0,MIDI_PRIO,&MIDI_task_stk[128-1],128);

	sequencer.playing = 1;
	GPIO_SetBits(GPIOD, GPIO_Pin_12);

	CoStartOS();

	for(;;);
}

void UI_task(void)
{
	uint8_t i;
	for(;;)
	{
		GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
		SPI_PIC_Send(PIC_GET_BUTTON,0,PIC_BUTTONS_ALL);
		CoTickDelay(1);

		for(i=0;i<4;i++)
			uiInput.buttons |= (SPI_PIC_Receive() << (i*8));

		CoTickDelay(1);

		SPI_PIC_Send(PIC_GET_ROTARY,0,PIC_ROTARY_ALL);
		CoTickDelay(1);

		for(i=0;i<11;i++)
			*(&uiInput.rotary1 + i) = SPI_PIC_Receive();

		CoTickDelay(1);

		UIhandler();
		CoTickDelay(40);
	}
}

void LCD_task(void)
{
	for(;;)
	{
		GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
		Menu_Update_handler();
		CoTickDelay(10);
	}
}


void SD_task(void)
{
	#define FILENR 0

	uint32_t SD_filesize[4];
//	uint32_t i=44;
	uint8_t j;

	GPIO_SetBits(GPIOD, GPIO_Pin_13);
	if( SDInit() == FR_OK ){
			SDGetNames("/"); 		// root directory
			GPIO_ResetBits(GPIOD, GPIO_Pin_13);			//TODO
		}

	for(j=0;j<4;j++)
		SD_filesize[j] = getFileSize(fnames[j]);

	NVICTimer2Init();
	NVICTimer5Init();
	Timer2Init();
	Timer5Init();

	/*	bufFlag = BUFF_A;
	SDGet512(wavBufA, fnames[FILENR] ,44);
	bufFlag = BUFF_B;*/

	for(;;)
	{
		if(sequencer.instr0.file_nr <= 3)
		{
			sequencer.instr0.file_length = SD_filesize[sequencer.instr0.file_nr];

			if (sequencer.instr0.bufFillFlag == BUFFF_NF){
				if(sequencer.instr0.bufFlag == BUFF_A){
					if((sequencer.instr0.i+=(WAV_BUF_SIZE*2)) > sequencer.instr0.file_length){
						sequencer.instr0.i = 44;
					}
					sequencer.instr0.bufABusy = TRUE;
					SDGet512(sequencer.instr0.wBufA, fnames[sequencer.instr0.file_nr], (DWORD)sequencer.instr0.i);
					sequencer.instr0.bufABusy = FALSE;
					sequencer.instr0.bufFillFlag = BUFFF_F;
				}
				else {
					if((sequencer.instr0.i+=(WAV_BUF_SIZE*2)) > sequencer.instr0.file_length){
						sequencer.instr0.i = 44;
					}
					sequencer.instr0.bufBBusy = TRUE;
					SDGet512(sequencer.instr0.wBufB, fnames[sequencer.instr0.file_nr], (DWORD)sequencer.instr0.i);

					sequencer.instr0.bufBBusy = FALSE;
					sequencer.instr0.bufFillFlag = BUFFF_F;
				}
			}
		}

		if(sequencer.instr1.file_nr <= 3)
		{
			sequencer.instr1.file_length = SD_filesize[sequencer.instr1.file_nr];

			if (sequencer.instr1.bufFillFlag == BUFFF_NF){
				if(sequencer.instr1.bufFlag == BUFF_A){
					if((sequencer.instr1.i+=(WAV_BUF_SIZE*2)) > sequencer.instr1.file_length){
						sequencer.instr1.i = 44;
					}
					sequencer.instr1.bufABusy = TRUE;
					SDGet512(sequencer.instr1.wBufA, fnames[sequencer.instr1.file_nr], (DWORD)sequencer.instr1.i);
					sequencer.instr1.bufABusy = FALSE;
					sequencer.instr1.bufFillFlag = BUFFF_F;
				}
				else {
					if((sequencer.instr1.i+=(WAV_BUF_SIZE*2)) > sequencer.instr1.file_length){
						sequencer.instr1.i = 44;
					}
					sequencer.instr1.bufBBusy = TRUE;
					SDGet512(sequencer.instr1.wBufB, fnames[sequencer.instr1.file_nr], (DWORD)sequencer.instr1.i);

					sequencer.instr1.bufBBusy = FALSE;
					sequencer.instr1.bufFillFlag = BUFFF_F;
				}
			}
		}

		if(sequencer.instr2.file_nr <= 3)
		{
			sequencer.instr2.file_length = SD_filesize[sequencer.instr2.file_nr];

			if (sequencer.instr2.bufFillFlag == BUFFF_NF){
				if(sequencer.instr2.bufFlag == BUFF_A){
					if((sequencer.instr2.i+=(WAV_BUF_SIZE*2)) > sequencer.instr2.file_length){
						sequencer.instr2.i = 44;
					}
					sequencer.instr2.bufABusy = TRUE;
					SDGet512(sequencer.instr2.wBufA, fnames[sequencer.instr2.file_nr], (DWORD)sequencer.instr2.i);
					sequencer.instr2.bufABusy = FALSE;
					sequencer.instr2.bufFillFlag = BUFFF_F;
				}
				else {
					if((sequencer.instr2.i+=(WAV_BUF_SIZE*2)) > sequencer.instr2.file_length){
						sequencer.instr2.i = 44;
					}
					sequencer.instr2.bufBBusy = TRUE;
					SDGet512(sequencer.instr2.wBufB, fnames[sequencer.instr2.file_nr], (DWORD)sequencer.instr2.i);

					sequencer.instr2.bufBBusy = FALSE;
					sequencer.instr2.bufFillFlag = BUFFF_F;
				}
			}
		}

	if(sequencer.instr3.file_nr <= 3)
		{
			sequencer.instr3.file_length = SD_filesize[sequencer.instr3.file_nr];

			if (sequencer.instr3.bufFillFlag == BUFFF_NF){
				if(sequencer.instr3.bufFlag == BUFF_A){
					if((sequencer.instr3.i+=(WAV_BUF_SIZE*2)) > sequencer.instr3.file_length){
						sequencer.instr3.i = 44;
					}
					sequencer.instr3.bufABusy = TRUE;
					SDGet512(sequencer.instr3.wBufA, fnames[sequencer.instr3.file_nr], (DWORD)sequencer.instr3.i);
					sequencer.instr3.bufABusy = FALSE;
					sequencer.instr3.bufFillFlag = BUFFF_F;
				}
				else {
					if((sequencer.instr3.i+=(WAV_BUF_SIZE*2)) > sequencer.instr3.file_length){
						sequencer.instr3.i = 44;
					}
					sequencer.instr3.bufBBusy = TRUE;
					SDGet512(sequencer.instr3.wBufB, fnames[sequencer.instr3.file_nr], (DWORD)sequencer.instr3.i);

					sequencer.instr3.bufBBusy = FALSE;
					sequencer.instr3.bufFillFlag = BUFFF_F;
				}
			}
		}

/*		if (bufFillFlag == BUFFF_NF){
			if(bufFlag == BUFF_A){
				if((i+=(WAV_BUF_SIZE*2)) > filesize){
					i = 44;
				}
				bufABusy = TRUE;
				SDGet512(wavBufA, fnames[FILENR], (DWORD)i);
				bufABusy = FALSE;
				bufFillFlag = BUFFF_F;
				//GPIO_ToggleBits(GPIOD, GPIO_Pin_15);

			}else {
				if((i+=(WAV_BUF_SIZE*2)) > filesize){
					i = 44;
				}
				bufBBusy = TRUE;
				SDGet512(wavBufB, fnames[FILENR], (DWORD)i);

				bufBBusy = FALSE;
				bufFillFlag = BUFFF_F;

				//GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
			}
		}*/

		CoTickDelay(1);
	}
}

void Sequencer_task(void)
{
	for(;;)
	{
		CoTickDelay(1);
	}
}

void Filter_task(void)
{
	for(;;)
	{
		CoTickDelay(1);
	}
}

void MIDI_task(void)
{
	for(;;)
	{
		CoTickDelay(1);
	}
}

