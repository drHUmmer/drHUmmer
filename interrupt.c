#include "interrupt.h"
//#include "hihat.h"
//#include "snaredrum.h"
//#include "basskick.h"
//#include "cymbal.h"

#include "ADC.h"

//float wavCnt = 0;


uint32_t SDCnt = 1;

uint8_t bufFlag = BUFF_A;
uint8_t bufABusy = FALSE;
uint8_t bufBBusy = FALSE;
uint8_t bufFillFlag = BUFFF_NF;

void TIM2_IRQHandler(void)
{
	//uint16_t GPIO_msk = 0;

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

			GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
		}

		if((sequencer.snaredrum.sequence &  sequencer.beatmask) && \
				(sequencer.snaredrum.substeps[sequencer.stepcnt] &  sequencer.submask))
		{
			//GPIO_msk |= GPIO_Pin_12;				//red
		}
		if((sequencer.bassdrum.sequence &  sequencer.beatmask) && \
				  (sequencer.bassdrum.substeps[sequencer.stepcnt] &  sequencer.submask))
		{
			//GPIO_msk |= GPIO_Pin_13;				//orange
		}
		if((sequencer.instr0.sequence &  sequencer.beatmask) && \
				  (sequencer.instr0.substeps[sequencer.stepcnt] &  sequencer.submask))
		{
			//GPIO_msk |= GPIO_Pin_14;				//green
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
		//GPIO_SetBits(GPIOD, GPIO_msk);

		sequencer.submask = (sequencer.submask >> 1) | ((sequencer.submask & 0x1) << 5);	//rotate right

	}
	else if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
		if(!(sequencer.timerflag) || ((sequencer.timerflag == 1) && (sequencer.beatclk == 1)))
		{
			//GPIO_ResetBits(GPIOD, (GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15));
		}
	}
}


void TIM5_IRQHandler(void)
{
	uint16_t adc1_dat = adcGet();

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

		//uint16_t SDData;
		//int16_t offset = 2048;

		if(bufFlag == BUFF_A){
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
		}

/*		uint16_t sampleMix = 2048;
		sampleMix = (hihatWav[sequencer.instr0.buffer_loc] + \
					 snaredrumWav[sequencer.instr1.buffer_loc] + \
					 basskickmWav[sequencer.instr2.buffer_loc] + \
					 cymbalWav[sequencer.instr3.buffer_loc]) / 4;

		dacPut(sampleMix);

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
		}*/
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
