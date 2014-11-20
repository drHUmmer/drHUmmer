/*
 * FILTER.C - filter kernel calculations, filter algorithms, other filter stuffz
 * Jan Trompper, 1603728
 *
 */

/*INCLUDES*/
#include "filter.h"
#include "DAC.h"
#include <math.h>

/*VARIABLES*/
IIRfilter_t testFilter;

/*FUNCTIONS*/

/* OBSOLETE, BUT KEEP FOR FUTURE REFERENCE PLZ
 * FirFilter()
 * Finite Impulse Response filter algorithm
 *
 * Usage:
 * FirFilter(&inputArray, &kernelArray, &outputVariable);
 */
uint8_t FirFilter(uint16_t *pInput, uint16_t *pKernel, uint16_t *output)
{
	uint32_t buffSize = (sizeof(pInput)/sizeof(uint16_t));	//set buffer size
	uint32_t i = 0;
	*output = 0;	//output should always be set to zero before beginning new FIR operation

	for(i=0;i<buffSize;i++)
	{
		*output += pInput[i]*pKernel[(buffSize-1)-i];	//actual FIR algorithm at work!
	}

	return 0;
}

/* IIRFilterCalc()
 * IIR filter coefficient calculations
 * returns filter type
 * Usage:
 * FilterCalc(&filterStruct, frequency, FILTER_TYPE);
 */

uint8_t IIRFilterCalc(IIRfilter_t *pf, uint16_t freq, uint8_t filterType)
{
	float temp;

	if((pf->freq!=freq)||(pf->type!=filterType))	//don't do shit if no change in settings
	{
		pf->freq = freq;		//store filter cutoff frequency
		pf->type = filterType;	//store filter type
		pf->fs = SAMPLE_RATE;	//store sample rate

		temp = (-2)*M_PI*((pf->freq)/(float)(pf->fs));	//typecast to ensure gloating point result
		pf->alpha = exp(temp);	//alpha is needed as a base number for the coeffs

		switch(filterType)	//decide on what type of filter to calculate
		{
			case LPF:	pf->a0 = (1-pf->alpha);	//calculate coeffs and store in struct
						pf->a1 = 0;				//LPF doesn't use coeff a1
						pf->b0 = pf->alpha;
						break;
			case HPF:	pf->a0 = ((1+pf->alpha)/2);	//calculate coeffs and store in struct
						pf->a1 = ((1+pf->alpha)/-2);
						pf->b0 = pf->alpha;
						break;
		}	//SWITCH
		return filterType;	//return filter type
	}	//IF
	return 0xFF;	//no change to filter settings
}

/* IRRFilterDo()
 * Apply 1st IIR filter algorithm
 *
 * Usage:
 * IIRFilterDo(&filterStruct, inputSample, &output);
 */
uint8_t IIRFilterDo(IIRfilter_t *pf, uint16_t input, uint16_t *output)
{
	int16_t temp=0;

	pf->xn = (int16_t)input - DC_COMP;							//subtract DC-component from input
	temp = (pf->a0*pf->xn)+(pf->a1*pf->xn_1)+(pf->b0*pf->yn_1);	//IIR filter algorithm
	*output = (uint16_t)(temp + DC_COMP);						//store output and add DC component for DAC

	pf->yn_1 = temp;	//store samples as previous samples for next run
	pf->xn_1 = pf->xn;

	return 0;
}


