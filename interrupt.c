#include "interrupt.h"
#include "hihat.h"
#include "snaredrum.h"
#include "basskick.h"
#include "cymbal.h"
#include "filter.h"
#include "DAC.h"

extern IIRfilter_t testFilter;

#include "ADC.h"

//float wavCnt = 0;


uint32_t SDCnt = 1;

uint8_t bufFlag = BUFF_A;
uint8_t bufABusy = FALSE;
uint8_t bufBBusy = FALSE;
uint8_t bufFillFlag = BUFFF_NF;

void TIM2_IRQHandler(void)
{
	uint16_t GPIO_msk = 0;			// TODO

	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

		if(sequencer.playing)
		{
			if(++sequencer.beatclk >= 6)
			{
				sequencer.beatclk = 0;
				if(++sequencer.stepcnt >= 16)
				{
					sequencer.stepcnt = 0;
				}
				sequencer.beatmask = (sequencer.beatmask >> 1) | (sequencer.beatmask << ((sizeof(sequencer.beatmask)*8) - 1));	//rotate right
			}

			if((sequencer.snaredrum.sequence &  sequencer.beatmask) && \
					(sequencer.snaredrum.substeps[sequencer.stepcnt] &  sequencer.submask))
			{
				GPIO_msk |= GPIO_Pin_13;				//green
			}
			if((sequencer.bassdrum.sequence &  sequencer.beatmask) && \
					  (sequencer.bassdrum.substeps[sequencer.stepcnt] &  sequencer.submask))
			{
				GPIO_msk |= GPIO_Pin_14;				//orange
			}
			if((sequencer.instr0.sequence &  sequencer.beatmask) && \
					  (sequencer.instr0.substeps[sequencer.stepcnt] &  sequencer.submask))
			{
				//GPIO_msk |= GPIO_Pin_14;				//red
				sequencer.instr0.triggerflag = 1;
			}
			if((sequencer.instr1.sequence &  sequencer.beatmask) && \
					  (sequencer.instr1.substeps[sequencer.stepcnt] &  sequencer.submask))
			{
				//GPIO_msk |= GPIO_Pin_15;				//blu
				sequencer.instr1.triggerflag = 1;
			}
			if((sequencer.instr2.sequence &  sequencer.beatmask) && \
					  (sequencer.instr2.substeps[sequencer.stepcnt] &  sequencer.submask))
			{
				sequencer.instr2.triggerflag = 1;
			}
			if((sequencer.instr3.sequence &  sequencer.beatmask) && \
					  (sequencer.instr3.substeps[sequencer.stepcnt] &  sequencer.submask))
			{
				sequencer.instr3.triggerflag = 1;
			}
				GPIO_SetBits(GPIOC, GPIO_msk);	//TODO

			sequencer.submask = (sequencer.submask >> 1) | ((sequencer.submask & 0x1) << 5);	//rotate right

		}
		else
		{
			sequencer.beatmask = 0x8000;
		}
	}
	else if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
		if(!(sequencer.timerflag) || ((sequencer.timerflag == 1) && (sequencer.beatclk == 1)))
		{
			GPIO_ResetBits(GPIOC, (GPIO_Pin_14 | GPIO_Pin_13)); //TODO
		}
	}
}


void TIM5_IRQHandler(void)
{
//	uint16_t adc1_dat = adcGet();		//TODO
	uint16_t audioOut = DC_COMP;
//	uint32_t audioCalc = 0;

	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);

		if(sequencer.playing)
		{
			if(sequencer.instr0.triggerflag)
			{
				sequencer.instr0.buffer_loc = 0;
				sequencer.instr0.triggerflag = 0;
			}

			if(sequencer.instr1.triggerflag)
			{
				sequencer.instr1.buffer_loc = 0;
				sequencer.instr1.triggerflag = 0;
			}

			if(sequencer.instr2.triggerflag)
			{
				sequencer.instr2.buffer_loc = 0;
				sequencer.instr2.triggerflag = 0;
			}

			if(sequencer.instr3.triggerflag)
			{
				sequencer.instr3.buffer_loc = 0;
				sequencer.instr3.triggerflag = 0;
			}


			if(sequencer.instr0.file_nr <= 3)
			{
				if(sequencer.instr0.bufFlag == BUFF_A){
					if(!sequencer.instr0.bufBBusy){
						sequencer.instr0.sample = sequencer.instr0.wBufB[sequencer.instr0.buffer_loc % WAV_BUF_SIZE];
					}
					if(((sequencer.instr0.buffer_loc+sequencer.instr0.tone) % WAV_BUF_SIZE) == 0){
						sequencer.instr0.bufFlag = BUFF_B;
						sequencer.instr0.bufFillFlag = BUFFF_NF;
					}
				}else {
					if(!sequencer.instr0.bufABusy){
						sequencer.instr0.sample = sequencer.instr0.wBufA[sequencer.instr0.buffer_loc % WAV_BUF_SIZE];
					}
					if(((sequencer.instr0.buffer_loc+sequencer.instr0.tone) % WAV_BUF_SIZE) == 0){
						sequencer.instr0.bufFlag = BUFF_A;
						sequencer.instr0.bufFillFlag = BUFFF_NF;
					}
				}
			}
			else
				sequencer.instr0.sample = hihatWav[sequencer.instr0.buffer_loc];

			if(sequencer.instr1.file_nr <= 3)
			{

				if(sequencer.instr1.bufFlag == BUFF_A){
					if(!sequencer.instr1.bufBBusy){
						sequencer.instr1.sample = sequencer.instr1.wBufB[sequencer.instr1.buffer_loc % WAV_BUF_SIZE];
					}
					if(((sequencer.instr1.buffer_loc+sequencer.instr1.tone) % WAV_BUF_SIZE) == 0){
						sequencer.instr1.bufFlag = BUFF_B;
						sequencer.instr1.bufFillFlag = BUFFF_NF;
					}
				}else {
					if(!sequencer.instr1.bufABusy){
						sequencer.instr1.sample = sequencer.instr1.wBufA[sequencer.instr1.buffer_loc % WAV_BUF_SIZE];
					}
					if(((sequencer.instr1.buffer_loc+sequencer.instr1.tone) % WAV_BUF_SIZE) == 0){
						sequencer.instr1.bufFlag = BUFF_A;
						sequencer.instr1.bufFillFlag = BUFFF_NF;
					}
				}
			}
			else
				sequencer.instr1.sample = snaredrumWav[sequencer.instr1.buffer_loc];

			if(sequencer.instr2.file_nr <= 3)
			{
				if(sequencer.instr2.bufFlag == BUFF_A){
					if(!sequencer.instr2.bufBBusy){
						sequencer.instr2.sample = sequencer.instr2.wBufB[sequencer.instr2.buffer_loc % WAV_BUF_SIZE];
					}
					if(((sequencer.instr2.buffer_loc+sequencer.instr2.tone) % WAV_BUF_SIZE) == 0){
						sequencer.instr2.bufFlag = BUFF_B;
						sequencer.instr2.bufFillFlag = BUFFF_NF;
					}
				}else {
					if(!sequencer.instr2.bufABusy){
						sequencer.instr2.sample = sequencer.instr2.wBufA[sequencer.instr2.buffer_loc % WAV_BUF_SIZE];
					}
					if(((sequencer.instr2.buffer_loc+sequencer.instr2.tone) % WAV_BUF_SIZE) == 0){
						sequencer.instr2.bufFlag = BUFF_A;
						sequencer.instr2.bufFillFlag = BUFFF_NF;
					}
				}
			}
			else
				sequencer.instr2.sample = basskickWav[sequencer.instr2.buffer_loc];

			if(sequencer.instr3.file_nr <= 3)
			{
				if(sequencer.instr3.bufFlag == BUFF_A){
					if(!sequencer.instr3.bufBBusy){
						sequencer.instr3.sample = sequencer.instr3.wBufB[sequencer.instr3.buffer_loc % WAV_BUF_SIZE];
					}
					if(((sequencer.instr3.buffer_loc+sequencer.instr3.tone) % WAV_BUF_SIZE) == 0){
						sequencer.instr3.bufFlag = BUFF_B;
						sequencer.instr3.bufFillFlag = BUFFF_NF;
					}
				}else {
					if(!sequencer.instr3.bufABusy){
						sequencer.instr3.sample = sequencer.instr3.wBufA[sequencer.instr3.buffer_loc % WAV_BUF_SIZE];
					}
					if(((sequencer.instr3.buffer_loc+sequencer.instr3.tone) % WAV_BUF_SIZE) == 0){
						sequencer.instr3.bufFlag = BUFF_A;
						sequencer.instr3.bufFillFlag = BUFFF_NF;
					}
				}
			}
			else
				sequencer.instr3.sample = cymbalWav[sequencer.instr3.buffer_loc];


			/*if(bufFlag == BUFF_A){
				if(!bufBBusy){
					dacPut(wavBufB[SDCnt]);
					SDCnt++;
					SDCnt = SDCnt % WAV_BUF_SIZE;
				}
				if(SDCnt == 0){
					bufFlag = BUFF_B;
					bufFillFlag = BUFFF_NF;
				}
			}else {
				if(!bufABusy){
					dacPut(wavBufA[SDCnt]);
					SDCnt++;
					SDCnt = SDCnt % WAV_BUF_SIZE;
				}

				if(SDCnt == 0){
					bufFlag = BUFF_A;
					bufFillFlag = BUFFF_NF;
				}
			}*/

			audioOut = (sequencer.instr0.sample * sequencer.instr0.level + \
						sequencer.instr1.sample * sequencer.instr1.level + \
						sequencer.instr2.sample * sequencer.instr2.level + \
						sequencer.instr3.sample * sequencer.instr3.level + \
						sequencer.bassdrum.sample * 100 + \
						sequencer.snaredrum.sample * 100) / 600;
	/*	//TODO

			 audioCalc = (hihatWav[sequencer.instr0.buffer_loc] * sequencer.instr0.level + \
						 snaredrumWav[sequencer.instr1.buffer_loc] * sequencer.instr1.level + \
						 basskickWav[sequencer.instr2.buffer_loc] * sequencer.instr2.level + \
						 cymbalWav[sequencer.instr3.buffer_loc] * sequencer.instr3.level) / 400;

			 audioOut = audioCalc;
	*/

			 if (FXsettings.fxEnable) {
				 if (FXsettings.fx1 != NONE) {
					switch(FXsettings.fx1)	//select which effect to demo with the (blue) user button
					{
						case LPF:	IIRFilterCalc(&testFilter, FXsettings.lpfFreq, LPF);
									IIRFilterDo(&testFilter, audioOut, &audioOut);	//apply filter
									break;
						case HPF:	IIRFilterCalc(&testFilter, FXsettings.hpfFreq, HPF);
									IIRFilterDo(&testFilter, audioOut, &audioOut);	//apply filter
									break;
						case BC:	BitCrush(audioOut, &audioOut, FXsettings.bcBits);
									break;
						case DS:	DownSample(audioOut, &audioOut, FXsettings.dsFreq);
									break;
						default:	break;
					}
				}

				if (FXsettings.fx2 != NONE) {
					switch(FXsettings.fx2)	//select which effect to demo with the (blue) user button
					{
						case LPF:	IIRFilterCalc(&testFilter, FXsettings.lpfFreq, LPF);
									IIRFilterDo(&testFilter, audioOut, &audioOut);	//apply filter
									break;
						case HPF:	IIRFilterCalc(&testFilter, FXsettings.hpfFreq, HPF);
									IIRFilterDo(&testFilter, audioOut, &audioOut);	//apply filter
									break;
						case BC:	BitCrush(audioOut, &audioOut, FXsettings.bcBits);
									break;
						case DS:	DownSample(audioOut, &audioOut, FXsettings.dsFreq);
									break;
						default:	break;
					}
				}
			 }

			dacPut(audioOut);	//actual sound is made hear (pun intended)	//TODO

			if((sequencer.instr0.buffer_loc += sequencer.instr0.tone) >= sequencer.instr0.file_length)
			{
				sequencer.instr0.buffer_loc = sequencer.instr0.file_length-1;
			}

			if((sequencer.instr1.buffer_loc += sequencer.instr1.tone) >= sequencer.instr1.file_length)
			{
				sequencer.instr1.buffer_loc = sequencer.instr1.file_length-1;
			}

			if((sequencer.instr2.buffer_loc += sequencer.instr2.tone) >= sequencer.instr2.file_length)
			{
				sequencer.instr2.buffer_loc = sequencer.instr2.file_length-1;
			}

			if((sequencer.instr3.buffer_loc += sequencer.instr3.tone) >= sequencer.instr3.file_length)
			{
				sequencer.instr3.buffer_loc = sequencer.instr3.file_length-1;
			}
		}
		else
		{
			sequencer.instr0.buffer_loc = 0;
			sequencer.instr1.buffer_loc = 0;
			sequencer.instr2.buffer_loc = 0;
			sequencer.instr3.buffer_loc = 0;
		}
	}
}

void NVICTimer2Init(void)
{
	/* TIM2 NVIC (nested vectored interrupt controller) configuration */
	NVIC_InitStruct.NVIC_IRQChannel 					= TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority 	= 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority 			= 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd 					= ENABLE;
	NVIC_Init(&NVIC_InitStruct);

}

void NVICTimer5Init(void)
{
	/* TIM5 NVIC (nested vectored interrupt controller) configuration */
	NVIC_InitStruct.NVIC_IRQChannel 					= TIM5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority 	= 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority 			= 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd 					= ENABLE;
	NVIC_Init(&NVIC_InitStruct);

}
