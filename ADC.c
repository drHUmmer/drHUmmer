#include "ADC.h"


void adcInit(void){
/******************************************************
 * - Init ADC1 I/O ch10 (PC0)
 * - Init ADC settings
 * 		o Independant mode
 * 		o Prescale 0
 * 		o no delay 2 samples
 * 		o 12-bit mode
 * 		o right aligned MSB 1st
 ******************************************************/

// Init ADC I/O
	// write access GPIO settings
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	// init gpio structure
	GPIO_StructInit(&GPIO_InitStructure);

	//for ADC1 on PC0 using IN10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOC, &GPIO_InitStructure);


// Init ADC settings
	// write access ADC settings
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);


	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;

	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;

	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;

	// init ADC structure
	ADC_StructInit(&ADC_InitStructure);

	// init ADC with ADC structure
	ADC_Init(ADC1, &ADC_InitStructure);

	// configure ADC Channel (ADC1 Ch10) = PC0
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_480Cycles);

	// enable ADC channel
	ADC_EOCOnEachRegularChannelCmd(ADC1, ENABLE);

	// enable ADC
	ADC_Cmd(ADC1, ENABLE);
}

uint16_t adcGet(void){
/******************************************************
 * Get ADC1 ch10 value
 ******************************************************/

	ADC_SoftwareStartConv(ADC1);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);

	return ADC_GetConversionValue(ADC1);
}
