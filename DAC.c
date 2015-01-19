#include "DAC.h"


void dacInit(void){
/******************************************************
 * - Init DAC I/O ch1 (PA4)
 * - Init DAC settings
 * 		o no trigger
 * 		o no waveform
 * 		o output buffer enable
 ******************************************************/


// Init DAC I/O
	// Enable write access to gpio registers
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	// Select GPIO settings for pin PA4 (DAC ch1)
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;

	// init gpio with GPIO_InitStructure
	GPIO_Init(GPIOA,&GPIO_InitStructure);


// Init DAC settings
	// Enable write access to dac registers
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	// Fill dacSetting struct
	DAC_StructInit(&dacSettings);
	//dacSettings.DAC_Trigger = DAC_Trigger_None;
	//dacSettings.DAC_WaveGeneration = DAC_WaveGeneration_None;
	//dacSettings.DAC_OutputBuffer = DAC_OutputBuffer_Enable;

	// Init dac ch1 (PA4) with dacSettings struct
	DAC_Init(DAC_Channel_1,&dacSettings);

	// Enable dac ch1 (PA4)
	DAC_Cmd(DAC_Channel_1,ENABLE);


}

void dacPut(uint16_t data){
	/******************************************************
	 * - Writes 12-bit data to DAC ch 1 output buffer
	 * - bits are right aligned (MSB 1st)
	 ******************************************************/

	DAC_SetChannel1Data(DAC_Align_12b_R,data);
}
