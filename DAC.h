# ifndef DAC_HEADER
# define DAC_HEADER

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_rcc.h"

/*CHOOSE YOUR DAC WISELY, YOUNG GRASSHOPPER*/
#define DAC_12_BIT	//change to DAC_16_BIT for 16 bit DAC

#ifdef DAC_12_BIT
#define DC_COMP 2047	//(2^12/2)-1
#define DAC_BITS 12
#define DAC_MAX_LEVEL 4095
#endif

#ifdef DAC_16_BIT
#define DC_COMP 32767	//(2^16)-1
#define DAC_BITS 16
#define DAC_MAX_LEVEL 65535
#endif

// structure used for GPIO setting
GPIO_InitTypeDef GPIO_InitStructure;

//structure used for DAC settings
DAC_InitTypeDef dacSettings;

void dacInit(void);
void dacPut(uint16_t data);

# endif /*DAC_HEADER*/
