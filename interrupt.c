#include "interrupt.h"
#include "hihat.h"
#include "snaredrum.h"
#include "basskick.h"
#include "cymbal.h"
#include "filter.h"
#include "DAC.h"

extern IIRfilter_t testFilter;

#ifdef FILTER_DEMO
extern uint8_t filterDemo;
#endif

//float wavCnt = 0;

void TIM2_IRQHandler(void)
{
	uint16_t GPIO_msk = 0;

	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

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
			GPIO_msk |= GPIO_Pin_12;				//red
		}
		if((sequencer.bassdrum.sequence &  sequencer.beatmask) && \
				  (sequencer.bassdrum.substeps[sequencer.stepcnt] &  sequencer.submask))
		{
			GPIO_msk |= GPIO_Pin_13;				//orange
		}
		if((sequencer.instr0.sequence &  sequencer.beatmask) && \
				  (sequencer.instr0.substeps[sequencer.stepcnt] &  sequencer.submask))
		{
			GPIO_msk |= GPIO_Pin_14;				//green
			sequencer.instr0.triggerflag = 1;
		}
		if((sequencer.instr1.sequence &  sequencer.beatmask) && \
				  (sequencer.instr1.substeps[sequencer.stepcnt] &  sequencer.submask))
		{
			GPIO_msk |= GPIO_Pin_15;				//blu
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
		GPIO_SetBits(GPIOD, GPIO_msk);

		sequencer.submask = (sequencer.submask >> 1) | ((sequencer.submask & 0x1) << 5);	//rotate right

	}
	else if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
		if(!(sequencer.timerflag) || ((sequencer.timerflag == 1) && (sequencer.beatclk == 1)))
		{
			GPIO_ResetBits(GPIOD, (GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15));
		}
	}
}

void TIM5_IRQHandler(void)
{
	GPIO_SetBits(GPIOD, GPIO_Pin_12);
	uint16_t sampleMix = DC_COMP;	//was 2048
	uint16_t audioOut = DC_COMP;

	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);

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

///*
		 audioOut = (hihatWav[sequencer.instr0.buffer_loc] + \
					 snaredrumWav[sequencer.instr1.buffer_loc] + \
					 basskickmWav[sequencer.instr2.buffer_loc] + \
					 cymbalWav[sequencer.instr3.buffer_loc]) / 4;
//*/
//		audioOut = 0;

		//this is where the filter party starts.........

#ifdef FILTER_DEMO	//uncomment FILTER_DEMO in "filter.h" for filter sweep demo
//		static uint8_t freqFlag=0, dsFreqFlag=0, bits=5, bitFlag=0;
//		static uint16_t freq=100, cnt=0, dsFreq=500;
//
//		if(!((cnt++)%100))	//code below sweeps variable freq up and down
//		{
//			if(freqFlag)
//			{
//				if(freq<450)
//				{
//					freq-=1;
//				}
//				else
//				{
//					freq-=5;
//				}
//				if(freq<=100)
//					freqFlag=0;
//			}
//			else
//			{
//				if(freq<450)
//				{
//					freq+=1;
//				}
//				else
//				{
//					freq+=5;
//				}
//				if(freq>=5000)
//					freqFlag=1;
//			}
//		}
//
//		if(!(cnt%100))	//code below sweeps variable sample freq up and down
//		{
//			if(dsFreqFlag)
//			{
//				dsFreq-=1;
//				if(dsFreq<=100)
//					dsFreqFlag=0;
//			}
//			else
//			{
//				dsFreq+=1;
//				if(dsFreq>=8000)
//					dsFreqFlag=1;
//			}
//		}
//
//		if(!(cnt%30000))
//		{
//			if(bitFlag)
//			{
//				bits--;
//				if(bits<=1)
//					bitFlag=0;
//			}
//			else
//			{
//				bits++;
//				if(bits>=DAC_BITS-1)
//					bitFlag=1;
//			}
//		}
//

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

//		switch(filterDemo%NUM_OF_FX)	//select which effect to demo with the (blue) user button
//		{
//			case LPF:	IIRFilterCalc(&testFilter, freq, LPF);
//						IIRFilterDo(&testFilter, audioOut, &audioOut);	//apply filter
//						break;
//			case HPF:	IIRFilterCalc(&testFilter, freq, HPF);
//						IIRFilterDo(&testFilter, audioOut, &audioOut);	//apply filter
//						break;
//			case BC:	BitCrush(audioOut, &audioOut, bits);
//						break;
//			case DS:	DownSample(audioOut, &audioOut, dsFreq);
//						break;
//			default:	break;
//		}
#endif

		dacPut(audioOut);	//actual sound is made hear (pun intended)

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

	GPIO_ResetBits(GPIOD, GPIO_Pin_12);
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
