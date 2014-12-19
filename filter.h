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

#define NUM_OF_FX 5	//4 effects + 1 clean sounding mode

#define LPF 	0x00	//low pass			//filter types
#define HPF 	0x01	//high pass
#define BC 		0x02	//bit crusher
#define DS 		0x03	//down sampler
#define NONE 	0x04

// FILTER RANGES
#define LPF_LOW		50
#define LPF_HIGH	20000
#define HPF_LOW		50
#define HPF_HIGH	20000
#define BC_LOW		1
#define BC_HIGH		11
#define DS_LOW		50
#define DS_HIGH		20000
#define LPF_STEP	50
#define HPF_STEP	50
#define DS_STEP		50
#define BC_STEP		1

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

typedef struct
{
	uint8_t		fx1		: 4;	// LPF, HPF, BC, DS, NONE
	uint8_t		fx2		: 4;	// LPF, HPF, BC, DS, NONE
	uint8_t 	bcBits;
	uint16_t	dsFreq;
	uint16_t	lpfFreq;
	uint16_t	hpfFreq;
}FXsettings_t;

/*VARIABLES*/
extern IIRfilter_t testFilter;
extern FXsettings_t FXsettings;
extern uint16_t filterStatus;

#ifdef FILTER_DEMO
extern uint8_t filterDemo;
#endif

/*FUNCTION PROTOTYPES*/
uint8_t FirFilter(uint16_t *pInput, uint16_t *pKernel, uint16_t *output);	//obsolete, but keep this for future reference please
uint8_t IIRFilterCalc(IIRfilter_t *pf, uint16_t freq, uint8_t filterType);
uint8_t IIRFilterDo(IIRfilter_t *pf, uint16_t input, uint16_t *output);
uint8_t BitCrush(uint16_t input, uint16_t *output, uint8_t bits);
uint16_t DownSample(uint16_t input, uint16_t *output, uint16_t freq);

#endif
