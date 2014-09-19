# ifndef ADC_HEADER
# define ADC_HEADER

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_rcc.h"

// structure used for GPIO setting
GPIO_InitTypeDef GPIO_InitStructure;


//structure used for ADC settings
ADC_CommonInitTypeDef ADC_CommonInitStructure;
ADC_InitTypeDef       ADC_InitStructure;


void adcInit(void);
uint16_t adcGet(void);

# endif /*ADC_HEADER*/
