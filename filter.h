/*
 * FILTER.H - header file for filter stuff
 * Jan Trompper, 1603728
 *
 *
 */

#ifndef FILTER_H
#define FILTER_H

/*INCLUDES*/
#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "misc.h"

/*DEFINES*/
#define FILTER_DEMO	//uncomment for filter sweep demo

#define IIR_CALC_ON 		0x0001	//filter status register bits
#define IIR_ENABLE			0x0002
#define BIT_CRUSH_ENABLE	0x0004
#define DOWN_SAMPLE_ENABLE	0x0008

#define LPF 0								//filter types
#define HPF 1
#define SAMPLE_RATE 44100					//sample frequency
#define MAX_FILT_FREQ ((SAMPLE_RATE/2)-100)	//sets max fcut to 100 Hz under fs/2

typedef struct
{
	uint8_t type;	//can be LPF or HPF
	uint16_t freq;	//frequency
	uint16_t fs;	//sample rate
	float alpha;	//alpha is needed to calculate filter coefficients
	float a0;		//filter coefficients
	float a1;
	float b0;
	int16_t xn;	//samples needed to calculate filter output
	int16_t yn_1;
	int16_t xn_1;
}IIRfilter_t;

/*VARIABLES*/
extern IIRfilter_t testFilter;
extern uint16_t filterStatus;

/*FUNCTION PROTOTYPES*/
uint8_t FirFilter(uint16_t *pInput, uint16_t *pKernel, uint16_t *output);	//obsolete, but keep this for future reference please
uint8_t IIRFilterCalc(IIRfilter_t *pf, uint16_t freq, uint8_t filterType);
uint8_t IIRFilterDo(IIRfilter_t *pf, uint16_t input, uint16_t *output);
uint16_t DownSample(uint16_t input, uint16_t *output, uint16_t freq);

#endif
